package pl.polsl.imagegallery.model;

public class FileDetails {
    private final String name;
    private final String make;
    private final String model;
    private final String aperture;
    private final String focalLength;
    private final String exposureTime;
    private final String flash;
    private final String dateOriginal;
    private final String lightSource;
    private final String ISO;
    private final String latitude;
    private final String longitude;
    private final String absolutePath;

    public FileDetails(
            String name, String make, String model,
            String aperture, String focalLength, String exposureTime, String flash, String dateOriginal, String lightSource, String iso,
            String latitude, String longitude, String absolutePath) {
        this.name = name;
        this.make = make;
        this.model = model;
        this.aperture = aperture;
        this.focalLength = focalLength;
        this.exposureTime = exposureTime;
        this.flash = flash;
        this.dateOriginal = dateOriginal;
        this.lightSource = lightSource;
        this.ISO = iso;
        this.latitude = latitude;
        this.longitude = longitude;
        this.absolutePath = absolutePath;
    }

    public String getName() {
        return name;
    }

    public String getMake() {
        return make;
    }

    public String getModel() {
        return model;
    }

    public String getAperture() {
        return aperture;
    }

    public String getFocalLength() {
        return focalLength;
    }

    public String getExposureTime() {
        return exposureTime;
    }

    public String getFlash() {
        return flash;
    }

    public String getDateOriginal() {
        return dateOriginal;
    }

    public String getLightSource() {
        return lightSource;
    }

    public String getISO() {
        return ISO;
    }

    public String getLatitude() {
        return latitude;
    }

    public String getLongitude() {
        return longitude;
    }

    public String getAbsolutePath() {
        return absolutePath;
    }
}
