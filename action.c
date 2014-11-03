/*We are going to build up the program to compute the action for the harmonic oscillator potential*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


#define iterations 3            /*some constants and fixed parameters*/
#define N 10
#define rep 5
double delta=0.5;
double m=1, hbar=1, w=1, a=0.1;


double square (double b);
double randomgen (double value, double delta);


double i_c[N]={0.3, 0.4, 0.5, 0.1, -0.2, -0.4, -0.2, 0.1, 0.2, 0.3};              /*initial configuration of the system*/
double path[iterations][N];

int main (){
  double value, S0=0, S_in, Sn;
  double S[N];
  double deltacond, r;
  for (int n=0; n<N; n++){
     S[n]=((m*a)/(2*hbar))*(square((i_c[n+1]-i_c[n])/a)-square(w)*((square(i_c[n+1])+square(i_c[n]))/2));
     S0=S0+S[n];
     printf("%0.2f\n", S0);
  }
  S_in=S0;
  printf("The initial action S0 is: %0.2f\n", S0);

  for (int j=0; j<iterations; j++){
     for (int n=0; n<N; n++){
        value=i_c[n];
        path[j][n]=i_c[n];      /*Here I will keep the coordinates of each final path*/
        for (int l=0; l<rep; l++){
           Sn=0;
           printf("Error 0: %f\n", value);
           randomgen(value, delta);
           printf("Error 1: %f\n", value);
           i_c[l]=value;
           for (int k=0; k<N; k++){
              S[k]=((m*a)/(2*hbar))*(square((i_c[k+1]-i_c[k])/a)-square(w)*((square(i_c[k+1])+square(i_c[k]))/2));
              Sn=Sn+S[k];
	   }
	   printf("Error 2: %f\n", Sn);
           if (Sn<=S0){
	     S0=Sn;
	     path[j][n]=value;
	   }
	   else{
	     deltacond=(double)exp(-(Sn-S0));
	     r=(double)random()/(double)RAND_MAX;
	     if (deltacond>r){
	       S0=Sn;
	       path[j][n]=value;
	     }
	   }
        }
     }
  S0=S_in;
  }

  for (int j=0; j<iterations; j++){
    printf("Coordenadas del path %d\n", j);
    for (int n=0; n<N; n++){
      printf("%0.3f\n", path[j][n]);
    }
  }
}


double square (double b){    /*defition of a function to square sth*/
  double z;
  z = b*b;
  return(z);
}


double randomgen (double value, double delta){
  time_t start, end;
  time (&start);
  srand(time(NULL));

  value=(2*delta)*((double)random()/(double)RAND_MAX)+(value-delta);
}
