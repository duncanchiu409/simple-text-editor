#include<stdio.h>
#include<unistd.h>
#include<termios.h>
#include<stdlib.h>
#include<ctype.h>

struct termios original;

void disable_raw_mode(){
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &original);
}

void enable_raw_mode(){
  tcgetattr(STDIN_FILENO, &original);
  atexit(disable_raw_mode); // register our function disable_raw_mode to be called automatically when program exits
    
  struct termios raw = original;
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= ~(CS8);
  raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN); // bitwise AND operation on raw.c_cflag and ~(ECHO) and put inside raw.c_cflag

  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;
  
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main(int argc, char* argv[]){
  enable_raw_mode();
  
  printf("Hello World:\n");

  while(1){
    char c = '\0';
    read(STDIN_FILENO, &c, 1);
    if(iscntrl(c)){
      printf("%d\r\n", c);
    }
    else{
      printf("%d ( '%c' )\r\n", c, c);
    }
    if(c == 'q'){
      break;
    }
  }
  
  return 0;
}