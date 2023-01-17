#ifndef SYSTEM_H // include guard
#define SYSTEM_H

#include "header.h"


class System{
    private: 
        int Length; int Nbr_Part;
        //sym_map2D<int, Move*> moves;
        sym_map2D<int, Move* > moves;
        vector<int> state;
        int counter;
        vector<double> state_time; vector<double> state_time1; vector<double> state_time2; vector<double> state_time3;
        double time; double time_flux;
        vector<double> flux_chem12; vector<double> flux_chem13; vector<double> flux_chem23;
        vector<double> count_1; vector<double> count_2; vector<double> count_3;
        vector<double> tdiff_1; vector<double> tdiff_2; vector<double> tdiff_3;
        vector<double> tchem_1; vector<double> tchem_2; vector<double> tchem_3;

        vector<double> flux_diff_test; vector<double> count_test; 
        
        void syst_actualize_state(const Move* m);// used in syst_evolve
        void compute_syst_cum_rates( vector<double>& cum_rates, vector<Move*>& ID_moves);
        vector<int> neighborhood(int I);//used in syst_evolve
        void flux_diff(Move* move, double dt);

    public:
        System(double t = 0);//initialize time of the system 
        System(int length, int nbr_part); // constructor : initialize random state

        vector<int> get_syst_state() const;
        vector<double> get_syst_state_time() const;
        vector<double> get_syst_state_time1() const;
        vector<double> get_syst_state_time2() const;
        vector<double> get_syst_state_time3() const;
        sym_map2D<int, Move> get_syst_moves() const;
        double get_syst_time() const;
        vector<double> get_flux_chem(int i, int j) const;
        vector<double> get_flux_diff(int i) const;
        double get_syst_count(int i) const;

        void syst_initialize_moves();
        void syst_evolve() ;//select move and delete it + update states
        //void syst_actualize_move(int init, int final);


};
#endif