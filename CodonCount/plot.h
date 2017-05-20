#ifndef PLOT_H
#define PLOT_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Genome.h"
#include "DNAconstants.h"
using namespace std;

std::string FileReader(std::string genome_name );
std::vector<double> getValues (std::vector<double> values,double min , double max);
std::vector< std::pair<double,double> > CalcDensity (std::vector<double> big_vec1, int dots);
vector<int> getQuadrsByCodon(int codon);






#endif

