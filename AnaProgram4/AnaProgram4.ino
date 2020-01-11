#define Buton 10
#define buzzerPin 11
#define Led12 12       //Kırmızı LED
#define Led13 13       //Yeşil led
#define BackechoPin 7
#define BacktrigPin 6
#define echoPin 9
#define trigPin 8

//Kapı arkası sensörü ölçüm mesafesi
int BackmaximumRange = 6;
int BackminimumRange = 1;

//Kapı önü sensör ölçü mesafesi
int maximumRange = 8;
int minimumRange = 1;

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
pinMode(Buton, INPUT);
pinMode(Led12, OUTPUT);
pinMode(Led13, OUTPUT);
pinMode(buzzerPin, OUTPUT);
pinMode(BacktrigPin, OUTPUT);
pinMode(BackechoPin, INPUT);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
Serial.begin(9600); // Seri haberleşme baud hızı: Ultrasonic sensör derğerlerini seri port ekranında görüntülemek için


lcd.begin();
lcd.setCursor(0,0);
lcd.print("DiKKAT! KAPI AR-");
lcd.setCursor(0,1);
lcd.print("KASINDA_BiRi_VAR");
  
}

void loop()
{
  int backolcum = BackMesafe(BackmaximumRange, BackminimumRange);
  int olcum = mesafe(maximumRange, minimumRange);
  if (digitalRead(Buton) == 1) and (backolcum <=6 and backolcum >=1) 
  { LCDGoster();
  }

 if (digitalRead(Buton) == 1) and (olcum <=8 and olcum >=1)
  {         
    melodi(backolcum*20);
    YanSon();
   }
}


 void LCDGoster()
{
  
  lcd.display();
delay(200);
lcd.noDisplay();
}

int melodi(int bekle)
{
  tone(buzzerPin, 440);
  delay(bekle);
  noTone(buzzerPin);
  delay(bekle);  
}

void YanSon()
{

  digitalWrite(Led13, HIGH); 
  digitalWrite(Led12, HIGH); 
  delay(120);                       // wait for 0.12 second
  digitalWrite(Led12, LOW);
  digitalWrite(Led13, LOW);    
  delay(120);   
}

int BackMesafe(int azamimenzil, int asgarimenzil)
{
  long sure, uzaklik;
  // Clears the trigPin
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
  sure = pulseIn(echoPin, HIGH);
  
  //Calculating the uzaklik
  //the speed of the sound is 340 m/s or 0.034 cm/µs 
  //the sound wave needs to travel forward and bounce backward. So divide it by 2
  uzaklik = (sure  * 0.034)/2;
 //uzaklik = sure /58.2;
  delay(50);
 

// Prints the uzaklik on the Serial Monitor
// Serial.print("Uzaklik: ");
//Serial.println(uzaklik);

  if(uzaklik >= azamimenzil || uzaklik <= asgarimenzil)
  return 0;
  return uzaklik;
}



int mesafe(int maxrange, int minrange)
{
  long duration, distance;
  // Clears the trigPin
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  //Calculating the distance
  //the speed of the sound is 340 m/s or 0.034 cm/µs 
  //the sound wave needs to travel forward and bounce backward. So divide it by 2
  distance = (duration  * 0.034)/2;
 //distance = duration /58.2;
  delay(50);
 

// Prints the distance on the Serial Monitor
//Serial.print("Distance: ");
//Serial.println(distance);

  if(distance >= maxrange || distance <= minrange)
  return 0;
  return distance;
}

 
