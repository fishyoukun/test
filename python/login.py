# -*- coding: utf-8 -*-
"""
Created on Fri Jan 12 22:08:59 2018

@author: fish
"""

import re
import time

def do_telnet(Host, username, password, finish, commands):
    import telnetlib
    
    tn = telnetlib.Telnet(Host,port=23,timeout=10)
    tn.set_debuglevel(2)
    
    ## enter username for login
    #tn.read_until('login: ')
    #tn.write(username + '\n')
    
    ## enter password
    #tn.read_until('password: ')
    #tn.write(password + '\n')
    
    ##execute command after login
    tn.read_until(finish)
    tn.write('%s\n' % 'ps')
    result = tn.read_until(finish)
    
    ### using re to find the pid of program
    try:
        mypid = re.findall(r'(\d+)\s\w+\s+\d+\w\s\w\s+\.\/a.out\s+',result)[0]
    except IndexError:
        print ("cannot find the pid of a.out")
        mypid = None
    
    if str(mypid) != 'None':
        print('kill a.out')
        tn.write('kill '+ mypid + '\n')
    else:
        print('No a.out running......\n')
    
    for command in commands:
        tn.write('%s\n' % command)
        log = tn.read_until(finish)
        try:
            file_object = open('log.txt','a')
            file_object.write(log)
        finally:
            file_object.close()
            
    log = tn.read_until('simulation done.')
    file_object = open('log.txt','a')
    try:
        file_object.write(log)
    finally:
        file_object.close()
    tn.close() 
    
if __name__ == '__main__':
    #config parameter
    Host = '199.33.33.33'  ##Telnet server Ip
    username = 'zte'
    password = 'zte'
    finish = '#'
    commands = ['rm a.out',
                'mv b.out a.out']
    do_telnet(Host, username, password, finish, commands)
    
        