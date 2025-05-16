#ifndef _TEMPLATE_H_
#define _TEMPLATE_H_

#include "common.h"

// traditional way to realize the template pattern
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

// using template to reduce virtual table derivatives
// sum up common functions into func: _TemplateMethod
// 
class TPLAbstractClass {
public:
    virtual ~TPLAbstractClass() = default;
    virtual void TemplateMethod() const = 0;

protected:
    template <typename T>
    static void _TemplateMethod(T & obj);

protected:
    virtual void RequireOperation1() const {
        std::cout << "BaseTPL1 Implemention operation1\n";
    }
    virtual void RequireOperation2() const {
        std::cout << "BaseTPL2 Implemention operation2\n";
    }
};

template <typename T>
void TPLAbstractClass::_TemplateMethod(T & obj) {
    this->BaseOperation1();
        this->RequireOperation1();
        this->BaseOperation2();
        this->Hook1();
        this->RequireOperation2();
        this->BaseOperation3();
        this->Hook2();
}

class SubTPLClass : public TPLAbstractClass {
public:
    void TemplateMethod() const override;

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
    void Hook1() const {}
    void Hook2() const {}

    void RequireOperation1() const override {
        std::cout << "SubTPL1 Implemention operation1\n";
    }
    void RequireOperation2() const override {
        std::cout << "SubTPL2 Implemention operation2\n";
    }
};

void SubTPLClass::TemplateMethod() const {
    _TemplateMethod(*this);
}

#endif