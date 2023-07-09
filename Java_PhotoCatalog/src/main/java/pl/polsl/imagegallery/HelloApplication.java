package pl.polsl.imagegallery;

import com.sothawo.mapjfx.Coordinate;
import com.sothawo.mapjfx.MapType;
import com.sothawo.mapjfx.Marker;
import com.sothawo.mapjfx.event.MapViewEvent;
import javafx.application.Application;
import javafx.collections.FXCollections;
import javafx.collections.transformation.FilteredList;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.TableColumn;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.image.Image;
import javafx.stage.FileChooser;
import javafx.stage.Stage;
import org.apache.commons.imaging.ImageReadException;
import org.apache.commons.imaging.ImageWriteException;
import pl.polsl.imagegallery.exceptions.InvalidExtensionException;
import pl.polsl.imagegallery.model.*;
import pl.polsl.imagegallery.model.conditions.Condition;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.time.format.DateTimeParseException;
import java.util.Arrays;
import java.util.List;
import java.util.function.Predicate;
import java.util.stream.Stream;

public class HelloApplication extends Application {

    private String chosenFile;
    private Marker marker;
    protected static HelloController CONTROLLER;

    @Override
    public void start(Stage stage) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("hello-view.fxml"));
        Parent parent = fxmlLoader.load();
        CONTROLLER = fxmlLoader.getController();
        CONTROLLER.fileTableView.setEditable(true);

        CONTROLLER.mapView.setMapType(MapType.OSM);
        CONTROLLER.mapView.initializedProperty().addListener(((observable, oldValue, newValue) -> {
            if (newValue) {
                CONTROLLER.mapView.setCenter(new Coordinate(50.288345629856565, 18.676749178215022));
                CONTROLLER.mapView.setZoom(18);
            }
        }));
        CONTROLLER.mapView.initialize();

        var exifAttributeColumns = Arrays.stream(ExifAttribute.values())
                .map(attribute -> {
                    var tableColumn = new TableColumn<FileDetails, String>(attribute.getName());
                    tableColumn.setCellValueFactory(new PropertyValueFactory<>(attribute.getCode()));
                    return tableColumn;
                }).toList();

        CONTROLLER.fileTableView.getColumns().addAll(exifAttributeColumns);

        marker = Marker.createProvided(Marker.Provided.BLUE).setPosition(new Coordinate(50.288506, 18.677515)).setVisible(
                true);

        CONTROLLER.mapView.addMarker(marker);


        chooseFileFromTable();

        FileChooser fileChooser = new FileChooser();
        addNewFile(stage, fileChooser);

        var exifAttributes = FXCollections.observableArrayList(ExifAttribute.values());
        CONTROLLER.filterAttribute.setItems(exifAttributes);
        CONTROLLER.filterAttribute.setConverter(new ExifAttribute.ExifAttributeStringConverter());

        CONTROLLER.filterAttribute.valueProperty().addListener(exifAttribute -> {
            var filterAttribute = CONTROLLER.filterAttribute.getSelectionModel().getSelectedItem();
            if (filterAttribute != null) {
                CONTROLLER.filterCondition.setItems(filterAttribute.getConditions());
            }
        });

        CONTROLLER.filterTableView.getColumns().addAll(
                Stream.of("Attribute", "Condition", "Value")
                        .map(attribute -> {
                            var tableColumn = new TableColumn<FileFilter, String>(attribute.toLowerCase());
                            tableColumn.setCellValueFactory(new PropertyValueFactory<>(attribute));
                            return tableColumn;
                        })
                        .toList()
        );

        CONTROLLER.addFilterButton.setOnAction(e -> {
            var exifAttribute = CONTROLLER.filterAttribute.getSelectionModel().getSelectedItem();
            var condition = CONTROLLER.filterCondition.getSelectionModel().getSelectedItem();
            var value = CONTROLLER.filterValueTextField.getCharacters().toString();

            if (exifAttribute != null && condition != null && !value.isBlank()) {
                createNewFileFilter(exifAttribute, condition, value);
            }
        });

        CONTROLLER.changeAttribute.setOnAction(e -> {
            String value = CONTROLLER.filterValueTextField.getCharacters().toString();
            ExifAttribute exifAttribute = CONTROLLER.filterAttribute.getSelectionModel().getSelectedItem();
            try {
                FileHolder.getFileHolder().changeExifSimple(FileHolder.getFileHolder().getFiles().stream()
                        .filter(item -> item.getName().equals(this.chosenFile))
                        .findFirst().get(), exifAttribute.toString(), value);

            } catch (IOException | ImageReadException | ImageWriteException ex) {
                ex.printStackTrace();
            }
            CONTROLLER.fileTableView.setItems(FileHolder.getFileHolder().getDetailsOfFiles());
        });
        checkIfMapClicked();

        Scene scene = new Scene(parent, 1280, 800);
        stage.setTitle("Photo album");
        stage.setScene(scene);
        stage.show();
    }

    private void createNewFileFilter(ExifAttribute exifAttribute, Condition<?> condition, String value) {
        try {
            FileFilter newFilter = new FileFilter(exifAttribute, condition, value);
            FileFilterHolder.getFilterHolder().addFilter(newFilter);

            List<FileFilter> filters = FileFilterHolder.getFilterHolder().getFilters();
            CONTROLLER.filterTableView.setItems(FXCollections.observableArrayList(filters));
            updateFilterPredicate(CONTROLLER, filters);
        } catch (NumberFormatException | DateTimeParseException ignored) {
        }
    }

    private void chooseFileFromTable() {

        CONTROLLER.fileTableView.setOnMouseClicked(e -> {
            try {
                FileDetails imageFile = CONTROLLER.fileTableView.getSelectionModel().getSelectedItem();

                if (imageFile == null)
                    return;
                String chosenFile = imageFile.getName();
                String absolutePath = imageFile.getAbsolutePath();
                refreshSelected(chosenFile, absolutePath);
            } catch (IOException ex) {
                ex.printStackTrace();
            }
        });
    }

    private void refreshSelected(String chosenFile, String absolutePath) throws IOException {
        this.chosenFile = chosenFile;
        FileDetails fileDetails = FileHolder.getFileHolder().getDetailsOfFile(FileHolder.getFileHolder().getFiles().stream()
                .filter(item -> item.getName().equals(chosenFile))
                .findFirst().get());
        CONTROLLER.mapView.removeMarker(marker);
        if (!fileDetails.getLatitude().isEmpty() && !fileDetails.getLongitude().isEmpty()) {
            this.marker.setVisible(true);
            this.marker.setPosition(new Coordinate(Double.parseDouble(fileDetails.getLatitude()), Double.parseDouble(fileDetails.getLongitude())));
            CONTROLLER.mapView.addMarker(marker);
        }
        FileInputStream fileInputStream = new FileInputStream(absolutePath);
        Image image = new Image(fileInputStream);
        fileInputStream.close();
        CONTROLLER.photoView.setImage(image);
    }

    private void addNewFile(Stage stage, FileChooser fileChooser) {
        CONTROLLER.browseFilesButton.setOnAction(e -> {
            File selectedFile = fileChooser.showOpenDialog(stage);
            try {
                FileHolder.getFileHolder().addFile(selectedFile);
            } catch (InvalidExtensionException invalidExtensionException) {
                invalidExtensionException.printStackTrace();
            }

            List<FileFilter> filters = FileFilterHolder.getFilterHolder().getFilters();
            CONTROLLER.fileTableView.setItems(FileHolder.getFileHolder().getDetailsOfFiles());
            updateFilterPredicate(CONTROLLER, filters);
        });
    }

    private void checkIfMapClicked() {
        CONTROLLER.mapView.addEventHandler(MapViewEvent.MAP_CLICKED, event -> {
            event.consume();
            final Coordinate newPosition = event.getCoordinate();
            if (marker.getVisible()) {
                marker.setPosition(newPosition);
                try {
                    FileHolder.getFileHolder().changeExifGPSFile(FileHolder.getFileHolder().getFiles().stream()
                            .filter(item -> item.getName().equals(this.chosenFile))
                            .findFirst().get(), newPosition.getLongitude(), newPosition.getLatitude());
                } catch (IOException | ImageReadException | ImageWriteException e) {
                    e.printStackTrace();
                }
                CONTROLLER.mapView.addMarker(marker);
            }
        });
    }

    static public void updateFileTable() {
        CONTROLLER.fileTableView.setItems(FileHolder.getFileHolder().getDetailsOfFiles());
    }

    static public void updateFilterTable() {
        List<FileFilter> filters = FileFilterHolder.getFilterHolder().getFilters();
        CONTROLLER.filterTableView.setItems(FXCollections.observableArrayList(filters));
        updateFilterPredicate(CONTROLLER, filters);
    }

    private static void updateFilterPredicate(HelloController controller, List<FileFilter> filters) {
        var fileDetails = (FilteredList<FileDetails>) controller.fileTableView.getItems();
        var predicate = filters.stream().<Predicate<FileDetails>>map(filter -> {
            var attrib = filter.getAttribute();
            var cond = filter.getCondition();
            var val = filter.getValue();
            return (FileDetails details) -> cond.test(attrib.getFromFileDetails(details), val);
        }).reduce(Predicate::and).orElse(x -> true);
        fileDetails.setPredicate(predicate);
    }

    public static void main(String[] args) {
        launch();
    }
}
