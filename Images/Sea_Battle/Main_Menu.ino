int pointerLocation = 1;
unsigned long missileCounter = 0;

void mainMenuTick() {
  int input = getUserInput();
  // Moving Location
  if (input == 3 && pointerLocation == 1) {
    pointerLocation = 2;
    moveingCursorSound();
  }
  else if (input == 3 && pointerLocation == 2) {
    pointerLocation = 3;
    moveingCursorSound();
  }
  else if (input == 3 && pointerLocation == 3) {
    pointerLocation = 4;
    moveingCursorSound();
  }
  else if (input == 4 && pointerLocation == 4) {
    pointerLocation = 3;
    moveingCursorSound();
  }
  else if (input == 4 && pointerLocation == 3) {
    pointerLocation = 2;
    moveingCursorSound();
  }
  else if (input == 4 && pointerLocation == 2) {
    pointerLocation = 1;
    moveingCursorSound();
  }

  // Play Game
  else if (input == 5 && pointerLocation == 1) {
    gameState = GAME_PHASE_1_ENEMY;
  }

  // Music Option
  else if (input == 5 && pointerLocation == 2) {
    if (arduboy.audio.enabled()) {
      arduboy.audio.off();
    }
    else {
      arduboy.audio.on();
    }
  }

  // Credits
  else if (input == 5 && pointerLocation == 3) {    
    gameState = CREDITS;
  }
  
  // How To Play
  else if (input == 5 && pointerLocation == 4) {
    gameState = INSTRUCTIONS;
  }
  
  
  
}

void mainMinuRender() {
  arduboy.clear();
  arduboy.drawBitmap(0,0,MENU_SCREEN,128,64,1);

  // Load image based on pointer location
  if (pointerLocation == 1) {
    arduboy.drawBitmap(3,6,POINTER,8,8,1);
    arduboy.drawBitmap(76,8,ANCHOR,48,48,1);
  }
  else if (pointerLocation == 2) {
    arduboy.drawBitmap(3,14,POINTER,8,8,1);
    arduboy.drawBitmap(76,8,MUSIC_NOTE,48,48,1);
  }
  else if (pointerLocation == 3) {
    arduboy.drawBitmap(3,22,POINTER,8,8,1);
    arduboy.drawBitmap(76,8,LIGHTHOUSE,48,48,1);
  }
  else {
    arduboy.drawBitmap(3,30,POINTER,8,8,1);
    arduboy.drawBitmap(76,8,COMPASS_ROSE,48,48,1);
  }

  // Load image based on sound
  if (arduboy.audio.enabled()) {
    arduboy.drawBitmap(28,14,ON,16,8,1);
  }
  else {
    arduboy.drawBitmap(28,14,OFF,16,8,1);
  }

  // Load image for missle
  if (millis() - missileCounter < 100) {
    arduboy.drawBitmap(2,46,MISSILE_1_1,64,16,1);
  }
  else if (millis() - missileCounter < 200) {
    arduboy.drawBitmap(2,46,MISSILE_1_2,64,16,1);
  }
  else if (millis() - missileCounter < 300) {
    arduboy.drawBitmap(2,46,MISSILE_1_3,64,16,1);
  }
  else if (millis() - missileCounter < 400) {
    arduboy.drawBitmap(2,46,MISSILE_2_1,64,16,1);
  }
  else if (millis() - missileCounter < 500) {
    arduboy.drawBitmap(2,46,MISSILE_2_2,64,16,1);
  }
  else {
    arduboy.drawBitmap(2,46,MISSILE_2_3,64,16,1);
    // Reset
    missileCounter = millis();
    
  }
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(BLUE_LED, LOW);
  arduboy.display();
}
