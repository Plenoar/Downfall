
#ifndef CONSTANTS_H
#define CONSTANTS_H

//This means each update happens every 0.00625 seconds (6.25ms).
#define FIXED_TIME_STEP (1.0f / 160.0f) // 160 updates per second

#define WINDOW_WIDTH 1700
#define WINDOW_HEIGHT 1000

#define WORLD_WIDTH 10000
#define WORLD_HEIGHT 2000

static const float PIXELS_PER_METER = 1000.0f;
static const float METERS_PER_PIXEL = 1.0f / PIXELS_PER_METER;
static const float PIXELS_PER_CM = 10.0f;
static const float CM_PER_PIXEL = 1.0f / PIXELS_PER_CM;
static const float CM_PER_METER = 100.0f;
static const float METERS_PER_CM = 1.0f / CM_PER_METER;
static const float KILOMETER = 1000000.0f;

#endif


