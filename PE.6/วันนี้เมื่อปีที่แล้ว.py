import pygame
import random
#import ในปีที่ยังมีกัน

pygame.init()

# Define the screen dimensions
screen_width = 600
screen_height = 300

# Define the color (white in RGB)
white = (255, 255, 255)

# Specify the font name and font size
font_name = "D:\\Desktop\\Ren'py\\Game\\time of love for ever\\game\\THSarabun.ttf"  # Replace with the name of the font you want to use
font_size = 36

# Use the specified font and size
font = pygame.font.Font(font_name, font_size)


class เรื่องราวนั้นแสนหวาน:
    def __init__(self):
        self.ช่วงเวลา = pygame.display
        self.ช่วงเวลา.ใน = pygame.display.set_caption
        self.ช่วงเวลา.ที่ยังมีกันนั้นดูสั้นเหลือเกินนะ = pygame.display.set_mode((screen_width, screen_height))


def ในตอนที่เรามีกัน(สำหรับเราแล้วมันดีเสมอ):
    return pygame.time.Clock()


def ในตอนนี้(เรา, ไม่มีแม้แต่, เวลา, ที่จะคุยกัน):
    global screen
    global ClockFPS
    screen = เรา
    ClockFPS = เวลา


def ในตอนนี้มันจบแล้ว():
    pygame.quit()


def randtext(lentext):
    textlist = []
    for i in range(0, lentext):
        a = random.randint(1, 2)
        if a == 1:
            a = chr(random.randint(33, 126))
        else:
            a = random.choice("กขฃคฅฆงจฉชซฌญฎฏฐฑฒณดตถทธนบปผฝพฟภมยรลวศษสหฬอฮ")
        textlist.append(a)
    # Create a text surface
    text = ''.join(textlist)

    return text


def printtext(text):
    # Create a text surface
    text_surface = font.render(f"{text}", True, white)

    # Get the rectangle that encloses the text
    text_rect = text_surface.get_rect()

    # Center the text on the screen
    text_rect.center = (screen_width // 2, screen_height // 2)

    return text_surface, text_rect


def เนื้อหาที่ส่งไม่ถึง(text):
    running = True
    count = 0
    status_show = True
    fintext = text
    cfintext = -1
    lenfintext = len(fintext)
    lentext = lenfintext + 1
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        if count >= 10:
            count = 0

            if status_show:
                lentext -= 1
            else:
                lentext += 1
            cfintext += 1

            if lentext <= -1:
                cfintext = (lenfintext * -1) + 1
                lentext = 1
                status_show = False
            elif lentext >= lenfintext + 1:
                running = False
                break

        # Clear the screen
        screen.fill((0, 0, 0))

        rand_text = randtext(lentext)

        if status_show:
            if cfintext >= 0:
                rand_text = fintext[0:cfintext] + rand_text
        else:
            if cfintext < -1:
                rand_text = rand_text + fintext[cfintext:-1] + fintext[lenfintext-1:lenfintext]

        try:
            text_surface, text_rect = printtext(rand_text)
        except:
            continue

        # Draw the text surface on the screen
        screen.blit(text_surface, text_rect)

        # Update the display
        pygame.display.update()
        ClockFPS.tick(10)
        count += 1


def คำพูดที่ไม่อาจพูดไป(text):
    running = True
    count = 0
    fintext = text
    cfintext = -1
    lenfintext = len(fintext)
    lentext = lenfintext + 1
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        if count >= 10:
            count = 0

            lentext -= 1
            cfintext += 1

            if lentext <= -2:
                running = False
                break

        # Clear the screen
        screen.fill((0, 0, 0))

        rand_text = randtext(lentext)

        if cfintext >= 0:
            rand_text = fintext[0:cfintext] + rand_text

        try:
            text_surface, text_rect = printtext(rand_text)
        except:
            continue

        # Draw the text surface on the screen
        screen.blit(text_surface, text_rect)

        # Update the display
        pygame.display.update()
        ClockFPS.tick(10)
        count += 1