#include <iostream>
#include <windows.h>
#include <conio.h>
int getKey(int lastKey){
  HANDLE hstdin;
  DWORD mode, timer;
  hstdin = GetStdHandle(STD_INPUT_HANDLE);
  GetConsoleMode(hstdin, &mode);
  SetConsoleMode(hstdin, ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT);
  timer = GetTickCount() + 50;
  while(!kbhit()){
    while(timer > GetTickCount()){
      if(kbhit()){
        int button = std::cin.get();
      switch(button){
        case 119:
          if(lastKey%2 == 0)lastKey = 1;
          break; //up
        case 97:
          if(lastKey%2 == 1)lastKey = 2;
          break;//left
        case 115: 
          if(lastKey%2 == 0)lastKey = 3;
          break;//down
        case 100: 
          if(lastKey%2 == 1)lastKey = 4;
          break;//right
      }
      }
    }
      SetConsoleMode(hstdin, mode);
      return lastKey;
  }
  SetConsoleMode(hstdin, mode);
  return lastKey;
}
int main(){
  DWORD written = 0;
  short x,y = 0;
  short oX,oY;
  const char *title = "Testing"; 
  const char *write = "abc"; 
  int lastKey = 3;
  char *input = new char[5];
  for(int i=0; i<5; i++){
    if(i%2==0)input[i]='a';
    else input[i]='b';
  }
  HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ|GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
  SetConsoleActiveScreenBuffer(hConsole);
  if(SetConsoleTitle(title))SetConsoleTitle(title);
  while(true){
      WriteConsoleOutputCharacter(hConsole, input, 1, {x,y}, &written);
      oX = x;
      oY = y;
      lastKey = getKey(lastKey);
      switch(lastKey){
        case 1: y--; break;
        case 2: x-=2; break;
        case 3: y++; break;
        case 4: x+=2; break;
          }
      WriteConsoleOutputCharacter(hConsole, " ", 1, {oX,oY}, &written);
      std::cout << x << " " << y << std::endl;
  }
  return 0;
}
