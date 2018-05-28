<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletRGBLEDButton.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletRGBLEDButton;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XYZ'; // Change XYZ to the UID of your RGB LED Button Bricklet

$ipcon = new IPConnection(); // Create IP connection
$rlb = new BrickletRGBLEDButton(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Get current button state
$state = $rlb->getButtonState();

if ($state == BrickletRGBLEDButton::BUTTON_STATE_PRESSED) {
    echo "State: Pressed\n";
} elseif ($state == BrickletRGBLEDButton::BUTTON_STATE_RELEASED) {
    echo "State: Released\n";
}

echo "Press key to exit\n";
fgetc(fopen('php://stdin', 'r'));
$ipcon->disconnect();

?>
