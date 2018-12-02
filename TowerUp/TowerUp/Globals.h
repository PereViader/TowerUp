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