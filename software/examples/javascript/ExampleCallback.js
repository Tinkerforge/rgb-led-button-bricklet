var Tinkerforge = require('tinkerforge');

// FIXME: This example is incomplete

var HOST = 'localhost';
var PORT = 4223;
var UID = 'XYZ'; // Change XYZ to the UID of your RGB LED Button Bricklet

var ipcon = new Tinkerforge.IPConnection(); // Create IP connection
var rlb = new Tinkerforge.BrickletRGBLEDButton(UID, ipcon); // Create device object

ipcon.connect(HOST, PORT,
    function (error) {
        console.log('Error: ' + error);
    }
); // Connect to brickd
// Don't use device before ipcon is connected

// Register button state changed callback
rlb.on(Tinkerforge.BrickletRGBLEDButton.CALLBACK_BUTTON_STATE_CHANGED,
    // Callback function for button state changed callback
    function (state) {
        console.log('State: ' + state);
    }
);

console.log('Press key to exit');
process.stdin.on('data',
    function (data) {
        ipcon.disconnect();
        process.exit(0);
    }
);
