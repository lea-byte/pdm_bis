#include "Functions.h"
#include "header.h"

/* double Potential(int localization){
        /* if (localization < step) return 0;
    else return V0;   
    return (tanh(0.1*(localization - length/2))+1)*0.5;

}; */

double Potential_type(int localization, int type){
    if (type == 1){
             /* if (localization < step) return 0;
        else return V0;   */ 
        return (tanh(0.07*(localization - length/2))+1)*0.5*V01;//0.07
    } else if (type == 2) {
              /* if (localization < step) return 0;
        else return V0; */   
        return (tanh(0.1*(localization - length/2))+1)*0.5*V02;//0.1
    } else if (type == 3) {
            /* if (localization < step) return 0;
        else return V0;   */
        return (tanh(0.2*(localization- length/2))+1)*0.5*V03;//0.2
    }
    return 0;
};

    /*double epsilon_fct(int i){
        double eps=0;
        if(i>=0 and i<length){
            eps = i*(0.7/length);
        } else {cout << "warning eps" << endl;
                return 0.;}
        return eps;
    }
/* double compute_rate(double init_pot, double final_pot, bool diff = true, bool chem = false){
    if (diff){
        return (1/t0_diff)*exp(- (final_pot-init_pot));
    }
    if (chem){
        return (1/t0_chem)*exp(- (final_pot-init_pot));//REVOIR!!!!!!!
    }
    return 0.;
}; */

/* vector<int> state_generator(int length, int nbr_part){
    
    vector<int> X0(length,0);// initial state

    //Random assignment of  particles to an initial localization in X0
    vector<int> temp = {};
    for (size_t i = 1; i <= nbr_part; i++)
    {
        static std::default_random_engine generator;
        std::uniform_real_distribution<double> distribution (0.,length);
        int id = (int)distribution(generator);
        // accept answer if not already occupied
        if(find(temp.begin(), temp.end(), id) == temp.end()){
            //If no elements match, the function returns last
            X0[id]= type;
            temp.push_back(id);
        } 
        else {i = i-1;};
         
    }
    cout << "state generator  ";
    return X0;
}; */

/* vector<double> rate_vector(int type1, int type2){
    vector<double> k(length, 0);
    int A = 1; double eps; double tau_chem;

    if(type1 == 1){
        if(type2 == 2){
            A = A12;
            eps = eps1;
            tau_chem = t0_chem_12;
        } else if(type2 == 3){
            A = A13;
            eps = eps2;
            tau_chem = t0_chem_13;
        }
    } else if(type1 == 2){
        if(type2 == 1){
            eps = eps1;
            tau_chem = t0_chem_12;
        } else if(type2 == 3){
            A = A23;
            eps = eps3;
            tau_chem = t0_chem_23;
        }
    } else if(type1 == 3){
        if(type2 == 1){
            eps = eps2;
            tau_chem = t0_chem_13;
        } else if(type2 == 2){
            eps = eps3;
            tau_chem = t0_chem_23;
        }
    }
        for (size_t i = 0; i < length; i++)
        {
           k[i] = A*(1/tau_chem)*exp(- max(Potential_type(i, type2)-Potential_type(i, type1), 0.) + eps);
           //cout << i << "  Potential_type(i, type2) "<< Potential_type(i, type2) << " Potential_type(i, type1) " << Potential_type(i, type1) << endl;
        }
        
    return k;

} */