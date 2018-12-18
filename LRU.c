#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define MAXLEN  50


typedef struct{
    int pages_num;
    int curr;
    int pages[MAXLEN];
    int faults;
    long time[MAXLEN];

}memory;



memory* lru_init(int n){

    //Create a new memory Struct
    //Initializing its parameters
    memory *m;
    m = malloc(sizeof(memory));
    m->pages_num = n;
    m->curr = 0;
    m->faults = 0;
    for(int i=0; i < n; i++)
        m->time[i] = -1;
    return m;
}



long get_time(){
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return  (currentTime.tv_sec );
}


int get_lru(memory* m){

    int num = m->pages_num;
    int lru = 0;

    for(int i=1; i < num; i++)
            if(m->time[i] < m->time[lru])
                lru = i;

    return lru;

}



void display(memory* m){

    //Print all memory pages to console
    int num = m->pages_num;
    for(int i=0; i < num; i++){
            printf("%02d ", m->time[i]);
    }

}




void add_process_lru(memory* m, int process){

    //Check if the process already in the memory
    int t = search_process(m, process);
    if(t >= 0){
        m->time[t] = m->curr;
        m->curr ++;
        printf("%02d     ",process); display_pages(m); printf("\n");
        return;
    }

     //Add the process to the memory and
    //Update the pointer for next page

    int i = get_lru(m);
    m->pages[i] = process;
    //printf("%d\n", m->time[i]);

    //memory fault case
    if(m->time[i] >= 0){
        m->time[i] = m->curr;
        m->curr++;
        m->faults ++;
        printf("%02d F   ",process); display_pages(m); printf("\n");
        return;
    }

    //No memory fault case
    m->time[i] = m->curr;
    m->curr++;
    printf("%02d     ",process); display_pages(m); printf("\n");

}



int memory_LRU(int num){

    memory* m = lru_init(num);
    int input;

    printf("Replacement Policy = LRU\n");
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");

    while(1){
        scanf("%d", &input);
        if(input == -1)
            break;
        add_process_lru(m, input);
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n", m->faults);
}

