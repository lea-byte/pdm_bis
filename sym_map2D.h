#ifndef SYM_MAP2D_H // include guard
#define SYM_MAP2D_H

#include "header.h"

template <typename key_T, typename val_T>
class sym_map2D
{

private:
    map<key_T, map<key_T, val_T>> m;

public:
    sym_map2D() = default;
    ~sym_map2D() = default;

        void Add(key_T k1, key_T k2, val_T v){ // create upper triangular matrix
        D(cout << "Add "<< k1 << " and " << k2 <<endl;)
        if (k1 <= k2)
        {
            m[k1][k2] = v;
        }
        else
        {
            m[k2][k1] = v;
        }
    };

    constexpr val_T &operator()(key_T k1, key_T k2){
        if (k1 >= k2)
        {
            return m[k2][k1];
        }
        else
        {
            return m[k1][k2];
        }
    };

    int get_size() const{
        int size = 0;
        for (auto &m_ : m)
        {
            size += m_.second.size();
        }
        return size;
    };

    void remove(key_T k1, key_T k2){
        if (k1 <= k2){
            delete m[k1][k2];
            D(cout << "remove " << k1 << " and " << k2 << endl;);
            m[k1].erase(k2);
            D(cout << "erase done" << endl;);              
        }else{
            delete m[k2][k1];
            m[k2].erase(k1);
        }
    };

    map<key_T, map<key_T, val_T>> get_map() const
    {
        return m;
    };

    
};

#endif