# -*- coding: utf-8 -*-
"""
Created on Thu Jul 12 15:47:46 2018

@author: fish
"""
from __future__ import division
import numpy as np
from matplotlib import pyplot as plt


N=8192
fs=300
f1=100
f2=30
plt.clf()
n=np.array(range(0,N))
x = 2*np.cos(2*np.pi*f1/fs*n)+np.sin(2*np.pi*f2/fs*n)*1j
#x = np.sin(2*np.pi*f2/fs*n)*1j
#plt.plot(n,x)
z=np.fft.fft(x)
z=np.fft.fftshift(z)
fs_n=n/N-0.5
y_abs_max=np.max(np.abs(z))

plt.figure(1)
plt.subplot(211)
plt.plot(fs_n,np.abs(z)/y_abs_max)
plt.xlabel('Hz /fs')
plt.ylabel('relavive amp')
plt.grid('true')
plt.subplot(212)
plt.plot(fs_n,np.angle(z)/np.pi)
plt.xlabel('Hz /fs')
plt.ylabel('pha')
plt.grid('true')
plt.show()



