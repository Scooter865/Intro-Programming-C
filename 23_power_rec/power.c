#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y){
  //e.g. power(2,3) needs to call power(2,2) then power(2,1)
  //cover y=0 case
  if (y == 0){
    return 1;
  }
  //base case when y = 1 (just return x) - don't think I need this actually
  //else if (y == 1){
  //  return x;
  //}
  //if y>0, multiply by x and run power with x and y-1
  else {
    return x * power(x,y-1);
  }
  //if y<0, multiply by x and run power with x and y+1
  //else{
  //  return x * power(x,y+1);
  //}
}
