// General User input
int getUserInput() {
  if (arduboy.pressed(LEFT_BUTTON)) {
    if (lastButtonPressed == 1) {
      return 0;
    }
    else {
      lastButtonPressed = 1;
      return 1;
    }
  }
  else if (arduboy.pressed(RIGHT_BUTTON)) {
    if (lastButtonPressed == 2) {
      return 0;
    }
    else {
      lastButtonPressed = 2;
      return 2;
    }
  }
  else if (arduboy.pressed(DOWN_BUTTON)) {
    if (lastButtonPressed == 3) {
      return 0;
    }
    else {
      lastButtonPressed = 3;
      return 3;
    }
  }
  else if (arduboy.pressed(UP_BUTTON)) {
    if (lastButtonPressed == 4) {
      return 0;
    }
    else {
      lastButtonPressed = 4;
      return 4;
    }
  }
  else if (arduboy.pressed(A_BUTTON)) {
    if (lastButtonPressed == 5) {
      return 0;
    }
    else {
      lastButtonPressed = 5;
      return 5;
    }
  }
  else if (arduboy.pressed(B_BUTTON)) {
    if (lastButtonPressed == 6) {
      return 0;
    }
    else {
      lastButtonPressed = 6;
      return 6;
    }
  }
  else {
    lastButtonPressed = 0;
    return 0;
  }

}
