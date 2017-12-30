#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DEFAULT_DEVICE "/dev/usbcheck"
#define DEFAULT_DURATION 800

#define ML_STOP 0x00
#define ML_UP 0x02
#define ML_DOWN 0x34
#define ML_LED 0x03
#define ML_LEFT 0x30
#define ML_RIGHT 0x31
#define ML_FIRE 0x03

#define ML_FIRE_DELAY 5000

void send_cmd(int fd, char *cmd, int count) {
  int retval = 0;

  retval = write(fd, cmd, count);
  if (retval < 0)
    fprintf(stderr, "could not send command to fd=%d\n", fd);
}

static void usage(char *name) {
  fprintf(
      stderr,
      "\nusage: %s [-mbslrudfch] [-t <msecs>]\n\n"
      "  -m      missile launcher [/dev/ml0]\n"
      "  -s      stop\n"
      "  -l      turn left\n"
      "  -r      turn right\n"
      "  -u      turn up\n"
      "  -d      turn down\n"
      "  -f      fire\n"
      "  -b      blink leds\n"
      "  -t      specify send_cmdment duration in milli seconds\n"
      "  -c      calibrate the missile launcher axes\n"
      "  -h      display this help\n\n"
      "notes:\n"
      "* it is possible to combine the directions of the two axes, e.g.\n"
      "  '-lu' send_cmds the missile launcher up and left at the same time.\n"
      "",
      name);
  exit(1);
}

int main(int argc, char *argv[]) {
  char c;
  int fd;
  char *cmd = malloc(sizeof(char));
  int cvalue;
  char buffer[20];
  int duration = DEFAULT_DURATION;
  char *dev = DEFAULT_DEVICE;
  char *data;

  opterr = 0;
  if (argc < 2)
    usage(argv[0]);

  while ((c = getopt(argc, argv, "m:bslru:d:fcht:")) != -1) {
    switch (c) {
    case 'm':
      dev = optarg;
      break;
    case 'l':
      cmd[0] = ML_LEFT;
      break;
    case 'r':
      cmd[0] = ML_RIGHT;
      break;
    case 'u':
      cvalue = atoi(optarg);
      cmd[0] = ML_UP;
      printf("Open device %s\n", dev);
      fd = open(dev, O_RDWR);
      if (fd == -1) {
        perror("open");
        exit(1);
      }

      printf("Send command %i\n", cmd[0]);
      int retval = 0;

      retval = read(fd, buffer, cvalue);
      if (retval < 0)
        fprintf(stderr, "could not send command to fd=%d\n", fd);
      close(fd);
      // if (retval != 16)
      fprintf(stderr, "number of bytes read = %d\n", retval);
      printf("receive: %s\n", buffer);
      break;
    case 'd':
      // cmd = "optarg";
      strcpy(cmd, optarg);
      cmd[0] = ML_DOWN;
      break;
    case 'f':
      cmd[0] = ML_FIRE;
      break;
    case 'b':
      cmd[0] = ML_LED;
      break;
    case 's':
      cmd[0] = ML_STOP;
      break;
    case 't':
      duration = atoi(optarg);
      break;
    case 'c': /*
                      retval = ioctl(fd, ML_IOCTCALIBRATE, ML_CALIBRATE_FULL);
                      if (retval < 0)
                              perror("ioctl");
                      */
      break;
    case '?':
      if (optopt == 'u')
        fprintf(stderr, "Option -%c requires an argument.\n", optopt);
      else if (isprint(optopt))
        fprintf(stderr, "Unknown option `-%c'.\n", optopt);
      else
        fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
    default:
      usage(argv[0]);
    }
  }

  printf("Open device %s\n", dev);
  fd = open(dev, O_RDWR);
  if (fd == -1) {
    perror("open");
    exit(1);
  }

  printf("Send command %i\n", cmd[0]);
  send_cmd(fd, cmd, strlen(cmd));

  // if (cmd & ML_FIRE)
  // 	duration = ML_FIRE_DELAY;
  // else if (cmd == ML_UP || cmd == ML_DOWN)
  // 	duration /= 2;
  // usleep(duration * 1000);

  // send_cmd(fd, ML_STOP);

  close(fd);

  return EXIT_SUCCESS;
}
