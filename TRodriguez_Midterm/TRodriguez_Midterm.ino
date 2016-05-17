/**************************************************************************/
/*! 
    This example will attempt to connect to an ISO14443A
    card or tag and retrieve some basic information about it
    that can be used to determine what type of card it is.   
   
    Note that you need the baud rate to be 115200 because we need to print
    out the data and read from the card at the same time!

    To enable debug message, define DEBUG in PN532/PN532_debug.h
    
*/
/**************************************************************************/


  #include <Wire.h>
  #include <PN532_I2C.h>
  #include <PN532.h>
  
  PN532_I2C pn532i2c(Wire);
  PN532 nfc(pn532i2c);

  #include <Adafruit_GFX.h>   // Core graphics library
  #include <RGBmatrixPanel.h> // Hardware-specific library
  
  #define CLK 8  // MUST be on PORTB! (Use pin 11 on Mega)
  #define LAT A3
  #define OE  9
  #define A   A0
  #define B   A1
  #define C   A2
  RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);
  
  int dest =0;
  int current = 0;



void setup(void) {
  
  Serial.begin(115200);
  Serial.println("Hello!");

  nfc.begin();
  matrix.begin();

  

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }
  
  // Got ok data, print it out!
  Serial.print("Found chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX); 
  Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC); 
  Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);
  
  // Set the max number of retry attempts to read from a card
  // This prevents us from waiting forever for a card, which is
  // the default behaviour of the PN532.
  nfc.setPassiveActivationRetries(0xFF);
  
  // configure board to read RFID tags
  nfc.SAMConfig();
    
  Serial.println("Waiting for an ISO14443A card");
}

void loop(void) {
  boolean success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
  uint8_t uidHex;
  
  // Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
  // 'uid' will be populated with the UID, and uidLength will indicate
  // if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
  dest=0;
  if (success) {
    Serial.println("Found a card!");
    Serial.print("UID Length: ");Serial.print(uidLength, DEC);Serial.println(" bytes");
    Serial.print("UID Value: ");
    nfc.PrintHex(uid,uidLength);


  if (uidLength == 4)
    {
      // We probably have a Mifare Classic card ... 
      uint32_t cardid = uid[0];
      cardid <<= 8;
      cardid |= uid[1];
      cardid <<= 8;
      cardid |= uid[2];  
      cardid <<= 8;
      cardid |= uid[3]; 
      Serial.print("Seems to be a Mifare Classic card #");
      Serial.println(cardid);

      
     if(cardid == 2741370283){  
        dest=30;
        Serial.print("2014");
        matrix.setCursor(0, 9);   // start at top left, with one pixel of spacing
        matrix.setTextSize(1);    // size 1 == 8 pixels high
  
  // print each letter with a rainbow color
  matrix.setTextColor(matrix.Color333(255,255,255));
  matrix.print('1');
  matrix.print('0');
  matrix.print('5');
  matrix.print('7');
  matrix.print('4');
      }
      if(cardid == 2473196971){
         Serial.print("2012");
         dest=17; 
        matrix.setCursor(0, 9);   // start at top left, with one pixel of spacing
        matrix.setTextSize(1);    // size 1 == 8 pixels high
  
  matrix.setTextColor(matrix.Color333(255,255,255));
  matrix.print('5');
  matrix.print('9');
  matrix.print('2');
  matrix.print('5');
        
      }  
      if(cardid == 1893545771){
        dest=9;
        Serial.print("2010");
                matrix.setCursor(0, 9);   // start at top left, with one pixel of spacing
        matrix.setTextSize(1);    // size 1 == 8 pixels high
  
  matrix.setTextColor(matrix.Color333(255,255,255));
  matrix.print('3');
  matrix.print('0');
  matrix.print('3');
  matrix.print('6');
        

      }
      if(cardid == 3014048172){
         Serial.print("2008");
         dest=8; 
                 matrix.setCursor(0, 9);   // start at top left, with one pixel of spacing
        matrix.setTextSize(1);    // size 1 == 8 pixels high
  
  matrix.setTextColor(matrix.Color333(255,255,255));
  matrix.print('3');
  matrix.print('0');
  matrix.print('4');
  matrix.print('1');
         
      }  
      if(cardid == 593983916){
         Serial.print("2006");
         dest=6; 
                 matrix.setCursor(0, 9);   // start at top left, with one pixel of spacing
        matrix.setTextSize(1);    // size 1 == 8 pixels high
  
  matrix.setTextColor(matrix.Color333(255,255,255));
  matrix.print('2');
  matrix.print('0');
  matrix.print('8');
  matrix.print('8');
      }
    }
    Serial.println("");
    
  }else{
    dest=0;
  }
    if (current != dest){
    matrix.fillScreen(matrix.Color333(0, 0, 0));
  }
//          
    for(int i = 0; i<current; i++){
       matrix.drawLine(i,0,i,7,matrix.Color333(255,255,255));
  }
  if (current<dest){
      current++;
  }
   if (current>dest){
      current=current-1;
  }
}
