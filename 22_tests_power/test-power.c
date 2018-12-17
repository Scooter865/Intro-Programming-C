#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

int main(void){
  unsigned x[] =   {0, 1, 2, 2, 2, 2, -2, -2/*,  2,     -2*/};
  unsigned y[] =   {0, 1, 0, 1, 2, 3,  3,  4/*, -3,     -3*/};
  unsigned ans[] = {1, 1, 1, 2, 4, 8, -8, 16/*,  0.125, -0.125*/};
  size_t n = 8;
  
  //loop through each test case
  for (int i = 0; i < n; i++) {
    printf("power returned %d, ans is %d\n", power(x[i], y[i]), ans[i]);
    if (power(x[i], y[i]) != ans[i]){
      printf("Encountered wrong answer\n");
      //exit if the returned value is incorrect
      exit(EXIT_FAILURE);
    }
  }
  printf("correct implementation!\n");
  return EXIT_SUCCESS;
}
