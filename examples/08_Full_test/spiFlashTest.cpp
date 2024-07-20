#include "spiFlashTest.h"

bool SpiFlashTest::start() {
  fspi = new SPIClass(FSPI);
  fspi->begin(FSPI_SCLK, FSPI_MISO, FSPI_MOSI, FSPI_CS); //SCLK, MISO, MOSI, SS
  pinMode(FSPI_CS, OUTPUT); //FSPI SS

  if (!SerialFlash.begin(*fspi, FSPI_CS)) 
  {
    Serial.println("Unable to access SPI Flash chip");
    return false;    
  }  

  char filename[20] = "test";
  char contents[10] = "abcdef";
  char filesize = 10;  
      
  if(!SerialFlash.create(filename, filesize)) {     
    Serial.println("Failed to Create File");
    return false;    
  }
  
  Serial.println("\tCreate File OK");
  SerialFlashFile file;
  file = SerialFlash.open(filename);
  file.write(contents, filesize);
 
 
  file = SerialFlash.open(filename); // open the file
  if (file) {
    char buffer[256] = {}; // create a buffer for the file contents
    file.read(buffer, 256); // read file to buffer    
    if(strcmp(contents, buffer) != 0)
    {
      Serial.println("File compare failed");
      return false;
    }
    else
    {
      Serial.println("\tFile Read OK");;
    }
  }else{
    Serial.println("File not found!");
    return false;    
  }

  SerialFlash.remove(filename);
  return true;    
}