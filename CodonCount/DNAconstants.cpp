
#include "DNAconstants.h"
#include <string>
#include <vector>

// generates 64 codons
using namespace std;

vector <string> getCodons(){

    vector <string> codons;
        for (unsigned i = 0 ; i < 4; ++i){
            for (unsigned j = 0 ; j < 4; ++j){
                for (unsigned k = 0 ; k < 4; ++k){
                std::string codon;
                codon += n_bases[i];
                codon += n_bases[j];
                codon += n_bases[k];
                codons.push_back(codon);
                }
            }
        }
    return codons;
}

vector <string> getQuadrs(){

    vector <string> quadrs;
        for (unsigned i = 0 ; i < 4; ++i){
            for (unsigned j = 0 ; j < 4; ++j){
                for (unsigned k = 0 ; k < 4; ++k){
                    for (unsigned m = 0 ; m < 4; ++m){
                    std::string quadr;
                    quadr += n_bases[i];
                    quadr += n_bases[j];
                    quadr += n_bases[k];
                    quadr += n_bases[m];
                    quadrs.push_back(quadr);
                    }
                }
            }
        }
    return quadrs;
}


