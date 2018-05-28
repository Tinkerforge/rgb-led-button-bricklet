using System;
using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change XYZ to the UID of your RGB LED Button Bricklet

	// Callback function for button state changed callback
	static void ButtonStateChangedCB(BrickletRGBLEDButton sender, byte state)
	{
		if(state == BrickletRGBLEDButton.BUTTON_STATE_PRESSED)
		{
			Console.WriteLine("State: Pressed");
		}
		else if(state == BrickletRGBLEDButton.BUTTON_STATE_RELEASED)
		{
			Console.WriteLine("State: Released");
		}
	}

	static void Main()
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletRGBLEDButton rlb = new BrickletRGBLEDButton(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Register button state changed callback to function ButtonStateChangedCB
		rlb.ButtonStateChangedCallback += ButtonStateChangedCB;

		Console.WriteLine("Press enter to exit");
		Console.ReadLine();
		ipcon.Disconnect();
	}
}
