/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CodonCounts.cpp
 * Author: Ergio
 * 
 * Created on 28 березня 2017, 2:28
 */
#include<string>
#include<vector>
#include<cstring>
#include<iostream>//not
#include "CodonCounts.h"
#include "DNAconstants.h"
using namespace std;


CodonCounts::CodonCounts(string gene_str){
            gene_string_ = gene_str;
        }

CodonCounts::~CodonCounts(){}




//old version
std::vector< std::pair<std::string,int> > CodonCounts::makeCountCodons()
{
  
  std::string::const_iterator beg;
  std::string::const_iterator end;
  beg = gene_string_.begin();
  end = gene_string_.end();

    std::vector< std::pair<std::string,int> > CountCodonsObj;
    for (unsigned i = 0 ; i < 4; ++i)
      for (unsigned j = 0 ; j < 4; ++j)
        for (unsigned k = 0 ; k < 4; ++k)
          {
            std::string codon;
            codon += n_bases[i];
            codon += n_bases[j];
            codon += n_bases[k];
	    std::string::const_iterator::difference_type pos = 0;
            unsigned count = 0;
	    for( ; (beg+pos) < end ; pos += 3 )
	      {
		if( std::string(beg+pos,beg+pos+3)==codon )
		  {
		    ++count;
		  }
	      }
            CountCodonsObj.push_back( std::pair< std::string, int >(codon,count) );
          }
    return CountCodonsObj;
  }




std::vector< std::vector<double> > CodonCounts::CodonsPositions(){
	std::string gene=gene_string_;
	vector<vector<double> > CodonPositionObj;
	double pos;
	int end = gene.length();
		for(int i = 0; i<64 ; ++i){
			vector <double> positions;
			positions.push_back(-1);
			pos = 0;
			for(; pos < end ; pos += 3)
				{
				if( gene.compare(pos,3,codons[i])==0 )
					{
						positions.push_back(pos/end);
					}
				}

			CodonPositionObj.push_back(positions);

		}


	return CodonPositionObj;
}



std::vector<double>  CodonCounts::CodonsPositionsOne(int num){
	std::string gene=gene_string_;
	double pos= 0;;
	int end = gene.length();
	string codon = codons[num];
	vector <double> positions;
	for(; pos < end ; pos += 3){
				if( gene.compare(pos,3,codon)==0 ){
					positions.push_back(pos/end);
				}
		}

	return positions;
}


std::vector<double>  CodonCounts::QuadrupletsPositionsOne(int num){
	std::string gene=gene_string_;
	double pos= 0;;
	int end = gene.length();
	string codon = quadrs[num];
	vector <double> positions;
	for(; pos < end ; pos += 3){
				if( gene.compare(pos,4,codon)==0 ){
					positions.push_back(pos/end);
				}
		}

	return positions;
}
