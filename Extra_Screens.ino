// Extra Screens
void creditsTick() {
  int input = getUserInput();
  if (input != 0) {
    gameState = MAIN_MENU;
  }
}

void creditsRender() {
  arduboy.clear();
  arduboy.drawBitmap(0,0,CREDITS_SCREEN,128,64,1);
  arduboy.display();
}

void instructionTick() {
  int input = getUserInput();
  if (input != 0) {
    gameState = MAIN_MENU;
  }
}

void instructionRender() {
  arduboy.clear();
  arduboy.drawBitmap(0,0,HOW_TO_PLAY_SCREEN,128,64,1);
  arduboy.display();
}
