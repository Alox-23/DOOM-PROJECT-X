#include "raycaster.h"

Raycaster::Raycaster(int num_rays)
{
    this->num_rays = num_rays;
    this->rays = new Ray[num_rays];
}

Raycaster::~Raycaster()
{
    delete[] rays;
}