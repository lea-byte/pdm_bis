#include "header.h"
#include "System.h"


//constructor
System::System(double t) {time = t;};

System::System(int length, int nbr_part){//state initializer
    Length = length;
    Nbr_Part = nbr_part;
    time = 0; time_flux=0;
    counter = 0;
    state_time = vector<double> (Length, 0);
    state_time1 = vector<double> (Length, 0); flux_chem12 = vector<double> (Length, 0);  count_1 = vector<double> (Length+1, 0); 
    state_time2 = vector<double> (Length, 0); flux_chem13 = vector<double> (Length, 0);  count_2 = vector<double> (Length+1, 0);
    state_time3 = vector<double> (Length, 0); flux_chem23 = vector<double> (Length, 0);  count_3 = vector<double> (Length+1, 0);
    tdiff_1 = vector<double> (Length+1, 0); tdiff_2 = vector<double> (Length+1, 0); tdiff_3 = vector<double> (Length+1, 0);
    tchem_1 = vector<double> (Length, 0); tchem_2 = vector<double> (Length, 0); tchem_3 = vector<double> (Length, 0);    
    set<int> occupied;
    set<int> empty;

    //initialize empty with every indices from 1 to Length
    for (int i = 0; i < Length; ++i){
        empty.emplace_hint(empty.end(), i);
    }
    //Random assignment of  particles to an initial localization in X0
    sample(empty.begin(), empty.end(), inserter(occupied,occupied.end()), Nbr_Part, std::mt19937{std::random_device{}()} );
    
    //Fill up initial state of system
    state = vector<int> (Length,0);// initial state with every empty sites
    for (const auto& elem : occupied)
    {
        state[elem] = type;
    }
    
    //Random assignment of  particles to an initial localization in X0
    //vector<int> temp = {};
    //for (size_t i = 1; i <= nbr_part; i++)
    //{   
        //static std::default_random_engine generator;
        //std::uniform_real_distribution<double> distribution (0.,length);
        //int id = (int)distribution(generator);
        // accept answer if not already occupied
        //if(find(temp.begin(), temp.end(), id) == temp.end()){
            //If no elements match, the function returns last
            //state[id]= type;
            //temp.push_back(id);
        //} 
        //else {i = i-1;};
         
    //}
    
    D(cout << "state generator  ";);

};

//getters
vector<int> System::get_syst_state() const{
    return state;
};


vector<double> System::get_syst_state_time() const{
    return state_time;
};

vector<double> System::get_syst_state_time1() const{
    return state_time1;
};

vector<double> System::get_syst_state_time2() const{
    return state_time2;
};

vector<double> System::get_syst_state_time3() const{
    return state_time3;
};
/* vector<double> System::get_syst_cum_rates() const{
    D(cout << "cum rates ";);
    return cum_rates;
}; */
/* sym_map2D<int, Move> System::get_syst_moves() const{
    return moves;
}; */

double System::get_syst_time() const{
    return time;
};

vector<double> System::get_flux_chem(int i, int j) const{
    vector<double> flux(Length,0);
    if (i == 1 && j ==2){
        for (size_t i = 0; i < flux_chem12.size(); i++){
            flux[i] = flux_chem12[i]/time_flux;
        }
        return flux;
    } else if (i == 1 && j ==3){
        for (size_t i = 0; i < flux_chem13.size(); i++){
            flux[i] = flux_chem13[i]/time_flux;
        }
        return flux;
    } else if (i == 2 && j ==3){
        for (size_t i = 0; i < flux_chem23.size(); i++){
            flux[i] = flux_chem23[i]/time_flux;
        }
        return flux;
    }
    else {
        cout << "check arguments in get_flux_chem()" << endl;
        return{0.};
    }
}


//methods for class System
/* void System::syst_actualize_move(int init, int final){
    double r = compute_rate(Potential(init), Potential(final));
    System::moves.Add(Move(init, final));
};
 */



/* void System::add_chem(int loc){
    if(state[loc] == 1){
        moves.Add(loc,loc, new Chem(loc, state[loc]));//mobe 1 to 2
        if(nbr_type == 3){
            moves.Add(loc,loc, new Chem(loc, state[loc]));//move 1 to 3
        }
    } else if (state[loc] == 2 and nbr_type == 2){
        moves.Add(loc,loc, new Chem(loc, state[loc]));//mobe 2 to 1
        if(nbr_type == 3){
            moves.Add(loc,loc, new Chem(loc, state[loc]));//mobe 2 to 3
        }
    } else if (state[loc] == 3 and nbr_type == 3){
        moves.Add(loc,loc, new Chem(loc, state[loc]));//move 3 to 1
        ;//mobe 3 to 2
        
}} */



void System::syst_initialize_moves(){
    int total_move = 0;

    if (state[0]!=0){ 
        moves.Add(0,1, new Diff(0, 1, state[0])); 
        if (chem){
            moves.Add(0,0, new Chem(0, state[0]));
        }
    //total_move +=2;
        }
  
    for (size_t i = 1; i < state.size(); i++){//iterate over all states   
        //define vector of moves in system
        if (i!=(state.size()-1) and state[i]!=0 ){
            moves.Add(i,i-1,new Diff(i, i-1, state[i]));

            moves.Add(i,i+1, new Diff(i, i+1, state[i]));

            if (chem){
                moves.Add(i,i, new Chem(i, state[i]));
            }
            //total_move += 3;

            //cout << "INIT: moves(i,i)->get_type() " << moves(i,i)->get_type() << endl;

            } 
        
    }

    if(state.back()!=0 ) { 
        moves.Add(state.size()-2, state.size()-1, new Diff(state.size()-2, state.size()-1, state.back()));
        if (chem){
            moves.Add(state.size()-1, state.size()-1, new Chem(state.size()-1, state.back()));
        }
        //total_move +=2;
    }; 

    D(cout << "total moves: " << total_move << endl;);
    D(cout << "moves.get_size(): " << moves.get_size()<< endl;);
};


void System::compute_syst_cum_rates( vector<double>& cum_rates, vector<Move*>& ID_moves){

    int n = 0;
    for(auto& slice : moves.get_map()){
        for (auto& move : slice.second){
            if (n == 0){
                cum_rates.push_back(move.second->get_move_rate());
                ID_moves.push_back(move.second);
                n =+1;
                D(cout << move.second->get_move_loc_init() << " and " << move.second->get_move_loc_fin()<< endl;)
            } else {
                cum_rates.push_back(cum_rates.back() + move.second->get_move_rate());
                ID_moves.push_back(move.second);
                D(cout << move.second->get_move_loc_init() << " and " << move.second->get_move_loc_fin()<< endl;)

            }
        }
        
    }
}; 

void System::syst_actualize_state(const Move* m){
    D(cout<<"call syst_actualize_state()" << endl;);

    if (m->get_move_loc_init() != m->get_move_loc_fin()){
        int temp = state[m->get_move_loc_init()];
        state[m->get_move_loc_init()] = state[m->get_move_loc_fin()];
        //D(cout << "m.get_move_loc_init(): " << m.get_move_loc_init() << endl;);
        state[m->get_move_loc_fin()] = temp;
        
        D(cout << "diffusion update" << endl;);

    } else {
        
        state[m->get_move_loc_init()] = m->select_Chem_move();// m->get_type();
        
        D(cout << "chemical update" << endl;);
    }
};



vector<int> System::neighborhood(int I){
    D(cout << "call neighborhood of "<< I << endl;);
    if (I != 0 & I != Length-1){
        return {I-1, I, I+1};
    }
    if (I == 0) {
        return {I, I+1};
    }
    else if (I == Length-1){
        return {I-1, I};
    }
    return {0};
};


void System::syst_evolve(){
    //compute system cumulative rates
    D(cout<< "computation of cum_rates " << endl;)
    vector<double> cum_rates;
    vector<Move*> ID_moves;
    vector<int> memory_state = state;
    compute_syst_cum_rates(cum_rates, ID_moves);
    counter += 1;
   
    //random time step generator
    static default_random_engine generator;
    exponential_distribution<double> distribution_exp(cum_rates.back());
    double time_step = distribution_exp(generator);
    time += time_step;

    //cout << "step time generated: " << time_step << endl;

    //random number generator
    static std::default_random_engine Generator;
    std::uniform_real_distribution<double> distribution(0.,cum_rates.back());
    D(cout << "cum_rates.size " << cum_rates.size() << endl;)
    D(cout << "cum_rates avant dernier : " << cum_rates[cum_rates.size()-2]<< endl;)
    D(cout << "cum_rates.back(): " << cum_rates.back()<< endl;)
    double rand = distribution(Generator);
    D(cout << "rand: "<< rand << endl;)


    //identify moves to do: k
    Move* move_selected = ID_moves[distance(cum_rates.begin(), lower_bound(cum_rates.begin(), cum_rates.end(), rand))];
    D(cout << "distance: "<< distance(cum_rates.begin(), lower_bound(cum_rates.begin(), cum_rates.end(), rand))<< endl;)
    D(cout<< "identify move to do " << endl;)


    //execute moves: update state
    //CALCULATE RHO
        for (size_t i = 0; i < state_time.size(); i++)
        {
            if(state[i] != 0){
                state_time[i] += time_step * (state[i]/state[i]);
                if (state[i] == 1){state_time1[i] += time_step * (state[i]/state[i]);
                } else if (state[i] == 2){state_time2[i] += time_step * (state[i]/state[i]);
                } else if (state[i] == 3){state_time3[i] += time_step * (state[i]/state[i]);
                }
                //D(cout << "state_time[" << i <<"] = "<< state_time[i] <<endl;)
            } else {
                state_time[i] += time_step * (state[i]);
                if (state[i] == 1){state_time1[i] += time_step * state[i];
                } else if (state[i] == 2){state_time2[i] += time_step * state[i];
                } else if (state[i] == 3){state_time3[i] += time_step * state[i];
                }
            //D(cout << "state_time[" << i <<"]=" << state_time[i] <<endl;)
            }
        }
    //BEGINNING
    if (counter > 500000){
    time_flux += time_step;
    //FLUX DIFF
    if(move_selected->get_move_loc_fin() > move_selected->get_move_loc_init()){

        //if(state[move_selected->get_move_loc_fin()] == 0){   
            
            if(state[move_selected->get_move_loc_init()] == 1){
                            //flux_diff_1[move_selected->get_move_loc_fin()]+= move_selected->get_move_rate();//1/time_step;
                            count_1[move_selected->get_move_loc_fin()]+=1;
                            //tdiff_1[move_selected->get_move_loc_fin()]+=time_step;
            } else if(state[move_selected->get_move_loc_init()] == 2){
                            //flux_diff_2[move_selected->get_move_loc_fin()]+= move_selected->get_move_rate();//1/time_step;
                            count_2[move_selected->get_move_loc_fin()]+=1;
                            //tdiff_2[move_selected->get_move_loc_fin()]+=time_step;
            } else if(state[move_selected->get_move_loc_init()] == 3){
                            //flux_diff_3[move_selected->get_move_loc_fin()]+= move_selected->get_move_rate();//1/time_step;
                            count_3[move_selected->get_move_loc_fin()]+=1;
                            //tdiff_3[move_selected->get_move_loc_fin()]+=time_step;
            }

        //} else 
        if (state[move_selected->get_move_loc_fin()] == 1){
                            //flux_diff_1[move_selected->get_move_loc_fin()]-= move_selected->get_move_rate();//1/time_step;
                            count_1[move_selected->get_move_loc_fin()]-=1;
        //} else 
        }if (state[move_selected->get_move_loc_fin()] == 2){
                            //flux_diff_2[move_selected->get_move_loc_fin()]-= move_selected->get_move_rate();//1/time_step;
                            count_2[move_selected->get_move_loc_fin()]-=1;
        //} else 
        }if (state[move_selected->get_move_loc_fin()] == 3){
                            //flux_diff_2[move_selected->get_move_loc_fin()]-= move_selected->get_move_rate();//1/time_step;
                            count_3[move_selected->get_move_loc_fin()]-=1;
        }           
                 
    } else if(move_selected->get_move_loc_fin() < move_selected->get_move_loc_init()){
                
        //if(state[move_selected->get_move_loc_fin()] == 0){ 
                    if(state[move_selected->get_move_loc_init()] == 1){
                        //flux_diff_1[move_selected->get_move_loc_init()]-= move_selected->get_move_rate();//1/time_step;
                        count_1[move_selected->get_move_loc_init()]-=1;
                        //tdiff_1[move_selected->get_move_loc_init()]+=time_step;
                    } else if(state[move_selected->get_move_loc_init()] == 2){
                        //flux_diff_2[move_selected->get_move_loc_init()]-= move_selected->get_move_rate();//1/time_step;
                        count_2[move_selected->get_move_loc_init()]-=1;
                        //tdiff_2[move_selected->get_move_loc_init()]+=time_step;
                    } else if(state[move_selected->get_move_loc_init()] == 3){
                        //flux_diff_3[move_selected->get_move_loc_init()]-= move_selected->get_move_rate();//1/time_step;
                        count_3[move_selected->get_move_loc_init()]-=1;
                        //tdiff_3[move_selected->get_move_loc_init()]+=time_step;
                    }
        //} else 
        if(state[move_selected->get_move_loc_fin()] == 1){
                    //flux_diff_1[move_selected->get_move_loc_init()]+= move_selected->get_move_rate();//1/time_step;
                    count_1[move_selected->get_move_loc_init()]+=1;
        //} else 
        if(state[move_selected->get_move_loc_fin()] == 2){
                    //flux_diff_2[move_selected->get_move_loc_init()]+= move_selected->get_move_rate();//1/time_step;
                    count_2[move_selected->get_move_loc_init()]+=1;    
        //} else 
        }if(state[move_selected->get_move_loc_fin()] == 3){
                    //flux_diff_3[move_selected->get_move_loc_init()]+= move_selected->get_move_rate();//1/time_step;
                    count_3[move_selected->get_move_loc_init()]+=1;
        }
    } 

    } } 
    //end
        
    
    //ACTUALIZE STATE

    syst_actualize_state(move_selected);
    
    if(counter > 500000){
    //FLUX CHEM
        if(move_selected->get_move_loc_fin() == move_selected->get_move_loc_init()){
            if(memory_state[move_selected->get_move_loc_fin()] == 1 ){
                if(state[move_selected->get_move_loc_fin()] == 2){
                flux_chem12[move_selected->get_move_loc_fin()] +=1;
                } else if(state[move_selected->get_move_loc_fin()] == 3){
                flux_chem13[move_selected->get_move_loc_fin()] +=1;
                }
            } else if(memory_state[move_selected->get_move_loc_fin()] == 2){
                if(state[move_selected->get_move_loc_fin()] == 1){
                flux_chem12[move_selected->get_move_loc_fin()] -=1;
                } else if(state[move_selected->get_move_loc_fin()] == 3){
                flux_chem23[move_selected->get_move_loc_fin()] +=1;
                }
            } else if(memory_state[move_selected->get_move_loc_fin()] == 3){
                if(state[move_selected->get_move_loc_fin()] == 2){
                flux_chem23[move_selected->get_move_loc_fin()] -=1;
                } else if(state[move_selected->get_move_loc_fin()] == 1){
                flux_chem13[move_selected->get_move_loc_fin()] -=1;
                }
            }
            
        }
    }
     

    D(cout<< "actualize state according to move " << endl;)
    D(cout<< "move chosen between " << move_selected->get_move_loc_init() << " and "<< move_selected->get_move_loc_fin() << endl;);

    //identify moves to remake
    set<pair<int,int>> moves_remake;


    int I0 = move_selected->get_move_loc_init();
    int I1 = move_selected->get_move_loc_fin();
    
    D(cout << "I0: " << I0 << " I1: " << I1 << endl;)
    if (I0 != I1){
        for(auto& n: neighborhood(I0)){
            if (n <= I0){moves_remake.insert({n,I0});}
            else {moves_remake.insert({I0,n});}
        };
        
        for(auto& n: neighborhood(I1)){
            if (n <= I1){moves_remake.insert({n,I1});}
            else {moves_remake.insert({I1,n});}
        };
    
    
        //Actualize moves inside "to_remake"
        D(cout<<"Moves to remake: "<<endl;);
        for (auto& r: moves_remake){
            if (state[r.first] != 0 or state[r.second] != 0){
                D(cout<<" add between " << r.first << " and " << r.second << endl;)
                if(r.first != r.second){
                    if(state[r.first] != 0){
                        moves.Add(r.first, r.second, new Diff(r.first, r.second, state[r.first]));

                    }
                    else if (state[r.second] != 0){
                        moves.Add(r.second, r.first, new Diff(r.second, r.first, state[r.second]));
                    }
                    
                    
                } else {
                    if (chem){
                        moves.Add(r.first, r.first, new Chem(r.first, state[r.first]));
                        //moves.Add(r.first, r.second, new Chem(r.first, state[r.first]));
                    }
                }
                
            } else {
                D(cout<<"remove between " << r.first << " and " << r.second << endl;);
                moves.remove(r.first, r.second);
                }
        
        }
    } else {
        if (chem){
            D(cout << "remove "<< moves(I0,I0)->get_move_loc_fin(););

            moves.remove(I0, I0);

            moves.Add(I0, I0, new Chem(I0, state[I0]));
            //moves.Add(I0,I0, new Chem(I0, state[I0])); 
        }
    }

    
    
}; 






vector<double> System::get_flux_diff(int i) const{
    vector<double> flux(Length+1,0);
    if (i==1){
        for(size_t i = 0; i<count_1.size(); ++i){
                flux[i] = count_1[i]/time_flux;
        }
    } else if (i==2){
        for(size_t i = 0; i<count_2.size(); ++i){
                flux[i] = count_2[i]/time_flux;
        }
    } else if (i==3){
        for(size_t i = 0; i<count_3.size(); ++i){
                flux[i] = count_3[i]/time_flux;
        }
    }
    return flux;
}


