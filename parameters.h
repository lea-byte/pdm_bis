#ifndef PARAMETERS_H // include guard
#define PARAMETERS_H
#include "header.h"


double dx; // discretization of space
double x0; // initial position
double xf; // final position
//double k_B = 1.380649*pow(10,-23); //constante de Boltzmann
//double T = 25; //temperature

    //characteristic reaction time
    double t0_diff = 1; // diffusion time
    //double t0_chem = 1; // chemical transformation time
    double t0_chem_12 = 1;
    double t0_chem_13 = 1;
    double t0_chem_23 = 1;
    //Potential
    double V0; 
    int step = 25;//if potential is step function
    double eps1 = 0.01; //btw 1 and 2
    double eps2 = 0.02; //btw 1 and 3   
    double eps3 = 0.03; //btw 2 and 3
    double V01 = 1;//30;
    double V02 = 1;//50;
    double V03 = 1;//10;
    //System inf
    int type = 1; //type by default of a molecule (or\text{such that,}\quad j_0=j_L=0\text{such that,}\quad j_0=j_L=0\text{such that,}\quad j_0=j_L=0\text{such that,}\quad j_0=j_L=0\text{such that,}\quad j_0=j_L=0\text{such that,}\quad j_0=j_L=0\text{such that,}\quad j_0=j_L=0\text{such that,}\quad j_0=j_L=0\text{such that,}\quad j_0=j_L=0\text{such that,}\quad j_0=j_L=0\text{such that,}\quad j_0=j_L=0\text{such that,}\quad j_0=j_L=0\text{such that,}\quad j_0=j_L=0\text{such that,}\quad j_0=j_L=0\text{such that,}\quad j_0=j_L=0\text{such that,}\quad j_0=j_L=0\text{such that,}\quad j_0=j_L=0\text{such that,}\quad j_0=j_L=0\text{such that,}\quad j_0=j_L=0 initially)
    double step_max = 400000000; //max time of simulation
    int length = 50;
    double nbr_part = 1;
    //Chemical moves
    bool chem = true; 
    int nbr_type = 3;
    double A12 = 1; double A13 = 1; double A23 = 1;
    bool write_state = false;

    void set_V0(double V){V0 = V;}

#endif