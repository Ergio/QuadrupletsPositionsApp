/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Genome.cpp
 * Author: Ergio
 * 
 * Created on 31 березня 2017, 23:28
 */

#include "Genome.h"
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>


using namespace std;
// return raw version of gene string
vector <string> Genome::rawGeneString(){
    string str = raw_strig_;
    str.erase (std::remove(str.begin(), str.end(), '\n'), str.end());
    std::vector <int> genes_start;
    std::vector <string> genes_raw_string;
   //genes_start - start points of gene description
   
    genes_start.push_back(0);
    static int k; 
    for( unsigned int i=1;i < str.length();i++){
    if(str[i]=='>'){ 
        k=genes_start.back();
        genes_start.push_back(i);
        genes_raw_string.push_back(str.substr (k,i-k));
        }
    }
    return genes_raw_string;
}

Genome::Genome(const string& raw_file_strig ) {
    raw_strig_ = raw_file_strig;
    chain_ = this->spanSeq();
    raw_vec_string_ = this->rawGeneString();
    }

// this function joints all genes and return one big sequence
string Genome::spanSeq(){
    vector <string> genes = this->Check3();
    string chain;
    for(unsigned int i = 0; i< genes.size() ;++i){
        if((genes[i].length()%3)==0){
            chain.append(genes[i]);
        }
        else {}
    }
    return chain;
    
}



// return vector  of sequence, where (sequence size)/3 ==0
vector <string> Genome::Check3(){
    vector <string> genes_string;
    for(unsigned int k = 0; k<raw_vec_string_.size();k++){
        
        Gene gene1(raw_vec_string_[k]);
        string str1 = gene1.getSeq();
        if (str1.size()%3==0){
            genes_string.push_back(gene1.getSeq());
        }

    }

    vector <string> chain;
    for(unsigned int i = 0; i< genes_string.size() ;++i){
        if((genes_string[i].length()%3)==0){
            chain.push_back(genes_string[i]);
        }
        else { 
        }
    }
    return chain;
    
}
Genome::~Genome(){}


// return 64 vectors of relative codon positions
std::vector< std::vector<double> > Genome::CodonsPositions(){
    std::vector< std::vector<double> > summary(64);// 64 types of triplets
    std::vector< std::vector<double> > temp;
    vector <string> genes = this->Check3();
    for(unsigned int i = 0; i< genes.size() ;++i){
        CodonCounts some_gene(genes[i]);
        temp = some_gene.CodonsPositions();

        for(unsigned int j=0; j<temp.size(); ++j){
            summary[j].insert(summary[j].end(), temp[j].begin(), temp[j].end());
        }
    }
    return summary;
    
}


std::vector<double> Genome::CodonsPositionsOne(int num){
    std::vector<double>  summary;
    std::vector<double>  temp;
    vector <string> genes = this->Check3();
    for(unsigned int i = 0; i< genes.size() ;++i){
        CodonCounts some_gene(genes[i]);
        temp = some_gene.CodonsPositionsOne(num);
        summary.insert(summary.end(), temp.begin(), temp.end());

    }
    return summary;

};


std::vector<double> Genome::QuadrupletsPositionsOne(int num){
    std::vector<double>  summary;
    std::vector<double>  temp;
    vector <string> genes = this->Check3();
    for(unsigned int i = 0; i< genes.size() ;++i){
        CodonCounts some_gene(genes[i]);
        temp = some_gene.QuadrupletsPositionsOne(num);
        summary.insert(summary.end(), temp.begin(), temp.end());

    }
    return summary;

};
