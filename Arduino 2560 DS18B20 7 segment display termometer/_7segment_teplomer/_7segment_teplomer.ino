#include <OneWire.h>
#include <DallasTemperature.h>
#define dspin 21
OneWire ds(dspin);
DallasTemperature teplomer(&ds);




//led bright 7 segment led display

int pinA1 = 16;
int pinB1 = 17;
int pinC1 = 2;
int pinD1 = 3;
int pinE1 = 4;
int pinF1 = 5;
int pinG1 = 6;
int pinDot1 = 7;
int pinA2 = 8;
int pinB2 = 9;
int pinC2 = 10;
int pinD2 = 11;
int pinE2 = 12;
int pinF2 = 13;
int pinG2 = 14;
int pinDot2 = 15;
int cas = 1000;
int i = 0;
int j = 0;

byte piny1[] = {pinA1, pinB1, pinC1, pinD1, pinE1, pinF1, pinG1, pinDot1};
byte piny2[] = {pinA2, pinB2, pinC2, pinD2, pinE2, pinF2, pinG2, pinDot2};
byte cislaLed [16][8] =
{
  {0, 0, 0, 0, 0, 0, 1, 1}, //0
  {1, 0, 0, 1, 1, 1, 1, 1}, //1
  {0, 0, 1, 0, 0, 1, 0, 1}, //2
  {0, 0, 0, 0, 1, 1, 0, 1}, //3
  {1, 0, 0, 1, 1, 0, 0, 1}, //4
  {0, 1, 0, 0, 1, 0, 0, 1}, //5
  {0, 1, 0, 0, 0, 0, 0, 1}, //6
  {0, 0, 0, 1, 1, 1, 1, 1}, //7
  {0, 0, 0, 0, 0, 0, 0, 1}, //8
  {0, 0, 0, 0, 1, 0, 0, 1}, //9
  {0, 0, 0, 1, 0, 0, 0, 1}, //A
  {1, 1, 0, 0, 0, 0, 0, 1}, //B
  {0, 1, 1, 0, 0, 0, 1, 1}, //C
  {1, 0, 0, 0, 0, 1, 0, 1}, //D
  {0, 1, 1, 0, 0, 0, 0, 1}, //E
  {0, 1, 1, 1, 0, 0, 0, 1}, //f
};
//hodnota testovaciho int pozdeji teplomer a hodnoty pro 
//rozdelena cisla
int hodnota = 100;
int prvniCislo = 0;
int druheCislo = 0;

void setup() {
  Serial.begin(9600);
  for (int i = 2; i < 18; i++)
  {
    pinMode(i, OUTPUT);
    //digitalWrite(i,LOW);
    //delay(cas);
    digitalWrite(i, HIGH);
  }
  teplomer.begin();

}

void loop() {
  //teplomerova cast
  teplomer.requestTemperatures();
  Serial.println(teplomer.getTempCByIndex(0));
hodnota = teplomer.getTempCByIndex(0);
  // rozdeleni cisel
  prvniCislo = PrvniCislo(hodnota);
  druheCislo = DruheCislo(hodnota);
  //chyba a normalni chod
  if(hodnota >= 100 || hodnota <0)
  {
    ZobrazCislo1(14);
    ZobrazCislo2(14);   
   
  }
  else
  {
    ZobrazCislo1(prvniCislo);
    ZobrazCislo2(druheCislo); 
  }
  
  delay(cas / 4);
  /*
  i++;
  if(i>=16)
  {
    i=0;
    j++;
  }
  if(j>=16){
    j=0;
    i=0;

  }
  */

}
void ZobrazCislo1(int cislo)
{
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(piny1[i], cislaLed[cislo][i]);

  }
}

void ZobrazCislo2(int cislo)
{
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(piny2[i], cislaLed[cislo][i]);

  }
}
//fce pro rozdeleni cisel
int PrvniCislo(int value)
{
  int prvni;
  if (value > 10) prvni = hodnota % 10;
  if (value >= 0 && value < 10 )prvni = hodnota % 10;
  else if (value < 0)Serial.println(" Teplota je pod 0 . ");
  return prvni;
}
int DruheCislo(int value)
{
  int druhe;
  if (value > 10) druhe = hodnota / 10;
  if (value >= 0 && value < 10 ) druhe = 0;;

  return druhe;
}

