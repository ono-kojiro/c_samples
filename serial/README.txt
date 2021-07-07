
Terminal 0
$ socat -d -d pty,raw,echo=0 pty,raw,echo=0

confirm pty device
2021/07/07 20:08:23 socat[6744] N PTY is /dev/pts/3                  
2021/07/07 20:08:23 socat[6744] N PTY is /dev/pts/4  
2021/07/07 20:08:23 socat[6744] N starting data ....

Terminal 1
$ ./serial -p /dev/pts/3

Terminal 2
$ ./serial -p /dev/pts/4


END


