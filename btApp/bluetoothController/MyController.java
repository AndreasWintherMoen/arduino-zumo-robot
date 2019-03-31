package bluetoothController;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.ListView;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import plab.serial.PLabSerial;

public class MyController {
	
	@FXML private TextField sendTextField;
	@FXML private TextArea textReceivedArea;
	@FXML private ListView<String> myListView;
	
	private PLabSerial serialConnection = new PLabSerial();;
	
	public void initialize() {
		listSerialPorts();
		serialConnection.addListener(this, "messageReceived");
	}
	
	@FXML void function0() {
		serialConnection.sendMessage("0");
	}
	
	@FXML void function1() {
		serialConnection.sendMessage("1");
	}
	
	@FXML void function2() {
		serialConnection.sendMessage("2");
	}
	
	@FXML void function3() {
		serialConnection.sendMessage("3");
	}
	
	@FXML void function4() {
		serialConnection.sendMessage("4");
	}
	
	@FXML void function5() {
		serialConnection.sendMessage("5");
	}
	
	@FXML void function6() {
		serialConnection.sendMessage("6");
	}
	
	public void messageReceived(String message, int value) {
		textReceivedArea.appendText("Message: "+ message + " , Value: "+ value + "\r\n");
	}
	
	@FXML void listSerialPorts() {
	    String[] portNames = serialConnection.getPortNames();
		ObservableList<String> items =FXCollections.observableArrayList (portNames);
		myListView.setItems(items);	
	}
	
	@FXML void openSelectedPort() {
		int index = myListView.getSelectionModel().getSelectedIndex(); 
		if (index > -1) {
		  String portName = myListView.getSelectionModel().getSelectedItem();
		  serialConnection.openPort(portName);		
		}
	} 
	
	@FXML void closePort() {
		serialConnection.closePort();
	}
	
	@FXML void sendText() {	
	    String s = sendTextField.getText() + "\r\n";
	    serialConnection.sendMessage(s);
	}
}
