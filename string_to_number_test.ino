#include <SPI.h>
#include <SD.h>
#include <LiquidCrystal.h>
#include <avr/pgmspace.h>
#define X1 A0
#define X2 A1
#define Y1 A2
#define Y2 A3
//Define your screen resolution as per your Touch screen (Max: 1024)
#define Xresolution 28 //128
#define Yresolution 28 //64
byte TouchMatrix[28][28];
 int sum[10];
//long int count = 0;//counter for w elements
//float maxSum = 0;

//const int rs = 10, en = 9, d4 = 5, d5 = 6, d6 = 3, d7 = 2;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int chipSelect = 4;
 int number = 0;
int a=0;
int b=0;
int n=0;
String inString = "";    // string to hold input

//byte oneTouch[783];


void setup() {

  Serial.begin(9600);
//  lcd.begin(16, 2);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");

  for (byte i = 0; i < 28; i++)
  {
    for (byte j = 0; j < 28; j++)
    {
      TouchMatrix[i][j] = 1;
    }
  }

  for(int i=0;i<10;i++){
    sum[i]=0;
  }


}





void loop() {

 // Serial.println(millis());
  float X1, Y1; //Touch Coordinates are stored in X,Y variable
  pinMode(Y1, INPUT);
  pinMode(Y2, INPUT);
  digitalWrite(Y2, LOW);
  pinMode(X1, OUTPUT);
  digitalWrite(X1, HIGH);
  pinMode(X2, OUTPUT);
  digitalWrite(X2, LOW);
  X1 = (analogRead(Y1)) * 0.12 - 52.77; //Reads X axis touch position

  pinMode(X1, INPUT);
  pinMode(X2, INPUT);
  digitalWrite(X2, LOW);
  pinMode(Y1, OUTPUT);
  digitalWrite(Y1, HIGH);
  pinMode(Y2, OUTPUT);
  digitalWrite(Y2, LOW);
  Y1 = (analogRead(X1)) * 0.15 - 70.5; //Reads Y axis touch position
  int X = X1;
  int Y = Y1;
  //TouchMatrix[X][Y] = 1;
  //    int k=0;
  //   for(int i=0;i<28;i++){
  //    for(int j=0;j<28;j++){
  //      oneTouch[k]=TouchMatrix[i][j];
  //      k++;
  //    }
  //   }
  int ti = millis();
  //if (ti % 5000==0) {

    File dataFile = SD.open("lol.txt");

    if (dataFile) {
      while ((dataFile.available()) && (n<2)) {
        int inChar = dataFile.read();
        if (inChar != 44) {
          //Serial.println(inChar);
          inString += (char)inChar;
        }                    
        else if (inChar = 44) {
          //      Serial.print("inString : ");
          //      Serial.println(inString);
          number = inString.toFloat();

//          count += 1;
          //while (n < 10) {
            if (b != 27) {
              sum[n] += number*TouchMatrix[a][b];
              Serial.print("1st ");
              Serial.print(n);
              Serial.print("  : ");
              Serial.println(sum[n]);
              b++;
            }
            else if (a!=27 && b == 27) {
              sum[n] += number*TouchMatrix[a][b];
              Serial.print("2nd ");
              Serial.print(n);
              Serial.print("  : ");
              Serial.println(sum[n]);
              a++;
              b = 0;
              
            }
            else if (a == 27 && b == 27) {
              sum[n] += number*TouchMatrix[a][b];
              a=0;
              b=0;
              Serial.print("3rd ");
              Serial.print(n);
              Serial.print("  : ");
              Serial.println(sum[n]);
              n++;
              
            }
            
          //}
          inString = "";
        }
        
      }




    }
//    for(int i=0;i<10;i++){
//      Serial.print("sum[i]");
//      Serial.println(sum[i]);
//    }
    
//    int j = 0;
//    for (int i = 0; i < 0; i++) {
//      if (sum[i] > sum[j]) {
//        j = i;
//      }
//    }
 //   Serial.print(sum[0]);
  //}

  //Serial.println(sum);


}



