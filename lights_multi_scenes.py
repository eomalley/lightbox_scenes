#!/usr/bin/env python3
import serial
import time
import pygame
import random
import threading
from gpiozero import Button

events = [];

def worker(event):
    missed_strikes = 0
    while not event.isSet():
        if random.randrange(0, 100) % 5 == 0 or missed_strikes >= 6:
            #if not ser.is_open:
            #    ser.open()
            print("sending: " + 'lightning')
            ser.write(('lightning' + "\n").encode('utf-8'))
            print("sent")
            #ser.close()
            missed_strikes = 0
        else:
            missed_strikes += 1
            print('no lightning ' + str(missed_strikes))
        event.wait(10)

def wake(event):
    sun = 0
    print("worker")
    while not event.isSet():
        if sun < 100:
            print("wake < 100")
            #if not ser.is_open:
            #    ser.open()
            print("sending: " + 'sunrise ' + str(sun))
            ser.write(('custom-fill=212,175,55+' + str(sun) + "\n").encode('utf-8'))
            print("sent")
            #ser.close()
            sun += 1
            event.wait(25)
        else:
            print("else!")
            event.set()

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    pygame.mixer.init(48000, -16, 1, 1024)
    pygame.mixer.init()
    pygame.mixer.music.load('morning.mp3')
    button2 = Button(4)
    button1 = Button(5)
    button4 = Button(6)
    button3 = Button(12)

    sunsets = [['sunset1', 'meadow.mp3'], ['sunset2', 'wind.mp3'], ['sunset3', 'cicadas.mp3']]
    day = [['sun', 'meadow.mp3'], ['overcast', 'stronger_wind.mp3']]
    storms = [['storm', 'rain_no_thunder.mp3'], ['storm','rain_thunder.mp3'],['storm', 'heavy_thunder_storm.mp3']]
    night = [['night', 'night_wind_crickets.mp3'], ['night', 'stronger_wind.mp3']]

    scene = "custom-fill=212,175,55+0" + "\n"
    sound = 'morning.mp3'

    button1Pos = -1
    button2Pos = -1
    button3Pos = -1
    button4Pos = -1

    time.sleep(1)

    while True:
        if button1.is_pressed:
            button1Pos += 1
            if button1Pos >= len(sunsets):
                button1Pos = 0

            scene = sunsets[button1Pos][0]
            sound = sunsets[button1Pos][1]
        if button2.is_pressed:
            button2Pos += 1
            if button2Pos >= len(day):
                button2Pos = 0

            scene = day[button2Pos][0]
            sound = day[button2Pos][1]
        if button3.is_pressed:
            button3Pos += 1
            if button3Pos >= len(storms):
                button3Pos = 0

            scene = storms[button3Pos][0]
            sound = storms[button3Pos][1]
        if button4.is_pressed:
            button4Pos += 1
            if button4Pos >= len(night):
                button4Pos = 0

            scene = night[button4Pos][0]
            sound = night[button4Pos][1]

        if len(scene) > 0 and len(sound) > 0:
            #if not ser.is_open:
            #    ser.open()
            print("sending: " + scene)
            print("playing: " + sound)
            pygame.mixer.music.load(sound)
            ser.write((scene + "\n").encode('utf-8'))
            print("sent")
            #ser.close()
            if sound == 'heavy_thunder_storm.mp3' or sound == 'morning.mp3':
                pygame.mixer.music.set_volume(0.3);
            pygame.mixer.music.play(-1)

            if sound == 'heavy_thunder_storm.mp3':
                event = threading.Event()
                thread = threading.Thread(target=worker, args=(event,))
                events.append(event)
                thread.start()
            elif sound == 'morning.mp3':
                event = threading.Event()
                thread = threading.Thread(target=wake, args=(event,))
                events.append(event)
                thread.start()
            else:
                if len(events) > 0:
                    for eaEvent in events:
                        eaEvent.set()
            
            scene = ''
            sound = ''
            time.sleep(2)
