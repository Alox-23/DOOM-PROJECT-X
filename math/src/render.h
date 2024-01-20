#include <SFML/Graphics.hpp>

class Render
{
    private:
        sf::RenderWindow* window;
        int wallsToRender;
        int spritesToRender;
    public:
        Render();
        void getWallsToRender();
        void getSpritesToRender();
        void draw();
        void draw2d();
        ~Render();
}