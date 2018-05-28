using System;
using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change XYZ to the UID of your RGB LED Button Bricklet

	static void Main()
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletRGBLEDButton rlb = new BrickletRGBLEDButton(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Get current button state
		byte state = rlb.GetButtonState();

		if(state == BrickletRGBLEDButton.BUTTON_STATE_PRESSED)
		{
			Console.WriteLine("State: Pressed");
		}
		else if(state == BrickletRGBLEDButton.BUTTON_STATE_RELEASED)
		{
			Console.WriteLine("State: Released");
		}

		Console.WriteLine("Press enter to exit");
		Console.ReadLine();
		ipcon.Disconnect();
	}
}
