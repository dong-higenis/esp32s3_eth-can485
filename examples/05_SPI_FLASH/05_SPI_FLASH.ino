#include <SerialFlash.h>
#include <SPI.h>

#define HSPI_MISO 39
#define HSPI_MOSI 38
#define HSPI_SCLK 37
#define HSPI_CS   36
static const int spiClk = 240000000; // 1 MHz
SPIClass * hspi = NULL;
const int FlashChipSelect = 4; 

void setup(){

  Serial.begin(115200);
  delay(3000);
  Serial.println("SPI Flash");
  hspi = new SPIClass(HSPI);
  hspi->begin(HSPI_SCLK, HSPI_MISO, HSPI_MOSI, HSPI_CS); //SCLK, MISO, MOSI, SS
  pinMode(HSPI_CS, OUTPUT); //HSPI SS

  if (!SerialFlash.begin(*hspi, HSPI_CS)) 
  {
    Serial.println("Unable to access SPI Flash chip");
    while(1){}
  }
  
}

void loop(){

  // MAIN MENU
  Serial.println("");
  Serial.println("");
  Serial.println("SerialFlash Read and Write");
  Serial.println("(switch your terminal to no line endings)");
  Serial.println("--------------------------");
  Serial.println("1) Create a new file");
  Serial.println("2) Open a file");
  Serial.println("3) Delete a file");
  Serial.println("--------------------------");
  Serial.println("Select a number");
  while(!Serial.available()){}
  char choice = Serial.read();
  while(Serial.available()){Serial.read();}

  switch(choice){

    case '1':
      newFile();
      break;

    case '2':
      openFile();
      break;

    case '3':
      deleteFile();
      break;

    default:
      Serial.println("Invalid Selection");
    
  }
  
}

/* Create a new file
 * 
 * Request filename up to 20 chars
 * Request a size up to 256 bytes
 * Request some contents
 * Create a file
 */
void newFile(){

  Serial.println("Enter a filename"); // Request filename from user
  while(!Serial.available()){} // Wait for user

  char filename[20] = {}; // buffer to store user filename
  Serial.readBytesUntil(' ', filename, 20);
  while(Serial.available()){Serial.read();}

  Serial.println("Enter a filesize in bytes"); // Request file size from user
  while(!Serial.available()){} // Wait for user

  char sizeArray[3] = {}; // buffer to store requested file size
  Serial.readBytesUntil(' ', sizeArray, 3);
  while(Serial.available()){Serial.read();}
  int filesize = atoi(sizeArray); // Convert char array to int (i.e. "40" to 40) 

  if(SerialFlash.create(filename, filesize)){ // Returns false if file already exists

    SerialFlashFile file; // Open the file we just created for writing
    file = SerialFlash.open(filename);
    Serial.println("Write some file contents:"); // Request file contents from user
    while(!Serial.available()){} // Wait for user

    char contents[256] = {}; // buffer to store file contents
    Serial.readBytesUntil(255, contents, 256);
    while(Serial.available()){Serial.read();} // Empty read buffer
    file.write(contents, filesize); // Write the contents buffer
    Serial.println("");
    Serial.print("New file ");
    Serial.print(filename);
    Serial.print(" created with size ");
    Serial.print(filesize);
    Serial.println(" bytes!");
  }else{
    Serial.println("");
    Serial.println("There was an error creating this file (does it already exist?)");
  }

  return;
  
}

/* Open a file
 * 
 * Print the directory listing
 * Request filename up to 20 chars
 * Open file and display contents
 */
void openFile(){

  printDir(); // Function to print the directory listing

  Serial.println("Enter a filename to OPEN"); // Request file name from user
  Serial.println();
  while(!Serial.available()){} // Wait for user

  char filename[20] = {}; // buffer to store the file name
  Serial.readBytesUntil(' ', filename, 20);
  while(Serial.available()){Serial.read();}

  Serial.println(filename);

  SerialFlashFile file;
  file = SerialFlash.open(filename); // open the file
  if (file) {
    Serial.print("File Name: ");
    Serial.println(filename);
    Serial.println();
    Serial.print("File Size: ");
    Serial.print(file.size());
    Serial.println(" bytes");
    Serial.println();
    Serial.println("File Contents:");
    char buffer[256] = {}; // create a buffer for the file contents
    file.read(buffer, 256); // read file to buffer
    Serial.print(buffer);
  }else{
    Serial.println("File not found!");
  }

  return;
  
}

/* Delete a file
 * 
 * Print the directory listing
 * Request filename up to 20 chars
 * Delete File
 */
void deleteFile(){

  printDir(); // Function to print the directory listing

  Serial.println("Enter a filename to DELETE"); // Request file name from user 
  while(!Serial.available()){} // Wait for user

  char filename[20] = {}; // buffer to store file name
  Serial.readBytesUntil(' ', filename, 20);
  while(Serial.available()){Serial.read();}

  SerialFlash.remove(filename); // Delete the file

  return;
  
}

/* Print Directory
 * 
 * Print a list of all files on the chip
 * Stolen from SerialFlash library example "ListFiles"
 */
void printDir(){

  Serial.println("Directory Listing");
  Serial.println("-----------------");

  SerialFlash.opendir();
  while (1) {
    char filename[64];
    uint32_t filesize;

    if (SerialFlash.readdir(filename, sizeof(filename), filesize)) {
      Serial.print("  ");
      Serial.print(filename);
      spaces(20 - strlen(filename));
      Serial.print("  ");
      Serial.print(filesize);
      Serial.print(" bytes");
      Serial.println();
    } else {
      break; // no more files
    }
  }
}

void spaces(int num) {
  for (int i=0; i < num; i++) {
    Serial.print(" ");
  }
}