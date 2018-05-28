function octave_example_simple_button()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "XYZ"; % Change XYZ to the UID of your RGB LED Button Bricklet

    ipcon = javaObject("com.tinkerforge.IPConnection"); % Create IP connection
    rlb = javaObject("com.tinkerforge.BrickletRGBLEDButton", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Get current button state
    state = rlb.getButtonState();

    if state == 0
        fprintf("State: Pressed\n");
    elseif state == 1
        fprintf("State: Released\n");
    end

    input("Press key to exit\n", "s");
    ipcon.disconnect();
end
