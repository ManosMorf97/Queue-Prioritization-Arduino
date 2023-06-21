// C++ code
//
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
using namespace std;
LiquidCrystal_I2C lcd(32,16,2);

const byte Rows=4;
const byte Cols=4;
byte rowpins[Rows]={2,3,4,5};
byte colpins[Cols]={6,7,8,9};
byte ledpin_full=10;
int limit=100;

char buttons[Rows][Cols]={{'1','2','3','A'},{'4','5','6','B'},
{'7','8','9','C'},{'*','0','#','D'}};
Keypad customKeypad = Keypad(makeKeymap(buttons),
                             rowpins, colpins, Rows, Cols);


byte full;
byte total_clients;
byte served_clients;
boolean activated=false;

void setup()
{
  pinMode(ledpin_full, OUTPUT);
  Serial.begin(1000);
}

void loop()
{
  char charkey=customKeypad.getKey();
  String textTotal=String(String("Total: ")+String(total_clients));
  String textServed=String(String("Served: ")+String(served_clients));
  //digitalWrite(ledpin_start,HIGH);
  lcd.setCursor(0, 0);
  lcd.print(textTotal);
  lcd.setCursor(0,1);
  lcd.print(textServed);
  switch(charkey){
    case 'A':
    if(!activated){
      lcd.init();
  	  lcd.setCursor(0, 0);
  	  lcd.backlight();
  	  lcd.display();
      activated=true;
    }
    lcd.clear();
    total_clients=0;
    served_clients=0;
    digitalWrite(ledpin_full,LOW);
    break;
    case 'B':
    increaseTotal(limit);
    if (total_clients==limit){
    	digitalWrite(ledpin_full,HIGH);
    }
    break;
    case 'C':
    increaseServed();
    break;
    default:
    break; 
  }    
}
void increaseTotal(int limit){
  total_clients=increased(total_clients,limit);
}

void increaseServed(){
  served_clients=increased(served_clients,total_clients);
}

byte increased(byte increased,int limit){
  increased=increased<limit?increased+1:increased;
  return increased;
}

