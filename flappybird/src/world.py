import pygame
import bird
import pipe
import BirdGroup
import PipeGroup
from settings import *

class World:
    def __init__(self):
        self.birds = BirdGroup.BirdGroup()
        self.pipes = PipeGroup.PipeGroup()
        self.screen = pygame.display.set_mode((WIDTH, HEIGHT))
        self.clock = pygame.time.Clock()
        self.bg = pygame.image.load("img/img/bg.png")
        self.bg.set_colorkey((255, 255, 255))

        for i in range(10):
            bird.Bird(pygame.math.Vector2(175, 300), self.birds)
        pipe.Pipe(pygame.math.Vector2(WIDTH, 300), self.pipes)
        self.font = pygame.font.SysFont('Arial', 20)
        self.display_text = ""
        self.max_score = 0

    def run(self):
        self.update()
        self.draw()

        self.clock.tick(FPS)
    
    def blit_text(self, surface, text, pos, font, color=pygame.Color('black')):
        words = [word.split(' ') for word in text.splitlines()]  # 2D array where each row is a list of words.
        space = font.size(' ')[0]  # The width of a space.
        max_width, max_height = surface.get_size()
        x, y = pos
        for line in words:
            for word in line:
                word_surface = font.render(word, 0, color)
                word_width, word_height = word_surface.get_size()
                if x + word_width >= max_width:
                   x = pos[0]  # Reset the x.
                   y += word_height  # Start on new row.
                surface.blit(word_surface, (x, y))
                x += word_width + space
            x = pos[0]  # Reset the x.
            y += word_height  # Start on new row.

    def update(self):
        self.max_score = self.birds.get_max_scores()
        self.update_display_text()
        self.birds.check_colision_mask(self.pipes)
        self.birds.update()
        self.birds.move()
        self.birds.ai()
        #self.birds.get_input()
        
        if self.birds.extinct() != True:
            self.pipes.update()

    def update_display_text(self):
        self.display_text = ""
        self.display_text += "Number of pipes: " + str(len(self.pipes.sprites())) + "\n"
        self.display_text += "Number of birds: " + str(len(self.birds.sprites())) + "\n"
        self.display_text += "Max score: " + str(self.max_score) + "\n"


    def draw(self):
        self.screen.fill((255, 255, 255))
        self.screen.blit(self.bg, (0,0))
        self.pipes.draw(self.screen)
        self.birds.draw(self.screen)
        self.blit_text(self.screen, self.display_text, (5, 5), self.font)
