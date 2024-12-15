#ifndef QUEUE_H
#define QUEUE_H

#include <list>
#include <initializer_list>
#include "SmartPointer.h"
#include "ExceptionHandler.h"

template <typename T>
class Queue {
private:
    SmartPointer<std::list<T>> data;

public:
    Queue() : data(new std::list<T>()) {}

    Queue(std::initializer_list<T> initList) : data(new std::list<T>(initList)) {}

    Queue(const Queue& other) : data(new std::list<T>(*other.data)) {}

    Queue& operator=(const Queue& other) {
        if (this != &other) {
            *data = *other.data;
        }
        return *this;
    }

    Queue(Queue&& other) noexcept : data(std::move(other.data)) {}

    Queue& operator=(Queue&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
        }
        return *this;
    }

    void enqueue(const T& value) {
        data->push_back(value);
    }


    T dequeue() {
        if (data->empty()) {
            throw QueueException("Очередь пуста.Невозможно удалить из очереди.");
        }
        T value = data->front();
        data->pop_front();
        return value;
    }

 
    T front() const {
        if (data->empty()) {
            throw QueueException("Очередь пуста. Не могу получить доступ к передней части.");
        }
        return data->front();
    }


    bool isEmpty() const {
        return data->empty();
    }

    size_t size() const {
        return data->size();
    }
};

#endif
