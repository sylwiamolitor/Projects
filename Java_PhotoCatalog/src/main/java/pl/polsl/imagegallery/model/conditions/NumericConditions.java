package pl.polsl.imagegallery.model.conditions;

import java.util.Objects;

public enum NumericConditions implements Condition<Double> {
    LESS_THAN("less than") {
        @Override
        public boolean apply(Double attr, Double value) {
            return attr < value;
        }
    },
    EQUALS("equals") {
        @Override
        public boolean apply(Double attr, Double value) {
            return Objects.equals(attr, value);
        }
    },
    GREATER_THAN("greater than") {
        @Override
        public boolean apply(Double attr, Double value) {
            return attr > value;
        }
    };

    private final String name;

    NumericConditions(String name) {
        this.name = name;
    }

    @Override
    public String toString() {
        return name;
    }

    @Override
    public Double convert(String value) {
        if (value == null || value.isBlank()) {
            return null;
        }
        return Double.parseDouble(value.replaceAll("[^\\d.,]", "").replace(',', '.'));
    }
}
