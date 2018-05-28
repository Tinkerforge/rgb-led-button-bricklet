function matlab_example_callback()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletRGBLEDButton;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'XYZ'; % Change XYZ to the UID of your RGB LED Button Bricklet

    ipcon = IPConnection(); % Create IP connection
    rlb = handle(BrickletRGBLEDButton(UID, ipcon), 'CallbackProperties'); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Register button state changed callback to function cb_button_state_changed
    set(rlb, 'ButtonStateChangedCallback', @(h, e) cb_button_state_changed(e));

    input('Press key to exit\n', 's');
    ipcon.disconnect();
end

% Callback function for button state changed callback
function cb_button_state_changed(e)
    if e.state == com.tinkerforge.BrickletRGBLEDButton.BUTTON_STATE_PRESSED
        fprintf('State: Pressed\n');
    elseif e.state == com.tinkerforge.BrickletRGBLEDButton.BUTTON_STATE_RELEASED
        fprintf('State: Released\n');
    end
end
