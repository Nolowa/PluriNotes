#ifndef UTILS_H
#define UTILS_H

#include <QException>

template<typename T> class Iterator{
public:
    virtual T& current() const = 0;
    virtual bool isDone() const = 0;
    virtual void next() = 0;

};

class AppException : public QException{
public:
    const QString message;
public:

    AppException(const QString msg) : message(msg) {};

    AppException* clone() const {
        return new AppException(*this);
    }
    void raise() const {
        throw *this;
    }
};


#endif // UTILS_H
