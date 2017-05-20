/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Genome.h
 * Author: Ergio
 *
 * Created on 31 березня 2017, 20:28
 */

#ifndef GENOME_H
#define GENOME_H
#include <string>
#include <vector>
#include "Gene.h"
#include "CodonCounts.h"
using namespace std;




class Genome {
    public:
        Genome(const string& raw_string);
        std::vector< std::vector<double> > CodonsPositions();
        std::vector<double>  CodonsPositionsOne(int num);
        std::vector<double> QuadrupletsPositionsOne(int num);
        string spanSeq();
        ~Genome(); 
    private:

        vector <string> rawGeneString();
        string raw_strig_;
        string chain_;
        vector<string> raw_vec_string_;
        map <string,string> descriptions_;// this feature not completed yet
        vector <string> Check3();
};

#endif /* GENOME_H */
