import com.tinkerforge.IPConnection;
import com.tinkerforge.BrickletRGBLEDButton;

public class ExampleSimpleColor {
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

		// Set light blue color
		rlb.setColor(0, 170, 234);

		System.out.println("Press key to exit"); System.in.read();
		ipcon.disconnect();
	}
}
