#include <EEPROM.h>
#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(1,2,3,4,5,6);
///////////////////////////////////////////////////////////////
const int opendelay=5250;//Opening motor running time
const int closedelay=5450;//Closing motor running time

///////////////////////////////////////////////////////////////
//Keypad////////////////
const int button1 = 53;

const int button2 = 51;

const int button3 = 49;

const int button4 = 47;

const int ovrbutton=18;//Override button to open door
const int doorbutton=19;//Door button to lock automatically
bool lockstatus;
const int buzzer=17;//buzzer
const int IN1=14;//Hbridge
const int IN2=15;//Hbridge
//Autoclose door
const int autoclose=1;
////////////////////////
const int locki=16;//internal lock switch


int button1state = 0;

int button2state = 0; 

int button3state = 0; 

int button4state = 0;
int doorstate=1;
int overridestate=0;


int lockistatus;
int check = 0;

int door;

int unlock_var = 0;

int unlock_code = 2115;

int lock_code = 6787;             //////////////////////////////////////////////////////////////For Locking out

int temp_num;

int gate = 0;



void setup() {

  

  pinMode(button1, INPUT);

  pinMode(button2, INPUT);

  pinMode(button3, INPUT);

  pinMode(button4, INPUT);
  
pinMode(locki, INPUT_PULLUP);

  pinMode(IN2, OUTPUT);
  pinMode(IN1, OUTPUT);
pinMode(buzzer, OUTPUT);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, HIGH);

   pinMode(ovrbutton, INPUT);
  pinMode(doorbutton, INPUT);

  // set up the LCD's number of columns and rows: 

  lcd.begin(16, 2);

  // Print a message to the LCD.

  lcd.print("System State:");
  doorstate = digitalRead(doorbutton);
if(doorstate == HIGH)//Automatic door lock
     {
      
      door=1;
     }
     if(doorstate == LOW)
     {
      door=0;
      
     }
  EEPROM.get(0,lockstatus);

   lockistatus = digitalRead(locki);  
}
void open()
{     if(door==1)
    {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      lcd.setCursor(0,1);

     lcd.print("Opening...        ");
      delay(opendelay);
  
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, HIGH);
      door=0;
      beeplong();
      delay(2000);
      }
      else if(door==0)
      {
        if(lockistatus!=LOW && lockstatus!=true )
        {
          lcd.setCursor(0,1);
        
       lcd.print("Door Open!!     ");
       delay(20);
        }
              
      
        
      }
}
void close()
{
  if(door==0)
     {beep();
      delay(750); 
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);

      lcd.setCursor(0,1);

     lcd.print("Closing...        ");
      delay(closedelay);
  
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, HIGH);
      door=1;
      beeplong();
    }
    
}

void beeplong()
{
  digitalWrite(buzzer, HIGH);
  delay(750);
  digitalWrite(buzzer, LOW);
}
void beepshort()
{
  digitalWrite(buzzer, HIGH);
  delay(300);
  digitalWrite(buzzer, LOW);
}

void beep()
{
  digitalWrite(buzzer, HIGH);
  delay(150);
  digitalWrite(buzzer, LOW);
}

//---------------------------------------------------------------------------------------------------------------------------------------
void loop(){
  lockistatus = digitalRead(locki);  
lcd.setCursor(0,0);  
lcd.print("System State:");
  // read the state of the pushbutton value:

  button1state = digitalRead(button1);

  button2state = digitalRead(button2);

  button3state = digitalRead(button3);

  button4state = digitalRead(button4);

 doorstate = digitalRead(doorbutton);
 overridestate = digitalRead(ovrbutton);

//  lcd.print("                   ");

//  // check if the pushbutton is pressed.

//  // if it is, the buttonState is HIGH:

//  if (button1state == HIGH) {     

//    // show "yes" message

//    lcd.setCursor(0,1);

//    lcd.print("Pressed");

//  } 

//  else {

//    // show "no" message

//    lcd.setCursor(0,1);

//    lcd.print("NOT Pressed");

//  }




EEPROM.get(0,lockstatus);


     lcd.setCursor(0,1);

     lcd.print("Waiting...        ");

///////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////




           
     if(doorstate == HIGH){
                          if (autoclose==1)
                          {
                           
                          close();
                          }
                          else if(autoclose==0)
                          {
                            door=1;
                          }
       }

       
      else if(doorstate == LOW)
       {
      //door=0;

      if (autoclose==1)
                          {
                            
                          open();
                          }
                          else if(autoclose==0)
                          {
                            door=0;
                          }
      
     }
     
     if(overridestate == HIGH)//override door open door lock
     {lcd.setCursor(0,1);
        
       lcd.print("OPEN            ");
       delay(400);
      open();
     }
     

     if(button1state == HIGH)

     {

       unlock_var = 56;

       lcd.setCursor(0,1);
        
       lcd.print("1               ");

       delay(400);

     }

     if(button2state == HIGH)

     {

       unlock_var = unlock_var*3;

       lcd.setCursor(0,1);
      
       lcd.print("2               ");

       delay(400);

     }

     if(button3state == HIGH)

     {

       temp_num = unlock_var;

       temp_num = temp_num/2;

       temp_num = temp_num-17;

       unlock_var = unlock_var + temp_num;

       lcd.setCursor(0,1);
      
       lcd.print("3               ");

       delay(400);

     }

     

    if(button4state == HIGH)

    {

lcd.setCursor(0,1);
        
        lcd.print("Enter               ");

       delay(400);
      check = 1;

    }

   

   if(check == 1)

   {

        lcd.setCursor(0,1);

        lcd.print("Checking Code...");

        delay(100);



///Overlock/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
if(unlock_var == lock_code)
{

lockstatus= !lockstatus;
EEPROM.put(0, lockstatus);
beeplong();
delay(50);
beepshort;
delay(50);
beep;  

}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



   
       
     

       if(unlock_var == unlock_code && lockstatus==false && lockistatus==HIGH)

       {

          lcd.setCursor(0,1);

          lcd.print("Access Granted    ");
          beepshort();
          delay(1000);

//Open Door

          open();
           
          delay(1500); //unlock delay

          unlock_var = 0;

       }

       else

       {

         lcd.setCursor(0,1);

         lcd.print("Access Denied     ");
          beepshort();
          delay(100);
          beepshort();
         delay(500);

         unlock_var = 0;

         

       }

      check = 0;

   } 
if (lockstatus==true && lockistatus==LOW)
{
  lcd.setCursor(0,1);
          
          lcd.print("  LOCKED  |IN EX");
          delay(40);
}
else if(lockstatus==true)
{
  lcd.setCursor(0,1);
          
          lcd.print("  LOCKED  |   EX");
          delay(40);
}

else if(lockistatus==LOW)
{
  lcd.setCursor(0,1);
          
          lcd.print("  LOCKED  |IN   ");
          delay(40);
}

   
   if (door==1)
   {
lcd.setCursor(13,0);

     lcd.print("[] ");
   }
   else if (door==0)
   {
lcd.setCursor(13,0);

     lcd.print("[ ]");
   }
  // delay(300);
   //lcd.clear();
}
