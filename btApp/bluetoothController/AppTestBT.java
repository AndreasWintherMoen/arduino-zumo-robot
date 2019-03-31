package bluetoothController;
 
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

 
public class AppTestBT extends Application {
	@Override
    public void start(final Stage primaryStage) throws Exception {
    	primaryStage.setTitle("Bluetooth Controller");
    	primaryStage.setScene(new Scene(FXMLLoader.load(AppTestBT.class.getResource("MyFXML.fxml"))));
		primaryStage.show();
	}

	public static void main(final String[] args) {
		Application.launch(args);
	}
}