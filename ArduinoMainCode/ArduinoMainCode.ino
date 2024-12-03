#include <SPI.h>
#include <MFRC522.h>
#define RST_PIN D3  // Reset Pin
#define SS_PIN D8   // NSS pin

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
String tagUID1 = "6B CE 2F E3";    // String med UID for tag#1. Tilpas til jeres tag!!!
String tagUID2 = "BC 80 EB 38";    // String med UID for tag#2. Tilpas til jeres tag!!!
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
        tag.concat(String(mfrc522.uid.uidByte[i], HEX));
      }
      tag.toUpperCase();
      if (tag.substring(1) == tagUID1 && tagOLD.substring(1) != tag.substring(1)) {  // Hvis UIDfra tag #1 er fundet.
        tagOLD = tag;
        Serial.println(F("Found Tag #1!"));
      } else if (tag.substring(1) == tagUID2 && tagOLD.substring(1) != tag.substring(1)) {  //Hvis UID fra tag #2 er fundet.
        tagOLD = tag;
        Serial.println(F("Found Tag #2!"));
      } else if (tagOLD.substring(1) != tag.substring(1)) {  // Hvis UID er ukendt.
        tagOLD = tag;
        Serial.print(F("Found Nonreg. Tag! "));
        Serial.println(tag);
      }
    }
  }
}
