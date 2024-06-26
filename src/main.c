#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/* TODO:
 * - use the standard library file functions (fopen, fread, etc) instead of the systemcalls
 * - split the hex print to a seperate function, write my own custom hex printer and not use printf for fun :3
 * - add a special mode to print a specific line, maybe add a human readable option?
 */

/* limits */
#define CYCLECAP 16

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

  /* iterate over every 10 bytes, print the data of each byte in hex */
  uint8_t buff[CYCLECAP];
  int c=0; // the line we are currently at
  int r;   // the amount of bytes read by read()
  while((r=read(fd, &buff, CYCLECAP))>0){
    /* print the line in hex because lol */
    printf("\n%.6X | ", c);

    /* print the raw data, every x columns specified by CYCLECAP (or until reaching EOF) */
    for(int i=0;i<r;i++){
      printf("%.2X ", buff[i]);
    }

    /* start printing the values as "characters"
     * WIP
    printf(" | ");
    for(int i=0;i<r;i++, c++){
      char b = (char)buff[i];

      if(b=='\n') { continue; }
      if(b=='\t') { continue; }
      else { printf("%c", b); }
    }
    */
    
    /* clean buffer by setting all the values to 0
     * TODO: i need a better method to clean up the buffer
     */    
    for(int i=0;i<CYCLECAP;i++){
      buff[i]=0;
    }

    c += CYCLECAP;
  }
  
  close(fd);
  return 0;
}

