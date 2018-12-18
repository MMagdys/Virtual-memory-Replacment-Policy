#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FIFO.h"
#include "CLOCK.h"
#include "LRU.h"


int main(){

    int num;
    char algo[6];

    scanf("%d", &num);
    scanf("%s", &algo);
    //printf("%s", algo);

    if(strcmp(algo, "FIFO") == 0)
        memory_FIFO(num);

    else if(strcmp(algo, "LRU") == 0)
        memory_LRU(num);

    else if(strcmp(algo, "CLOCK") == 0)
        memory_CLOCK(num);


}


