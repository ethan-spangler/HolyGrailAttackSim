//
// Created by Ethan on 11/30/2019.
//

#ifndef HW6_SAFEQUEUE_H
#define HW6_SAFEQUEUE_H
#include <semaphore.h>
#include <queue>
#include <pthread.h>
#include <string>

#include "AttackMessage.h"

using std::queue;

template <typename T>
class SafeQueue {

private:
    queue<T> _queue;
    pthread_mutex_t _mutex;
    sem_t _sem;

public:
    // Constructor
    SafeQueue();

    // Actions
    void Enqueue(T obj);
    T Dequeue();

}; // class SafeQueue
#endif //HW6_SAFEQUEUE_H
