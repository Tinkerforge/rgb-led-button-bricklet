#!/usr/bin/perl

use Tinkerforge::IPConnection;
use Tinkerforge::BrickletRGBLEDButton;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XYZ'; # Change XYZ to the UID of your RGB LED Button Bricklet

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $rlb = Tinkerforge::BrickletRGBLEDButton->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Set light blue color
$rlb->set_color(0, 170, 234);

print "Press key to exit\n";
<STDIN>;
$ipcon->disconnect();
