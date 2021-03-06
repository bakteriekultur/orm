#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
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
short wrapAround(short coord, short max){
  if(coord<0)return max;
  if(coord>max)return 0;
  return coord;
}
int main(){
  const char *title = "Orm i konsolen"; 

  HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ|GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
  SetConsoleActiveScreenBuffer(hConsole);
  if(SetConsoleTitle(title))SetConsoleTitle(title);
  DWORD written = 1;
  COORD mWindowSize = GetLargestConsoleWindowSize(hConsole);
  CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
  GetConsoleScreenBufferInfo(hConsole, &bufferInfo);
  bool running = true;
  bool fruitSearch = true;
  bool sameFruitCoord = false;
  bool newSize = false;
  short x = 20;
  short y = 30;
  short mWidth = mWindowSize.X;
  short mHeight = mWindowSize.Y;
  short cWidth = bufferInfo.srWindow.Right - bufferInfo.srWindow.Left +1;
  short cHeight = bufferInfo.srWindow.Bottom - bufferInfo.srWindow.Top +1;
  short snakeL = 2;
  short coords[mHeight*mWidth][2];
  short fCoords[2];
  coords[0][0] = x;
  coords[0][1] = y; //startkoordinater för huvudet och en svans
  coords[1][0] = x;
  coords[1][1] = y-1;
  const char *head = "*^<v>"; //alla olika huvuden
  const char *tail = "-|"; //alla olika svansar
  int lastKey = 3;
  for(int i=2;i<mHeight*mWidth;i++){
    coords[i][0] = 0;
    coords[i][1] = 0;
  }
  

  while(running){
    GetConsoleScreenBufferInfo(hConsole, &bufferInfo);
    short cWidth = bufferInfo.srWindow.Right - bufferInfo.srWindow.Left +1; //kollar nuvarande fönsterstorlek
    short cHeight = bufferInfo.srWindow.Bottom - bufferInfo.srWindow.Top +1;
    coords[0][0] = wrapAround(coords[0][0], cWidth);
    x = coords[0][0];
    coords[0][1] = wrapAround(coords[0][1], cHeight);
    y = coords[0][1];
    if((coords[0][0] == fCoords[0] || coords[0][0] == fCoords[0]+1) && coords[0][1] == fCoords[1]){
      newSize = true;
      fruitSearch = true;
      WriteConsoleOutputCharacter(hConsole, " ", 1, {fCoords[0], fCoords[1]}, &written);
    }
    while(fruitSearch){
      fCoords[0] = rand()%cWidth;
      fCoords[1] = rand()%cHeight;
      sameFruitCoord = false;
      for(short i=0;i<snakeL;i++){
        if(coords[i][0]==fCoords[0] && coords[i][1]==fCoords[1]){
          sameFruitCoord = true;
          break;
        }
      }
        if(!sameFruitCoord){
          fruitSearch = false;
          WriteConsoleOutputCharacter(hConsole, "@", 1, {fCoords[0], fCoords[1]}, &written);
        }
      }
    for(short i=1;i<snakeL;i++){
      if(coords[0][0]==coords[i][0] && coords[0][1]==coords[i][1]){
        running = false;                                                    //kollision med sin svans.
        lastKey = 0;
        }
      }
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
      if(!newSize)WriteConsoleOutputCharacter(hConsole, " ", 1, {coords[snakeL-1][0],coords[snakeL-1][1]}, &written);
      else{
        newSize = false;
        snakeL++;
      }
      for(int i=snakeL-1; i>0; i--){
        coords[i][0] = coords[i-1][0];
        coords[i][1] = coords[i-1][1];
        }
      coords[0][0] = x;
      coords[0][1] = y;
    }
  std::cout << "Du dog, du at " << snakeL-2 << " frukter!"<<std::endl;
  return 0;
}
