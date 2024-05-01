import pygame
import math
import wall
import ray

"""
if ray.get_collision().x != 0 and ray.get_collision().y != 0:
                distance = math.sqrt(
                    ((self.game.player.rect.centerx - ray.get_collision().x)**2) + 
                    ((self.game.player.rect.centery - ray.get_collision().y)**2)
                )
                distance *= math.cos(math.radians(self.game.player.angle - deg))
                

                proj_height = self.game.renderer.HEIGHT / (distance / 2) + 0.00001

                self.ray_casting_result.append(
                    (distance, proj_height)
                )
            else:
                self.ray_casting_result.append(
                    (None, None)
                )

"""

class Raycaster:
    FOV = 90
    NUM_RAYS = 0
    def __init__(self, game):
        self.rays = []
        self.ray_casting_result = []
        self.game = game 
        self.NUM_RAYS = int(self.game.renderer.WIDTH / self.game.renderer.SCALE)
        for i in range(self.NUM_RAYS):
            self.rays.append(ray.Ray())

    def update(self, sector):
        self.ray_casting_result = []
        deg = self.game.player.angle - self.FOV/2
        increment = self.FOV/(self.NUM_RAYS-1+0.0000001)
        print("LOLOLLLOLLLLOLo")
        for ray in self.rays:
            ray.update(deg, pygame.math.Vector2(self.game.player.rect.centerx, self.game.player.rect.centery))
            for wall in sector.walls:
                ray.check_wall_collide(wall, self.game.player)
                wall.printEquation()

            ray.printEquation()               
            print(ray.get_collision())

            pygame.draw.circle(self.game.renderer.screen, (255, 0, 0), ray.get_collision(), 3)

            ray.draw_2d2(self.game, deg, 1000)
            ray.draw_2d1(self.game, deg, 1)

            if ray.get_collision().x != 0 and ray.get_collision().y != 0:
                distance = math.sqrt(
                    ((self.game.player.rect.centerx - ray.get_collision().x)**2) + 
                    ((self.game.player.rect.centery - ray.get_collision().y)**2)
                )
                distance *= math.cos(math.radians(self.game.player.angle - deg))

                proj_height = self.game.renderer.HEIGHT / (distance / 2) + 0.00001

                self.ray_casting_result.append(
                    (distance, proj_height)
                )
            else:
                self.ray_casting_result.append(
                    (None, None)
                )

            deg += increment
            ray.reset_wall_collision_for_next_check()
        self.ray_casting_result.reverse()

    def get_raycasting_result(self):
        return self.ray_casting_result

    def draw_rays(self, screen):
        for i, ray in enumerate(self.walls):
            ray.draw(screen, self.player.rect.center)