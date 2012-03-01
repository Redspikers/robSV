#ifndef __POMPE__
#define __POMPE__

#include "constantes.h"

class Pompe
{
    public:
    Pompe(); 
    void compresser();
    void relacher();



    private:
    int pompe_elec; //int pour l'instant
    
};

#endif