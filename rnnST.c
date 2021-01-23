#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// number of simulation steps
static int nmbSteps;

// global free parameter of the recurrent neural network
static double B;
static double R;
static double W;



// activity value of the single neuron
static double a_1;


// connectivity values of the recurrent neural network
//



void getCommandLine(int argc, char *argv[]){

  if(argc == 1){
      B = 25.0;
      R = 12.0;
      W = -50.0;
      nmbSteps = 5000;
      return;
  }

  if(argc == 5){
      
    if( sscanf(argv[1],"%lf",&B) != 1){
      printf("Could not parse numeric value from 1st command line argument: '%s'\n\n", argv[1]);
      exit(EXIT_FAILURE);
    }

    if( sscanf(argv[2],"%lf",&R) != 1){
      printf("Could not parse numeric value from 2nd command line argument: '%s'\n\n", argv[2]);
      exit(EXIT_FAILURE);
    }

    if( sscanf(argv[3],"%lf",&W) != 1){
      printf("Could not parse numeric value from 3rd command line argument: '%s'\n\n", argv[3]);
      exit(EXIT_FAILURE);
    }

    if( sscanf(argv[4],"%d",&nmbSteps) != 1){
      printf("Could not parse numeric value from 4th command line argument: '%s'\n\n", argv[4]);
      exit(EXIT_FAILURE);
    }

    return;
  }

  printf("\nWrong number of command line parameters! Please use in the following to ways:\n\n");
  printf("1.) using default values (B=25, R=12, W=-50.0, nmbSteps=5000):  %s    \n\n", argv[0]);
  printf("2.) specifing free numeric parameters B, R, W and nmbSteps:  %s  <B> <R> <W> <nmbSteps>   \n\n\n", argv[0]);
  exit(EXIT_FAILURE);
}


double sigmoide(double x){
  double y;
  y = 1.0 / (1 + exp(-x));
  return y;
}

void resetNeuronActivities(){
  a_1= 0.0002;
}


void updateNeuronActivities(double s){
  a_1 = B + R*sigmoide(a_1) + s*W;
}

int main(int argc, char *argv[])
{

  getCommandLine(argc,argv);
  resetNeuronActivities();

  int i;
  double inputSignal;
  double motorSignal;
  double delta;

  delta = 1.0 / ((double)nmbSteps);
  inputSignal = 0.0;
  while(inputSignal < 1.0){
    updateNeuronActivities(inputSignal);
    printf("%f\t%f\n", inputSignal,sigmoide(a_1));
    inputSignal = inputSignal + delta;
  }

  while(inputSignal > 0.0){
    updateNeuronActivities(inputSignal);
    motorSignal = sigmoide(a_1);
    printf("%f\t%f\n", inputSignal,motorSignal);
    inputSignal = inputSignal - delta;
  }

  exit(EXIT_SUCCESS);
}


