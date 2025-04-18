#ifndef _QUEUE_H
#define _QUEUE_H

#include <stdexcept>

using namespace std;

const uint32_t
    QUEUE_SIZE = MAX_ROWS * MAX_ROWS;
  
template <typename QueueType>
class Queue {
public:
    Queue() {
        data = new QueueType[QUEUE_SIZE];
        capacity = QUEUE_SIZE;
        count = tail = 0;
        head = QUEUE_SIZE - 1;
    }
  
    ~Queue() {delete[] data;};
  
    void clear() { count = tail = 0; head = QUEUE_SIZE - 1; }
  
    uint32_t size() { return count; }
    bool isEmpty() { return count == 0; }
  
    void enqueue(QueueType d) {
        if (count == capacity) {
            unsigned int tmpCap = capacity * 2;
            QueueType* tmpData = new QueueType[tmpCap];

            if (tmpData == nullptr)
                throw overflow_error("Queue is full");

            for (unsigned int i = 0; i < capacity; i++)
                tmpData[i] = data[(head + i + 1) % capacity];

            delete[] data;
            
            data = tmpData;
            head = tmpCap - 1;
            tail = capacity;
            capacity = tmpCap;
        }

        data[tail] = d;
        tail = (tail + 1) % capacity;
        count++;
    }
  
    QueueType dequeue() {
  
        if (count == 0)
            throw underflow_error("Queue is empty");

        head = ++head % QUEUE_SIZE;

        count--;

        return data[head];
    }

private:
    QueueType
        *data;
    
    uint32_t
        head,tail,
        count,
        capacity;
};

#endif
