#include<stdio.h>
#include<unistd.h>
#include<termios.h>
#include<stdlib.h>

struct termios original;

void disable_raw_mode(){
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &original);
}

void enable_raw_mode(){
  tcgetattr(STDIN_FILENO, &original);
  atexit(disable_raw_mode);
  
  struct termios raw = original;
  raw.c_cflag &= ~(ECHO | ICANON); // bitwise AND operation on raw.c_cflag and ~(ECHO) and put inside raw.c_cflag
  
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main(int argc, char* argv[]){
  enable_raw_mode();
  
  printf("Hello World:\n");

  char c;
  while(read(STDIN_FILENO, &c, 1) == 1 && c != 'q'){
    printf("%c", c);
  }
  
  return 0;
}