#include <Keypad.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

const byte rows = 4; 
const byte cols = 4;
const byte red = 13;
const byte green = 12;

int buzz = 10000;
char keys[rows][cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
                         };
byte rowPins[rows] = {9,8,7,6}; 
byte colPins[cols] = {5,4,3,2}; 
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

LiquidCrystal_I2C lcd(0x27, 16, 2);
int LCDRow =0;

bool Detected = false;
bool locked = false;

int buzzer = 10;

String passcode = "000";
String input = "";

char key ;

void setup()
{
  	Serial.begin (9600);
    pinMode (red , OUTPUT);
    pinMode (green , OUTPUT);
    pinMode (buzzer, OUTPUT);
    lcd.begin();
    lcd.backlight();
 }
     
void loop()
{
    digitalWrite(green , 1);
    digitalWrite(red , 1);
  lcd.setCursor(0,0);
  lcd.print("    WELCOME! ");
  char key = keypad.getKey();
    if (key && key!= '#')
    {
      input +=key;
      Serial.println(key);
      lcd.setCursor (LCDRow, 1);
      lcd.print(key);
      lcd.setCursor (++LCDRow, 1);
        }
      		if (key == '#')
            {
              if (passcode == input)
              {
                lcd.clear();
      			    lcd.print("    success");
                digitalWrite(buzzer,1);
                digitalWrite(green, 0);
                delay(100);
                digitalWrite(buzzer,0);
                delay(100);
                digitalWrite(buzzer,1);
                delay(100);
                digitalWrite(buzzer,0);
                delay(100);
                digitalWrite(green, 1);
              	locked = true;
                input = "";
                lcd.setCursor(0,0);
             	  LCDRow =0;
                delay(5000);
                lcd.clear();
              }
              else{
                {
                  lcd.clear();
                  lcd.print("   try  again");
                  digitalWrite(red , 0);
                  digitalWrite(buzzer,1);
                  delay(1000);
                  digitalWrite(buzzer,0);
                  digitalWrite(red , 1);
                  delay(1000);

                input = "";
                lcd.setCursor(0,0);
                LCDRow= 0;
                delay(1000);}
                while (passcode == input);
              }
            }
}
                 
                
