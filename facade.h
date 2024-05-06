#ifndef __FACADE_H_
#define __FACADE_H_


#include "common.h"

/// 外观可以通过使用简单接口， 但将绝大部分工作委派给其他类的类来识别。 通常情况下， 外观管理其所使用的对象的完整生命周期。

class Subsystem_1 {
public:
    std::string Operation_1() const {
        return "Subsystem_1 : Ready!\n";
    }

    std::string Operation_N() const {
        return "Subsystem_1 : Go!\n";
    }
};


class Subsystem_2 {
public:
    std::string Operation_1() const {
        return "Subsystem2: Get ready!\n";
    }

    std::string Operation_Z() const {
        return "Subsystem_2: Fire\n";
    }
};

class Facade {
protected:
    Subsystem_1 * sub_1;
    Subsystem_2 * sub_2;
public:
    Facade(Subsystem_1 * s1 = nullptr, Subsystem_2 * s2 = nullptr){
        this->sub_1 = s1 ?: new Subsystem_1;
        this->sub_2 = s2 ?: new Subsystem_2;
    }
    ~Facade(){
        delete sub_1;
        delete sub_2;
    }
    std::string Operation() {
        std::string result = "Facade initializes subsystems:\n";
        result += this->sub_1->Operation_1();
        result += this->sub_2->Operation_Z();
        result += "Facade orders subsystems to perform the action:\n";
        result += this->sub_1->Operation_N();
        result += this->sub_2->Operation_Z();
        return result;
    }

};

#endif