#ifndef  __SIMPLE_FACTORY_H
#define  __SIMPLE_FACTORY_H


class Product {
public:
    virtual ~Product(){}
    virtual std::string Operation() const = 0;
};

class ConcreteProduct1 : public Product{
public:
    std::string Operation() const override {
        return "{Result of the ConcreteProduct1}";
    }
};

class ConcreteProduct2 : public Product{
public:
    std::string Operation() const override {
        return "{Result of the ConcreteProduct2}";
    }
};

class Creator {
public:
    virtual ~Creator(){};
    virtual Product * FactoryMethod() const = 0;

    std::string SomeOperation() const {
        Product * product = this->FactoryMethod();
        std::string result = "Creator: The same creator's code has just worked with " + product->Operation();
        delete product;
        return result;
    }
};

class ConcreteCreator1 : public Creator{
public:
    Product * FactoryMethod() const override {
        return new ConcreteProduct1();
    }
};

class ConcreteCreator2 : public Creator{
public:
    Product * FactoryMethod() const override {
        return new ConcreteProduct2();
    }
};

void ClientCode(const Creator & creator){
    std::cout << "Client: I'm not aware of the creator's class " << creator.SomeOperation() << std::endl;
}


//////////
//simple facotory
//fault: 不符合开闭原则，要增加fruit就得修改工厂源代码
class AbstractFruit{
public:
    virtual void showName() = 0;
};

class Apple : public AbstractFruit{
    virtual void showName() {
        std::cout << "This is Apple" << std::endl;
    }
};

class Banana : public AbstractFruit{
    virtual void showName() {
        std::cout << "This is Banana" << std::endl;
    }
};

class Pear : public AbstractFruit{
    virtual void showName() {
        std::cout << "This is Pear" << std::endl;
    }
};

class FruitFactory{
public:
    static AbstractFruit * CreateFruit(std::string flag){
        if(flag == "apple"){
            return new Apple();
        } else if(flag == "banana"){
            return new Banana();
        } else if(flag == "Pear"){
            return new Pear();
        } else {
            return nullptr;
        }
    }
};


void test(){
    FruitFactory * factory = new FruitFactory;
    AbstractFruit * fruit = factory->CreateFruit("apple");
    fruit->showName();
    delete fruit;

    fruit = factory->CreateFruit("banana");
    fruit->showName();

    delete factory;
}

//factory function pattern = simple factory + "开闭原则"
//将工厂抽象出来，新建一个抽象工厂类
//fault: 增加了系统中类的个数，复杂度；增加了系统的抽象性和理解难度

//abstract factory
class AbstractFruitFactory{
public:
    virtual AbstractFruit * CreateFruit() = 0;
};

class AppleFactory : public AbstractFruitFactory{
public:
    virtual AbstractFruit * CreateFruit(){
        return new Apple;
    }
};

class BananaFactory : public AbstractFruitFactory{
public:
    virtual AbstractFruit * CreateFruit(){
        return new Banana;
    }
};

class PearFacory : public AbstractFruitFactory{
public:
    virtual AbstractFruit * CreateFruit(){
        return new Pear;
    }
};

void test_1(){
    AbstractFruitFactory * factory = nullptr;
    AbstractFruit * fruit = nullptr;

    //
    factory = new AppleFactory;
    fruit = factory->CreateFruit();
    fruit->showName();

    delete fruit;
    delete factory;

    factory = new BananaFactory;
    fruit = factory->CreateFruit();
    fruit->showName();

    delete fruit;
    delete factory;

}


/////abstract factory pattern
//客户端不知道它所需要的对象的类
//抽象工厂类通过其子类来指定创建哪个对象

//抽象苹果
class AbstractApple{
public:
    virtual void showName() = 0;
};

//中国苹果
class ChineseApple : public AbstractApple{
public:
    virtual void showName(){
        std::cout << "Chinese Apple" << std::endl;
    }
};

class USAApple : public AbstractApple{
public:
    virtual void showName(){
        std::cout << "USA Apple" << std::endl;
    }
};

class JapaneseApple : public AbstractApple{
public:
    virtual void showName(){
        std::cout << "Japanese Apple" << std::endl;
    }
};

//抽象香蕉
class AbstractBanana{
public:
    virtual void showName() = 0;
};

class ChineseBanana : public AbstractBanana{
public:
    virtual void showName(){
        std::cout << "Chinese Banana" << std::endl;
    }
};

class USABanana : public AbstractBanana{
public:
    virtual void showName(){
        std::cout << "USA Banana" << std::endl;
    }
};

class JapaneseBanana : public AbstractBanana{
public:
    virtual void showName(){
        std::cout << "Japanese Banana" << std::endl;
    }
};

////
class AbstractFactory{
public:
    virtual AbstractApple * CreateApple() = 0;
    virtual AbstractBanana * CreateBanana() = 0;
    //virtual AbstractPear * CreatePear() = 0;
};

class ChineseFactory : public AbstractFactory{
public:
    virtual AbstractApple * CreateApple() {
        return new ChineseApple;
    }
    virtual AbstractBanana * CreateBanana(){
        return new ChineseBanana;
    }
};

class JapanFactory : public AbstractFactory{
public:
    virtual AbstractApple * CreateApple() {
        return new JapaneseApple;
    }
    virtual AbstractBanana * CreateBanana(){
        return new JapaneseBanana;
    }
};

/////
void test_2(){
    AbstractFactory * factory = nullptr;
    AbstractApple * apple = nullptr;
    AbstractBanana * banana = nullptr;

    factory = new ChineseFactory;
    apple = factory->CreateApple();
    banana = factory->CreateBanana();

    apple->showName();
    banana->showName();

    delete apple;
    delete banana;
}









#endif