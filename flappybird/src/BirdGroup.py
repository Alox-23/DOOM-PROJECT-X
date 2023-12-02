import pygame
import settings

class BirdGroup(pygame.sprite.Group):
    def __init__(self):
        super().__init__()
        
    def draw(self, screen):
        for sprite in self.sprites():
            sprite.draw(screen)

    def update(self):
        for sprite in self.sprites():
            sprite.update()

    def check_colision_mask(self, pipe_group):
        for sprite in self.sprites():
            if pygame.sprite.spritecollide(sprite, pipe_group, False, pygame.sprite.collide_mask):
                sprite.die()

    def move(self):
        for sprite in self.sprites():
            sprite.move()

    def get_input(self):
        for sprite in self.sprites():
            sprite.get_input()
    
    def ai(self):
        for sprite in self.sprites():
            sprite.ai()

    def extinct(self):
        if len(self.sprites()) == 0:
            return True
        else:
            return False
    
    def get_scores(self):
        scores = []
        for sprite in self.sprites():
            scores.append(sprite.score)

        return scores

    def get_max_scores(self):
        return max(self.get_scores())
