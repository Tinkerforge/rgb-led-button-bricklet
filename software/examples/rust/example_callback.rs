use std::{error::Error, io, thread};
use tinkerforge::{ipconnection::IpConnection, rgb_led_button_bricklet::*};

const HOST: &str = "127.0.0.1";
const PORT: u16 = 4223;
const UID: &str = "XYZ"; // Change XYZ to the UID of your RGB LED Button Bricklet

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection
    let rgb_led_button_bricklet = RGBLEDButtonBricklet::new(UID, &ipcon); // Create device object

    ipcon.connect(HOST, PORT).recv()??; // Connect to brickd
                                        // Don't use device before ipcon is connected

    //Create listener for button state changed events.
    let button_state_changed_listener = rgb_led_button_bricklet.get_button_state_changed_receiver();
    // Spawn thread to handle received events. This thread ends when the rgb_led_button_bricklet
    // is dropped, so there is no need for manual cleanup.
    thread::spawn(move || {
        for event in button_state_changed_listener {
            if event == RGB_LED_BUTTON_BRICKLET_BUTTON_STATE_PRESSED {
                println!("State: Pressed");
            } else if event == RGB_LED_BUTTON_BRICKLET_BUTTON_STATE_RELEASED {
                println!("State: Released");
            }
        }
    });

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    ipcon.disconnect();
    Ok(())
}
