
//Includer libraries til brug af diverse funktioner som LCD skærm og MFRC522 rfid reader
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>



#define RST_PIN D3    // Reset Pin
#define SS_PIN D8     // NSS pin
#define SCL_PIN D1    // ?
#define SDA_PIN D2    // ?
//#define RED_PIN D0    // Red
//#define GREEN_PIN D4  // Green

LiquidCrystal_I2C lcd(0x3f, 16, 2); //Opret Liquid Crystal skærm (navn,længde,højde)
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
String tagOLD = ""; //definer og initialiser variabel
unsigned long lastTagTime = 0;             //Opbevarer tid siden sidste tag læst
const unsigned long clearInterval = 5000;  // Time interval to clear tagOLD (in milliseconds)

void setup() { // setup loop kører ved start af program en gang
  lcd.init();                        // Initialize the LCD
  lcd.backlight();                    // turn on backlight
  Serial.begin(115200);               // Initialiser serial kommunikation med PC
  while (!Serial) {};                 // Vent til serial er parat
  SPI.begin();                        // Initialiser SPI bus
  mfrc522.PCD_Init();                 // Initialiser MFRC522
  //RED_PIN = LOW;                      // Turn off the red led
  //GREEN_PIN = LOW;                    // Turn off the green led
  delay(4);                           // Godt at have for nogle Bards
  Serial.println(F("Scan PICC..."));  // Skriv til serial uden at bruge RAM
  //PICC betyder "Proximity Integrated Circuit Card"
  lcd.setCursor(0, 0); // sæt skriveposition til starten
  lcd.print("Hello, World!"); // skriv hello world på skærmen
}
void loop() { //Løkke der kører hver 500 ms grundet delayet
  delay(500); //Delay på 500 ms

  lcd.print(Serial.read()); // skriver på LCD skærm hvad der står i serial forbindelsen

  // rød led ikke modtager info
  // grøn led modtaget D0 og D1
  //lcd display fulde navn og nødkontakt
  if (millis() - lastTagTime > clearInterval) { //Checker om der er gået en bestemt mængde tid siden sidste tag blev scannet
    tagOLD = "";  // Reset tagOLD
  }

  if (!mfrc522.PICC_IsNewCardPresent()) {  // Gør intet, hvis kortet ikke er nyt.
  
  } else {
    if (!mfrc522.PICC_ReadCardSerial()) {  //Laes PICC
      Serial.println("Kan ikke laese UID"); //Skriver i konsolen
      //RED_PIN = HIGH;
      return;
    } else {
      String tag = ""; // giver variablen tag en ny værdi
      for (byte i = 0; i < mfrc522.uid.size; i++) { // for loop som starter med i = 0 hvor i stiger med en for hvert loop og stopper når i er større en længden på UID et
        tag.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ")); //forbinder de forskellige værdier med tag
        tag.concat(String(mfrc522.uid.uidByte[i], DEC)); //omdanner UID til decimaltal
        tag.toUpperCase(); // laver tag uppercase
      }

      if (tagOLD.substring(1) != tag.substring(1)) {  // Hvis UID er ukendt.
        tagOLD = tag;                                 // Store the new tag
        lastTagTime = millis();                       // Reset the timer
        Serial.println(tag); // skriv tag i serial forbindelsen
      }
    }

  }
}
