#include <Wire.h>
//#include <LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN D3    // Reset Pin
#define SS_PIN D8     // NSS pin
#define SCL_PIN D1    // ?
#define SDA_PIN D2    // ?
#define RED_PIN D0    // Red
#define GREEN_PIN D4  // Green

//LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
String tagOLD = "";
unsigned long lastTagTime = 0;             // Stores the time of the last detected tag
const unsigned long clearInterval = 5000;  // Time interval to clear tagOLD (in milliseconds)

void setup() {
  //lcd.begin();                        // Initialize the LCD
  //lcd.backlight();                    // turn on backlight
  Serial.begin(115200);               // Initialiser serial kommunikation med PC
  while (!Serial) {};                 // Vent til serial er parat
  SPI.begin();                        // Initialiser SPI bus
  mfrc522.PCD_Init();                 // Initialiser MFRC522
  RED_PIN = LOW;                      // Turn off the red led
  GREEN_PIN = LOW;                    // Turn off the green led
  delay(4);                           // Godt at have for nogle Bards
  Serial.println(F("Scan PICC..."));  // Skriv til serial uden at bruge RAM
  //PICC betyder "Proximity Integrated Circuit Card"
  //lcd.setCursor(0, 0);
  //lcd.print("Hello, World!");
}
void loop() {
  delay(500);

  // rød led ikke modtager info
  // grøn led modtaget D0 og D1
  //lcd display fulde navn og nødkontakt
  if (millis() - lastTagTime > clearInterval) {
    tagOLD = "";  // Reset tagOLD
  }

  if (!mfrc522.PICC_IsNewCardPresent()) {  // Gør intet, hvis kortet ikke er nyt.
    Serial.println(".");
  } else {
    if (!mfrc522.PICC_ReadCardSerial()) {  //Laes PICC
      Serial.println("Kan ikke laese UID");
      RED_PIN = HIGH;
      return;
    } else {
      String tag = "";
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        tag.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        tag.concat(String(mfrc522.uid.uidByte[i], DEC));
        tag.toUpperCase();
      }

      if (tagOLD.substring(1) != tag.substring(1)) {  // Hvis UID er ukendt.
        tagOLD = tag;                                 // Store the new tag
        lastTagTime = millis();                       // Reset the timer
        Serial.println(tag);
      }
    }
  }
}
