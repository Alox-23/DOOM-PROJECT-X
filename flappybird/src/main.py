import pygame
import bird
import pipe
import world
from settings import *

pygame.init()

world = world.World()

running = True
while running:

    world.run()

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
    
    pygame.display.update()

pygame.quit()

