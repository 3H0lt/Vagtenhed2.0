
import processing.serial.*; // Import the Serial library
import de.bezier.data.sql.*;

// Variables for database
MySQL db;
String dbName = "IoT";
FestDatabase festDB;

Serial myPort1; // Declare a Serial object
Serial myPort2;
String receivedData; // Variable to store the incoming data
String[] dataSplitted;
int[] decimalNumber;
String decimalNumberString = "";
void setup() {
  size(400, 200); // Create a window
  println((Object[]) Serial.list()); // List all available serial ports
  // Change "COM3" to the correct port name for your Arduino
  myPort1 = new Serial(this, Serial.list()[2], 115200); // Initialize the serial port
  myPort1.bufferUntil('\n'); // Trigger serialEvent on newline
  
   // Initialize database
  festDB = new FestDatabase(connect("192.168.4.1", 3306, dbName, "mysql", "RoboTech!"), "info", "Genstande", "CardID", "Name");
  

  // Get name from person
  //println(festDB.getUserName(66845705)); // her indsættes kortid og databasen giver et navn
}

void draw() {
  if ( myPort1.available() > 0) //Er data parat?
  {
    receivedData = myPort1.readStringUntil('\n'); //Laes data og gem det

    if (receivedData != null && receivedData != ".") {
      receivedData = trim(receivedData); // Remove leading/trailing whitespace
      
      // Remove spaces in between numbers
      receivedData = receivedData.replace(" ", "");
      if (receivedData != ""){
      int Rdata = int(receivedData);
      println(festDB.getUserName(Rdata));
      myPort1.write(festDB.getUserName(Rdata));
      }
 println(receivedData);
    }
  }
  delay(100);
}
