package pl.polsl.imagegallery.model.conditions;

public enum StringConditions implements Condition<String> {
    LESS_THAN("less than") {
        @Override
        public boolean apply(String attr, String value) {
            return attr.compareTo(value) < 0;
        }
    },
    EQUALS("equals") {
        @Override
        public boolean apply(String attr, String value) {
            return attr.compareTo(value) == 0;
        }
    },
    GREATER_THAN("greater than") {
        @Override
        public boolean apply(String attr, String value) {
            return attr.compareTo(value) > 0;
        }
    };

    private final String name;

    StringConditions(String name) {
        this.name = name;
    }

    @Override
    public String toString() {
        return name;
    }

    @Override
    public String convert(String value) {
        if (value == null || value.isBlank()) {
            return null;
        }
        return value;
    }
}
