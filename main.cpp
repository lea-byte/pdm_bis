#include "header.h"
#include "Functions.cpp"
#include "Move.cpp"
#include "System.cpp"

int main() {
    
    ofstream fw("C:\\Users\\leagr\\Documents\\PdM\\Generalbis\\Result.txt", std::ofstream::out);
    ofstream fw_count("C:\\Users\\leagr\\Documents\\PdM\\Generalbis\\Count.txt", std::ofstream::out);
    ofstream fw_prop("C:\\Users\\leagr\\Documents\\PdM\\Generalbis\\Prop.txt", std::ofstream::out);
    ofstream fw_time("C:\\Users\\leagr\\Documents\\PdM\\Generalbis\\Time.txt", std::ofstream::out);
    ofstream fw_time1("C:\\Users\\leagr\\Documents\\PdM\\Generalbis\\Time1.txt", std::ofstream::out);
    ofstream fw_time2("C:\\Users\\leagr\\Documents\\PdM\\Generalbis\\Time2.txt", std::ofstream::out);
    ofstream fw_time3("C:\\Users\\leagr\\Documents\\PdM\\Generalbis\\Time3.txt", std::ofstream::out);
    ofstream flux_chem12("C:\\Users\\leagr\\Documents\\PdM\\Generalbis\\flux12.txt", std::ofstream::out);
    ofstream flux_chem13("C:\\Users\\leagr\\Documents\\PdM\\Generalbis\\flux13.txt", std::ofstream::out);
    ofstream flux_chem23("C:\\Users\\leagr\\Documents\\PdM\\Generalbis\\flux23.txt", std::ofstream::out);
    ofstream flux_diff1("C:\\Users\\leagr\\Documents\\PdM\\Generalbis\\flux_diff1.txt", std::ofstream::out);
    ofstream flux_diff2("C:\\Users\\leagr\\Documents\\PdM\\Generalbis\\flux_diff2.txt", std::ofstream::out);
    ofstream flux_diff3("C:\\Users\\leagr\\Documents\\PdM\\Generalbis\\flux_diff3.txt", std::ofstream::out);

    vector<int> count(length, 0);
    vector<double> prop; 
    //vector<double> V = {0,0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2, 2.1, 2.2,2.3,2.4, 2.5, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<double> V = {0, 0.5, 1, 2, 10}; 
     
     /* for (auto& i: V)
     { */ 
        //set_V0(0.1*i);
        //set_V0(i);
    

        //DEFINE SYSTEM
        System S(length, nbr_part);
        S.syst_initialize_moves();

        for (size_t j = 0; j < length; j++){
            if(write_state){
                fw << S.get_syst_state()[j]<< " " ;
            }
            if (S.get_syst_state()[j] != 0){
                count[j] += 1;
            }
                } 
        fw << "\n";


        //begin Gillespie
        int step = 1;
        while (step <= step_max) {
            D(cout<< "begin step:" << step << endl <<endl;);
            S.syst_evolve();
            D(cout<< "end" <<endl <<endl;);

            if(step % 1 == 0){
            if (fw.is_open() ){
            for (size_t j = 0; j < length; j++){
                if(write_state){
                    fw << S.get_syst_state()[j] << " ";
                }
                if (S.get_syst_state()[j] != 0){
                    count[j] += 1;
                }
                
            } 
            fw << "\n";
            } else {cout << "Problem with opening file";} }
            step += 1;
        }; 
        
        double lhs = 0; double rhs = 0;
        for (size_t j = 0; j < count.size(); j++){
                fw_count << count[j] << " ";
                if(j < 50){
                    lhs += count[j];
                } else {
                    rhs += count[j];
                }
        }

        prop.push_back(rhs/lhs);
        //cout << "prop " << rhs/lhs << endl;

        /* vector<double> K12 = rate_vector(1,2);  vector<double> K21 = rate_vector(2,1);
        vector<double> K13 = rate_vector(1,3);  vector<double> K31 = rate_vector(3,1);
        vector<double> K23 = rate_vector(2,3);  vector<double> K32 = rate_vector(3,2); */

    for (size_t i = 0; i < S.get_syst_state_time().size(); i++)
    {
        fw_time << (1/S.get_syst_time())*S.get_syst_state_time()[i] << " ";
        flux_chem12 << S.get_flux_chem(1,2)[i]<< " ";
        fw_time1 << (1/S.get_syst_time())*S.get_syst_state_time1()[i] << " ";  
        flux_chem13 <<S.get_flux_chem(1,3)[i] << " ";
        fw_time2 << (1/S.get_syst_time())*S.get_syst_state_time2()[i] << " ";
        flux_chem23 << S.get_flux_chem(2,3)[i] << " ";
        fw_time3 << (1/S.get_syst_time())*S.get_syst_state_time3()[i] << " ";
    }
    for (size_t i = 0; i < S.get_syst_state_time().size()+1; i++){
        flux_diff1 << S.get_flux_diff(1)[i] << " ";
        flux_diff2 << S.get_flux_diff(2)[i] << " ";
        flux_diff3 << S.get_flux_diff(3)[i] << " ";
    }
        fw_time << "\n"; 
        fw_time1 << "\n"; flux_chem12 << "\n"; flux_diff1 << "\n";
        fw_time2 << "\n"; flux_chem13 << "\n"; flux_diff2 << "\n";
        fw_time3 << "\n"; flux_chem23 << "\n"; flux_diff3 << "\n";
    cout << S.get_syst_time();
    //} // END for

    fw.close();
    fw_count.close();

    for (size_t j = 0; j < prop.size(); j++){
                fw_prop << prop[j] << " ";
    }
    
    fw_prop.close();

    
    
};