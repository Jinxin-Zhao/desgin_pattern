#ifndef  __GENERATOR_H_
#define  __GENERATOR_H_

#include "common.h"

class Product1{
public:
    void ListParts() const {
        std::cout << "Product parts: ";
        for (size_t i = 0; i < parts_.size(); ++i){
            if(parts_[i] == parts_.back()){
                std::cout << parts_[i];
            } else {
                std::cout << parts_[i] << ",";
            }
        }
    }

    std::vector<std::string>  parts_;
};

class Builder {
public:
    virtual ~Builder(){}
    virtual void ProducePartA() const = 0;
    virtual void ProducePartB() const = 0;
    virtual void ProducePartC() const = 0;
};

class ConcreteBuilder1 : public Builder {
private:
    Product1 * product;

public:
    ConcreteBuilder1(){
        this->Reset();
    }

    ~ConcreteBuilder1(){
        delete product;
    }

    void Reset(){
        this->product = new Product1();
    }

    void ProducePartA() const override {
        this->product->parts_.push_back("PartA1");
    }

    void ProducePartB() const override {
        this->product->parts_.push_back("PartB1");
    }

    void ProducePartC() const override {
        this->product->parts_.push_back("PartC1");
    }

    ///
//    Product1 * GetProduct1() {
//        Product1 * result = this->product;
//        this->Reset();
//        return result;
//    }

    std::unique_ptr<Product1> GetProduct1() {
        Product1 * result = this->product;
        this->Reset();
        return std::unique_ptr<Product1>(result);
    }
};


/**
 * The Director is only responsible for executing the building steps in a
 * particular sequence. It is helpful when producing products according to a
 * specific order or configuration. Strictly speaking, the Director class is
 * optional, since the client can control builders directly.
 */
class Director{
private:
    Builder * builder;
public:
    void set_builder(Builder * builder){
        this->builder = builder;
    }

    void BuildMinimalViableProduct(){
        this->builder->ProducePartA();
    }

    void BuildFullFeaturedProduct(){
        this->builder->ProducePartA();
        this->builder->ProducePartB();
        this->builder->ProducePartC();
    }
};

void ClientCode(Director& director)
{
    ConcreteBuilder1* builder = new ConcreteBuilder1();
    director.set_builder(builder);
    std::cout << "Standard basic product:\n";
    director.BuildMinimalViableProduct();

    std::unique_ptr<Product1> p= builder->GetProduct1();
    p->ListParts();

    std::cout << "Standard full featured product:\n";
    director.BuildFullFeaturedProduct();

    p = builder->GetProduct1();
    p->ListParts();

    // Remember, the Builder pattern can be used without a Director class.
    std::cout << "Custom product:\n";
    builder->ProducePartA();
    builder->ProducePartC();
    p = builder->GetProduct1();
    p->ListParts();

    delete builder;
}




#endif