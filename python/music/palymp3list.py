import playmp3 as pl
songlist=[r'1.mp3',
          r'11.mp3']
for i in range(0,len(songlist)):
    pl.playmp3(songlist[i])


