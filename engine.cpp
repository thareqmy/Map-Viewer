#include <pthread.h>
#include <strings.h>
#include <string.h>
#include <termios.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include "Frame.h"
#include "Line.h"
#include <stdint.h>
#include <iostream>



typedef struct keyQueue {
    struct keyQueue *next;
    char key;
} keyQueue_t;

typedef struct ThreadInfo {
    pthread_t tid;           /* thread id */
    pthread_mutex_t kqmutex; /* protects key queue from race condition between threads */
    keyQueue_t kqhead;       /* input keys queued to this thread */
    char *keys;              /* keys this thread responds to */
    char *name;              /* name of this thread */
} threadInfo_t;

Frame f;

static struct termios origtc, newtc;


threadInfo_t threads[] = { 
    { 0, PTHREAD_MUTEX_INITIALIZER, { NULL, '\0' }, "asdw", "Thread T1" }
};

  int h = 0;
  int g = 0;
  Color bgc(255,255,255);
  Line l1(20, 20, 700, 700);
//   Plane2D segitiga("segitiga.txt");
  //Plane2D pesawat("40479_plane3d.txt");

void *service(void *arg) {

    
    char key;

    threadInfo_t *t = &threads[(int64_t)arg];    // get pointer to thread
    for(;;) {
        pthread_mutex_lock(&t->kqmutex);     // lock other threads out while we tamper 
        key = '\0';                          // initialize key to NULL
        if (t->kqhead.next != NULL) {        // Anything queued up for us?
            keyQueue_t *kq = t->kqhead.next; // if so get ptr to key pkt
            key = kq->key;                   // fetch key from pkt
            t->kqhead.next = kq->next;       // Point to next key in queue (or NULL if no more queued up).
            free(kq);
        }  

        pthread_mutex_unlock(&t->kqmutex);   // unlock key queue
        if (key != '\0') {
            Color c(0,0,0);
            if (key == 'a') {
                h-=10;
            } else if (key == 'd') {
                h+=10;
            //printf("... %s pulled key '%c' from queue\n", t->name, key);


            } else if (key == 's') {
                g+=10;
            } else if (key == 'w') {
                g-=10;
            }


            

            
            
            
            //f.lineToFrame(c, l1);
            f.lineToFrame(c, l1);
            // f.plane2DToFrame(300,300,10,c, segitiga);
        } else {

        }
        // ⇓ usleep() probably more practical as 1-sec too long for most cases
                                 // sleep so we don't loop too fast eating CPU
    }
    return NULL;
}

int main() {

    f.createBackground(bgc);
    /* Fire up threads */
    for (long i = 0; i < sizeof (threads) / sizeof (threadInfo_t); i++) {
        if (pthread_create(&threads[i].tid, NULL, service, (void *)i) < 0) {
            perror("pthread_create()");
            exit(-1);
        }
    }

    tcgetattr(0, &origtc);                         // get orig tty settings
    newtc = origtc;                                // copy them
    newtc.c_lflag &= ~ICANON;                      // put in '1 key mode'
    newtc.c_lflag &= ~ECHO;                        // turn off echo

    for(;;) {
        tcsetattr(0, TCSANOW, &newtc);             // echo off 1-key read mode
        char c = getchar();                        // get single key immed.
        tcsetattr(0, TCSANOW, &origtc);            // settings back to normal
       // printf("Key '%c' pressed...\n", c);        // show user what we got
        for (int i = 0; i < sizeof (threads) / sizeof (threadInfo_t); i++) {
            threadInfo_t *t = &threads[i];         // get shorthand ptr to thread
            if (strchr(t->keys, c) != NULL) {      // this thread listens for this key
                pthread_mutex_lock(&t->kqmutex);   // lock other threads out while we tamper 
                keyQueue_t *kq;
                kq =(keyQueue_t *)calloc(sizeof (struct keyQueue), 1); // allocate pkt
                kq->key = c;                       // stash key there
                keyQueue_t *kptr = &t->kqhead;     // get pointer to queue head
                while(kptr->next != NULL)          // find first empty slot
                    kptr = kptr->next;
                kptr->next = kq;                   // enqueue key packet to thread
                pthread_mutex_unlock(&t->kqmutex); // unlock key queue
            }
        }
    }
    return 0;
}