Imports System
Imports Tinkerforge

Module ExampleSimpleColor
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XYZ" ' Change XYZ to the UID of your RGB LED Button Bricklet

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim rlb As New BrickletRGBLEDButton(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Set light blue color
        rlb.SetColor(0, 170, 234)

        Console.WriteLine("Press key to exit")
        Console.ReadLine()
        ipcon.Disconnect()
    End Sub
End Module
