void gamePhaseTwoTick() {

  playerBoard;

  // Player Turn
  if (gamePhaseStatus == PLAYER_TURN_STATE ) {
    // Move Cursor
    int input = getUserInput();
    // Move Right
    if      (input == 2 && pointer[1] < 5) { pointer[1]++; moveingCursorSound(); }
    // Move Left
    else if (input == 1 && pointer[1] > 0) { pointer[1]--; moveingCursorSound(); }
    // Move Down
    else if (input == 3 && pointer[0] < 5) { pointer[0]++; moveingCursorSound(); }
    // Move Up
    else if (input == 4 && pointer[0] > 0) { pointer[0]--; moveingCursorSound(); }

    // Shoot
    else if (input == 5) {
      // Check if it a ship is HIT
      int shoot = shootHere(enemyBoard, enemyShips, pointer);
      if (shoot == 2 ) {
        hitShipSound();
        gamePhaseStatus = PLAYER_HIT;
      }
      // Check if it a ship is SUNK
      else if (shoot == 3 ) {
        sinkShipSound();
        gamePhaseStatus = PLAYER_SINK;
        if (checkForAllSunk(enemyBoard)) {
          gameState = WIN;
        }
      }
      // Check if it a ship is MISS
      else if (shoot == 1 ) {
        gamePhaseStatus = PLAYER_MISS;
      } 
    }

  } // gamePhaseStatus == PLAYER_TURN_STATE
  
  // Enemy Turn
  else if (gamePhaseStatus == ENEMY_TURN_STATE) {
    delay(500);
    enemyAI();
  } // gamePhaseStatus == ENEMY_TURN_STATE

  // Player Status
  else if (gamePhaseStatus == PLAYER_MISS){ 
    if (getUserInput() == 5) {
      gamePhaseStatus = ENEMY_TURN_STATE;
    }
  }
  else if (gamePhaseStatus == PLAYER_HIT | gamePhaseStatus == PLAYER_SINK){ 
    if (getUserInput() == 5) {
      gamePhaseStatus = PLAYER_TURN_STATE;
    }
  }
  // Enemy Status
  else if (gamePhaseStatus == ENEMY_MISS){ 
    if (getUserInput() == 5) {
      gamePhaseStatus = PLAYER_TURN_STATE;
    }
  }
  // Enemy Status
  else if (gamePhaseStatus == ENEMY_HIT | gamePhaseStatus == ENEMY_SINK){ 
    if (getUserInput() == 5) {
      gamePhaseStatus = ENEMY_TURN_STATE;
    }
  }

} // gamePhaseTwoTick()


// Display Screen to User
void gamePhaseTwoRender() {
  arduboy.clear();
  arduboy.drawBitmap(0,0,GAME_PHASE_2_SCREEN,128,64,1);

  // Marker Location
  arduboy.drawBitmap(72+(8*pointer[1]), 4+(8*pointer[0]), MARKER, 8, 8);
  
  // Player Ships
  // place two ship
  // Horizontal
  if (playerShips[0][2] == 1) { arduboy.drawBitmap(7+(8*playerShips[0][0]), 4+(8*playerShips[0][1]), SHIP_SIZE_2_HORIZONTIAL, 16, 8); }
  // Vertical
  else { arduboy.drawBitmap(7+(8*playerShips[0][0]), 4+(8*playerShips[0][1]), SHIP_SIZE_2_VERTICAL, 8, 16); }
  // place ship three
  // Horizontal
  if (playerShips[1][2] == 1) { arduboy.drawBitmap(7+(8*playerShips[1][0]), 4+(8*playerShips[1][1]), SHIP_SIZE_3_HORIZONTIAL, 24, 8); }
  // Vertical
  else { arduboy.drawBitmap(7+(8*playerShips[1][0]), 4+(8*playerShips[1][1]), SHIP_SIZE_3_VERTICAL, 8, 24); }
  // place ship four
  // Horizontal
  if (playerShips[2][2] == 1) { arduboy.drawBitmap(7+(8*playerShips[2][0]), 4+(8*playerShips[2][1]), SHIP_SIZE_4_HORIZONTIAL, 32, 8); }
  // Vertical
  else { arduboy.drawBitmap(7+(8*playerShips[2][0]), 4+(8*playerShips[2][1]), SHIP_SIZE_4_VERTICAL, 8, 32); }

  // Hit or Miss (I guess they never miss huh) Markers
  for (int i=0; i<6; i++) {
    for (int j=0; j<6; j++) {
      // Player Misses
      if (playerBoard[i][j] == 5)       { arduboy.drawBitmap(7+(8*j), 4+(8*i), MISS_MARKER, 8, 8); }
      // Player Hits - Clear space first
      else if (playerBoard[i][j] == 6)  { arduboy.fillRect(7+(8*j), 4+(8*i), 8, 8, 0); 
                                          arduboy.drawBitmap(7+(8*j), 4+(8*i), HIT_MARKER, 8, 8); } 
      // Enemy Misses
      if (enemyBoard[i][j] == 5)        { arduboy.drawBitmap(72+(8*j), 4+(8*i), MISS_MARKER, 8, 8); }
      // Enemy Hit
      else if (enemyBoard[i][j] == 6)   { arduboy.drawBitmap(72+(8*j), 4+(8*i), HIT_MARKER, 8, 8);} 
    }
  }

  // Display State
  switch (gamePhaseStatus) {
    case PLAYER_TURN_STATE:
      arduboy.drawBitmap(73, 56, YOUR_TURN, 48, 8);
      digitalWrite(RED_LED, HIGH);
      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(BLUE_LED, HIGH);
      break;
    case ENEMY_TURN_STATE:
      arduboy.drawBitmap(8, 56, ENEMY_TURN, 48, 8);
      digitalWrite(RED_LED, HIGH);
      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(BLUE_LED, HIGH);
      break;
    case PLAYER_HIT:
      arduboy.drawBitmap(81, 56, HIT, 32, 8);
      digitalWrite(RED_LED, HIGH);
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(BLUE_LED, HIGH);
      break;
    case ENEMY_HIT:
      arduboy.drawBitmap(16, 56, HIT, 32, 8);
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(BLUE_LED, HIGH);
      break;
    case PLAYER_MISS:
      arduboy.drawBitmap(81, 56, MISS, 32, 8);
      digitalWrite(RED_LED, HIGH);
      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(BLUE_LED, LOW);
      break;
    case ENEMY_MISS:
      arduboy.drawBitmap(16, 56, MISS, 32, 8);
      digitalWrite(RED_LED, HIGH);
      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(BLUE_LED, LOW);
      break;
    case PLAYER_SINK:
      arduboy.drawBitmap(81, 56, SINK, 32, 8);
      digitalWrite(RED_LED, HIGH);
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(BLUE_LED, HIGH);
      break;
    case ENEMY_SINK:
      arduboy.drawBitmap(16, 56, SINK, 32, 8);
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(BLUE_LED, HIGH);
      break;
  }

  arduboy.display();

  //shipData(); // TESTING //
}

//////////////////// HELPER FUNCTIONS //////////////////////
// 1 -> MISS
// 2 -> HIT
// 3 -> SINK
// 0 -> NOT VALID
int shootHere(int board[6][6], int ship[3][4], int location[2]) {
  // Check if HIT on 2 Ship
  if (board[location[0]][location[1]] == 2) {
    board[location[0]][location[1]] = 6; // place hit marker
    // Reduce and check
    ship[0][3]--;
    if (ship[0][3] == 0) { return 3; } // SINK
    else { return 2; } // HIT 
  }
  // Check if HIT on 3 Ship
  else if (board[location[0]][location[1]] == 3) {
    board[location[0]][location[1]] = 6; // place hit marker
    // Reduce and check
    ship[1][3]--;
    if (ship[1][3] == 0) { return 3; } // SINK
    else { return 2; } // HIT 
  }
  // Check if HIT on 4 Ship
  else if (board[location[0]][location[1]] == 4) {
    board[location[0]][location[1]] = 6; // place hit marker
    // Reduce and check
    ship[2][3]--;
    if (ship[2][3] == 0) { return 3; } // SINK
    else { return 2; } // HIT 
  }
  // Check is Miss
  else if (board[location[0]][location[1]] == 0) {
    board[location[0]][location[1]] = 5;
    return 1; // MISS
  }
  
  // NOT VALID
  return 0;
}


// Scan the board and return true if all are sunk
boolean checkForAllSunk (int board[6][6]) {
  for (int i=0; i<6; i++) {
    for (int j=0; j<6; j++) {
      if (board[i][j] == 2 | board[i][j] == 3 | board[i][j] == 4) {
        return false; //There is still more ship
      }
    }
  }
  
  return true; // All Ships are gone
  
}

// Test raw ship data
void shipData() {
  //////////////// TESTING //////////////////////
  Serial.println();
  Serial.println("Player: ");
  for (int i=0; i<6; i++) {
    for (int j=0; j<6; j++) {
      Serial.print(playerBoard[i][j]);
      Serial.print("\t");
    }
    Serial.println();
  }
  Serial.print("Ship 2: ");
  for (int i=0; i<4; i++) {
    Serial.print(playerShips[0][i]);
  }
  Serial.println();
  Serial.print("Ship 3: ");
  for (int i=0; i<4; i++) {
    Serial.print(playerShips[1][i]);
  }
  Serial.println();
  Serial.print("Ship 4: ");
  for (int i=0; i<4; i++) {
    Serial.print(playerShips[2][i]);
  }
  Serial.println();
  Serial.println();
  Serial.println("Enemy: ");
  for (int i=0; i<6; i++) {
    for (int j=0; j<6; j++) {
      Serial.print(enemyBoard[i][j]);
      Serial.print("\t");
    }
    Serial.println();
  }
  Serial.print("Ship 2: ");
  for (int i=0; i<4; i++) {
    Serial.print(enemyShips[0][i]);
  }
  Serial.println();
  Serial.print("Ship 3: ");
  for (int i=0; i<4; i++) {
    Serial.print(enemyShips[1][i]);
  }
  Serial.println();
  Serial.print("Ship 4: ");
  for (int i=0; i<4; i++) {
    Serial.print(enemyShips[2][i]);
  }
  /////////////////// TESTING //////////////////////
}
