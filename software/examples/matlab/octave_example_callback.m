function octave_example_callback()
    more off;

    % FIXME: This example is incomplete

    HOST = "localhost";
    PORT = 4223;
    UID = "XYZ"; % Change XYZ to the UID of your RGB LED Button Bricklet

    ipcon = javaObject("com.tinkerforge.IPConnection"); % Create IP connection
    rlb = javaObject("com.tinkerforge.BrickletRGBLEDButton", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Register button state changed callback to function cb_button_state_changed
    rlb.addButtonStateChangedCallback(@cb_button_state_changed);

    input("Press key to exit\n", "s");
    ipcon.disconnect();
end

% Callback function for button state changed callback
function cb_button_state_changed(e)
    fprintf("State: %d\n", e.state);
end
