#ifndef CAMERA_H
#define CAMERA_H

#include "typedef.h"

void UpdateCamera(WORLD world ,CAMERA *camera, USER *user, float deltaTime);
void NewUpdateCamera(WORLD world ,CAMERA *camera, USER *user, float deltaTime);
#endif