#include <Password.h>
#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

Servo myservo;

Password password = Password("2991211");  // password
int dlugosc = 8;                        // length of the password
 
/*--------------------------------------------
LiquidCrystal lcd(RS, E, DB4, DB5, DB6, DB7);*/
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
 
int ledRed = 11;
int ledGreen = 12;
int buzzer = 13;
//int relay = 10;
 
int ilosc; // number of clicks
 
const byte ROWS = 4; // rows
const byte COLS = 3; // cols
 
char keys[ROWS][COLS] =
{
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
 
byte rowPins[ROWS] = {2,3,4,5};
byte colPins[COLS] = {6,7,8};
 
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
 
void setup()
{
  myservo.write(360);
  myservo.attach(10);
  Serial.begin(9600);
  keypad.addEventListener(keypadEvent);  
  pinMode(ledRed, OUTPUT);  
  pinMode(ledGreen, OUTPUT);
  pinMode(buzzer, OUTPUT);
//  pinMode(relay, OUTPUT);
 
  digitalWrite(ledRed, HIGH);
  digitalWrite(ledGreen, LOW);
  //digitalWrite(relay,LOW);
 
  lcd.begin(16, 2);
 
  lcd.setCursor(1,0);
  lcd.print("  :Welcome:");
  lcd.setCursor(0,1);
  lcd.print("PLEASE ENTER PIN");
}
 
void loop()
{
  keypad.getKey();
}
void keypadEvent(KeypadEvent eKey)
{
  switch (keypad.getState())
  {
    case PRESSED:
   
int i;
for( i = 1; i <= 1; i++ )
{
  digitalWrite(buzzer, HIGH);  
  delay(50);            
  digitalWrite(buzzer, LOW);  
  delay(50);      
}    
 
Serial.print("Pressed: ");
Serial.println(eKey);
 
switch (eKey)
{

case '#':{
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print(" << CLOUSED >>");
  myservo.write(360);
  int i;
  for( i = 1; i <= 2; i++ )
  {
    digitalWrite(buzzer, HIGH);  
    delay(70);            
    digitalWrite(buzzer, LOW);  
    delay(70);      
  }
  digitalWrite(ledRed, HIGH);
  digitalWrite(ledGreen, LOW);
  break;
}
case '*':{
  password.reset();
  ilosc = 0;
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("  :Welcome:");
  lcd.setCursor(0,1);
  lcd.print("PLEASE ENTER PIN");
break;
}
//break;

 
default:
ilosc=ilosc+1;
password.append(eKey);
}
//Serial.println(ilosc);
 
if(ilosc == 1)
{
lcd.clear();
lcd.setCursor(1,0);
lcd.print("   < PIN >");
lcd.setCursor(0,1);
lcd.print("*_");
}
if(ilosc == 2)
{
lcd.clear();
lcd.setCursor(1,0);
lcd.print("   < PIN >");
lcd.setCursor(0,1);
lcd.print("**_");
}
if(ilosc == 3)
{
lcd.clear();
lcd.setCursor(1,0);
lcd.print("   < PIN >");
lcd.setCursor(0,1);
lcd.print("***_");
}
if(ilosc == 4)
{
lcd.clear();
lcd.setCursor(1,0);
lcd.print("   < PIN >");
lcd.setCursor(0,1);
lcd.print("****_");
}
if(ilosc == 5)
{
lcd.clear();
lcd.setCursor(1,0);
lcd.print("   < PIN >");
lcd.setCursor(0,1);
lcd.print("*****_");
}
if(ilosc == 6)
{
lcd.clear();
lcd.setCursor(1,0);
lcd.print("   < PIN >");
lcd.setCursor(0,1);
lcd.print("******_");
}
if(ilosc == 7)
{
lcd.clear();
lcd.setCursor(1,0);
lcd.print("   < PIN >");
lcd.setCursor(0,1);
lcd.print("*******_");
}
if(ilosc == 8)
{
lcd.clear();
lcd.setCursor(1,0);
lcd.print("   < PIN >");
lcd.setCursor(0,1);
lcd.print("********");
}
 
if(ilosc == dlugosc)
{
delay(250);
checkPassword();
ilosc = 0;
}
}
}
 
void checkPassword()
{
  if (password.evaluate())
  {
int i;
for( i = 1; i <= 2; i++ )
{
  digitalWrite(buzzer, HIGH);  
  delay(70);            
  digitalWrite(buzzer, LOW);  
  delay(70);      
}    
    ilosc = 0;
 
    Serial.println("Success");    
 
    digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, HIGH);

    //digitalWrite(relay,HIGH);
    myservo.write(0);
    delay(2000);
     //digitalWrite(relay,LOW);

    
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print(" << SUCCESS >>");    
 }  
  else  
  {
int i;
for( i = 1; i <= 1; i++ )
{
  digitalWrite(buzzer, HIGH);  
  delay(200);            
  digitalWrite(buzzer, LOW);  
  delay(200);      
}  
    ilosc = 0;  
    password.reset();
 
    Serial.println("Wrong");
 
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledRed, HIGH);    
             
    lcd.clear();
    lcd.setCursor(0,1);	
    lcd.print("  << WRONG >>");
    delay(2000);
   
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("  :Welcome:");
    lcd.setCursor(0,1);
    lcd.print("PLEASE ENTER PIN");    
  }
}
