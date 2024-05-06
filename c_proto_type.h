#ifndef _PROTO_TYPE_H
#define _PROTO_TYPE_H

enum Type {
    PROTOTYPE_1 = 0,
    PROTOTYPE_2
};

/**
 * The example class that has cloning ability. We'll see how the values of field
 * with different types will be cloned.
 */

class Prototype {
protected:
    std::string prototype_name_;
    float prototype_field_;

public:
    Prototype(){
        std::cout << "Prototype()" << std::endl;
    }
    Prototype(std::string prototype_name) : prototype_name_(prototype_name){
        std::cout << "Prototype(std::string prototype_name) " << std::endl;
    }

    virtual ~Prototype(){}
    virtual std::unique_ptr<Prototype> clone() const = 0;

    virtual void Method(float prototype_field){
        this->prototype_field_ = prototype_field;
        std::cout << "Call Method from " << prototype_name_ << "with field " << prototype_field << std::endl;
    }
};

/**
 * ConcretePrototype1 is a Sub-Class of Prototype and implement the Clone Method
 * In this example all data members of Prototype Class are in the Stack. If you
 * have pointers in your properties for ex: String* name_ ,you will need to
 * implement the Copy-Constructor to make sure you have a deep copy from the
 * clone method
 */

class ConcretePrototype1 : public Prototype {
private:
    float concrete_prototype_field1_;
public:
    ConcretePrototype1(std::string prototype_name,float concrete_prototype_field): Prototype(prototype_name),concrete_prototype_field1_(concrete_prototype_field){
        std::cout << "ConcretePrototype1(std::string prototype_name,float concrete_prototype_field) " << std::endl;
    }

    /**
   * Notice that Clone method return a Pointer to a new ConcretePrototype1
   * replica. so, the client (who call the clone method) has the responsability
   * to free that memory. I you have smart pointer knowledge you may prefer to
   * use unique_pointer here.
   */
   std::unique_ptr<Prototype> clone() const override {
       auto * p = new ConcretePrototype1(*this);
       return std::unique_ptr<Prototype>(p) ;
   }
};



class ConcretePrototype2 : public Prototype {
private:
    float concrete_prototype_field2_;

public:
    ConcretePrototype2(std::string prototype_name, float concrete_prototype_field)
            : Prototype(prototype_name), concrete_prototype_field2_(concrete_prototype_field) {
        std::cout << "2 constructed " << std::endl;
    }
    std::unique_ptr<Prototype> clone() const override {
        return std::unique_ptr<Prototype>(new ConcretePrototype2(*this));
    }
};


/**
 * In PrototypeFactory you have two concrete prototypes, one for each concrete
 * prototype class, so each time you want to create a bullet , you can use the
 * existing ones and clone those.
 */
 class PrototypeFactory{
 private:
     std::unordered_map<Type,Prototype *, std::hash<int>> prototypes_;

 public:
     PrototypeFactory(){
         prototypes_[Type::PROTOTYPE_1] = new ConcretePrototype1("PROTOTYPE_1",50.f);
         prototypes_[Type::PROTOTYPE_2] = new ConcretePrototype1("PROTOTYPE_2",60.f);
     }
     ~PrototypeFactory(){
         delete prototypes_[Type::PROTOTYPE_1];
         delete prototypes_[Type::PROTOTYPE_2];
     }

     std::unique_ptr<Prototype> CreatePrototype(Type type){
         return prototypes_[type]->clone();
     }
 };


void Client(PrototypeFactory & prototype_factory){
    std::cout << "Let's create a Prototype 1\n";

    std::unique_ptr<Prototype>  prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_1);
    prototype->Method(90);

    std::cout << "Let's create a Prototype 2\n";
    prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_2);
    prototype->Method(10);
}

//int main(){
//    PrototypeFactory * prototype_factory = new PrototypeFactory();
//    Client(*prototype_factory);
//    delete prototype_factory;
//    return 0;
//}



#endif