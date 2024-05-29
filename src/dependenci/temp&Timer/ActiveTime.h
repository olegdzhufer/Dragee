#ifndef ACTIVETIME_H
#define ACTIVETIME_H



typedef struct ActiveTime
{
    uint8_t h;
    uint8_t m;
    uint8_t s;

    char* (*getTime)(ActiveTime* timer);
    void (*nextSec)(ActiveTime* timer);
    void (*resetTimer)(ActiveTime* timer);

}ActiveTime;



char* getTime(ActiveTime* timer){

    char result[9];

    sprintf(result, "%02d:%02d:%02d", timer->h % 100, timer->m % 100, timer->s % 100);

    return result;

}

void nextSec(ActiveTime* timer){
    if(timer->s < 60){
        timer->s ++;
    }else if(timer->m < 60){
        timer->s = 0;
        timer->m ++;
    }else{
        timer->m = 0;
        timer->s = 0;
        timer->h ++;
    }
}

void resetTimer(ActiveTime* timer){

    timer->h = 0;
    timer->m = 0;
    timer->s = 0;
}


ActiveTime* initTimer(){
    ActiveTime* timer = (ActiveTime*)malloc(sizeof(ActiveTime));

    if (timer){
        timer->s = 0;
        timer->m = 0;
        timer->h = 0;

        timer->getTime = getTime;
        timer->nextSec = nextSec;
        timer->resetTimer = resetTimer;
    }

    return NULL;
}



#endif