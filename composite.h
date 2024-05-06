#ifndef __COMPOSITE_H
#define __COMPOSITE_H

//组合模式(对象树、Object Tree、Composite)：一种结构型设计模式，你可以使用它将对象组合成树状结构， 并且能像使用独立对象一样使用它们。

//问题引入: 假如你有两类对象: 【产品】和【盒子】。
// 一个盒子中可以包含多个产品或几个较小的盒子。这些小盒子中同样可以包含一些产品或更小的盒子，以此类推。
// 例子: 一个订购系统，订单中可以包含无包装的简单产品，也可以包含装满产品的盒子。。。以及其他盒子。
// 此时如何计算每张订单的总价格？

// 【问题分析】
// 你可以尝试直接计算： 打开所有盒子， 找到每件产品， 然后计算总价。 这在真实世界中或许可行，
// 但在程序中， 你并不能简单地使用循环语句来完成该工作。 你必须事先知道所有 产品和 盒子的类别，
// 所有盒子的嵌套层数以及其他繁杂的细节信息。 因此， 直接计算极不方便， 甚至完全不可行。

// 【解决方案】
// 组合模式建议使用一个通用接口来与 产品和 盒子进行交互， 并且在该接口中声明一个计算总价的方法。
// 那么方法该如何设计呢？ 对于一个产品， 该方法直接返回其价格； 对于一个盒子， 该方法遍历盒子中的所有项目，
// 询问每个项目的价格， 然后返回该盒子的总价格。 如果其中某个项目是小一号的盒子， 那么当前盒子也会遍历其中的所有项目，
// 以此类推， 直到计算出所有内部组成部分的价格。 你甚至可以在盒子的最终价格中增加额外费用， 作为该盒子的包装费用。


#include "common.h"

// Component class declares common operations for both simple and complex objects of a composition
class Component {
    using this_type = Component;
public:
    virtual ~Component() {}
    void SetParent(this_type * parent){
        this->parent_ = parent;
    }
    this_type * GetParent() const {
        return this->parent_;
    }

    //
    virtual void Add(this_type * component) {}
    virtual void Remove(this_type * component) {}

    // a method that lets the client code figure out whether a component can bear children
    virtual bool IsComposite() const {
        return false;
    }

    virtual std::string Operation() const = 0;

protected:
    this_type * parent_;
};

// A leaf can't have any children
class Leaf : public Component {
public:
    std::string Operation() const override {
        return "Leaf";
    }
};

// The composite class represents the complex components that may have children
// usually, the composite objects delegate the actual work to their children and then "sum-up" the result
class Composite : public Component {
public:
    void Add(Component * Component) override {
        this->children_.push_back(Component);
        Component->SetParent(this);
    }

    void Remove(Component * Component) override {
        children_.remove(Component);
        Component->SetParent(nullptr);
    }

    bool IsComposite() const override {
        return true;
    }

    std::string Operation() const override {
        std::string result;
        for (const Component * c : children_){
            if (c == children_.back()){
                result += c->Operation();
            } else {
                result += c->Operation() + "+";
            }
        }
        return "Branch(" + result + ")";
    }
protected:
    std::list<Component *> children_;
};

void ClientCode(Component * component){
    std::cout << "RESULT: " << component->Operation();
}



#endif