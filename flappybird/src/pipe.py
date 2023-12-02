import pygame
from settings import *

class Pipe(pygame.sprite.Sprite):
    def __init__(self, pos, group):
        super().__init__(group)
        self.gap = 400
        self.speed = 3

        img1 = pygame.image.load("img/img/bee_killer.png")
        img1.set_colorkey((255, 255, 255))
        img2 = pygame.image.load("img/img/bee_killer.png")
        img2.set_colorkey((255, 255, 255))

        top = pygame.math.Vector2(pos.x, pos.y - img1.get_height()//2 - self.gap//2)
        bottom = pygame.math.Vector2(pos.x, pos.y + img2.get_height()//2 + self.gap//2)

        self.img = self.join_surf(img1, img2, self.gap)
        self.img.set_colorkey((0,0,0))
        self.rect = self.img.get_rect()
        self.rect.center = pos

        self.mask = pygame.mask.from_surface(self.img)
        self.mask_img = self.mask.to_surface()

    def draw(self, screen):
        """
        screen.blit(self.img1, self.rect1)
        screen.blit(self.img2, self.rect2)
        screen.blit(self.mask_img, self.rect1)
        """
        screen.blit(self.img, self.rect)
    def update(self):
        self.rect.x -= self.speed

    def join_surf(self, surf1, surf2, gap):
        h1 = surf1.get_height()
        w1 = surf1.get_width()
        h2 = surf2.get_height()
        w2 = surf2.get_width()
        g = gap

        a = w1
        b = h1

        C = (0, h1 + g)
        B = (0, 0)

        surf3 = pygame.Surface((w1, h1 + h2 + g))
        surf3.blit(surf1, B)
        surf3.blit(surf2, C)

        return surf3
