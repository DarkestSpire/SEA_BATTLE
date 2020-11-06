// Brady Heater
// 9/24/2020
// Sea Battle

// Includes
#include "Bitmaps_Screens.h" 
#include "Bitmaps_Misc.h" 
#include "Bitmaps_Menu.h" 
#include "Bitmaps_Ships.h" 
#include <Arduboy2.h>
#include <Sprites.h>
#include <ArduboyTones.h>

// Define Gamestates for the overall game
unsigned char gameState;
#define STARTUP 1
#define MAIN_MENU 2
#define INSTRUCTIONS 3
#define CREDITS 4
#define GAME_PHASE_1 5
#define GAME_PHASE_1_ENEMY 6
#define GAME_PHASE_2 7
#define WIN 8
#define LOSE 9

// make an instance of arduboy
Arduboy2Base arduboy;
ArduboyTones sound(arduboy.audio.enabled);
extern ArduboyTones sound;

// Deine for Input
// Button Press
int lastButtonPressed = 0;

// Deine for phase 2
unsigned char gamePhaseStatus;
#define PLAYER_TURN_STATE 1
#define ENEMY_TURN_STATE 2
#define PLAYER_HIT 3
#define ENEMY_HIT 4
#define PLAYER_MISS 5
#define ENEMY_MISS 6
#define PLAYER_SINK 7
#define ENEMY_SINK 8

// Pointer Location [0] -> Y, [1] -> X
int pointer[2] = {0, 0};

// Define for phase 1
// Boards
// 0 -> Nothing
// 2 -> 2 Ship
// 3 -> 3 Ship
// 4 -> 4 Ship
// 5 -> Miss
// 6 -> Hit
int playerBoard[6][6] = { {0, 0, 0, 0, 0, 0}, 
                          {0, 0, 0, 0, 0, 0}, 
                          {0, 0, 0, 0, 0, 0}, 
                          {0, 0, 0, 0, 0, 0}, 
                          {0, 0, 0, 0, 0, 0}, 
                          {0, 0, 0, 0, 0, 0} };

int enemyBoard[6][6] =  { {0, 0, 0, 0, 0, 0}, 
                          {0, 0, 0, 0, 0, 0}, 
                          {0, 0, 0, 0, 0, 0}, 
                          {0, 0, 0, 0, 0, 0}, 
                          {0, 0, 0, 0, 0, 0}, 
                          {0, 0, 0, 0, 0, 0} };

// Boat Placement & information
// [X][0] Location X
// [X][1] Location Y
// [X][2] 0 Vertical, 1 Horizontal
// [X][4] Size, Health
int playerShips[3][4] = { {0, 0, 0, 2}, {0, 0, 0, 3}, {0, 0, 0, 4} };
int enemyShips[3][4] = { {0, 0, 0, 2}, {0, 0, 0, 3}, {0, 0, 0, 4} };

// current Ship in use
int currentShipPlacement = 0;

// Sounds
uint16_t introSong[] = {  NOTE_E3,500, NOTE_REST,500, NOTE_D3,500, NOTE_C3,1000,
                          NOTE_D3,500, NOTE_E3,1000, NOTE_REST,500, NOTE_E3,500, 
                          NOTE_REST,500, NOTE_D3,500, NOTE_C3,1000, NOTE_D3,500,
                          NOTE_B3,500, TONES_END }; // Intro Sound

// Enemy AI
// checkerboard type - to make the AI not seem less mechanical
boolean boardIsEven;

// Setup Everything
void setup() {
  // Testing //
  Serial.begin(9600);

  // Start Arduboy
  arduboy.begin();
  arduboy.initRandomSeed();

  // enable sound
  arduboy.audio.on();

  // LED
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  // Setup Game
  gameState = STARTUP;
}


// Play game
void loop() {
  // Tick
  if (gameState == STARTUP) {
    startupTick();
    startupRender();
  }
  else if (gameState == MAIN_MENU) {
    mainMenuTick();
    mainMinuRender();
  }
  else if (gameState == INSTRUCTIONS) {
    instructionTick();
    instructionRender();
  }
  else if (gameState == CREDITS) {
    creditsTick();
    creditsRender();
  }
  else if (gameState == GAME_PHASE_1) {
    gamePhaseOneTick();
    gamePhaseOneRender();
  }
  else if (gameState == GAME_PHASE_1_ENEMY) {
    gamePhaseOneEnemyTick();
  }
  else if (gameState == GAME_PHASE_2) {
    gamePhaseTwoTick();
    gamePhaseTwoRender();
  }
  else if (gameState == WIN) {
    gameWinRender();
    if (getUserInput() == 5) {
      gameState = STARTUP;
    }
  }
  else if (gameState == LOSE) {
    gameLoseRender();
    if (getUserInput() == 5) {
      gameState = STARTUP;
    }
  }
  else {
    // Test
    arduboy.clear();
    arduboy.drawBitmap(0,0,WIN_SCREEN,128,64,1);
    arduboy.display();
  }
  
}

// FINAL STATES
void gameWinRender() {
  arduboy.clear();
  arduboy.drawBitmap(0,0,WIN_SCREEN,128,64,1);
  arduboy.display();
}

void gameLoseRender() {
  arduboy.clear();
  arduboy.drawBitmap(0,0,LOSE_SCREEN,128,64,1);
  arduboy.display();
}

// Sound Functions
// Play when moving Cursor
void moveingCursorSound() {
  sound.tone(NOTE_CS5, 30);
}

// Play when placing ship
void placeShipSound() {
  sound.tone(NOTE_C4, 30);
}

// Play when hit ship
void hitShipSound() {
  sound.tone(NOTE_A4, 30);
}

// Play when sink ship
void sinkShipSound() {
  sound.tone(NOTE_B4, 30);
}
