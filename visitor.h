#ifndef __VISITOR_H_
#define __VISITOR_H_

#include "common.h"
// 假如你的团队开发了一款能够使用巨型图像中地理信息的应用程序。 图像中的每个节点既能代表复杂实体 （例如一座城市），
// 也能代表更精细的对象 （例如工业区和旅游景点等）。 如果节点代表的真实对象之间存在公路， 那么这些节点就会相互连接。
// 在程序内部， 每个节点的类型都由其所属的类来表示， 每个特定的节点则是一个对象。

// 一段时间后， 你接到了实现将图像导出到 XML 文件中的任务。 这些工作最初看上去非常简单。 你计划为每个节点类添加导出函数，
// 然后递归执行图像中每个节点的导出函数。 解决方案简单且优雅： 使用多态机制可以让导出方法的调用代码不会和具体的节点类相耦合。
// 但你不太走运， 系统架构师拒绝批准对已有节点类进行修改。 他认为这些代码已经是产品了， 不想冒险对其进行修改， 因为修改可能会引入潜在的缺陷。


// solution
// 如果现在该操作能在不同类的对象上执行会怎么样呢？ 比如在我们的示例中， 各节点类导出 XML 文件的实际实现很可能会稍有不同。
// 因此， 访问者类可以定义一组 （而不是一个） 方法， 且每个方法可接收不同类型的参数.

class CVConcreteComponentA;
class CVConcreteComponentB;

class Visitor {
public:
    virtual void VisitConcreteComponentA(const CVConcreteComponentA * element) const = 0;
    virtual void VisitConcreteComponentB(const CVConcreteComponentB * element) const = 0;
};

class CVComponent {
public:
    virtual ~CVComponent() {}
    virtual void Accept(Visitor * visitor) const = 0;
};

class CVConcreteComponentA : public CVComponent {
public:
    void Accept(Visitor * visitor) const override {
        visitor->VisitConcreteComponentA(this);
    }
    std::string ExclusiveMethodOfConcreteComponentA() const {
        return "A";
    }
};

class CVConcreteComponentB : public CVComponent {
public:
    void Accept(Visitor * visitor) const override {
        visitor->VisitConcreteComponentB(this);
    }
    std::string SpecialMethodOfConcreteComponentB() const {
        return "B";
    }
};

class CVConcreteVisitor1 : public Visitor {
public:
    void VisitConcreteComponentA(const CVConcreteComponentA * ele) const override{
        std::cout << ele->ExclusiveMethodOfConcreteComponentA() << " + ConcreteVisitor1\n";
    }

    void VisitConcreteComponentB(const CVConcreteComponentB * ele) const override {
        std::cout << ele->SpecialMethodOfConcreteComponentB() << " + ConcreteVisitor1\n";
    }
};

class CVConcreteVisitor2 : public Visitor {
public:
    void VisitConcreteComponentA(const CVConcreteComponentA * ele) const override{
        std::cout << ele->ExclusiveMethodOfConcreteComponentA() << " + ConcreteVisitor2\n";
    }

    void VisitConcreteComponentB(const CVConcreteComponentB * ele) const override {
        std::cout << ele->SpecialMethodOfConcreteComponentB() << " + ConcreteVisitor2\n";
    }
};

#endif