Imports System
Imports Tinkerforge

Module ExampleCallback
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XYZ" ' Change XYZ to the UID of your RGB LED Button Bricklet

    ' Callback subroutine for button state changed callback
    Sub ButtonStateChangedCB(ByVal sender As BrickletRGBLEDButton, ByVal state As Byte)
        If state = BrickletRGBLEDButton.BUTTON_STATE_PRESSED Then
            Console.WriteLine("State: Pressed")
        Else If state = BrickletRGBLEDButton.BUTTON_STATE_RELEASED Then
            Console.WriteLine("State: Released")
        End If
    End Sub

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim rlb As New BrickletRGBLEDButton(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Register button state changed callback to subroutine ButtonStateChangedCB
        AddHandler rlb.ButtonStateChangedCallback, AddressOf ButtonStateChangedCB

        Console.WriteLine("Press key to exit")
        Console.ReadLine()
        ipcon.Disconnect()
    End Sub
End Module
