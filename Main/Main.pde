
import processing.serial.*; // Import the Serial library

Serial myPort; // Declare a Serial object
String receivedData; // Variable to store the incoming data

void setup() {
  size(400, 200); // Create a window
  println(Serial.list()); // List all available serial ports
  // Change "COM3" to the correct port name for your Arduino
  myPort = new Serial(this, Serial.list()[0], 115200); // Initialize the serial port
  myPort.bufferUntil('\n'); // Trigger serialEvent on newline
}

void draw() {
}

void serialEvent(Serial myPort) {
  if (receivedData != null) {
    receivedData = myPort.readStringUntil('\n'); // Read until a newline
    receivedData = trim(receivedData);
    String hexNumber = receivedData;
    int decimalNumber = parseIntOrNull(hexNumber);
    System.out.println("Hexadecimal: " + hexNumber);
    System.out.println("Decimal: " + decimalNumber);
  }
}

public Integer parseIntOrNull(String value) {
    try {
        return Integer.parseInt(value);
    } catch (NumberFormatException e) {
        return null;
    }
}
