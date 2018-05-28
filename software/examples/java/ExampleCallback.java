import com.tinkerforge.IPConnection;
import com.tinkerforge.BrickletRGBLEDButton;

public class ExampleCallback {
	private static final String HOST = "localhost";
	private static final int PORT = 4223;

	// Change XYZ to the UID of your RGB LED Button Bricklet
	private static final String UID = "XYZ";

	// Note: To make the example code cleaner we do not handle exceptions. Exceptions
	//       you might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletRGBLEDButton rlb = new BrickletRGBLEDButton(UID, ipcon); // Create device object

		ipcon.connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Add button state changed listener
		rlb.addButtonStateChangedListener(new BrickletRGBLEDButton.ButtonStateChangedListener() {
			public void buttonStateChanged(int state) {
				if(state == BrickletRGBLEDButton.BUTTON_STATE_PRESSED) {
					System.out.println("State: Pressed");
				} else if(state == BrickletRGBLEDButton.BUTTON_STATE_RELEASED) {
					System.out.println("State: Released");
				}
			}
		});

		System.out.println("Press key to exit"); System.in.read();
		ipcon.disconnect();
	}
}
