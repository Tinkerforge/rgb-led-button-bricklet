function matlab_example_simple_button()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletRGBLEDButton;

    % FIXME: This example is incomplete

    HOST = 'localhost';
    PORT = 4223;
    UID = 'XYZ'; % Change XYZ to the UID of your RGB LED Button Bricklet

    ipcon = IPConnection(); % Create IP connection
    rlb = handle(BrickletRGBLEDButton(UID, ipcon), 'CallbackProperties'); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Get current button state
    state = rlb.getButtonState();
    fprintf('State: %i\n', state);

    input('Press key to exit\n', 's');
    ipcon.disconnect();
end
