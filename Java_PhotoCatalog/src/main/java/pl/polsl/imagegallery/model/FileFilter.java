package pl.polsl.imagegallery.model;

import pl.polsl.imagegallery.model.conditions.Condition;

public class FileFilter {

    private final ExifAttribute attribute;
    private final Condition<?> condition;
    private final String value;

    public FileFilter(ExifAttribute attribute, Condition<?> condition, String value) {
        this.attribute = attribute;
        this.condition = condition;
        this.value = value;
    }

    public ExifAttribute getAttribute() {
        return attribute;
    }

    public Condition<?> getCondition() {
        return condition;
    }

    public String getValue() {
        return value;
    }

    public boolean test(FileDetails fileDetails) {
        return condition.test(attribute.getFromFileDetails(fileDetails), value);
    }
}
