package pl.polsl.imagegallery.model.conditions;

import java.time.LocalDateTime;

public enum DateConditions implements Condition<LocalDateTime> {
    BEFORE("before") {
        @Override
        public boolean apply(LocalDateTime attr, LocalDateTime value) {
            return attr.isBefore(value);
        }
    },
    AT("at") {
        @Override
        public boolean apply(LocalDateTime attr, LocalDateTime value) {
            return attr.isEqual(value);
        }
    },
    AFTER("after") {
        @Override
        public boolean apply(LocalDateTime attr, LocalDateTime value) {
            return attr.isAfter(value);
        }
    };

    private final String name;

    DateConditions(String name) {
        this.name = name;
    }

    @Override
    public String toString() {
        return name;
    }

    @Override
    public LocalDateTime convert(String value) {
        if (value == null || value.isBlank()) {
            return null;
        }
        return LocalDateTime.parse(value);
    }
}
