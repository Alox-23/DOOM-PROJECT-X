import pygame
import math

class Wall:
    def __init__(self, cords):
        self.pos = cords
        self.slope = 0
        self.intercept = 0
        self.calculateEquation()

    def draw(self, screen):
        pygame.draw.line(screen, (255,255,255), self.pos[0], self.pos[1], 5)

    def calculateEquation(self): 
        if self.pos[0].x != self.pos[1].x:
            self.slope = (self.pos[1].y - self.pos[0].y) / (self.pos[1].x - self.pos[0].x)
            self.intercept = self.pos[0].y - self.slope * self.pos[0].x
        else:
            self.slope = None
            self.intercept = self.pos[0].x

    def printEquation(self):
        if self.slope != None:

            print("y =", self.slope, "x +", self.intercept)
        else:
            print("x =", self.intercept)