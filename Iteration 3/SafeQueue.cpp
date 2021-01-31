//
// Created by Ethan on 11/30/2019.
//

#include "SafeQueue.h"

// Templated Constructor
template <typename T>
SafeQueue<T>::SafeQueue()
{
    // Initialize the mutex and semaphore
    pthread_mutex_init(&_mutex, NULL);
    sem_init(&_sem, 0, 0);
}

// Add an object to the queue
template <typename T>
void SafeQueue<T>::Enqueue(T obj)
{
    // Lock the mutex to enforce mutual exclusion
    pthread_mutex_lock(&_mutex);

    // Add the object to the queue
    _queue.push(obj);

    // Unlock the mutex to allow others access
    pthread_mutex_unlock(&_mutex);

    // Increment the semaphore, signalling there is an object within
    sem_post(&_sem);
}

// Remove an object from the front of the queue
template <typename T>
T SafeQueue<T>::Dequeue()
{
    // Wait if the queue is empty, if not, decrement the semaphore
    sem_wait(&_sem);

    // Lock the mutex to enforce mutual exclusion
    pthread_mutex_lock(&_mutex);

    // Get the item from teh front of the queue, and pop it off
    T obj = _queue.front();
    _queue.pop();

    // Unlock the mutex to allow others access
    pthread_mutex_unlock(&_mutex);

    return obj;
}

// This is my poor way of making this allow certain types without throwing a fit
template class SafeQueue<std::string>;
template class SafeQueue<Message>;


