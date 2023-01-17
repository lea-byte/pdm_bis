#ifndef DIFF_H // include guard
#define DIFF_H
#include "header.h"

class Diff: public Move{
    private:
        //double tau_diff = 1;
        double rate_diff;
        int type;
        void compute_move_rate() override {rate_diff = (1/t0_diff)*exp(- max(Potential_type(loc1, type)-Potential_type(loc0, type),0.));
        //cout << "rate_diff: " << rate_diff << endl;
        };
            
    public:
        Diff() : Move() {};
        Diff(int l0, int l1, int t): Move(l0, l1){type = t; compute_move_rate(); };
        ~Diff() = default;

        //double get_tau_diff() const {return tau_diff;};
        double get_move_rate() const override {return rate_diff;}; //specialized method
        int get_type() const override {return 0;};
        int select_Chem_move() const override {
            cout << "Calling select_Chem_move() for Diff move!"<<endl;
            return 0;}
        




};

#endif