#ifndef HEADERFILE_H // checks if a unique HEADERFILE_H is defined
#define HEADERFILE_H

#ifdef DEBUG
#  define D(x) x
#else
#  define D(x)
#endif // DEBUG //How to use: D(cerr << "oopsie";)

#include <iostream>
#include <vector>
#include <algorithm>  
#include <string>
#include <random>
#include <fstream>
#include <map>
#include <set>
#include <iterator>
using namespace std;

// other '.h' files
#include "parameters.h"
#include "Functions.h"
#include "Move.h"
#include "Diff.h"
#include "Chem.h"
#include "sym_map2D.h"
#include "System.h"

#endif
