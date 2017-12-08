function matlab_example_simple_color()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletRGBLEDButton;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'XYZ'; % Change XYZ to the UID of your RGB LED Button Bricklet

    ipcon = IPConnection(); % Create IP connection
    rlb = handle(BrickletRGBLEDButton(UID, ipcon), 'CallbackProperties'); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Set light blue color
    rlb.setColor(0, 170, 234);

    input('Press key to exit\n', 's');
    ipcon.disconnect();
end
