import pygame
import player
import sector
import raycaster
import obj_renderer

class Game:
    def __init__(self):
        self.delta_time = 0

        self.renderer = obj_renderer.Obj_renderer(self)
        self.raycaster = raycaster.Raycaster(self)
        self.clock = pygame.time.Clock()

        self.font = pygame.font.SysFont("Comic Sans MS", 30)
        self.debug_text = ""

        """
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
        """
        self.sector = sector.Sector(
            [
                [pygame.math.Vector2(50, 350), pygame.math.Vector2(350, 50)]
            ]
        )
        self.player = player.Player(self)

    def blit_text(self, surface, text, pos, color=pygame.Color("green")):
        words = [word.split(' ') for word in text.splitlines()]
        space = self.font.size(' ')[0]
        max_width, max_height = surface.get_size()
        x, y = pos

        for line in words:
            for word in line:
                word_surface = self.font.render(word, 0, color)
                word_width, word_height = word_surface.get_size()

                if x + word_width >= max_width:
                    x = pos[0]
                    y += word_height

                surface.blit(word_surface, (x, y))

                x += word_width + space

            x = pos[0]
            y += word_height

    def mainloop(self):
        running = True
        while running:
            running = self.handle_quit()

            self.draw()

            self.update()

            self.player.draw()
            pygame.display.update()

        pygame.quit()
        quit()

    def update(self):
        self.player.update()

        self.debug_text = ""
        self.debug_text += "player angle: " + str(self.player.angle) + "\n"
        self.debug_text += "player pos: " + str(self.player.rect.centerx) + ", " + str(self.player.rect.centery) + "\n"
        self.debug_text += "fps: " + str(int(self.clock.get_fps())) + "\n"

        self.raycaster.update(self.sector)

        self.delta_time = self.clock.tick(60)

    def draw(self):
        self.renderer.screen.fill((26, 26, 26))

        self.sector.draw_walls(self.renderer.screen)

        self.renderer.draw()

        self.blit_text(self.renderer.screen, self.debug_text, (10, 10))

    def handle_quit(self):
        for event in pygame.event.get():
                if event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_ESCAPE:
                        return False
                if event.type == pygame.QUIT:
                    return False
        
        return True
                