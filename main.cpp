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
  DWORD written = 1;
  short x,y = 25;
  short height, width = 50;
  short snakeL = 2;
  short coords[height*width][2];
  coords[0][0] = x;
  coords[0][1] = y;
  coords[1][0] = x;
  coords[1][1] = y-1;
  short oX,oY;
  const char *title = "Testing"; 
  const char *head = "*^<v>"; 
  const char *tail = "-|"; 
  int lastKey = 3;
  char *input = new char[5];
  for(int i=0; i<5; i++){
    if(i%2==0)input[i]='a';
    else input[i]='b';
  }
  for(int i=2;i<height*width;i++){
    coords[i][0] = 0;
    coords[i][1] = 0;
  }

  HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ|GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
  SetConsoleActiveScreenBuffer(hConsole);
  if(SetConsoleTitle(title))SetConsoleTitle(title);
  while(true){
        WriteConsoleOutputCharacter(hConsole, head+lastKey, 1, {x,y}, &written);
      for(int i=1;i<snakeL;i++){
        if(coords[i][0]-coords[i-1][0]==0) WriteConsoleOutputCharacter(hConsole, tail+1, 1, {coords[i][0],coords[i][1]}, &written);//färdats vertikalt
        else WriteConsoleOutputCharacter(hConsole, tail, 1, {coords[i][0],coords[i][1]}, &written);//färdats horisontellt
      }
      lastKey = getKey(lastKey);
      switch(lastKey){
        case 1: y--; break;
        case 2: x-=2; break;
        case 3: y++; break;
        case 4: x+=2; break;
          }
      oX = coords[snakeL-1][0];
      oY = coords[snakeL-1][1];
      for(int i=snakeL-1; i>0; i--){
        coords[i][0] = coords[i-1][0];
        coords[i][1] = coords[i-1][1];
        }
      coords[0][0] = x;
      coords[0][1] = y;
      WriteConsoleOutputCharacter(hConsole, " ", 1, {oX,oY}, &written);
      std::cout << x << " " << y << std::endl;
  }
  return 0;
}
