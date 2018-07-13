# -*- coding: utf-8 -*-
"""
Created on Thu Jul 12 19:13:21 2018

@author: fish
"""
from __future__ import division
import numpy as np
from matplotlib import pyplot as plt
from pydub import AudioSegment
import os
from scipy.io import wavfile
import time
import pygame

'read audio file different style,now mp3 style'
song = AudioSegment.from_mp3("1.mp3")
length = len(song)
dura_time = song.duration_seconds
samplefs = song.frame_rate
print 'length = ', (length)
print 'frame_rate = ', (samplefs)
print 'time =', (length/samplefs)
print 'duration time =', (dura_time)
# play music
file=r'1.mp3'
pygame.mixer.init()
print("play music start")
track = pygame.mixer.music.load(file)

pygame.mixer.music.play(10, 0)
time.sleep(dura_time*10)
pygame.mixer.music.stop()
print "play over"