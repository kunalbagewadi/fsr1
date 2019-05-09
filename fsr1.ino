//********************************* global variable declartion ***********************************************

#define FSR_SIGNATURE 0xA7
#define DATA_LENGTH 17
byte inData[DATA_LENGTH];
int iter = 0;
//********************************** basic pin and serial port setup***********************************

void setup(){
  Serial.begin(115200);
}

//*********************************** main loop to write data into serial port 1************************

void loop(){
 // read smart shoe data and send through serial port 1
    ssRead(iter);
    Serial.write(inData,DATA_LENGTH);
    iter++;
    delay(50);  // 20Hz
}

/*
void loop(){  // See inData[] on serial port
 
    ssRead(iter);
    Serial.print(iter);
    Serial.print(" ");
    //Serial.write(inData,DATA_LENGTH);
    for(int i=0;i < DATA_LENGTH;i++)
    {
      Serial.print(inData[i]);
      Serial.print(" ");
    }
    Serial.println("");
    
    iter++;
    delay(1000);
}
*/
// *************** subfunction for reading FSR data **************************************
void ssRead(int iter){

  int fsr0 = analogRead(0);
//  int fsr1 = 0;
//  int fsr2 = 0;
//  int fsr3 = 0;
//  int fsr4 = 0;
//  int fsr5 = 0;
  // unused analog ports
  int fsr1 = analogRead(1); 
  int fsr2 = analogRead(2);
  int fsr3 = analogRead(3);
  int fsr4 = analogRead(4);
  int fsr5 = analogRead(5);  
  
  int rawRead[] = {fsr0, fsr1, fsr2, fsr3, fsr4, fsr5};
  
  inData[0] = 0xFF;
  inData[1] = 0xFF;
  inData[2] = FSR_SIGNATURE;
  inData[3] = highByte(iter);
  inData[4] = lowByte(iter);
  for (int j = 0; j < 6; j++){    // 6= #ints in rawRead[]
    inData[5+2*j] = highByte(rawRead[j]);
    inData[6+2*j] = lowByte(rawRead[j]);
  }
}
