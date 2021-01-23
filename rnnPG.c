#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// number of simulation steps
static int nmbSteps;

// global free parameter of the recurrent neural network
static double E;
static double F;
static double P;
static double W;


// activity values of the single neurons
static double a_1;
static double a_2;
static double a_3;

// connectivity values of the recurrent neural network
static double a;
static double b;


void getCommandLine(int argc, char *argv[]){

  if(argc == 1){
      E = 0.08;
      F = 0.1;
      P = -10.0;
      W = 20.0;
      nmbSteps = 5000;
      return;
  }

  if(argc == 6){
      
    if( sscanf(argv[1],"%lf",&E) != 1){
      printf("Could not parse numeric value from 1st command line argument: '%s'\n\n", argv[1]);
      exit(EXIT_FAILURE);
    }

    if( sscanf(argv[2],"%lf",&F) != 1){
      printf("Could not parse numeric value from 2nd command line argument: '%s'\n\n", argv[2]);
      exit(EXIT_FAILURE);
    }

    if( sscanf(argv[3],"%lf",&P) != 1){
      printf("Could not parse numeric value from 3rd command line argument: '%s'\n\n", argv[3]);
      exit(EXIT_FAILURE);
    }

    if( sscanf(argv[4],"%lf",&W) != 1){
      printf("Could not parse numeric value from 4th command line argument: '%s'\n\n", argv[4]);
      exit(EXIT_FAILURE);
    }

    if( sscanf(argv[5],"%d",&nmbSteps) != 1){
      printf("Could not parse numeric value from 5th command line argument: '%s'\n\n", argv[5]);
      exit(EXIT_FAILURE);
    }

    return;
  }

  printf("\nWrong number of command line parameters! Please use in the following to ways:\n\n");
  printf("1.) using default values (E=0.08, F=0.1, P=-10.0, W=20.0; nmbSteps=5000):  %s    \n\n", argv[0]);
  printf("2.) specifing free numeric parameters E, F, B, W and nmbSteps:  %s  <E> <F> <P> <W> <nmbSteps>    \n\n\n", argv[0]);
  exit(EXIT_FAILURE);
}


double sigmoide(double x){
  double y;
  y = 1.0 / (1 + exp(-x));
  return y;
}

void resetNeuronActivities(){
  a_1 = 0.0002;
  a_2 = 0.003;
  a_3 = 0.001;
}



void setConnectivityParameters(){
  a = (1.0 + E)*4.0*cos(F);
  b = (1.0 + E)*4.0*sin(F);
}


void updateNeuronActivities(){
  a_1 = a*sigmoide(a_1) + b*sigmoide(a_2) - 0.5*(a+b);
  a_2 = a*sigmoide(a_2) - b*sigmoide(a_1) + 0.5*(b-a);
  a_3 = W*sigmoide(a_2) + P;
}

int main(int argc, char *argv[]){

  

  getCommandLine(argc,argv);
  setConnectivityParameters();
  resetNeuronActivities();

  int i = 0;
  while(i++ < nmbSteps){
    updateNeuronActivities();
    printf("%d\t%f\t%f\t%f\n",
	   i,sigmoide(a_1),sigmoide(a_2),sigmoide(a_3));
  }
  

 
  exit(EXIT_SUCCESS);
}


