#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// number of simulation steps
static double S;
static int nmbSteps;

// global free parameter of the recurrent neural network



// activity value of the single neuron
static double a_1;
static double a_2;

// connectivity values of the recurrent neural network
//



void getCommandLine(int argc, char *argv[]){

  if(argc == 1){
    S=0.6;
    nmbSteps = 5000;
    return;
  }

  if(argc == 3){
      
    if( sscanf(argv[1],"%lf",&S) != 1){
      printf("Could not parse numeric value from 1st command line argument: '%s'\n\n", argv[1]);
      exit(EXIT_FAILURE);
    }

    if( sscanf(argv[2],"%d",&nmbSteps) != 1){
      printf("Could not parse numeric value from 2nd command line argument: '%s'\n\n", argv[2]);
      exit(EXIT_FAILURE);
    }
    return;
  }

  printf("\nWrong number of command line parameters! Please use in the following to ways:\n\n");
  printf("1.) using default values (S=0.6, nmbSteps=5000):  %s    \n\n", argv[0]);
  printf("2.) specifing free numeric parameters S and nmbSteps:  %s  <S> <nmbSteps>   \n\n\n", argv[0]);
  exit(EXIT_FAILURE);
}


double sigmoide(double x){
  double y;
  y = 1.0 / (1 + exp(-x));
  return y;
}

void resetNeuronActivities(){
  a_1= 0.0002;
  a_2= 0.0001;
}


void updateNeuronActivities(double s1,double s2){
  a_1 = 25.0 + 12.0*sigmoide(a_1) - 20.0*sigmoide(a_2) - s2*50.0;
  a_2 = 25.0 + 12.0*sigmoide(a_2) - 20.0*sigmoide(a_1) - s1*50.0;
}

int main(int argc, char *argv[])
{

  getCommandLine(argc,argv);
  resetNeuronActivities();

  int i;
  double inputSignal1;
  double inputSignal2;
  double motorSignal1;
  double motorSignal2;
  double delta;

  delta = 1.0 / ((double)nmbSteps);
  inputSignal1 = 0.0;
  inputSignal2 = S;
  while(inputSignal1 < 1.0){
    updateNeuronActivities(inputSignal1,inputSignal2);
    motorSignal1 = sigmoide(a_1);
    motorSignal2 = sigmoide(a_2);

    printf("%f\t%f\t%f\t%f\n", inputSignal1, inputSignal2,motorSignal1,motorSignal2);
    inputSignal1 = inputSignal1 + delta;
  }

  while(inputSignal1 > 0.0){
    updateNeuronActivities(inputSignal1,inputSignal2);
    motorSignal1 = sigmoide(a_1);
    motorSignal2 = sigmoide(a_2);

    printf("%f\t%f\t%f\t%f\n", inputSignal1, inputSignal2,motorSignal1,motorSignal2);
    inputSignal1 = inputSignal1 - delta;
  }

  exit(EXIT_SUCCESS);
}


