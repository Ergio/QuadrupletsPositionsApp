/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CodonCounts.h
 * Author: Ergio
 *
 * Created on 28 березня 2017, 2:28
 */

#ifndef CODONCOUNTS_H
#define CODONCOUNTS_H

#include <string>
#include <vector>

using namespace std;

class CodonCounts {
    public:
        CodonCounts(string gene_str);
        std::vector< std::pair<std::string,int> > makeCountCodons();

        std::vector< std::vector<double> > CodonsPositions();
        std::vector<double> CodonsPositionsOne(int num);
        std::vector<double> QuadrupletsPositionsOne(int num);
        ~CodonCounts();
        //quadrupletPosition(string gene)
    private:
        string gene_string_;
};


#endif /* CODONCOUNTS_H */
