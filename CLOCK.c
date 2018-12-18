#include <stdio.h>
#include <stdlib.h>
#define MAXLEN  50


typedef struct{
    int pages_num;
    int curr;
    int pages[MAXLEN];
    int faults;
    int clock[MAXLEN];

}memory;


memory* clock_init(int n){

    //Create a new memory Struct
    //Initializing its parameters
    memory *m;
    m = malloc(sizeof(memory));
    m->pages_num = n;
    m->curr = 0;
    m->faults = 0;
    for(int i=0; i < n; i++)
        m->clock[i] = -1;
    return m;
}

/*
int search_process(memory* m, int process){

    //Search if the process exist in the memory
    int num = m->pages_num;
    for(int i = 0; i < num; i++){
        if(m->pages[i] == process)
            return i;
    }
    return -1;

}
*/

void add_process_clock(memory* m, int process){

    //Check if the process already in the memory
    int t = search_process(m, process);
    if(t >= 0){
            m->clock[t] = 1;
        printf("%02d     ",process); display_pages(m); printf("\n");
        return;
    }

    //Add the process to the memory and
    //Update the pointer for next page

    while(m->clock[m->curr] == 1){
        m->clock[m->curr] = 0;
        m->curr = (m->curr+1)%m->pages_num;
    }

    m->pages[m->curr] = process;

    // Memory fault case
    if(m->clock[m->curr] == 0){
        m->clock[m->curr] = 1;
        m->curr = (m->curr+1)%m->pages_num;
        m->faults ++;
        printf("%02d F   ",process); display_pages(m); printf("\n");
         return;
    }

    // No memory fault case
    m->clock[m->curr] = 1;
    m->curr = (m->curr+1)%m->pages_num;
    printf("%02d     ",process); display_pages(m); printf("\n");


}

/*
void display_pages(memory* m){

    //Print all memory pages to console
    int num = m->pages_num;
    for(int i=0; i < num; i++){
        if(m->pages[i])
            printf("%02d ", m->pages[i]);
    }

}
*/

int memory_CLOCK(int num){

    memory* m = clock_init(num);
    int input;

    printf("Replacement Policy = CLOCK\n");
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");

    while(1){
        scanf("%d", &input);
        if(input == -1)
            break;
        add_process_clock(m, input);
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n", m->faults);
}

