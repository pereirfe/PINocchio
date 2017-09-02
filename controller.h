#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "pin.H"

// Major settings regarding sync and round size
#define MAX_THREADS 1024             // Max number of spawned threads by application
#define INSTRUCTIONS_ON_ROUND 100000 // Number of instructions to be executed per round
#define INSTRUCTIONS_ON_DELAY 0      // Instructions to be executed on a delay (to be revisited)
#define MAX_DELAYS 500               // Max number of delays on a given thread

// Holds information of all thread
typedef struct _THREAD_INFO THREAD_INFO;
struct _THREAD_INFO {
    // Current max of instructions to be executed
    INT64 ins_max;
    // Number of instructions executed on current
    INT64 ins_count;
    // LCM created struct
    PIN_MUTEX wait_controller;
};
extern THREAD_INFO * all_threads;

// Used to lock controller and msg
extern PIN_MUTEX msg_mutex;
extern PIN_MUTEX controller_mutex;

// MSG struct
typedef struct _MSG MSG;
struct _MSG {
    INT64 tid;
    INT64 msg_type;
};

// MSG buffer
extern MSG msg_buffer;

// MSG types
#define MSG_REGISTER 0
#define MSG_DONE 1

// Temporary structure to force sync
typedef struct _HOLDER HOLDER;
struct _HOLDER {
    int max_tid;
    int * states;

    // flushes counter
    int sync_flushes;
    int delayed_flushes;
};
extern HOLDER thread_holder;

// Function used to when instrumentation should stop
void fail();

// Init controller and its communication
void controller_init();

// Send request to controller, concurrent allowed
void send_request(MSG msg);

// Controller main function, pintool should spawn a thread using it
void controller_main(void * arg);

#endif // CONTROLLER_H_
