#include <stdint.h>

#include "RVCOS.h"

void WriteString(const char *str){
    const char *Ptr = str;
    while(*Ptr){
        Ptr++;
    }
    RVCWriteText(str,Ptr-str);
}

void WriteInt(int val){
    char Buffer[16];
    int Index = 14;
    int IsNeg = 0;
    Buffer[15] = '\0';
    do{
        Buffer[Index] = val % 10;
        if(Buffer[Index] < 0){
            Buffer[Index] = -Buffer[Index];
        }
        Buffer[Index] += '0';
        Index--;
        val /= 10;
        if(val < 0){
            val = -val;
            IsNeg = 1;
        }
    }while(val);
    if(IsNeg){
        Buffer[Index] = '-';
        Index--;
    }
    Buffer[Index] = ' ';
    WriteString(Buffer + Index);
}


int main() {
  uint32_t* time;
  WriteString("time is: ");
  RVCTickCount(time);
  WriteInt(*time);
  WriteString("\n");

  for (int i =0 ; i < 10000; i++){
    ;
  }

  WriteString("time is: ");
  RVCTickCount(time);
  WriteInt(*time);
  return 0;
}
