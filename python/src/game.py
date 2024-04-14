import pygame
import player
import sector

class Game:
    def __init__(self):
        self.delta_time = 0

        self.screen = pygame.display.set_mode((1200, 700))
        self.clock = pygame.time.Clock()
        pygame.font.init()
        self.font = pygame.font.SysFont("Comic Sans MS", 30)
        self.debug_text = ""
        self.debug_text_surf = self.font.render(self.debug_text, False, (0,0,0))

        self.sector = sector.Sector(
            [
                [pygame.math.Vector2(50, 350), pygame.math.Vector2(350, 50)],
                [pygame.math.Vector2(350, 50), pygame.math.Vector2(850, 50)],
                [pygame.math.Vector2(850, 50), pygame.math.Vector2(1150, 350)],
                [pygame.math.Vector2(1150, 350), pygame.math.Vector2(850, 650)],
                [pygame.math.Vector2(850, 650), pygame.math.Vector2(350, 650)],
                [pygame.math.Vector2(350, 650), pygame.math.Vector2(50, 350)]
            ]
        )
        self.player = player.Player(self)

    def mainloop(self):
        running = True
        while running:
            running = self.handle_quit()

            self.update()

            self.draw()

        pygame.quit()
        quit()

    def update(self):
        self.player.update()

        self.debug_text = ""
        self.debug_text += "player angle: " + str(self.player.angle) + "-----"
        self.debug_text += "player pos: " + str(self.player.rect.centerx) + ", " + str(self.player.rect.centery) + "-----"
        self.debug_text_surf = self.font.render(self.debug_text, False, (0,255,0))

        self.delta_time = self.clock.tick(60)

    def draw(self):
        self.screen.fill((26, 26, 26))

        self.sector.draw_walls(self.screen)

        self.player.draw()

        self.screen.blit(self.debug_text_surf, (0,0))
        
        pygame.display.update()

    def handle_quit(self):
        for event in pygame.event.get():
                if event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_ESCAPE:
                        return False
                if event.type == pygame.QUIT:
                    return False
        
        return True
                