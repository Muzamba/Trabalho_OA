#include "head.h"

int main(int argc, char const *argv[]) {
   
    char string1[] = "123456ariel";
    char string2[] = "036518Ariel";


    //insereLista("lista1.txt");
    makeInd1("lista1.txt", "indicelista1.ind");
    makeInd2("lista1.txt", "indicelista1.ind", "curso1.ind");
    arquSort("indicelista1.ind", 6);
    makeInd2("lista1.txt", "indicelista1.ind", "curso1.ind");
    arquSort("curso1.ind", 2);



    
    
    return 0;
}


