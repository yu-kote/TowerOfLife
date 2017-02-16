#pragma once
#include "cinder/app/App.h"

enum WindowSize
{
    WIDTH = 1440,
    HEIGHT = 900,
};

bool sphereToSphere(ci::Vec3f pos1_, float radius1_, ci::Vec3f pos2_, float radius2_);