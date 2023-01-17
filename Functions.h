#ifndef FUNCTIONS_H // include guard
#define FUNCTIONS_H

#include "header.h"
//#include "Functions.cpp"

double Potential(int localization); // return potential value at "localization"
double Potential_type(int localization, int type);

double compute_rate(double init_pot, int final_pot, bool diff = true, bool chem = false);// à appeler dans syst_initialize

//vector<int> state_generator(int length, int nbr_part);



#endif