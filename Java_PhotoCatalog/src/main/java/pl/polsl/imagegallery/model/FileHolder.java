package pl.polsl.imagegallery.model;

import com.drew.imaging.jpeg.JpegMetadataReader;
import com.drew.imaging.jpeg.JpegProcessingException;
import com.drew.metadata.Directory;
import com.drew.metadata.Metadata;
import com.drew.metadata.exif.ExifDirectoryBase;
import com.drew.metadata.exif.ExifSubIFDDescriptor;
import com.drew.metadata.exif.ExifSubIFDDirectory;
import com.drew.metadata.exif.GpsDirectory;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.collections.transformation.FilteredList;
import org.apache.commons.imaging.ImageReadException;
import org.apache.commons.imaging.ImageWriteException;
import org.apache.commons.imaging.Imaging;
import org.apache.commons.imaging.common.ImageMetadata;
import org.apache.commons.imaging.common.RationalNumber;
import org.apache.commons.imaging.formats.jpeg.JpegImageMetadata;
import org.apache.commons.imaging.formats.jpeg.exif.ExifRewriter;
import org.apache.commons.imaging.formats.tiff.TiffImageMetadata;
import org.apache.commons.imaging.formats.tiff.constants.ExifTagConstants;
import org.apache.commons.imaging.formats.tiff.fieldtypes.FieldType;
import org.apache.commons.imaging.formats.tiff.taginfos.TagInfo;
import org.apache.commons.imaging.formats.tiff.write.TiffOutputDirectory;
import org.apache.commons.imaging.formats.tiff.write.TiffOutputField;
import org.apache.commons.imaging.formats.tiff.write.TiffOutputSet;
import pl.polsl.imagegallery.exceptions.InvalidExtensionException;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.stream.Collectors;

public class FileHolder {

    private final ObservableList<File> files;

    private static FileHolder fileHolder;

    private FileHolder() {
        this.files = FXCollections.observableArrayList();
    }

    public static FileHolder getFileHolder() {
        if (fileHolder == null) {
            fileHolder = new FileHolder();
        }
        return fileHolder;
    }

    public void addFile(final File newFile) throws InvalidExtensionException {
        if (checkIfJPEG(newFile)) {
            this.files.add(newFile);
        } else {
            throw new InvalidExtensionException();
        }
    }

    public void removeFileAtIndex(int index) {
        this.files.remove(index);
    }

    public ObservableList<File> getFiles() {
        return files;
    }

    public FilteredList<FileDetails> getDetailsOfFiles() {
        List<FileDetails> list = files.stream().map(this::getDetailsOfFile).collect(Collectors.toList());
        return new FilteredList<>(FXCollections.observableArrayList(list), x -> true);
    }

    public FileDetails getDetailsOfFile(File file) {
        Directory basicDetails = getEXIFParameters(file, ExifDirectoryBase.class);
        Directory subIFDDetails = getEXIFParameters(file, ExifSubIFDDirectory.class);
        Directory gpsDetails = getEXIFParameters(file, GpsDirectory.class);

        String name = file.getName();
        String make = "";
        String model = "";
        String aperture = "";
        String focalLength = "";
        String exposureTime = "";
        String flash = "";
        String dateOriginal = "";
        String lightSource = "";
        String iso = "";
        String latitude = "";
        String longitude = "";

        if (basicDetails != null) {
            make = basicDetails.getString(ExifDirectoryBase.TAG_MAKE);
            model = basicDetails.getString(ExifDirectoryBase.TAG_MODEL);
        }

        if (subIFDDetails != null) {
            ExifSubIFDDescriptor descriptor = new ExifSubIFDDescriptor((ExifSubIFDDirectory) subIFDDetails);
            aperture = descriptor.getFNumberDescription();
            focalLength = descriptor.getFocalLengthDescription();
            exposureTime = descriptor.getExposureTimeDescription();
            flash = descriptor.getFlashDescription();
            dateOriginal = subIFDDetails.getString(ExifDirectoryBase.TAG_DATETIME_ORIGINAL);
            lightSource = descriptor.getWhiteBalanceDescription();
            iso = descriptor.getIsoEquivalentDescription();
        }

        if (gpsDetails != null) {
            if (((GpsDirectory) gpsDetails).getGeoLocation() != null) {
                latitude = String.valueOf(((GpsDirectory) gpsDetails).getGeoLocation().getLatitude());
                longitude = String.valueOf(((GpsDirectory) gpsDetails).getGeoLocation().getLongitude());
            }
        }

        return new FileDetails(name, make, model,
                aperture, focalLength, exposureTime, flash, dateOriginal, lightSource, iso,
                latitude, longitude, file.getAbsolutePath());
    }

    public <T extends Directory> Directory getEXIFParameters(File jpegFile, Class<T> type) {
        try {
            Metadata metadata = JpegMetadataReader.readMetadata(jpegFile);
            return metadata.getFirstDirectoryOfType(type);
        } catch (JpegProcessingException | IOException e) {
            e.printStackTrace();
        }
        return new ExifSubIFDDirectory();
    }

    public void changeExifSimple(final File file, String parameter, String value)
            throws IOException, ImageReadException, ImageWriteException {
        Path srcPath = Paths.get(file.getAbsolutePath());
        Path dstPath = Paths.get(file.getAbsolutePath() + "temp");
        Files.copy(srcPath, dstPath, StandardCopyOption.COPY_ATTRIBUTES);
        updateExif(file, dstPath.toFile(), parameter, value);
        Files.delete(srcPath);
        Files.move(dstPath, srcPath);
    }

    public void changeExifGPSFile(final File file, final double longitude, final double latitude)
            throws IOException, ImageReadException, ImageWriteException {
        Path srcPath = Paths.get(file.getAbsolutePath());
        Path dstPath = Paths.get(file.getAbsolutePath() + "temp");
        Files.copy(srcPath, dstPath, StandardCopyOption.COPY_ATTRIBUTES);
        setExifGPSTag(file, dstPath.toFile(), longitude, latitude);
        Files.delete(srcPath);
        Files.move(dstPath, srcPath);
    }

    public void setExifGPSTag(final File file, final File dst, final double longitude, final double latitude)
            throws IOException, ImageReadException, ImageWriteException {
        OutputStream os;
        TiffOutputSet outputSet = null;
        final ImageMetadata metadata = Imaging.getMetadata(file);
        final JpegImageMetadata jpegMetadata = (JpegImageMetadata) metadata;
        if (null != jpegMetadata) {
            final TiffImageMetadata exif = jpegMetadata.getExif();

            if (null != exif) {
                outputSet = exif.getOutputSet();
            }
        }

        if (null == outputSet) {
            outputSet = new TiffOutputSet();
        }
        outputSet.removeField(ExifTagConstants.EXIF_TAG_LIGHT_SOURCE);
        outputSet.setGPSInDegrees(longitude, latitude);

        os = new FileOutputStream(dst);
        OutputStream os2 = new BufferedOutputStream(os);
        new ExifRewriter().updateExifMetadataLossless(file, os2, outputSet);

    }


    public void updateExif(final File file, final File dst, String parameter, String value)
            throws IOException, ImageReadException, ImageWriteException {
        OutputStream os;
        TiffOutputSet outputSet = null;

        final ImageMetadata metadata = Imaging.getMetadata(file);
        final JpegImageMetadata jpegMetadata = (JpegImageMetadata) metadata;
        if (null != jpegMetadata) {
            final TiffImageMetadata exif = jpegMetadata.getExif();

            if (null != exif) {
                outputSet = exif.getOutputSet();
            }
        }


        if (null == outputSet) {
            outputSet = new TiffOutputSet();
        }
        final TiffOutputDirectory exifDirectory = outputSet.getOrCreateExifDirectory();

        if (parameter.equals("ISO")) {
            exifDirectory.removeField(ExifTagConstants.EXIF_TAG_ISO);
            exifDirectory.add(ExifTagConstants.EXIF_TAG_ISO, Short.parseShort(value));
        }
        if (parameter.equals("Focal Length")) {
            exifDirectory.removeField(ExifTagConstants.EXIF_TAG_FOCAL_LENGTH);
            exifDirectory.add(ExifTagConstants.EXIF_TAG_FOCAL_LENGTH, RationalNumber.valueOf(Double.parseDouble(value)));
        }
        if (parameter.equals("Exposure Time")) {
            exifDirectory.removeField(ExifTagConstants.EXIF_TAG_EXPOSURE_TIME);
            exifDirectory.add(ExifTagConstants.EXIF_TAG_EXPOSURE_TIME, RationalNumber.valueOf(Integer.parseInt(value)));
        }
        if (parameter.equals("Aperture")) {
            exifDirectory.removeField(ExifTagConstants.EXIF_TAG_FNUMBER);
            exifDirectory.add(ExifTagConstants.EXIF_TAG_FNUMBER, RationalNumber.valueOf(Integer.parseInt(value)));
        }
        if (parameter.equals("Light Source")) {
            exifDirectory.removeField(ExifTagConstants.EXIF_TAG_LIGHT_SOURCE);
            exifDirectory.add(ExifTagConstants.EXIF_TAG_LIGHT_SOURCE, Short.parseShort(value));
        }
        if (parameter.equals("Date and Time (Original)")) {
            TiffOutputField dateTimeFieldOriginal = exifDirectory.findField(0x9003);
            FieldType originalFieldType = null;
            TagInfo originalTagInfo = null;
            if (dateTimeFieldOriginal != null) {
                originalFieldType = dateTimeFieldOriginal.fieldType;
                originalTagInfo = dateTimeFieldOriginal.tagInfo;
            }
            exifDirectory.removeField(ExifDirectoryBase.TAG_DATETIME_ORIGINAL);
            final TiffOutputField dateTimeOutputField = new TiffOutputField(originalTagInfo, originalFieldType, value.length(), value.getBytes());
            exifDirectory.add(dateTimeOutputField);
        }

        os = new FileOutputStream(dst);
        os = new BufferedOutputStream(os);

        new ExifRewriter().updateExifMetadataLossless(file, os, outputSet);

    }

    private boolean checkIfJPEG(File file) {
        Pattern pattern = Pattern.compile(".+\\.jpeg|.+\\.jpg", Pattern.CASE_INSENSITIVE);
        Matcher matcher = pattern.matcher(file.getName());
        return matcher.matches();
    }
}
