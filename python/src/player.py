import pygame
import math

class Player:
    PLAYER_SPEED = 0.5
    PLAYER_ROT_SPEED = 5
    def __init__(self, game):
        self.game = game

        self.angle = 0
        
        self.image = pygame.image.load("assets/arrow2.png")
        self.rect = self.image.get_rect()
        self.rect.center = (350, 250)

    def draw(self):
        self.game.screen.blit(pygame.transform.rotate(self.image, self.angle-90), self.rect)

    def update(self):
        sin_a = math.sin(math.radians(-self.angle))
        cos_a = math.cos(math.radians(-self.angle))
        dx, dy = 0, 0
        speed = self.PLAYER_SPEED * self.game.delta_time
        speed_sin = speed * sin_a
        speed_cos = speed * cos_a

        keys = pygame.key.get_pressed()
        if keys[pygame.K_q]:
            self.rect.center = (250, 350)
        if keys[pygame.K_w]:
            dx += speed_cos
            dy += speed_sin
        if keys[pygame.K_s]:
            dx += -speed_cos
            dy += -speed_sin
        if keys[pygame.K_a]:
            dx += speed_sin
            dy += -speed_cos
        if keys[pygame.K_d]:
            dx += -speed_sin
            dy += speed_cos

        if keys[pygame.K_LEFT]:
            self.angle += self.PLAYER_ROT_SPEED
        if keys[pygame.K_RIGHT]:
            self.angle -= self.PLAYER_ROT_SPEED

        self.rect.centerx += dx
        self.rect.centery += dy

        
        if self.angle > 360:
            self.angle = self.angle - 360;

        if self.angle < 0:
            self.angle = 360 - self.angle;
