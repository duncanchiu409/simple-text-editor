// includes 

#include <asm-generic/errno-base.h>
#include<stdio.h>
#include<unistd.h>
#include<termios.h>
#include<stdlib.h>
#include<ctype.h>
#include<errno.h>

// defines

#define CTRL_KEY(k) ((k) & 0x1f)

// data

struct termios original;

// terminal

void die(const char* s){
  perror(s);
  exit(1);
}

void disable_raw_mode(){
  if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &original) == -1){
    die("tcsetattr");
  }
}

void enable_raw_mode(){
  if(tcgetattr(STDIN_FILENO, &original) == -1){
    die("tcgetattr");
  }
  atexit(disable_raw_mode); // register our function disable_raw_mode to be called automatically when program exits
    
  struct termios raw = original;
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= ~(CS8);
  raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN); // bitwise AND operation on raw.c_cflag and ~(ECHO) and put inside raw.c_cflag

  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;
  
  if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1){
    die("tcsetattr");
  }
}

char editorReadKey(){
  int nread;
  char c;
  while((nread = read(STDIN_FILENO, &c, 1)) != -1){
    if(nread == -1 && errno != EAGAIN) die("read");
  }
  return c;
}

void editorProcessKeypress(){
  char c = editorReadKey();

  switch(c){
    case CTRL_KEY('q'):
      exit(0);
      break;
  }
}

// init

int main(int argc, char* argv[]){
  enable_raw_mode();
  
  printf("Hello World:\n");

  while(1){
    // char c = '\0';
    // if(read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN){
    //   die("read");
    // }
    // if(iscntrl(c)){
    //   printf("%d\r\n", c);
    // }
    // else{
    //   printf("%d ( '%c' )\r\n", c, c);
    // }
    // if(c == CTRL_KEY('q')){
    //   break;
    // }

    editorProcessKeypress();
  }
  
  return 0;
}