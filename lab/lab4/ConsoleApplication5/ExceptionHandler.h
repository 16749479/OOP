#ifndef EXCEPTION_HANDLER_H
#define EXCEPTION_HANDLER_H

#include <stdexcept>
#include <string>

class QueueException : public std::runtime_error {
public:
    explicit QueueException(const std::string& message) : std::runtime_error(message) {}
};

#endif
