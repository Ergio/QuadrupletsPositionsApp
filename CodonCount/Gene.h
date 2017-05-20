/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   gene.h
 * Author: Ergio
 *
 * Created on 28 березня 2017, 0:26
 */

#ifndef GENE_H
#define GENE_H
#include <string>
#include<vector>
#include<map>
using namespace std;

class Gene {
    public:
        Gene(string raw_string);
        string getSeq();
        ~Gene(); 
    private:
        string raw_string_;
        string sequence_;
        map <string,string> descriptions_;// this feature not completed yet
        string getSeqence();// just forget about getSeq() :)
};


#endif /* GENE_H */

