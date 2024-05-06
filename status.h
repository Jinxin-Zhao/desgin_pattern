#ifndef _STATUS_H_
#define _STATUS_H_

//其主要思想是程序在任意时刻仅可处于几种有限的状态中。 在任何一个特定状态中， 程序的行为都不相同， 且可瞬间从一个状态切换到另一个状态。
//不过， 根据当前状态， 程序可能会切换到另外一种状态， 也可能会保持当前状态不变。 这些数量有限且预先定义的状态切换规则被称为转移。

#include "common.h"

class WordFile;

class State {
protected:
    WordFile * context_;

public:
    virtual ~State(){}

    void set_context(WordFile * context){
        this->context_ = context;
    }
    virtual void Handle1() = 0;
    virtual void Handle2() = 0;
};


class WordFile{
private:
    State * state_;
public:
    WordFile(State * state) : state_(nullptr) {
        this->TransitionTo(state);
    }
    ~WordFile() {
        delete state_;
    }
    void TransitionTo(State * state) {
        std::cout << "WordFile: Transition to " << typeid(*state).name() << std::endl;
        if (this->state_ != nullptr) {
            delete this->state_;
        }
        this->state_ = state;
        this->state_->set_context(this);
    }
    void Request1() {
        this->state_->Handle1();
    }
    void Request2() {
        this->state_->Handle2();
    }
};

class ConcreteStateA : public State {
public:
    void Handle1() override;
    void Handle2() override {
        std::cout << "ConcreteStateA handles request2" << std::endl;
    }
};

class ConcreteStateB : public State {
public:
    void Handle1() override {
        std::cout << "ConcreteStateB handles request1" << std::endl;
    }
    void Handle2() override {
        std::cout << "ConcreteStateB handles request2" << std::endl;
        std::cout << "ConcreteStateB wants to change the state of the context" << std::endl;
        this->context_->TransitionTo(new ConcreteStateA);
    }
};

void ConcreteStateA::Handle1()
{
    std::cout << "ConcreteStateA handles request1" << std::endl;
    std::cout << "ConcreteStateA wants to change the state of the context=" << std::endl;
    this->context_->TransitionTo(new ConcreteStateB);
}

#endif