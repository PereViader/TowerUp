#pragma once

// Size of the window  in pixels
const int WINDOW_WIDTH = 720;
const int WINDOW_HEIGHT = 1280;

// blocks are BLOCK_SIZE x BLOCK_SIZE in size
const float BLOCK_SIZE = 80.0f; 

// from the center to each side, if the block falls within this margin, the block will stack on the middle
// otherwise it will stack on the side
// This means that this value must be <= BLOCK_SIZE/2.0f
// because the margin can't be bigger than the block itself
const float CENTER_BLOCK_STACK_MARGIN = 15;

// Cooldown that must be wait between each block placement
const float TIME_BETWEEN_BLOCKS = 1;

//Speed of the camera when it moves after placing each block
const float CAMERA_SPEED = 5;

//Swing parameters
//Angle the swing moves from-to
const float SWING_ANGLE = 120; // angle must be >= 0 && <= 180
const float SWING_SPEED = 60;
const float SWING_LENGHT = 300;  // swing lenght must be > 0 && < WINDOW_WIDTH
const float SWING_WIDTH = 20;

//Falling velocity of the blocks
const float BLOCK_VELOCITY = 400;