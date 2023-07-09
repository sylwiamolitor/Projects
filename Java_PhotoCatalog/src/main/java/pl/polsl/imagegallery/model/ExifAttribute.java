package pl.polsl.imagegallery.model;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.util.StringConverter;
import pl.polsl.imagegallery.model.conditions.Condition;
import pl.polsl.imagegallery.model.conditions.DateConditions;
import pl.polsl.imagegallery.model.conditions.NumericConditions;
import pl.polsl.imagegallery.model.conditions.StringConditions;

import java.util.function.Function;

public enum ExifAttribute {

    NAME("name", "Name", StringConditions.values(), FileDetails::getName),
    MAKE("make", "Make", StringConditions.values(), FileDetails::getMake),
    MODEL("model", "Model", StringConditions.values(), FileDetails::getModel),
    APERTURE("aperture", "Aperture", NumericConditions.values(), FileDetails::getAperture),
    FOCAL_LENGTH("focalLength", "Focal Length", NumericConditions.values(), FileDetails::getFocalLength),
    EXPOSURE_TIME("exposureTime", "Exposure Time", NumericConditions.values(), FileDetails::getExposureTime),
    FLASH("flash", "Flash", StringConditions.values(), FileDetails::getFlash),
    DATE_ORIGINAL("dateOriginal", "Date and Time (Original)", DateConditions.values(), FileDetails::getDateOriginal),
    LIGHT_SOURCE("lightSource", "Light Source", StringConditions.values(), FileDetails::getLightSource),
    ISO("ISO", "ISO", NumericConditions.values(), FileDetails::getISO);

    public static class ExifAttributeStringConverter extends StringConverter<ExifAttribute> {
        @Override
        public String toString(ExifAttribute object) {
            return object.getName();
        }

        @Override
        public ExifAttribute fromString(String string) {
            return null;
        }
    }

    private final String code;
    private final String name;
    private final Condition<?>[] conditions;
    private final Function<FileDetails, String> fromFileDetails;

    ExifAttribute(String code, String name, Condition<?>[] conditions,
                  Function<FileDetails, String> fromFileDetails) {
        this.code = code;
        this.name = name;
        this.conditions = conditions;
        this.fromFileDetails = fromFileDetails;
    }

    public String getCode() {
        return code;
    }

    public String getName() {
        return name;
    }

    public String toString() {
        return name;
    }

    public ObservableList<Condition<?>> getConditions() {
        return FXCollections.observableArrayList(conditions);
    }

    public String getFromFileDetails(FileDetails fileDetails) {
        return fromFileDetails.apply(fileDetails);
    }
}
