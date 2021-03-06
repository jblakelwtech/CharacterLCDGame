//ASCII Dungeon Madness by Julian Blake

/// Colin ideas:  Bonus treasure room, main char can get into it and must get out before the flames consume him to get all the treasure

#include <LiquidCrystal.h>
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d7=5, d6=4, d5=3, d4=2;
LiquidCrystal lcd(rs, en, d7, d6, d5, d4);

//const int rs1 = 13, en1 = 10, d41 = 9, d51 = 8, d61 = 7, d71 = 6;
//LiquidCrystal lcd1(rs1, en1, d41, d51, d61, d71);

//Custom characters byte arrays
byte maincharacter[8] = {
  0b00000,
  0b10100,
  0b11100,
  0b00111,
  0b11100,
  0b10011,
  0b00000,
  0b00000,
};  

byte maincharstepping[8] = {
  0b00000,
  0b01000,
  0b01100,
  0b00111,
  0b11100,
  0b10011,
  0b00000,
  0b00000,
};

byte demonbaddie[8] = {
  0b00111,
  0b11111,
  0b11111,
  0b10101,
  0b10111,
  0b10101,
  0b01111,
  0b00000
};

byte heart[8] = {
  0b00000,
  0b00110,
  0b01001,
  0b10010,
  0b10010,
  0b01001,
  0b00110,
  0b00000
};

byte bigboss[8] = {
  0b10100,
  0b10011,
  0b10011,
  0b01100,
  0b01100,
  0b10011,
  0b10011,
  0b10100
};

byte invertedbigboss[8] = {
  0b01011,
  0b01100,
  0b01100,
  0b10011,
  0b10011,
  0b01100,
  0b01100,
  0b01011
};

//button used for action button on pin 1 to ground
int testbutton = 1;

//used for random number generator, flag starts false
bool buttonpressedyet = false;

//used for random number generator, flag for when random number is higher than millis so you can press a button.
bool randomhighermillis = false;

//random number afterwhich buttons can be pressed if millis is higher 16-256. 
// Once millis>this number, subtract millis from this number to get the player seed number

short seedrandom = random(16, 256);
//Number below is how many mS the player has not pressed the button after randomhighermillis is true
int playerrando = 0; 


int walk_animation_index = 0;
const int WALK_ANIMATION_ADDRESS = 7;
int hero_x = 0;  
int hero_y = 0; 

int demon_x = 0;
int demon_y = 0;

const int DEMON_ADDRESS = 6;

void setup() {
  //serial for testing, maybe remove later?
  Serial.begin(9600);
  Serial.print("Hello world.");
    Serial.print("seedrandom: ");
  Serial.print(seedrandom);
  // set up the LCD's number of columns and rows:
  lcd.begin(20, 4);
  lcd.clear();
  lcd.createChar(WALK_ANIMATION_ADDRESS + 1, maincharacter);
  lcd.createChar(WALK_ANIMATION_ADDRESS, maincharstepping);
  lcd.createChar(DEMON_ADDRESS, demonbaddie);
  lcd.createChar(5, heart);
  lcd.createChar(4, bigboss);
  lcd.createChar(3, invertedbigboss);
  lcd.setCursor(0,0); //set cursor top left
 
  //ints used to move the maincharacter
  int charxaxis = 3;
  int charyaxis = 3;
}

unsigned long timeseed;

void update() {
  walk_animation_index++;
  walk_animation_index %= 2;
  
  hero_x++;
  hero_x %= 20;

  hero_y++;
  hero_y %= 4;

  int demon_x_increment = 0;
  int demon_y_increment = 0;
  int demon_new_position = random(0, 8);

  switch(demon_new_position) {
      case 0 :
        demon_x_increment = -1;
        demon_y_increment = 1;
        break;
      case 1 :
        demon_x_increment = 0;
        demon_y_increment = 1;
        break;
      case 2 :
        demon_x_increment = 1;
        demon_y_increment = 1;
         break;
      case 3 :
         break;
      case 4 :
         break;
      case 5 :
         break;
      case 6 :
         break;
      case 7 :
         break;
      case 8 :
         break;
   }

   demon_x += demon_x_increment;
   demon_x %= 20;
   demon_y += demon_y_increment;
   demon_y %= 4;
}

void draw() {

  /*
  lcd.setCursor(16,0);
  lcd.write(byte(6));

  lcd.setCursor(15,0);
  lcd.write(byte(5));

  lcd.setCursor(14,0);
  lcd.write(byte(4));

  lcd.setCursor(13,0);
  lcd.write(byte(3));

  Serial.print(playerrando);

  //milis used to compare to random number to make an extra-random numer;
  //the point being to make a seed partially from the time the arduino is powered;
  //up until the first button is pressed, so that the real random number is not timeable;
  timeseed = millis();
  
  if (timeseed > seedrandom) {
    randomhighermillis = true;
    playerrando++;
   
    Serial.println(playerrando);
  }
    
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
  // main character X and Y location on LCD
  lcd.setCursor(0,0);
  lcd.write(byte(7));
  delay(1000);
  lcd.setCursor(0,0);
  lcd.write(byte(8));
  delay(1000);
  
  lcd.setCursor(charxaxis,charyaxis);
  lcd.write(byte(7));
  
  lcd.setCursor(20,3);
  lcd.write(byte(7));
  */

  lcd.clear();
  lcd.setCursor(hero_x, hero_y);
  lcd.write(WALK_ANIMATION_ADDRESS + walk_animation_index);

  lcd.setCursor(demon_x, demon_y);
  lcd.write(DEMON_ADDRESS); 
  delay(1000);
}

void loop() {
  update();
  draw();
}
