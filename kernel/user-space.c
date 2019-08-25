#include <ctype.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DEFAULT_DEVICE "/dev/usbcheck"

#define ML_STOP 0x00
#define ML_READ_BYTE 0x02
#define ML_WRITE_BYTE 0x03
#define ML_READ_DEVICE_CODE 4
#define ML_LED 0x30

#define RAM_WE 0x00

int hex[] = {'0', '1', '2', '3', '4', '5', '6', '7',
             '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

typedef struct {
  char cmd;
  uint16_t value;
  uint16_t index;
  char data[2];
} usb_msg_t;

void send_cmd(int fd, char *cmd, int count) {
  int retval = 0;

  retval = write(fd, cmd, count);
  if (retval < 0)
    fprintf(stderr, "could not send command to fd=%d\n", fd);
}

static void usage(char *name) {
  fprintf(stderr,
          "\nusage: %s [-mwrudlh]\n\n"
          "  -m      eprom programmer [/dev/usbcheck]\n"
          "  -w      write data to a address (-a \"address\" -w \"data\")\n"
          "  -r      read data from an address (-a \"address\" -r).\n"
          "  -u      read data from avr [experimental].\n"
          "  -d      write data to avr [experimental].\n"
          "  -l      turn LED on or off: 0 => Off, 1 => On\n"
          "  -k      read device code\n"
          "  -h      display this help\n\n"
          "",
          name);
  exit(1);
}

int open_device(int *fd, char *dev) {
  printf("Open device %s\n", dev);
  *fd = open(dev, O_RDWR);
  if (*fd == -1) {
    perror("open");
    return 1;
  }
  return 0;
}

int main(int argc, char *argv[]) {
  char c;
  int fd;
  char *cmd = malloc(sizeof(usb_msg_t));
  int cvalue;
  char buffer[20];
  char *dev = DEFAULT_DEVICE;
  char *data;
  usb_msg_t usb_msg = {ML_WRITE_BYTE, 0x1143, 0x2254, ""};
  uint8_t my_msg[sizeof(usb_msg_t)];
  uint16_t serial_address = 0;
  uint8_t serial_data = 0;
  uint8_t serial_crc = 0;
  int retval;

  opterr = 0;
  if (argc < 2)
    usage(argv[0]);

  while ((c = getopt(argc, argv, "m:a:c:w:r:k:l:u:d:h")) != -1) {
    switch (c) {
    case 'm':
      dev = optarg;
      break;

    case 'a':
      sscanf(optarg, "%u", (unsigned int *)&serial_address);
      printf("Address: %d\n", serial_address);
      break;

    case 'c':
      sscanf(optarg, "%hhu", &serial_crc);
      printf("crc: %d\n", serial_crc);
      break;

    case 'w':
      sscanf(optarg, "%hhu", &serial_data);
      printf("data: %hhu\n", serial_data);
      my_msg[0] = ML_WRITE_BYTE;
      my_msg[1] = (serial_address >> 0) & 0xFF;
      my_msg[2] = (serial_address >> 8) & 0xFF;
      my_msg[3] = 0x00;
      my_msg[4] = 0x00;
      my_msg[5] = serial_data;
      my_msg[6] = serial_crc;

      if (open_device(&fd, dev))
        return -1;

      printf("Send command %i\n", my_msg[0]);
      send_cmd(fd, my_msg, sizeof(my_msg));
      close(fd);
      return EXIT_SUCCESS;

      break;

    case 'r':
      sscanf(optarg, "%hhu", &serial_data);
      printf("data: %hhu\n", serial_data);
      my_msg[0] = ML_READ_BYTE;
      my_msg[1] = (serial_address >> 0) & 0xFF;
      my_msg[2] = (serial_address >> 8) & 0xFF;
      my_msg[3] = (1 << RAM_WE);
      my_msg[4] = 0x00;
      my_msg[5] = serial_data;
      my_msg[6] = serial_crc;

      if (open_device(&fd, dev))
        return -1;

      retval = 0;
      retval = read(fd, my_msg, 1);
      if (retval < 0)
        fprintf(stderr, "could not send command to fd=%d\n", fd);
      close(fd);

      fprintf(stderr, "number of bytes read = %d\n", retval);
      printf("receive: %s\n", my_msg);
      printf("receive: %c%c\n", hex[(my_msg[0] >> 4) & 0xf],
             hex[(my_msg[0] >> 0) & 0xf]);

      close(fd);

      return EXIT_SUCCESS;

      break;

    case 'k':
      cvalue = atoi(optarg);
      if (cvalue != 0)
        cvalue = 0x80;

      my_msg[0] = ML_READ_DEVICE_CODE;
      my_msg[1] = cvalue;
      my_msg[2] = 0x00;
      my_msg[3] = 0x00;
      my_msg[4] = 0x00;
      my_msg[5] = 0x00;
      my_msg[6] = 0x00;

      if (open_device(&fd, dev))
        return -1;

      retval = 0;
      retval = read(fd, my_msg, 1);
      if (retval < 0)
        fprintf(stderr, "could not send command to fd=%d\n", fd);
      close(fd);

      fprintf(stderr, "number of bytes read = %d\n", retval);
      printf("receive: %s\n", my_msg);
      printf("receive: %c%c\n", hex[(my_msg[0] >> 4) & 0xf],
             hex[(my_msg[0] >> 0) & 0xf]);

      close(fd);

      return EXIT_SUCCESS;

      break;

    case 'l':
      cvalue = atoi(optarg);
      if (cvalue != 0)
        cvalue = 0x01;

      if (open_device(&fd, dev))
        return -1;

      cmd[0] = ML_LED;
      cmd[1] = cvalue;
      cmd[2] = 0x00;
      cmd[3] = 0x00;
      cmd[4] = 0x00;
      cmd[5] = 0x00;
      cmd[6] = 0x00;
      printf("Send command %i\n", cmd[0]);
      send_cmd(fd, cmd, sizeof(cmd));

      close(fd);

      return 0;

    case 'u':
      my_msg[0] = ML_READ_BYTE;
      my_msg[1] = 0x31;
      my_msg[2] = 0x32;
      my_msg[3] = 0x33;
      my_msg[4] = 0x34;

      memcpy(buffer, my_msg, sizeof(my_msg));
      cvalue = atoi(optarg);

      if (open_device(&fd, dev))
        return -1;

      printf("Send command %i\n", cmd[0]);
      retval = 0;

      if (cvalue > (sizeof(buffer) - 1))
        cvalue = (sizeof(buffer) - 1);

      retval = read(fd, buffer, cvalue);
      if (retval < 0)
        fprintf(stderr, "could not send command to fd=%d\n", fd);
      close(fd);

      fprintf(stderr, "number of bytes read = %d\n", retval);
      printf("receive: %s\n", buffer);

      close(fd);

      return EXIT_SUCCESS;
      break;

    case 'd':
      my_msg[0] = ML_WRITE_BYTE;
      my_msg[1] = 0x66;
      my_msg[2] = 0x31;
      my_msg[3] = 0x77;
      my_msg[4] = 0x32;

      strncpy(&(my_msg[5]), optarg, 2);

      if (open_device(&fd, dev))
        return -1;

      printf("Send command %i\n", my_msg[0]);
      send_cmd(fd, my_msg, sizeof(my_msg));
      close(fd);

      return EXIT_SUCCESS;

      break;

    case '?':
      if (optopt == 'u')
        fprintf(stderr, "Option -%c requires an argument.\n", optopt);
      else if (optopt == 'l')
        fprintf(stderr, "Option -%c requires an argument: On = 1, Off = 0.\n",
                optopt);
      else if (isprint(optopt))
        fprintf(stderr, "Unknown option `-%c'.\n", optopt);
      else
        fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);

      break;

    default:
      usage(argv[0]);
      break;
    }
  }

  return EXIT_SUCCESS;
}
