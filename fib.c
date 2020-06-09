/*
AUTHOR: Yousam Asham
MACID: ashamy1
STUDENT#: 400174082
SFWRENG 2S03 Dr. Nedialov
*/
#include <stdio.h>
#include "bmp.h"
#include <string.h>
#include <stdlib.h>
char* Fibonacci_word(int n){
  char* before = "1", *current = "0", *temp;
  char* new_element = (char*)malloc(n*n*n*n*n*n);
  if (!new_element)
    return NULL;
  int i=0;
  temp=malloc(strlen(current)+1);
  if (temp==NULL) return NULL;
  strcpy(temp,current);
  strcat(strcat(new_element,current), before);
  current = new_element;
  before = temp;
  new_element=NULL;
  temp=NULL;
  for (i=0;i<n-3;i++){
    temp=malloc(strlen(current)+1);
    if (temp==NULL) return NULL;
    strcpy(temp,current);
    new_element=strcat(current,before);
    before = temp;
    new_element=NULL;
    temp=NULL;
  }
  free(temp);
  free(new_element);
  return current;
}
int fib(int n, int x, int y, int step, RGB bc, RGB fc, int w, int h, RGB* image){
  #define I(i, j) image[(i)*w + j]
  if (step < 2){
    printf("Step must be at least '2'\n");
    return 0;
  }
  if(x < 0 || x >= w || y < 0 || y >= h){
    printf("Starting position out of image dimensions\n");
    return 0;
  }
  char* word = Fibonacci_word(n);
  if (word==NULL)
    return 0;
  int word_length = strlen(word),c,g,i;
  for (g = 0; g < w*h ; g++)
    image[g]=bc;
  typedef enum {
    up,
    right,
    down,
    left
  } direction;
  direction dir = 0;
  for (i = 0; i<word_length;i++){
      if (dir == right){
        for (c = 0; c < step ; c++)
          I(x, y + c)=fc;
        if(y+step < 0 || y+step > w || x < 0 || x > h){
          printf("Moving right...\nPosition out of image dimensions\n %d\n %d\n",x, y);
          return 0;
        }
        y+=step;
    }
      if (dir == left){
        for (c = 0; c < step ; c++)
          I(x, y - c)=fc;
        if(y-step < 0 || y-step > w || x < 0 || x > h){
          printf("Moving left...\nPosition out of image dimensions\n %d\n %d\n",x, y);
          return 0;
        }
        y-=step;
    }
      if (dir == up){
        for (c = 0; c < step ; c++)
          I(x + c, y)=fc;
        if(y < 0 || y > w || x+step < 0 || x+step > h){
          printf("Moving up...\nPosition out of image dimensions\n %d\n %d\n",x, y);
          return 0;
        }
        x+=step;
    }
      if (dir == down){
        for (c = 0; c < step ; c++)
         I(x - c, y)=fc;;
       if(y < 0 || y > w || x-step < 0 || x-step > h){
         printf("Moving down...\nPosition out of image dimensions\n %d\n %d\n",x, y);
         return 0;
       }
       x-=step;
    }
    if (word[i] == '0'){
      if ((i+1) % 2 == 0){
        if (dir == up)
          dir = left;
        else
          dir--;
      }
      else{
        if (dir == left)
          dir = up;
        else
          dir++;
  }
  }
  }
  free(word);
  return word_length;
}
