#ifndef RAYCASTER_H
#define RAYCASTER_H

#include <SFML/Graphics.hpp>
#include "ray.h"
#include "sector.h"

class Raycaster
{
    private:
        int num_rays;
        Ray *rays;
    public:
        Raycaster(int num_rays);
        void raycast(Sector sector);
        void draw_rays(sf::RenderWindow *window);
        ~Raycaster();
};
#endif