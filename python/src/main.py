import pygame
import game

if __name__ == "__main__":
    pygame.font.init()
    pygame.display.init()
    g = game.Game()
    g.mainloop()