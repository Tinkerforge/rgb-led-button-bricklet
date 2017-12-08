<?php

// FIXME: This example is incomplete

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletRGBLEDButton.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletRGBLEDButton;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XYZ'; // Change XYZ to the UID of your RGB LED Button Bricklet

// Callback function for button state changed callback
function cb_buttonStateChanged($state)
{
    echo "State: $state\n";
}

$ipcon = new IPConnection(); // Create IP connection
$rlb = new BrickletRGBLEDButton(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Register button state changed callback to function cb_buttonStateChanged
$rlb->registerCallback(BrickletRGBLEDButton::CALLBACK_BUTTON_STATE_CHANGED,
                       'cb_buttonStateChanged');

echo "Press ctrl+c to exit\n";
$ipcon->dispatchCallbacks(-1); // Dispatch callbacks forever

?>
