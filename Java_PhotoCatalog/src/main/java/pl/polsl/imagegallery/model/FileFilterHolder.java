package pl.polsl.imagegallery.model;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;

public class FileFilterHolder {

    private final ObservableList<FileFilter> filters;

    private static FileFilterHolder fileHolder;

    private FileFilterHolder() {
        this.filters = FXCollections.observableArrayList();
    }

    public static FileFilterHolder getFilterHolder() {
        if (fileHolder == null) {
            fileHolder = new FileFilterHolder();
        }
        return fileHolder;
    }

    public void addFilter(final FileFilter newFilter) {
        this.filters.add(newFilter);
    }

    public void removeFilterAtIndex(int index) {
        this.filters.remove(index);
    }

    public ObservableList<FileFilter> getFilters() {
        return filters;
    }
}
