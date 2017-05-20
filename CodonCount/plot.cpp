#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "plot.h"
using namespace std;

std::vector< std::pair<double,double> > CalcDensity (std::vector<double> big_vec1, int dots){
    double density;
    vector<double> count;
    std::vector< std::pair<double,double> > input1;
    double pos;
    double lvl(dots);
    for(double i=0;i<lvl;i++){
        count = getValues(big_vec1,i/lvl,(i+1)/lvl);
        pos = (i)/lvl;
        density = count.size();
        input1.push_back(std::pair< double, double >(density,pos));
    }
    return input1;
}

std::vector<double> getValues (std::vector<double> values,double min , double max){
    vector<double> result;
    for(unsigned int i = 0;i<values.size();++i){
        if(values[i]>=min){
            if(values[i]<=max){result.push_back(values[i]);}
        }
    }
    return result;
}




// reads file and give string without /n and /r
string FileReader(std::string genome_name ){

    ifstream ifile;
    int length;
    char * buffer;

    ifile.open ( genome_name.c_str(), ios::binary );
    ifile.seekg (0, ios::end);
    length = ifile.tellg();
    ifile.seekg (0, ios::beg);
    buffer = new char [length];

    ifile.read (buffer,length);
    ifile.close();
    std::string str(buffer);
    delete [] buffer;
    return str;
}

vector<int> getQuadrsByCodon(int codon){
	vector<int> quad;
	quad.push_back((codon-1)*4);
	quad.push_back((codon-1)*4+1);
	quad.push_back((codon-1)*4+2);
	quad.push_back((codon-1)*4+3);
	return quad;
}



