#include <emscripten.h>
#include <string>
#include <stdio.h>
#include <iostream>

#define MAXN 10

//获得今天零点的时间戳，秒
unsigned int getTodayZeroTime() 
{  
    time_t t = time(NULL); 
    struct tm * tm= localtime(&t);  
    tm->tm_hour = 0;  
    tm->tm_min = 0;  
    tm->tm_sec = 0;  
    return  mktime(tm);
}  

//将数字转为指定进制，decimal为进制值
void f( long int x, char *p ,int decimal)
{
  int i;
  int n;
  int m;
  n = x;
  if (x<0)
  {
     x = -x;
     *p = '-';
     p ++;
  }
  if (x==0)
     *p = '0';
  for (i=0; i<MAXN; i++)
  {
     m = x % decimal;
     x = x / decimal;
     if (m<MAXN)
        *(p + MAXN - 1 -i) = m + '0';
     else
        *(p + MAXN - 1 -i) = m + 'a' - 10;
     if (x==0)
     {
        m = MAXN - 1 -i;
        break;
     }
  }
  for (i=0; i<MAXN-m; i++)
  {
     *(p + i) = *(p + m + i);
     *(p + m + i) = 0;
  }
}

// emcc verify.cc -o verify.html -s EXPORTED_FUNCTIONS="['_verifyCommand']" -s EXPORTED_RUNTIME_METHODS='["ccall"]'

extern "C" {
 int verifyCommand(std::string cmd) {
  int t_time = getTodayZeroTime();
  char t_cmd[MAXN]="";
  f(t_time,t_cmd,36);

  if(strcmp(t_cmd, cmd.data()) == 0){
    return 1;
  }else{
    return 0;
  }
 }
}