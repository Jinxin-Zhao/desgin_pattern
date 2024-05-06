#ifndef _TEMPLATE_H_
#define _TEMPLATE_H_

#include "common.h"

class AbstractClass {
public:
    void TemplateMethod() const {
        this->BaseOperation1();
        this->RequireOperation1();
        this->BaseOperation2();
        this->Hook1();
        this->RequireOperation2();
        this->BaseOperation3();
        this->Hook2();
    }

protected:
    void BaseOperation1() const {
        std::cout << "Abstraction base operation1" << std::endl;
    }
    void BaseOperation2() const {
        std::cout << "Abstraction base operation2\n";
    }
    void BaseOperation3() const {
        std::cout << "Abstraction base operation3\n";
    }
    virtual void RequireOperation1() const = 0;
    virtual void RequireOperation2() const = 0;

    virtual void Hook1() const {}
    virtual void Hook2() const {}
};

class ConcreteClass1 : public AbstractClass {
protected:
    void RequireOperation1() const override {
        std::cout << "c1 Implemention operation1\n";
    }
    void RequireOperation2() const override {
        std::cout << "c1 Implemention operation2\n";
    }

};

class ConcreteClass2 : public AbstractClass {
protected:
    void RequireOperation1() const override {
        std::cout << "c2 Implemention operation1\n";
    }
    void RequireOperation2() const override {
        std::cout << "c2 Implemention operation2\n";
    }

    void Hook1() const override {
        std::cout << "c2 Override Hook1\n";
    }
};


#endif