import pygame
import pipe
from settings import *

class PipeGroup(pygame.sprite.Group):
    def __init__(self):
        self.pipe_dist = 400
        super().__init__()

    def draw(self, screen):
        for sprite in self.sprites():
            sprite.draw(screen)

    def update(self):
        self.auto_add()
        self.auto_del()
        for sprite in self.sprites():
            sprite.update()

    def auto_del(self):
        for sprite in self.sprites():
            if sprite.rect.x+sprite.img.get_width()+1 < 0:
                sprite.kill()

    def auto_add(self):
        for i, sprite in enumerate(self.sprites()):
            if i == len(self.sprites())-1 and len(self.sprites()) < 2:
                pipe.Pipe(pygame.math.Vector2(self.sprites()[i].rect.x+self.pipe_dist, 300), self)

    def get_rects(self):
        rects = []
        for sprite in self.sprites():
            rects.append(sprite.rect)
        return rects
