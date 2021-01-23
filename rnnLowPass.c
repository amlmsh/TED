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
static double a_2;


// connectivity values of the recurrent neural network
//



void getCommandLine(int argc, char *argv[]){

  if(argc == 1){
      B = -2.67;
      R = 5;
      W = 0.35;
      nmbSteps = 30000;
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
  printf("1.) using default values (B=-2.67, R=5.0, W=0.35, nmbSteps=30000):  %s    \n\n", argv[0]);
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
  a_2 = 10.0 + 15.0*sigmoide(a_2) + (-30*sigmoide(a_1));
}

int main(int argc, char *argv[])
{

  getCommandLine(argc,argv);
  resetNeuronActivities();

  int i;
  double inputSignal;
  double delta;
  double g;

  delta = 50.0 / ((double) nmbSteps );
  g = 10.0 /  ((double) nmbSteps );


  for(i=0; i < nmbSteps; i++){
    inputSignal = delta*((double) i);

    inputSignal = sin(g*((double) i)*inputSignal);

    // scale to interval [0,1]
    inputSignal = (inputSignal + 1.0 ) / 2.0;
    updateNeuronActivities(inputSignal);
    printf("%f\t%f\t%f\n", inputSignal,sigmoide(a_1),sigmoide(a_2));
  }

  exit(EXIT_SUCCESS);
}


