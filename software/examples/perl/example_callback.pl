#!/usr/bin/perl

# FIXME: This example is incomplete

use strict;
use Tinkerforge::IPConnection;
use Tinkerforge::BrickletRGBLEDButton;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XYZ'; # Change XYZ to the UID of your RGB LED Button Bricklet

# Callback subroutine for button state changed callback
sub cb_button_state_changed
{
    my ($state) = @_;

    print "State: $state\n";
}

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $rlb = Tinkerforge::BrickletRGBLEDButton->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Register button state changed callback to subroutine cb_button_state_changed
$rlb->register_callback($rlb->CALLBACK_BUTTON_STATE_CHANGED, 'cb_button_state_changed');

print "Press key to exit\n";
<STDIN>;
$ipcon->disconnect();
