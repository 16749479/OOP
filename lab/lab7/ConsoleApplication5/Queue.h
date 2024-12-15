#ifndef QUEUE_H
#define QUEUE_H

#include <list>
#include <initializer_list>
#include <iostream>
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

    class PositiveIterator {
    private:
        typename std::list<T>::iterator it;
        typename std::list<T>::iterator end;

    public:
        PositiveIterator(typename std::list<T>::iterator start, typename std::list<T>::iterator end)
            : it(start), end(end) {
            while (it != end && (isPositive(*it))) {
                ++it;
            }
        }

        bool hasNext() const {
            return it != end;
        }

        T next() {
            if (it == end) {
                throw QueueException("Больше нет элементов.");
            }
            T value = *it;
            ++it;
            while (it != end && (isPositive(*it))) {
                ++it;
            }
            return value;
        }

    private:
        bool isPositive(const T& value) const {
            if constexpr (std::is_integral<T>::value || std::is_floating_point<T>::value) {
                return value > 0;
            }
            else {
                return false; 
            }
        }
    };

    class NegativeIterator {
    private:
        typename std::list<T>::iterator it;
        typename std::list<T>::iterator end;

    public:
        NegativeIterator(typename std::list<T>::iterator start, typename std::list<T>::iterator end)
            : it(start), end(end) {
            while (it != end && (isNegative(*it))) {
                ++it;
            }
        }

        bool hasNext() const {
            return it != end;
        }

        T next() {
            if (it == end) {
                throw QueueException("Больше нет элементов..");
            }
            T value = *it;
            ++it;
            while (it != end && (isNegative(*it))) {
                ++it;
            }
            return value;
        }

    private:
        bool isNegative(const T& value) const {
            if constexpr (std::is_integral<T>::value || std::is_floating_point<T>::value) {
                return value < 0;
            }
            else {
                return false; 
            }
        }
    };

    PositiveIterator positiveIterator() {
        return PositiveIterator(data->begin(), data->end());
    }

    NegativeIterator negativeIterator() {
        return NegativeIterator(data->begin(), data->end());
    }
};

#endif
