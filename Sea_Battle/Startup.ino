// First Startup

void startupTick() {
  // Wait for startup
  if (getUserInput() == 5) {
    // Reset Boards
    for (int i=0; i<6; i++) {
      for (int j=0; j<6; j++) {
        enemyBoard[i][j] = 0;
        playerBoard[i][j] = 0;
      }
    }
    // Reset Ships
    for (int i=0; i<3; i++) {
      for (int j=0; j<3; j++) {
        playerShips[i][j] = 0;
        enemyShips[i][j] = 0;
      } 
    }
    for (int i=0; i<3; i++) {
      playerShips[i][3] = i+2;
      enemyShips[i][3] = i+2;
    }

    // current Ship in use
    currentShipPlacement = 0;

    // Choose who goes first - image GamePhase2
    if (random(0,2) == 0) { gamePhaseStatus = PLAYER_TURN_STATE; }
    else                  { gamePhaseStatus = ENEMY_TURN_STATE; }

    // Choose checkerboard patter - Enemy AI
    if (random(0,2) == 0) { boardIsEven = true; }
    else                  { boardIsEven = false; }

    // Kill Sound
    sound.tone(NOTE_REST);
    
    gameState = MAIN_MENU;
  }

  // Play Intro Song
  if (!sound.playing()) {
    sound.tonesInRAM(introSong);
  }
  
  
}


void startupRender() {
  arduboy.clear();
  arduboy.drawBitmap(0,0,TITLE_SCREEN,128,64,1);
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(BLUE_LED, HIGH);
    
  if (millis() - clockCounter < 400) {
    
  }
  else if (millis() - clockCounter < 800) {
    arduboy.drawBitmap(9,23,PRESS_A,32,8,1);
    digitalWrite(BLUE_LED, LOW);
  }
  else {
    clockCounter = millis();
  }
  
  arduboy.display();
}
