function matlab_example_simple_button()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletRGBLEDButton;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'XYZ'; % Change XYZ to the UID of your RGB LED Button Bricklet

    ipcon = IPConnection(); % Create IP connection
    rlb = handle(BrickletRGBLEDButton(UID, ipcon), 'CallbackProperties'); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Get current button state
    state = rlb.getButtonState();

    if state == BrickletRGBLEDButton.BUTTON_STATE_PRESSED
        fprintf('State: Pressed\n');
    elseif state == BrickletRGBLEDButton.BUTTON_STATE_RELEASED
        fprintf('State: Released\n');
    end

    input('Press key to exit\n', 's');
    ipcon.disconnect();
end
