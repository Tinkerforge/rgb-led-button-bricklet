function octave_example_simple_button()
    more off;

    % FIXME: This example is incomplete

    HOST = "localhost";
    PORT = 4223;
    UID = "XYZ"; % Change XYZ to the UID of your RGB LED Button Bricklet

    ipcon = javaObject("com.tinkerforge.IPConnection"); % Create IP connection
    rlb = javaObject("com.tinkerforge.BrickletRGBLEDButton", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Get current button state
    state = rlb.getButtonState();
    fprintf("State: %d\n", state);

    input("Press key to exit\n", "s");
    ipcon.disconnect();
end
