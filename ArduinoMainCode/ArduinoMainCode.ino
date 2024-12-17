#include <LCD-I2C.h>
#include <SPI.h>
#include <MFRC522.h>
#define RST_PIN D3  // Reset Pin
#define SS_PIN D8   // NSS pin
#define SCL_PIN D1 // ?
#define SDA_PIN D2 // ?

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
String tagOLD = "";

void setup() {
  Serial.begin(115200);               // Initialiser serial kommunikation med PC
  while (!Serial) {};                 // Vent til serial er parat
  SPI.begin();                        // Initialiser SPI bus
  mfrc522.PCD_Init();                 // Initialiser MFRC522
  delay(4);                           // Godt at have for nogle Bards
  Serial.println(F("Scan PICC..."));  // Skriv til serial uden at bruge RAM
  //PICC betyder "Proximity Integrated Circuit Card"
}
void loop() {
  delay(500);
  if (!mfrc522.PICC_IsNewCardPresent()) {  // Gør intet, hvis kortet ikke er nyt.
    Serial.print(".");
  } else {
    if (!mfrc522.PICC_ReadCardSerial()) {  //Laes PICC
      Serial.println("Kan ikke laese UID");
      return;
    } else {
      String tag = "";
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        tag.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        tag.concat(String(mfrc522.uid.uidByte[i],HEX));
        String hexNumber = Tag; // Example hexadecimal number
        int decimalNumber = Integer.parseInt(hexNumber, 16);
        System.out.println("Hexadecimal: " + hexNumber);
        System.out.println("Decimal: " + decimalNumber);
      }
      tag.toUpperCase();
      if (tagOLD.substring(1) != tag.substring(1)) {  // Hvis UID er ukendt.
        tagOLD = tag;
        
        Serial.println(decimalNumber);
      }
    }
  }
}
