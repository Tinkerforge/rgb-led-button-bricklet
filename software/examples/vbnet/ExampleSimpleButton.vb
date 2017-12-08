Imports System
Imports Tinkerforge

' FIXME: This example is incomplete

Module ExampleSimpleButton
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XYZ" ' Change XYZ to the UID of your RGB LED Button Bricklet

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim rlb As New BrickletRGBLEDButton(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Get current button state
        Dim state As Byte = rlb.GetButtonState()
        Console.WriteLine("State: " + state.ToString())

        Console.WriteLine("Press key to exit")
        Console.ReadLine()
        ipcon.Disconnect()
    End Sub
End Module
