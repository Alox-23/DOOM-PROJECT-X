import pygame
from settings import *
import random

class Bird(pygame.sprite.Sprite):
    def __init__(self, pos, group):
        super().__init__(group)
        self.ANIMATION_COOLDOWN = 150
        self.last_animation_update_time = pygame.time.get_ticks()
        self.dead = False

        self.animation_list = []
        self.index = 0
        self.scale = 3



        for i in range(1,4):
            self.animation_list.append(pygame.transform.scale(pygame.image.load(f"img/img/{i}.png"), 
                                                             (pygame.image.load(f"img/img/{i}.png").get_width() * self.scale,
                                                              pygame.image.load(f"img/img/{i}.png").get_height() * self.scale)))

        self.img = self.animation_list[self.index]
        self.rect = self.img.get_rect()
        self.rect.center = pos;
        self.mask = pygame.mask.from_surface(self.img)
        self.mask_img = self.mask.to_surface()

        self.vel_y = 0
        self.jump_power = 8
        self.gravity = 1
        self.vel_y_cap = 15
        self.rot = 0
        self.score = 0

    def draw(self, screen):
        screen.blit(self.img, self.rect)

    def update(self):
        self.check_death()
        self.update_rot()
        self.update_animation()
        self.rect.y += self.vel_y

    def update_rot(self):
        self.rot = -self.vel_y * 3

    def move(self):
        self.vel_y += self.gravity
        if self.vel_y >= self.vel_y_cap:
            self.vel_y = self.vel_y_cap
    
    def jump(self):
        self.vel_y = -self.jump_power
        self.index = 2

    def get_input(self):
        if self.dead != True:
            keys = pygame.key.get_pressed()

            if keys[pygame.K_UP]:
               self.jump()
    
    def check_death(self):
        if self.rect.y > HEIGHT:
            self.kill()
        elif self.rect.y < 0:
            self.die()

    def die(self):
        self.dead = True

    def check_colision_rect(self, rects):
        for rect in rects:
            if self.rect.colliderect(rect):
                self.die()

    def check_colision_mask(self, masks, rects):
        for mask, i in enumerate(masks):
            if self.mask.overlap(mask, (rects[i].x - self.rect.x, rects[i].y - self.rect.y)):
                pass
    
    def ai(self):
        if random.randint(1, 10) == 1:
            self.jump()

    def update_animation(self):
        if pygame.time.get_ticks() - self.last_animation_update_time > self.ANIMATION_COOLDOWN:
            self.index += 1
            self.last_animation_update_time = pygame.time.get_ticks()
        print(self.index)
        if self.index > len(self.animation_list)-1:
            self.index = 0 

        self.img = pygame.transform.rotate(self.animation_list[self.index], self.rot)
        self.mask = pygame.mask.from_surface(self.img)
        self.mask_img = self.mask.to_surface()

