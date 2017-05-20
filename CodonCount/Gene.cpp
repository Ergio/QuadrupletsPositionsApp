#include <string>
#include <vector>
#include "DNAconstants.h"
#include "Gene.h"

using namespace std;


Gene::Gene(string raw_string) {
            raw_string_ = raw_string;
            sequence_ = this->getSeqence();
        }
string Gene::getSeqence(){
            size_t gene_start = raw_string_.length();
            size_t  gene_stop = 0;

            for(unsigned int i=0; i < 7 ; ++i){
                if(gene_start > raw_string_.find(start_codons[i])){
                    gene_start = raw_string_.find(start_codons[i]);
                }

            }

            for(unsigned int i=0; i < 3; ++i){
                if(gene_stop < raw_string_.rfind(stop_codons[i])){
                    gene_stop = raw_string_.rfind(stop_codons[i]);
                }
            }


            string genes_string = raw_string_.substr (gene_start, gene_stop - gene_start+3); 
            return genes_string; 
            
        }
Gene::~Gene(){}
string Gene::getSeq(){return sequence_;}

