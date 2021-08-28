#include <string.h>
#include <termios.h>
#include "baudrate.h"

int get_baudrate_flag(int baudrate)
{
	int flag = B0;

	switch(baudrate) {
		case 0:
			flag = B0; break;
		case 50:
			flag = B50; break;
		case 75:
			flag = B75; break;
		case 110:
			flag = B110; break;
		case 134:
			flag = B134; break;
		case 150:
			flag = B150; break;
		case 200:
			flag = B200; break;
		case 300:
			flag = B300; break;
		case 600:
			flag = B600; break;
		case 1200:
			flag = B1200; break;
		case 1800:
			flag = B1800; break;
		case 2400:
			flag = B2400; break;
		case 4800:
			flag = B4800; break;
		case 9600:
			flag = B9600; break;
		case 19200:
			flag = B19200; break;
		case 38400:
			flag = B38400; break;
		case 57600:
			flag = B57600; break;
		case 115200:
			flag = B115200; break;
		case 230400:
			flag = B230400; break;
		default:
			break;
	}

	return flag;
}

