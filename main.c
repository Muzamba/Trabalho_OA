#include "head.h"

int main(int argc, char const *argv[]) {
    lista* ped;
    ped = createList();
   
    
    

    
    
    makeInd1("lista1.txt", "indicelista1.ind");
    atualizaLista("lista1.txt", "indicelista1.ind");
    //makeInd2("lista1.txt", "indicelista1.ind", "curso1.ind");

    //removeLista("lista1.txt", "indicelista1.ind", "044072IgorRibeirodeAssis", ped);
    //makeInd1("lista1.txt", "indicelista1.ind");
    //printf("%d\n", ped->size);
    //printf("%d\n", ped->head->info.end);
    //insereLista("lista1.txt", ped);

    destroyList(ped);
    
    
    return 0;
}


