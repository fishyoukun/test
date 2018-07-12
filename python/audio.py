# -*- coding: utf-8 -*-
"""
Created on Thu Jul 12 19:13:21 2018

@author: fish
"""

#from __future__ import division
import numpy as np
from matplotlib import pyplot as plt
from pydub import AudioSegment
import os


song = AudioSegment.from_mp3("1.mp3")
# song = AudioSegment.from_wav("3.wav")
# ogg_version = AudioSegment.from_ogg("never_gonna_give_you_up.ogg")
# flv_version = AudioSegment.from_flv("never_gonna_give_you_up.flv")
#
# mp4_version = AudioSegment.from_file("never_gonna_give_you_up.mp4", "mp4")
# wma_version = AudioSegment.from_file("never_gonna_give_you_up.wma", "wma")
# aac_version = AudioSegment.from_file("never_gonna_give_you_up.aiff", "aac")
# song is not modified
# AudioSegments are immutable
single = song.split_to_mono()
# single[0].export("single_l.mp3", format="mp3")
# single[1].export("single_r.mp3", format="mp3")
# backwards = song.reverse()
# backwards.export("2.mp3", format="mp3")
length = len(song)
print song
print length
sample=single[0][:8192]
print sample
# sample.export("sample.mp3", format="mp3")
#z=np.fft.fft(song)
#plt.plot(np.abs(z))

# os.system('sample.mp3')
# plt.plot(sample.raw_data/2**15)
# plt.show()