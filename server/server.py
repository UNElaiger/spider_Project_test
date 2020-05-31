# -*- coding: utf-8 -*-
import pygame
import socket
import sys
import speech_recognition as sr
import os
import sys
import random

say = ""

def command():
    r=sr.Recognizer()
    with sr.Microphone() as source:
        print("Speak")
        r.pause_threshold = 1 # пауза
        r.adjust_for_ambient_noise(source, duration=1)  # duration отвечает за колличество секунд которые нужно транскрибировать
        audio = r.listen(source) # слслушаем микрофон
    try:
        zadanie = r.recognize_google(audio, language="ru-RU").lower()
        say = zadanie
        print("You say: " + zadanie)
    except sr.UnknownValueError:
        print("I dont understand")
        zadanie = command()
    return zadanie

def find():
    if "привет" in command():
        print("worked")
    else:
        print("false")


#while True:
    #find()




pygame.init()
black=(0,0,0)
#размер окна
#width = 1365
#height = 165
#screen = pygame.display.set_mode((width, height))








def main():
    clock = pygame.time.Clock()
    done = False
    flag1 = False
    flag2 = False
    flag3 = False
    sc = pygame.display.set_mode((400, 300))
    sc.fill((200, 255, 200))
    font = pygame.font.Font(None, 72)
    text = font.render("wait connect", 1, (0, 100, 0))
    place = text.get_rect(center=(200, 150))
    sc.blit(text, place)

    pygame.display.update()

    sock = socket.socket()  # создаем сокет
    sock.bind(("", 9076))  # port na cotorom my budem prinimat soobcheniya
    sock.listen(5)  # максимальновозможное кол-во подключений
    conn, addr = sock.accept()  # ждем подлкючение нам вернется котреж с сокетом и ip клиента
    print("New connection from ", addr)
    while not done:
        value_ob = conn.recv(1024)  # max кол-во байт для чтения 1024
        print(value_ob)
        for event in pygame.event.get():  # обработка клавиш
            if (event.type == pygame.QUIT):
                done = True
                # sock.close() #закрытие сокета
                sys.exit(1)  # выход из программы
            if (event.type == pygame.KEYDOWN and event.key == pygame.K_1):
                if (flag1 == False):
                    mess = "LED1"
                    print("LED1_ON")
                    flag1 = True
                    conn.sendto(mess.encode(), addr)
                elif (flag1 == True):
                    mess = "LED1"
                    print("LED1_OFF")
                    flag1 = False
                    conn.sendto(mess.encode(), addr)
            if (event.type == pygame.KEYDOWN and event.key == pygame.K_2):
                if (flag2 == False):
                    mess = "LED2"
                    print("LED2_ON")
                    flag2 = True
                    conn.sendto(mess.encode(), addr)
                elif (flag2 == True):
                    mess = "LED2"
                    print("LED2_OFF")
                    flag2 = False
                    conn.sendto(mess.encode(), addr)
            if (event.type == pygame.KEYDOWN and event.key == pygame.K_3):
                if (flag3 == False):
                    mess = "LED3"
                    print("LED3_ON")
                    flag1 = True
                    conn.sendto(mess.encode(), addr)
                elif (flag3 == True):
                    mess = "LED3"
                    print("LED3_OFF")
                    flag1 = False
                    conn.sendto(mess.encode(), addr)
            if (event.type == pygame.KEYUP and event.key == pygame.K_SPACE):
                # if "светик 1" in command() or " светик 1" in command():
                say = command()
                print(say)
                if say.find('светик 1') != -1:
                    if (flag1 == False):
                        mess = "LED1"
                        print("LED1_ON")
                        flag1 = True
                        conn.sendto(mess.encode(), addr)
                        break
                    elif (flag1 == True):
                        mess = "LED1"
                        print("LED1_OFF")
                        flag1 = False
                        conn.sendto(mess.encode(), addr)
                        break
                # elif "светик 2" in command() or " светик 2" in command():
                elif say.find('светик 2') != -1:
                    if (flag2 == False):
                        mess = "LED2"
                        print("LED2_ON")
                        flag2 = True
                        conn.sendto(mess.encode(), addr)
                        break
                    elif (flag2 == True):
                        mess = "LED2"
                        print("LED2_OFF")
                        flag2 = False
                        conn.sendto(mess.encode(), addr)
                        break
                # elif "светик 3" in command() or " светик 3" in command():
                elif say.find('светик 3') != -1:
                    if (flag3 == False):
                        mess = "LED3"
                        print("LED3_ON")
                        flag3 = True
                        conn.sendto(mess.encode(), addr)
                        break
                    elif (flag3 == True):
                        mess = "LED3"
                        print("LED3_OFF")
                        flag3 = False
                        conn.sendto(mess.encode(), addr)
                        break
                else:
                    print("повторите пожалуйста")
        value_ob = font.render(str(value_ob), 1, black)
        sc.fill((200, 255, 200))
        # sc.blit(value_ob,place)
        pygame.display.update()

        clock.tick(60)

if __name__ == "__main__":
    main()