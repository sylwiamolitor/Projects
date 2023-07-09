module pl.polsl.imagegallery {
    requires javafx.controls;
    requires javafx.fxml;
    requires com.sothawo.mapjfx;
    requires metadata.extractor;
    requires org.apache.commons.imaging;


    opens pl.polsl.imagegallery to javafx.fxml;
    exports pl.polsl.imagegallery;
    exports pl.polsl.imagegallery.exceptions;
    opens pl.polsl.imagegallery.exceptions to javafx.fxml;

    opens pl.polsl.imagegallery.model to javafx.fxml;
    exports pl.polsl.imagegallery.model;
    exports pl.polsl.imagegallery.model.conditions;
    opens pl.polsl.imagegallery.model.conditions to javafx.fxml;
}
