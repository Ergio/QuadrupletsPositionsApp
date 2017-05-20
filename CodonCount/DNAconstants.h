    /*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DNAconstants.h
 * Author: Ergio
 *
 * Created on 28 березня 2017, 2:42
 */

#ifndef DNACONSTANTS_H
#define DNACONSTANTS_H

#include<string>
#include<vector>


static const char n_bases[4] ={'A','T','G','C'};
static const std::string stop_codons[3]={"TAG","TGA","TAA"};
static const std::string start_codons[7]={"ATG","GTG","ATT","TTG","ATA","ACG","CTG"};

std::vector <std::string> getCodons();
std::vector <std::string> getQuadrs();
static const std::vector <std::string> codons = getCodons();
static const std::vector <std::string> quadrs =  getQuadrs();



#endif /* DNACONSTANTS_H */
