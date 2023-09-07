#include<stdio.h>
#include<unistd.h>

int main(int argc, char* argv[]){
  printf("Hello World:\n");

  char c;
  while(read(STDIN_FILENO, &c, 1) == 1 && c != 'q'){
    printf("%c", c);
  }
  
  return 0;
}