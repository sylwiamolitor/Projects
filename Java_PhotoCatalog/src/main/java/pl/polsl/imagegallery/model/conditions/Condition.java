package pl.polsl.imagegallery.model.conditions;

public interface Condition<T> {

    default boolean test(String attr, String value) {
        T convertedAttr = convert(attr);

        if (convertedAttr == null) {
            return false;
        } else {
            return apply(convertedAttr, convert(value));
        }
    }

    boolean apply(T attr, T value);
    T convert(String value);
}
