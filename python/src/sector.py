import pygame
import math
import wall

class Sector:
    def __init__(self, cords):
        self.walls = []
        for wall_cords in cords:
            self.walls.append(wall.Wall(wall_cords))
        
    def draw_walls(self, screen):
        for i, wall in enumerate(self.walls):
            print(f"{i}: ", end = "")
            wall.printEquation()
            wall.draw(screen)