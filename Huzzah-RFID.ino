/*
 * Typical pin layout used:
 * -------------------------------------------------
 *             MFRC522      Arduino       Arduino   
 *             Reader/PCD   Uno/101       Mega      
 * Signal      Pin          Pin           Pin       
 * -------------------------------------------------
 * RST/Reset   RST          9             5         
 * SPI SS      SDA(SS)      10            15        
 * SPI MOSI    MOSI         11 / ICSP-4   13        
 * SPI MISO    MISO         12 / ICSP-1   12        
 * SPI SCK     SCK          13 / ICSP-3   14        
 */

#include <SPI.h>
#include <MFRC522.h>

constexpr uint8_t RST_PIN = 9;     // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = 15;     // Configurable, see typical pin layout above
 
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key; 

// Init array that will store new NUID 
byte nuidPICC[4];


void setup() { 
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 

  
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  //Serial.println(F("This code scan the MIFARE Classsic NUID."));
  //Serial.print(F("Using the following key:"));
  printHex(key.keyByte, MFRC522::MF_KEY_SIZE);
}
 
void loop() {

  // Look for new cards
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  //Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  //Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    //Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

   // Store NUID into nuidPICC array
   for (byte i = 0; i < 4; i++) {
     nuidPICC[i] = rfid.uid.uidByte[i];
   }
   


  if(0xB5 == nuidPICC[0] && 0x31 == nuidPICC[1] &&    //Change this to your cards UID
      0x56 == nuidPICC[2] && 0x45 == nuidPICC[3] )
    {
      Serial.println();
      Serial.println("Access GRANTED :)");
      delay(3000);
    }
  else
    {
      Serial.println();
      Serial.println("Access DENIED :(");
      delay(2000);
    }
    
   
  //Serial.println(F("The NUID tag is:"));
  //Serial.print(F("In hex: "));
  //printHex(rfid.uid.uidByte, rfid.uid.size);
  //Serial.println();
  //Serial.print(F("In dec: "));
  //printDec(rfid.uid.uidByte, rfid.uid.size);
  //Serial.println();
  //Serial.println();
  //Serial.println();        


  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}


/**
 * Helper routine to dump a byte array as hex values to Serial. 
 */
void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    //Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    //Serial.print(buffer[i], HEX);
  }

}

/**
 * Helper routine to dump a byte array as dec values to Serial.
 */
void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    //Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    //Serial.print(buffer[i], DEC);
  }
}