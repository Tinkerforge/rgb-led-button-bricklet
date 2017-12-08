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

ipcon.on(Tinkerforge.IPConnection.CALLBACK_CONNECTED,
    function (connectReason) {
        // Get current button state
        rlb.getButtonState(
            function (state) {
                console.log('State: ' + state);
            },
            function (error) {
                console.log('Error: ' + error);
            }
        );
    }
);

console.log('Press key to exit');
process.stdin.on('data',
    function (data) {
        ipcon.disconnect();
        process.exit(0);
    }
);
