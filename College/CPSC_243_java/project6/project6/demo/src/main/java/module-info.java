module fiveCard {
    requires javafx.controls;
    requires javafx.fxml;
    requires javafx.media;
    opens fiveCard to javafx.fxml;
    exports fiveCard;
}
