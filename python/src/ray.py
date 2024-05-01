import pygame
import math

class Ray:
    def __init__(self):
        self.slope = 0
        self.intercept = 0
        self.wall_collision = pygame.math.Vector2()
        self.wall_collision.x = 0
        self.wall_collision.y = 0

    def draw(self, screen, pos):
        pygame.draw.line(screen, (255,0,0), (pos.x, pos.y), self.wall_collision, 1)

    def update(self, deg, pos):
        if deg == 90 or deg == 270:
            self.slope = None
            self.intercept = pos.x
        elif deg == 0 or deg == 180:
            self.slope = 0
            self.intercept = pos.y
        else:
            self.slope = math.tan(math.radians(deg))
            self.intercept = self.slope * pos.x  + pos.y

    def check_wall_collide(self, wall, player):
        wall_collision = pygame.math.Vector2()
        wall_collision.x = 0
        wall_collision.y = 0
        print("ahah")
        if self.slope == None and wall.slope == None:
            wall_collision.x = wall.intercept
            wall_collision.y = self.slope * wall.intercept + self.intercept
        elif self.slope == None:
            wall_collision.x = self.intercept
            wall_collision.y = wall.slope * self.intercept + wall.intercept
        elif wall.slope == None:
            return 0
        else:

            wall_collision.x = (wall.intercept - self.intercept)/((self.slope - wall.slope)+0.00001)
            wall_collision.y = self.slope * wall_collision.x + self.intercept
 
        #check if the wall_colision is insode of the wall or not
        #if wall_collision.y > wall.pos[1].y and wall_collision.y < wall.pos[0].y and wall_collision.x > wall.pos[0].x and wall_collision.x < wall.pos[1].x:
        self.wall_collision.x = wall_collision.x
        self.wall_collision.y = wall_collision.y
            
        return self.wall_collision
    
    def set_equation(self, slope, intercept):
        self.slope = slope
        self.intercept = intercept
        return self

    def reset_wall_collision_for_next_check(self):
        self.wall_collision.x = 0
        self.wall_collision.y = 0

    def get_collision(self):
        return self.wall_collision

    def printEquation(self):
        if self.slope != None:
            print("y =", self.slope, "x +", self.intercept)
        else:
            print("x =", self.intercept)

    def draw_2d(self, game, deg, d):
        pygame.draw.line(game.renderer.screen, (255, 255, 255),game.player.rect.center, (game.player.rect.centerx + d * math.cos(math.radians(-deg)), game.player.rect.centery + d * math.sin(math.radians(-deg))), 1)
        #pygame.draw.line(game.renderer.screen, (255, 255, 255),game.player.rect.center, (self.get_collision().x, self.get_collision().y), 1)