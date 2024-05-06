#ifndef  __BRIDGE_H_
#define  __BRIDGE_H_

#include "common.h"

class BridgeImplementation {
public:
    virtual ~BridgeImplementation() {}
    virtual std::string Operation() const = 0;
};

class BridgeConcreteImplementationA : public BridgeImplementation {
public:
    std::string Operation() const override {
        return "Concrete A\n";
    }
};

class BridgeConcreteImplementationB : public BridgeImplementation {
public:
    std::string Operation() const override {
        return "Concrete B\n";
    }
};

class Abstraction {
protected:
    BridgeImplementation * implementation_;
public:
    Abstraction(BridgeImplementation * imp) : implementation_(imp) {
    }
    virtual ~Abstraction(){}
    virtual std::string Operation() const {
        return "Abstraction: Base operation with:\n" + this->implementation_->Operation();
    }
};

class ExtendedAbstraction : public Abstraction {
public:
    ExtendedAbstraction(BridgeImplementation * imp) : Abstraction(imp){}
    std::string Operation() const override {
        return "ExtendedAbstraction: Extended operation with:\n" + this->implementation_->Operation();
    }

    void test_bridge(){
        BridgeImplementation * imp = new BridgeConcreteImplementationA;
        Abstraction * abstraction = new Abstraction(imp);
        abstraction->Operation();

        imp = new BridgeConcreteImplementationB;
        abstraction = new ExtendedAbstraction(imp);
        abstraction->Operation();
    }
};

#endif