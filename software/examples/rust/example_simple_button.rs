use std::{io, error::Error};

use tinkerforge::{ip_connection::IpConnection, 
                  rgb_led_button_bricklet::*};


const HOST: &str = "localhost";
const PORT: u16 = 4223;
const UID: &str = "XYZ"; // Change XYZ to the UID of your RGB LED Button Bricklet.

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection.
    let rlb = RgbLedButtonBricklet::new(UID, &ipcon); // Create device object.

    ipcon.connect((HOST, PORT)).recv()??; // Connect to brickd.
    // Don't use device before ipcon is connected.

		// Get current button state.
let state = rlb.get_button_state().recv()?;

		if state == RGB_LED_BUTTON_BRICKLET_BUTTON_STATE_PRESSED {
			println!("State: Pressed");
		}
		else if state == RGB_LED_BUTTON_BRICKLET_BUTTON_STATE_RELEASED {
			println!("State: Released");
		}

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    ipcon.disconnect();
    Ok(())
}
