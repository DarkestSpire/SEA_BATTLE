// General Game Play

// Setup Enemy Player
void gamePhaseOneEnemyTick() {

  // Turn Off Menu Blue Light
  digitalWrite(BLUE_LED, HIGH);
  
  boolean nextShip;
  // Place ships
  while(true) {
    
    for (int i=0; i<3; i++) {
      // Vertical, Horizontal
      enemyShips[i][2] = random(0,2);
      
      // Vertical
      if (enemyShips[i][2] == 0) {
        // place X
        enemyShips[i][0] = random(0,6);
        //place Y
        enemyShips[i][1] = random(0,7-enemyShips[i][3]);
      }
      // Horizontal
      else {
        // place X
        enemyShips[i][0] = random(0,7-enemyShips[i][3]);
        //place Y
        enemyShips[i][1] = random(0,6);
      }
    }
    
    // Place Ship
    placeShip(enemyBoard, enemyShips);
    if (checkBoard(enemyBoard)) {
      break;
    }
    // Fail - Clear Output
    else {
      for (int i=0; i<6; i++) {
        for (int j=0; j<6; j++) {
          enemyBoard[i][j] = 0;
        }
      }
    }

  } // While(true)
  
  gameState = GAME_PHASE_1;
} // gamePhaseOneEnemyTick()

// Setup the board
void gamePhaseOneTick() {
  int input = getUserInput();
  
  // Move Right
  if (input == 2) {
    // Vertical Check
    if (playerShips[currentShipPlacement][2] == 0 && playerShips[currentShipPlacement][0] < 5) {
      playerShips[currentShipPlacement][0]++;
      moveingCursorSound();
    }
    // Horizontal
    else if (playerShips[currentShipPlacement][2] == 1 && playerShips[currentShipPlacement][0] < 6-playerShips[currentShipPlacement][3] ) {
      playerShips[currentShipPlacement][0]++;
      moveingCursorSound();
    }
  }
  
  // Move Left
  if (input == 1) {
    if ( playerShips[currentShipPlacement][0] > 0) {
      playerShips[currentShipPlacement][0]--;
      moveingCursorSound();
    }
  }

  // Move Down
  if (input == 3) {
    // Vertical Check
    if (playerShips[currentShipPlacement][2] == 0 && playerShips[currentShipPlacement][1] < 6-(playerShips[currentShipPlacement][3]) ) {
      playerShips[currentShipPlacement][1]++;
      moveingCursorSound();
    }
    // Horizontal
    else if (playerShips[currentShipPlacement][2] == 1 && playerShips[currentShipPlacement][1] < 5 ) {
      playerShips[currentShipPlacement][1]++;
      moveingCursorSound();
    }
  }

  // Move Up
  if (input == 4) {
    if ( playerShips[currentShipPlacement][1] > 0) {
      playerShips[currentShipPlacement][1]--;
      moveingCursorSound();
    }
  }

  // Rotate
  if (input == 6) {
    // Vertical to Horizontal
    if (playerShips[currentShipPlacement][2] == 0 && playerShips[currentShipPlacement][0] < 7-playerShips[currentShipPlacement][3]) {
      playerShips[currentShipPlacement][2] = 1;
      moveingCursorSound();
    }
    // Horizontal to Vertical
    else if (playerShips[currentShipPlacement][1] < 7-playerShips[currentShipPlacement][3]) {
      playerShips[currentShipPlacement][2] = 0;
      moveingCursorSound();
    }
  }

  // Next Ship
  if (input == 5) {
    currentShipPlacement++;
    placeShipSound();
    // check if finished
    if (currentShipPlacement > 2) {
      
      // Validate
      placeShip(playerBoard, playerShips);
      if (checkBoard(playerBoard)) {
        gameState = GAME_PHASE_2;
      }
      // Reset
      else {
        for (int i=0; i<6; i++) {
          for (int j=0; j<6; j++) {
            playerBoard[i][j] = 0;
          }
        }
        currentShipPlacement = 0;
      }
      
    }
  }
  
} // gamePhaseOneTick()

// Render Ships
void gamePhaseOneRender() {
  arduboy.clear();
  arduboy.drawBitmap(0,0,GAME_PHASE_1_SCREEN,128,64,1);

  // place pointer
  if (currentShipPlacement == 0) { arduboy.drawBitmap(68,19,POINTER,8,8,1); }
  else if (currentShipPlacement == 1) { arduboy.drawBitmap(86,19,POINTER,8,8,1); }
  else if (currentShipPlacement == 2) { arduboy.drawBitmap(102,19,POINTER,8,8,1); }

  // place ships
  // place two ship
  // Horizontal
  if (playerShips[0][2] == 1) { arduboy.drawBitmap(7+(8*playerShips[0][0]), 8+(8*playerShips[0][1]), SHIP_SIZE_2_HORIZONTIAL, 16, 8); }
  // Vertical
  else { arduboy.drawBitmap(7+(8*playerShips[0][0]), 8+(8*playerShips[0][1]), SHIP_SIZE_2_VERTICAL, 8, 16); }

  // place ship three
  if (currentShipPlacement > 0) {
    // Horizontal
    if (playerShips[1][2] == 1) { arduboy.drawBitmap(7+(8*playerShips[1][0]), 8+(8*playerShips[1][1]), SHIP_SIZE_3_HORIZONTIAL, 24, 8); }
    // Vertical
    else { arduboy.drawBitmap(7+(8*playerShips[1][0]), 8+(8*playerShips[1][1]), SHIP_SIZE_3_VERTICAL, 8, 24); }
  }

  // place ship four
  if (currentShipPlacement > 1) {
    // Horizontal
    if (playerShips[2][2] == 1) { arduboy.drawBitmap(7+(8*playerShips[2][0]), 8+(8*playerShips[2][1]), SHIP_SIZE_4_HORIZONTIAL, 32, 8); }
    // Vertical
    else { arduboy.drawBitmap(7+(8*playerShips[2][0]), 8+(8*playerShips[2][1]), SHIP_SIZE_4_VERTICAL, 8, 32); }
  }

  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, HIGH);
  
  
  arduboy.display();
} // gamePhaseOneRender()


////////////// HELPER /////////////////////

// Place ship
// Place ships for the original board
void placeShip(int board[6][6], int ship[3][4]) {
  for (int i=0; i<3; i++) {
    // Vertical
    if (ship[i][2] == 0) {
      for (int j=0; j<ship[i][3]; j++) {
        board[ship[i][1]+j][ship[i][0]] = ship[i][3];
      }
    }
    // Horizontal
    else {
      for (int j=0; j<ship[i][3]; j++) {
        board[ship[i][1]][ship[i][0]+j] = ship[i][3];
      }
    }
  }
}

// Check Board
// Conferm if board is valid
boolean checkBoard(int board[6][6]) {
  int shipTwo = 0;
  int shipThree = 0;
  int shipFour = 0;

  for (int i=0; i<6; i++) {
    for (int j=0; j<6; j++) {
      if (board[i][j] == 2) {
        shipTwo++;
      }
      else if (board[i][j] == 3) {
        shipThree++;
      }
      else if (board[i][j] == 4) {
        shipFour++;
      }
    }
  }
  if ((shipTwo == 2) && (shipThree == 3) && (shipFour == 4)) {
    return true;
  }
  else {
    return false;
  }
  
}
