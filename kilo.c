#include<stdio.h>
#include<unistd.h>
#include<termios.h>

void enable_raw_mode(){
  struct termios raw;

  tcgetattr(STDIN_FILENO, &raw);

  raw.c_cflag &= ~(ECHO); // bitwise AND operation on raw.c_cflag and ~(ECHO) and put inside raw.c_cflag
  
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