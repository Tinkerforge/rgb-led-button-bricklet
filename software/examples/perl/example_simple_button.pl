#!/usr/bin/perl

use strict;
use Tinkerforge::IPConnection;
use Tinkerforge::BrickletRGBLEDButton;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XYZ'; # Change XYZ to the UID of your RGB LED Button Bricklet

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $rlb = Tinkerforge::BrickletRGBLEDButton->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Get current button state
my $state = $rlb->get_button_state();

if ($state == $rlb->BUTTON_STATE_PRESSED)
{
    print "State: Pressed\n";
}
elsif ($state == $rlb->BUTTON_STATE_RELEASED)
{
    print "State: Released\n";
}

print "Press key to exit\n";
<STDIN>;
$ipcon->disconnect();
