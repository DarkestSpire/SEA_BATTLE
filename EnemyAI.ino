// This is the Enemy AI

/*
 * For this AI if the AI has not has a previous hit, it will guess in a random checkerboard pattern
 * If it gets a hit, the AI will start guesing in a drirection until it gets a sink
 * once it sinks it will continue to guess in a checkerboard pattern
 */

// Pointer Location [0] -> Y, [1] -> X
int enemyPointer[2];
// Enemy Shot Outcome
int enemyShot = 0;

// Enemy important memory
// This will lead the AI back for finding the full ship
int enemyPointerOriginalHit[2];
boolean hitShipLookingForSink = false;
// 0 -> Up
// 1 -> Down
// 2 -> Left
// 3 -> Right
int searchDirection = 0;
int enemyHits = 0;

// There is a possible chance to be locked out this it to prevent the AI from doing so;
int lockedNum;

// Run this function on Enemy Turn
void enemyAI() {
  // reset Shot
  enemyShot = 0;

  // Follow up a hit ship check all four directions, if no find give up
  while (hitShipLookingForSink) {

    // Check all directions
    // Up + how many hits
    if (searchDirection == 0 && enemyPointerOriginalHit[0] - enemyHits >= 0) {
      enemyPointer[0] = enemyPointerOriginalHit[0] - enemyHits;
      enemyPointer[1] = enemyPointerOriginalHit[1];
      enemyShot = shootHere(playerBoard, playerShips, enemyPointer);
    }
    // Down + how many hits
    else if (searchDirection == 1 && enemyPointerOriginalHit[0] + enemyHits <= 5) {
      enemyPointer[0] = enemyPointerOriginalHit[0] + enemyHits;
      enemyPointer[1] = enemyPointerOriginalHit[1];
      enemyShot = shootHere(playerBoard, playerShips, enemyPointer);
    }
    // Left + how many hits
    else if (searchDirection == 2 && enemyPointerOriginalHit[1] - enemyHits >= 0) {
      enemyPointer[0] = enemyPointerOriginalHit[0];
      enemyPointer[1] = enemyPointerOriginalHit[1] - enemyHits;
      enemyShot = shootHere(playerBoard, playerShips, enemyPointer);
    }
    // Right + how many hits
    else if (searchDirection == 3 && enemyPointerOriginalHit[1] + enemyHits <= 5) {
      enemyPointer[0] = enemyPointerOriginalHit[0];
      enemyPointer[1] = enemyPointerOriginalHit[1] + enemyHits;
      enemyShot = shootHere(playerBoard, playerShips, enemyPointer);
    }
    // Prevent possible issue
    else if (searchDirection > 3) {
      hitShipLookingForSink = false;
      searchDirection = 0;
    }

    // save for the AI
    // MISS
    if (enemyShot == 1) {
      enemyHits = 1;
      searchDirection++;
      break;
    }
    // Not Valid
    else if (enemyShot == 0) {
      enemyHits = 1;
      searchDirection++;
    }
     // HIT or SINK
    else if (enemyShot == 2 | enemyShot == 3) {
      break;
    }
  }
    
  // Guess in a checker pattern if no leads
  lockedNum = 0; // Reset Checker
  while(enemyShot == 0) {
    // Even Style
    if (boardIsEven && lockedNum < 100) {
      // Guess
      enemyPointer[0] = random(0, 6);
      enemyPointer[1] = (enemyPointer[0]%2) + random(0, 3)*2;
      enemyShot = shootHere(playerBoard, playerShips, enemyPointer);

      // Prevent Lock
      lockedNum++;
    }
    // Odd Style
    else if (!boardIsEven && lockedNum < 100) {
      enemyPointer[0] = random(0, 6);
      enemyPointer[1] = ((random(0, 3)*2)+1) - (enemyPointer[0]%2);
      enemyShot = shootHere(playerBoard, playerShips, enemyPointer);

      // Prevent Lock
      lockedNum++;
      
    }
    // Prevent Locked
    else {
      enemyPointer[0] = random(0, 6);
      enemyPointer[1] = random(0, 6);
      enemyShot = shootHere(playerBoard, playerShips, enemyPointer);
    }

    // Save results for the init pointer
    if (enemyShot == 2) {
      enemyPointerOriginalHit[0] = enemyPointer[0];
      enemyPointerOriginalHit[1] = enemyPointer[1];
    }

    
    
  } // while(enemyShot == 0)
  
  // Update Outcomes at the end
  // MISS
  if (enemyShot == 1) {
    gamePhaseStatus = ENEMY_MISS;
  }
  // HIT
  else if (enemyShot == 2) {
    hitShipSound();
    gamePhaseStatus = ENEMY_HIT;

    // Save Results to keep the location
    hitShipLookingForSink = true;
    enemyHits++;
  }
  // SINK
  else if (enemyShot == 3) {
    sinkShipSound();
    gamePhaseStatus = ENEMY_SINK;

    // Reset AI search
    hitShipLookingForSink = false;
    enemyHits = 0;
    searchDirection = 0;

    // End Game
    if (checkForAllSunk(playerBoard)) {
      clockCounter = millis(); // Update clock to hold the screen
      gameState = LOSE;
    }
    
  }
  
}
