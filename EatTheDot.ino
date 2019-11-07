#include <M5StickC.h>

float pitch = 0;
float roll = 0;
float yaw = 0;

int x = 40; //Start position for player
int y = 10;
int r = 1;

int foodx = 158; //Start Position of food
int foody = 78;

int foodx1 = 159; //Counter for edge of screen
int foody1 = 79;

void setup() {
  M5.begin();
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(BLACK);
  M5.MPU6886.Init();
}

void loop() {
  
  M5.MPU6886.getAhrsData(&pitch, &roll, &yaw);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.drawCircle(x, y, r, RED);
  M5.Lcd.drawCircle(foodx, foody, 1, GREEN);
  
  if (roll > -25) {  //read MPU roll data for left and right
    x--;
  }
  if (roll < -5) {
    x++;
  }
  if (pitch > -15) {  //read MPU pitch data for up and down
    y++;
  }
  if (pitch < -1) {
    y--;
  }
  if (x < 0) { //keeps player inbounds
    x = 1;
  }
  if (x > 160) {
    x = 159;
  }
  if (y < 0) {
    y = 1;
  }
  if (y > 80) {
    y = 79;
  }
  if (foodx < foodx1) { //moves food
    foodx1 = foodx;
    foodx--;
  }
  if (foodx == 1) { //keeps food inbounds
    foodx1 = 0;
  }
  if (foodx > foodx1) {
    foodx1 = foodx;
    foodx++;
  }
  if (foodx == 158) {
    foodx1 = 159;
  }
  if (foody < foody1) {
    foody1 = foody;
    foody--;
  }
  if (foody == 1) {
    foody1 = 0;
  }
  if (foody > foody1) {
    foody1 = foody;
    foody++;
  }
  if (foody == 78) {
    foody1 = 79;
  }
  if ((foodx <= x + r + 1 && foodx >= x - r -1) && (foody <= y + r + 1 && foody >= y - r -1)) { //detects collision
    r++;
    foodx = random(2, 158);
    foody = random(2, 78);
  }
  if (digitalRead(M5_BUTTON_HOME) == LOW) { //cheat button
    r++;
  }
  if (r == 50) {
    r = 2;
  }
  delay(50);  //set speed of game
}
