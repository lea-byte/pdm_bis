#ifndef CHEM_H // include guard
#define CHEM_H
#include "header.h"

class Chem: virtual public Move{
    private:
        
        double rate_chem1;
        double rate_chem2;
        int type;

        void compute_move_rate() override {
            if(type == 1){
                    // transfo 1 to 2
                    //double eps = min(Potential_type(loc1, 2), Potential_type(loc0, type)) + 0.5*abs(Potential_type(loc1, 2)- Potential_type(loc0, type));
                    rate_chem1 = A12*(1/t0_chem_12)*exp(- max(Potential_type(loc1, 2)-Potential_type(loc0, type), 0.) - eps1);
                if(nbr_type == 2){   
                    rate_chem2 =0;
                } else if(nbr_type == 3){ //transfo 1 to 3
                    //double epsbis = min(Potential_type(loc1, 3), Potential_type(loc0, type)) + 0.5*abs(Potential_type(loc1, 3)- Potential_type(loc0, type));
                    //rate_chem2 = (1/t0_chem_13)*exp(- max(Potential_type(loc1, 3)-Potential_type(loc0, type), 0.) - loc0*0.7/length);
                    //cout<< Potential_type(loc1, 3)-Potential_type(loc0, type) << endl;
                    rate_chem2 = A13*(1/t0_chem_13)*exp(- max(Potential_type(loc1, 3)-Potential_type(loc0, type), 0.) - eps2);
                } 
            } else if(type == 2){
                // transfo 2 to 1
                //double eps = min(Potential_type(loc1, 1), Potential_type(loc0, type)) + 0.5*abs(Potential_type(loc1, 1)- Potential_type(loc0, type));
                rate_chem2 = (1/t0_chem_12)*exp(- max(Potential_type(loc1, 1)-Potential_type(loc0, type), 0.) - eps1);
                if(nbr_type == 2){                    
                    rate_chem1 = 0; //transfo 2 to 3
                } else if (nbr_type == 3){
                    //double epsbis = min(Potential_type(loc1, 3), Potential_type(loc0, type)) + 0.5*abs(Potential_type(loc1, 3)- Potential_type(loc0, type));
                    //cout<< Potential_type(loc1, 3)-Potential_type(loc0, type) << endl;
                    rate_chem1 = A23*(1/t0_chem_23)*exp(- max(Potential_type(loc1, 3)-Potential_type(loc0, type), 0.) - eps3);
                }
                
            } else if(type == 3){
                 // transfo 3 to 2
                    //double eps = min(Potential_type(loc1, 2), Potential_type(loc0, type)) + 0.5*abs(Potential_type(loc1, 2)- Potential_type(loc0, type));
                    rate_chem2 = (1/t0_chem_23)*exp(- max(Potential_type(loc1, 2)-Potential_type(loc0, type), 0.) - eps3);
                 // transfo 3 to 1 
                    //double epsbis = min(Potential_type(loc1, 1), Potential_type(loc0, type)) + 0.5*abs(Potential_type(loc1, 1)- Potential_type(loc0, type));  
                    rate_chem1 = (1/t0_chem_13)*exp(- max(Potential_type(loc1, 1)-Potential_type(loc0, type), 0.) - eps2);
                }
            

            //rate_chem = (1/tau_chem)*exp(- (Potential_type(loc1, type1)-Potential_type(loc0, type0)));
            };

    
    public:

        Chem() : Move() {};
        Chem(int l, int t): Move(l, l){
            //type =-type0 +3; 
            type = t;
            compute_move_rate(); 
            //cout << "loc1: " << loc1 << " loc2: " << loc0 << " type: " << type << " rate_chem1: " << rate_chem1 << " rate_chem2: " << rate_chem2 << endl;
        };
        ~Chem() = default;

        

        double get_move_rate() const override {return rate_chem1+rate_chem2;}; //specialized method
        int get_type() const override{
            D(cout << "call get_type() for chem" << endl;);
            return type;};


        int select_Chem_move() const override{
            static std::default_random_engine generator;
            std::uniform_real_distribution<double> Distribution(0., rate_chem1+rate_chem2);
            double rand = Distribution(generator);
            //cout <<"OG type: " << type << " rate_chem1: " << rate_chem1 << " rate_chem2: " << rate_chem2 << " rand: " << rand <<endl;
                if(rand < rate_chem1 ){
                    //reaction 1 chosen
                    //cout << "reaction 1 chosen " << (type % 3) + 1 <<endl;
                    return (type % 3) + 1;
                    //return (type + 1) % 2 + 2;
                } else {
                    //reaction 2 chosen
                    //cout << "reaction 2 chosen " << (type + 1) % 3 + 1 <<endl;
                    
                    return (type + 1) % 3 + 1;
                    //return ((type + 1) % 4) % 3 + 1;

                }
            
        cerr<<"unknown type"<<endl;
        exit(0);

        }    
};



#endif