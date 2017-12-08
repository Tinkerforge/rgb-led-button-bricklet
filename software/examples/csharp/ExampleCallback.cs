using System;
using Tinkerforge;

// FIXME: This example is incomplete

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change XYZ to the UID of your RGB LED Button Bricklet

	// Callback function for button state changed callback
	static void ButtonStateChangedCB(BrickletRGBLEDButton sender, byte state)
	{
		Console.WriteLine("State: " + state);
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
