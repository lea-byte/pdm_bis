#include "Move.h"
//#include "header.h"

// constructor
Move::Move(int l0, int l1){
    loc0 = l0; loc1 = l1; //compute_move_rate();
}; 


//getters
int Move::get_move_loc_init() const {return loc0;};
int Move::get_move_loc_fin() const {return loc1;};
//int Move::get_move_type() const {return type;};


/* void Move::compute_move_rate(){
     if (diff){
        rate = (1/t0_diff)*exp(- (Potential(loc1)-Potential(loc0)));
    }
    if (chem){
        rate = (1/t0_chem)*exp(- (Potential(loc1)-Potential(loc0)));;
    } 
}; */