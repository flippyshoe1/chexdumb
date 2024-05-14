#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/* TODO:
 * - use the standard library file functions (fopen, fread, etc) instead of the systemcall
 * - split the hex print to a seperate function, write my own custom hex printer and not use printf for fun :3
 */

/* quick and dirty assert macro to save writing */
#define ASSERT(_e, ...) if(!(_e)) { fprintf(stderr, __VA_ARGS__); exit(1); }

int main(int argc, char **argv){

  /* argv[1] is the path to the file */
  ASSERT(argc==2, "Invalid amount of arguements\n");
  char *path = argv[1];

  /* get the file descriptor of the file */
  int fd;
  ASSERT((fd=open(path, 0)) > 0,
	 "Failed to open file, err: %s\n", strerror(errno));

  /* iterate over every 128 bytes, print the data of each byte in hex */
  uint8_t buff[128];
  int c=0;
  while(read(fd, &buff, 128)>0){
    for(int i=0;i<128;i++, c++){
      if(i%10==0){
	printf("\n%.6X | ", c/12);
      }
      
      printf("%.2X ", buff[i]);
    }
  }
  
  close(fd);
  return 0;
}

