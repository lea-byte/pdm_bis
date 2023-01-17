#ifndef MOVE_H // include guard
#define MOVE_H
#include "header.h"

class Move{
    protected:
        int loc0; // localization of the move
        int loc1;
        //double rate; // rate of move
        //bool diff = true;
        //bool chem = false;
    
    public:
        Move() = default;

        virtual void compute_move_rate() = 0;
        virtual int select_Chem_move() const = 0;

        Move(int l0, int l1); // constructor
        virtual ~Move() = default; // destructor
        
        int get_move_loc_init() const;
        int get_move_loc_fin() const;

        virtual double get_move_rate() const = 0;
        virtual int get_type() const = 0;




};
#endif