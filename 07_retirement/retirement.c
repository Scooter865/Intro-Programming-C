#include "stdlib.h"
#include "stdio.h"

struct _retire_info {
  int months; //months spent working or retired
  double contribution; //dollars contributed
  double rate_of_return; //yeah
};
typedef struct _retire_info retire_info;

double balanceCalc(retire_info status, double startBal) {
  double bal = startBal;
  bal = bal + (bal * status.rate_of_return);
  bal = bal + status.contribution;
  return bal;
}

void retirement(int startAge, double intial, retire_info working, retire_info retired) {
  double balance = intial;
  int ageYear = startAge / 12;
  int ageMonth = startAge % 12;
  
  for(int i = startAge; i < (startAge + working.months + retired.months); ++i) {
    ageYear = i / 12;
    ageMonth = i % 12;
    
    printf("Age %3d month %2d you have $%.2lf\n", ageYear, ageMonth, balance);

    if (i < (startAge + working.months)) {
      balance = balanceCalc(working, balance);
    }
    else {
      balance = balanceCalc(retired, balance);
    }
  }
}

int main(void) {
  retire_info working;
  retire_info retired;

  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045/12;

  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01/12;

  retirement(327, 21345, working, retired);

  return EXIT_SUCCESS;
}
