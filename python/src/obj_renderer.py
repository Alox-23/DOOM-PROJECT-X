import pygame
import math

class Obj_renderer:
    FOV = 90
    RES = WIDTH, HEIGHT = 1200, 700
    SCALE = 2
    FPS = 60
    SCREEN_DIST = WIDTH // 2 / math.tan(math.radians(FOV // 2))
    screen = pygame.display.set_mode(RES)
    
    def __init__(self, game):
        self.game = game

    def draw(self):
        for ray, ray_info in enumerate(self.game.raycaster.get_raycasting_result()):
            if ray_info[1] == None:
                continue
            wall_column = pygame.Surface((self.SCALE, ray_info[1]))
            wall_column.fill((255, 255, 255))

            self.screen.blit(wall_column, (ray*self.SCALE, self.HEIGHT//2 - ray_info[1]))