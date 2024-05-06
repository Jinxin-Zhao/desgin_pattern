#ifndef __SINGLE_INSTANCE_H_
#define __SINGLE_INSTANCE_H_

// 单例模式是一种创建型设计模式， 让你能够保证一个类只有一个实例， 并提供一个访问该实例的全局节点。
// 1. 保证一个类只有一个实例, 最常见的原因是控制某些共享资源 （例如数据库或文件） 的访问权限。
// 2. 为该实例提供一个全局访问节点.和全局变量一样， 单例模式也允许在程序的任何地方访问特定对象。 但是它可以保护该实例不被其他代码覆盖。

// solution:
// 将默认构造函数设为私有， 防止其他对象使用单例类的new运算符
// 新建一个静态构建方法作为构造函数。 该函数会 “偷偷” 调用私有构造函数来创建对象， 并将其保存在一个静态成员变量中。
// 此后所有对于该函数的调用都将返回这一缓存对象
// 如果你的代码能够访问单例类， 那它就能调用单例类的静态方法。 无论何时调用该方法， 它总是会返回相同的对象。

// 单线程版本
class Singleton {
protected:
    Singleton(const std::string value) : value_(value){
    }
    static Singleton * singleton_;

    static Singleton * pinstance_;

    static std::mutex mutex_;

    std::string value_;
public:
    Singleton(Singleton & other) = delete;

    void operator=(const Singleton &) = delete;

    static Singleton * GetInstance(const std::string & value);

    static Singleton * GetThreadInstance(const std::string & value);

    void SomeBusinessLogic(){
    }
    std::string value() const {
        return value_;
    }
};

// normal singleton
Singleton * Singleton::singleton_ = nullptr;

// multithread singleton
Singleton * Singleton::pinstance_{nullptr};
std::mutex Singleton::mutex_;

Singleton * Singleton::GetInstance(const std::string & value){
    if (singleton_ == nullptr){
        singleton_ = new Singleton(value);
    }
    return singleton_;
}

// multithread singleton
Singleton * Singleton::GetThreadInstance(const std::string & value){
    std::lock_guard<std::mutex> lock(mutex_);
    if (pinstance_ == nullptr){
        pinstance_ = new Singleton(value);
    }
    return pinstance_;
}

void TestSingleThreadSingletonFoo(){
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton * singleton = Singleton::GetInstance("Foo");
    std::cout << singleton->value() << "\n";
}

void TestSingleThreadSingletonBar(){
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton * singleton = Singleton::GetInstance("Bar");
    std::cout << singleton->value() << "\n";
}

// multithread thread
void TestMultiThreadSingletonFoo(){
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton * singleton = Singleton::GetThreadInstance("Foo");
    std::cout << singleton->value() << "\n";
}

void TestMultiThreadSingletonBar(){
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton * singleton = Singleton::GetThreadInstance("Bar");
    std::cout << singleton->value() << "\n";
}

//多线程版本
class TSingleton{

};

#endif