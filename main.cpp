#include <iostream>
#include "c_simple_factory.h"
#include "c_generator.h"
#include "c_proto_type.h"
#include "composite.h"
//structed design pattern
#include "s_adapter.h"
#include "iterator.h"
#include "facade.h"
#include "c_single_instance.h"
#include "observer.h"
#include "strategy.h"
#include "template.h"
#include "status.h"
#include "visitor.h"

int main()
{
    Creator * creator = new ConcreteCreator1();
    ClientCode(*creator);
    Creator * creator2 = new ConcreteCreator2();
    ClientCode(*creator2);

    delete creator;
    delete creator2;


    //// generator
    std::cout << "start to test generator pattern ===================\n";
    Director * director = new Director();
    ClientCode(*director);
    delete director;

    PrototypeFactory * prototype_factory = new PrototypeFactory();
    Client(*prototype_factory);
    delete prototype_factory;

    //// composite
    std::cout << "==================== composite =================" << std::endl;
    std::unique_ptr<Component> tree(new Composite);
    std::unique_ptr<Component> branch_1(new Composite);

    std::unique_ptr<Component> leaf_1(new Leaf);
    std::unique_ptr<Component> leaf_2(new Leaf);
    std::unique_ptr<Component> leaf_3(new Leaf);
    branch_1->Add(leaf_1.get());
    branch_1->Add(leaf_2.get());
    std::unique_ptr<Component> branch_2(new Composite);
    branch_2->Add(leaf_3.get());

    tree->Add(branch_1.get());
    tree->Add(branch_2.get());
    std::cout << "a composite tree:\n ";
    ClientCode(tree.get());

    ////////
    std::cout << "==================== iterator =================" << std::endl;
    // type: int
    Container<int> cont;
    for (int i = 0; i < 10; ++i){
        cont.Add(i);
    }

    std::unique_ptr<Iterator<int, Container<int>>> it(cont.CreateIterator());
    for (it->First(); !it->IsDone(); it->Next()) {
        std::cout << *it->Current() << " ";
    }
    std::cout << std::endl;

    // type: custom type
    Container<Data> cont_2;
    Data a(100), b(1000), c(100000);
    cont_2.Add(a);
    cont_2.Add(b);
    cont_2.Add(c);

    std::unique_ptr<Iterator<Data, Container<Data>>> it_2(cont_2.CreateIterator());
    for (it_2->First(); !it_2->IsDone(); it_2->Next()) {
        std::cout << it_2->Current()->data() << " ";
    }
    std::cout << std::endl;


    ////// facade patteren
    std::cout << "==================== facade =================" << std::endl;
    Subsystem_1 * sub_1 = new Subsystem_1;
    Subsystem_2 * sub_2 = new Subsystem_2;

    Facade * facade = new Facade(sub_1, sub_2);
    std::cout << facade->Operation();


    ////// singleton patteren
    std::cout << "==================== singleton =================" << std::endl;
    std::thread t1(TestSingleThreadSingletonBar);
    std::thread t2(TestSingleThreadSingletonFoo);
    t1.join();
    t2.join();
    std::cout << "multithread singleton" << std::endl;
    // multithread thread singleton
    std::thread m_t1(TestMultiThreadSingletonBar);
    std::thread m_t2(TestMultiThreadSingletonFoo);
    m_t1.join();
    m_t2.join();

    std::cout << "==================== observer =================" << std::endl;
    Subject * subject = new Subject;
    std::unique_ptr<Observer> ob1 (new Observer(*subject));
    std::unique_ptr<Observer> ob2 (new Observer(*subject));
    std::unique_ptr<Observer> ob3 (new Observer(*subject));

    subject->CreateMessage("Hello world! ");
    ob3->RemoveMeFromTheList();

    subject->CreateMessage("The weather is hot today!");
    std::unique_ptr<Observer> ob4 (new Observer(*subject));

    ob2->RemoveMeFromTheList();
    std::unique_ptr<Observer> ob5(new Observer(*subject));

    subject->CreateMessage("My new car is great!");
    ob5->RemoveMeFromTheList();
    ob4->RemoveMeFromTheList();
    ob3->RemoveMeFromTheList();

    std::cout << "==================== strategy =================" << std::endl;
    Context * context = new Context(new ConcreteStrategyA);
    std::cout << "Client: Strategy is set to normal sorting.\n";
    context->DoSomeBusinessLogic();
    std::cout << "\n";
    std::cout << "Client: Strategy is set to reverse sorting.\n";
    context->set_strategy(new ConcreteStrategyB);
    context->DoSomeBusinessLogic();
    delete context;

    std::cout << "==================== template =================" << std::endl;
    std::unique_ptr<ConcreteClass1> c1(new ConcreteClass1);
    c1->TemplateMethod();

    std::unique_ptr<ConcreteClass2> c2(new ConcreteClass2);
    c2->TemplateMethod();

    std::cout << "==================== status =================" << std::endl;
    WordFile * wd = new WordFile(new ConcreteStateA);
    wd->Request1();
    wd->Request2();
    delete wd;

    std::cout << "==================== visitor =================" << std::endl;
    std::array<const CVComponent*, 2> components = {new CVConcreteComponentA, new CVConcreteComponentB};
    std::cout << "The client code works with all visitors via the base Visitor interface:\n";
    CVConcreteVisitor1 * visitor1 = new CVConcreteVisitor1;
    for (const CVComponent * comp : components){
        comp->Accept(visitor1);
    }
    CVConcreteVisitor2 * visitor2 = new CVConcreteVisitor2;
    for (const CVComponent * comp : components){
        comp->Accept(visitor2);
    }
    for (const CVComponent * comp : components){
        delete comp;
    }
    delete visitor1;
    delete visitor2;



    return 0;
}