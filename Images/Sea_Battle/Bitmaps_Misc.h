// Misc

unsigned char const ENEMY_TURN[] PROGMEM =
{
  // 48, 8
  0x00, 0x00, 0x3e, 0x2a, 0x22, 0x00, 0x3e, 0x04, 
  0x08, 0x10, 0x3e, 0x00, 0x3e, 0x2a, 0x22, 0x00, 
  0x3c, 0x02, 0x3c, 0x02, 0x3c, 0x00, 0x06, 0x38, 
  0x06, 0x00, 0x00, 0x00, 0x02, 0x3e, 0x02, 0x00, 
  0x3e, 0x20, 0x3e, 0x00, 0x3e, 0x0a, 0x34, 0x00, 
  0x3e, 0x04, 0x08, 0x10, 0x3e, 0x00, 0x00, 0x00, 
};

unsigned char const HIT[] PROGMEM =
{
  // 32, 8
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x3e, 0x08, 0x3e, 0x00, 0x22, 
  0x3e, 0x22, 0x00, 0x02, 0x3e, 0x02, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

unsigned char const HIT_MARKER[] PROGMEM =
{
  // 8, 8
  0x62, 0x89, 0x30, 0x4a, 0x94, 0xaa, 0x44, 0x29, 
};

unsigned char const MARKER[] PROGMEM =
{
  // 8, 8
  0xe7, 0x81, 0x81, 0x00, 0x00, 0x81, 0x81, 0xe7, 
};

unsigned char const MISS[] PROGMEM =
{
  // 32, 8
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 
  0x02, 0x3c, 0x02, 0x3c, 0x00, 0x22, 0x3e, 0x22, 
  0x00, 0x24, 0x2a, 0x12, 0x00, 0x24, 0x2a, 0x12, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

unsigned char const MISS_MARKER[] PROGMEM =
{
  // 8, 8
  0x00, 0x00, 0x24, 0x18, 0x18, 0x24, 0x00, 0x00, 
};

unsigned char const NOT_VALID[] PROGMEM =
{
  // 32, 8
  0x3e, 0x04, 0x08, 0x3e, 0x00, 0x1c, 0x22, 0x1c, 
  0x00, 0x02, 0x3e, 0x02, 0x00, 0x00, 0x1e, 0x20, 
  0x1e, 0x00, 0x3c, 0x0a, 0x3c, 0x00, 0x3e, 0x20, 
  0x00, 0x22, 0x3e, 0x22, 0x00, 0x3e, 0x22, 0x1c, 
};

unsigned char const POINTER[] PROGMEM =
{
  // 8, 8
  0x00, 0x00, 0x00, 0x3e, 0x1c, 0x08, 0x00, 0x00, 
};

unsigned char const PRESS_A[] PROGMEM =
{
  // 32, 8
  0x00, 0x3e, 0x0a, 0x04, 0x00, 0x3e, 0x0a, 0x34, 
  0x00, 0x3e, 0x2a, 0x22, 0x00, 0x24, 0x2a, 0x12, 
  0x00, 0x24, 0x2a, 0x12, 0x00, 0x00, 0x00, 0x3c, 
  0x0a, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

unsigned char const SINK[] PROGMEM =
{
  // 32, 8
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x2a, 
  0x12, 0x00, 0x22, 0x3e, 0x22, 0x00, 0x3e, 0x04, 
  0x08, 0x10, 0x3e, 0x00, 0x3e, 0x08, 0x36, 0x00, 
  0x00, 0x00, 0x2e, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

unsigned char const YOUR_TURN[] PROGMEM =
{
  // 48, 8
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 
  0x38, 0x06, 0x00, 0x1c, 0x22, 0x1c, 0x00, 0x3e, 
  0x20, 0x3e, 0x00, 0x3e, 0x0a, 0x34, 0x00, 0x00, 
  0x00, 0x02, 0x3e, 0x02, 0x00, 0x3e, 0x20, 0x3e, 
  0x00, 0x3e, 0x0a, 0x34, 0x00, 0x3e, 0x04, 0x08, 
  0x10, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};