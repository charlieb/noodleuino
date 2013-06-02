#include <stdio.h>   /* Standard input/output definitions */
#include <stdlib.h>
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#if 0
/*
 * 'open_port()' - Open serial port 1.
 *
 * Returns the file descriptor on success or -1 on error.
 */
int open_port(void)
{
  int fd; /* File descriptor for the port */

  fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
  if (fd == -1)
  {
    /* Could not open the port. */
    perror("open_port: Unable to open /dev/ttyS0 - ");
  }
  else
    fcntl(fd, F_SETFL, 0);

  int n = write(fd, "ATZ\r", 4);
  if (n < 0)
    fputs("write() of 4 bytes failed!\n", stderr);

  return (fd);
}

int read_port(void)
{
  int fd = open("/dev/ttyS0", O_RDONLY | O_NOCTTY);
  if (fd == -1)
  {
    /* Could not open the port. */
    perror("open_port: Unable to open /dev/ttyS0 - ");
  }

  char buffer[32];
  int n = read(fd, buffer, sizeof(buffer));
  if (n < 0)
    fputs("read failed!\n", stderr);
  return (fd);
}
#endif

/*
The values for speed are 
B115200
B230400
B9600
B19200
B38400
B57600
B1200
B2400
B4800

The values for parity are 0 (meaning no parity), PARENB|PARODD (enable parity and use odd), PARENB (enable parity and use even), PARENB|PARODD|CMSPAR (mark parity), and PARENB|CMSPAR (space parity).
*/
/***********************************/

#include <sys/types.h>
#include <sys/stat.h>

/* baudrate settings are defined in <asm/termbits.h>, which is
   included by <termios.h> */
#define BAUDRATE B115200            
/* change this definition for the correct port */
#define MODEMDEVICE "/dev/ttyUSB2"
#define _POSIX_SOURCE 1 /* POSIX compliant source */

#define FALSE 0
#define TRUE 1

volatile int STOP=FALSE; 

main() {
  int fd,c, res;
  struct termios oldtio,newtio;
  char buf[255];
  /* 
     Open modem device for reading and writing and not as controlling tty
     because we don't want to get killed if linenoise sends CTRL-C.
     */
  fd = open(MODEMDEVICE, O_RDWR | O_NOCTTY); 
  if (fd < 0) { 
    perror(MODEMDEVICE);
    exit(-1);
  }

  tcgetattr(fd,&oldtio); /* save current serial port settings */
  bzero(&newtio, sizeof(newtio)); /* clear struct for new port settings */

  /* 
BAUDRATE: Set bps rate. You could also use cfsetispeed and cfsetospeed.
CRTSCTS : output hardware flow control (only used if the cable has
all necessary lines. See sect. 7 of Serial-HOWTO)
CS8     : 8n1 (8bit,no parity,1 stopbit)
CLOCAL  : local connection, no modem contol
CREAD   : enable receiving characters
*/
  newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;

  /*
IGNPAR  : ignore bytes with parity errors
ICRNL   : map CR to NL (otherwise a CR input on the other computer
will not terminate input)
otherwise make device raw (no other input processing)
*/
  newtio.c_iflag = IGNPAR | ICRNL;

  /*
     Raw output.
     */
  newtio.c_oflag = 0;

  /*
ICANON  : enable canonical input
disable all echo functionality, and don't send signals to calling program
*/
  newtio.c_lflag = ICANON;

  /* 
     initialize all control characters 
     default values can be found in /usr/include/termios.h, and are given
     in the comments, but we don't need them here
     */
  newtio.c_cc[VINTR]    = 0;     /* Ctrl-c */ 
  newtio.c_cc[VQUIT]    = 0;     /* Ctrl-\ */
  newtio.c_cc[VERASE]   = 0;     /* del */
  newtio.c_cc[VKILL]    = 0;     /* @ */
  newtio.c_cc[VEOF]     = 4;     /* Ctrl-d */
  newtio.c_cc[VTIME]    = 0;     /* inter-character timer unused */
  newtio.c_cc[VMIN]     = 1;     /* blocking read until 1 character arrives */
  newtio.c_cc[VSWTC]    = 0;     /* '\0' */
  newtio.c_cc[VSTART]   = 0;     /* Ctrl-q */ 
  newtio.c_cc[VSTOP]    = 0;     /* Ctrl-s */
  newtio.c_cc[VSUSP]    = 0;     /* Ctrl-z */
  newtio.c_cc[VEOL]     = 0;     /* '\0' */
  newtio.c_cc[VREPRINT] = 0;     /* Ctrl-r */
  newtio.c_cc[VDISCARD] = 0;     /* Ctrl-u */
  newtio.c_cc[VWERASE]  = 0;     /* Ctrl-w */
  newtio.c_cc[VLNEXT]   = 0;     /* Ctrl-v */
  newtio.c_cc[VEOL2]    = 0;     /* '\0' */

  /* 
     now clean the modem line and activate the settings for the port
     */
  tcflush(fd, TCIFLUSH);
  tcsetattr(fd,TCSANOW,&newtio);

  /*
     terminal settings done, now handle input
     In this example, inputting a 'z' at the beginning of a line will 
     exit the program.
     */
  while (STOP==FALSE) {     /* loop until we have a terminating condition */
    /* read blocks program execution until a line terminating character is 
       input, even if more than 255 chars are input. If the number
       of characters read is smaller than the number of chars available,
       subsequent reads will return the remaining chars. res will be set
       to the actual number of characters actually read */
    res = read(fd,buf,255); 
    buf[res]=0;             /* set end of string, so we can printf */
    printf(":%s:%d\n", buf, res);
    if (buf[0]=='z') STOP=TRUE;
  }
  /* restore the old port settings */
  tcsetattr(fd,TCSANOW,&oldtio);
}


