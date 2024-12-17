
import processing.serial.*; // Import the Serial library

Serial myPort; // Declare a Serial object
String receivedData; // Variable to store the incoming data

void setup() {
  size(400, 200); // Create a window
  println(Serial.list()); // List all available serial ports
  // Change "COM3" to the correct port name for your Arduino
  myPort = new Serial(this, Serial.list()[2], 115200); // Initialize the serial port
  myPort.bufferUntil('\n'); // Trigger serialEvent on newline
}

void draw() {
  if ( myPort.available() > 0) //Er data parat?
{
receivedData = myPort.readStringUntil('\n'); //Laes data og gem det
  if (receivedData != null && receivedData != ".") {
    receivedData = trim(receivedData);
    String hexNumber = receivedData;
    int decimalNumber = Integer.parseInt(hexNumber,16);
    System.out.println("Hexadecimal: " + hexNumber);
    System.out.println("Decimal: " + decimalNumber);
  }
}
}
