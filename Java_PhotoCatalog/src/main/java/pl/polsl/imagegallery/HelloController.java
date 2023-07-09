package pl.polsl.imagegallery;

import com.sothawo.mapjfx.MapView;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.scene.image.ImageView;
import javafx.stage.FileChooser;
import pl.polsl.imagegallery.model.*;
import pl.polsl.imagegallery.model.conditions.Condition;

import static pl.polsl.imagegallery.HelloApplication.*;

public class HelloController {

    public MapView mapView;

    @FXML
    public TableView<FileDetails> fileTableView;

    @FXML
    public TableView<FileFilter> filterTableView;

    @FXML
    public ComboBox<ExifAttribute> filterAttribute;

    @FXML
    public ComboBox<Condition<?>> filterCondition;

    @FXML
    public TextField filterValueTextField;

    @FXML
    public Button addFilterButton;

    @FXML
    public Button removeFilterButton;

    @FXML
    public Button browseFilesButton;

    @FXML
    public Button removeFilesButton;

    @FXML
    public Button changeAttribute;

    @FXML
    public ImageView photoView;


    @FXML
    private void BrowseFilesButtonClicked(ActionEvent actionEvent) {
        FileChooser fileChooser = new FileChooser();
    }

    @FXML
    private void DeleteFilesButtonClicked(ActionEvent actionEvent) {
        FileHolder.getFileHolder().removeFileAtIndex(CONTROLLER.fileTableView.getSelectionModel().getSelectedIndex());
        updateFileTable();
    }

    @FXML
    public void DeleteFiltersButtonClicked(ActionEvent actionEvent) {
        FileFilterHolder.getFilterHolder().removeFilterAtIndex(CONTROLLER.filterTableView.getSelectionModel().getSelectedIndex());
        updateFileTable();
        updateFilterTable();
    }
}
