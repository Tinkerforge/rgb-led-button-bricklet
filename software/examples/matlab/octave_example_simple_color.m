function octave_example_simple_color()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "XYZ"; % Change XYZ to the UID of your RGB LED Button Bricklet

    ipcon = javaObject("com.tinkerforge.IPConnection"); % Create IP connection
    rlb = javaObject("com.tinkerforge.BrickletRGBLEDButton", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Set light blue color
    rlb.setColor(0, 170, 234);

    input("Press key to exit\n", "s");
    ipcon.disconnect();
end
