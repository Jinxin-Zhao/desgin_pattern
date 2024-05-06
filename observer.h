#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class IObserver {
public:
    virtual  ~IObserver(){}
    virtual  void Update(const std::string & message) = 0;
};

class ISubject {
public:
    virtual ~ISubject(){}
    virtual void Attach(IObserver * observer) = 0;
    virtual void Detach(IObserver * observer) = 0;
    virtual void Notify() = 0;
};

class Subject : public ISubject{
public:
    virtual ~Subject(){
        std::cout << "Subject destructor\n";
    }
    void Attach(IObserver * observer) override {
        list_observer_.push_back(observer);
    }
    void Detach(IObserver * observer) override {
        list_observer_.remove(observer);
    }
    void Notify() override {
        std::list<IObserver*>::iterator it = list_observer_.begin();
        HowManyObserver();
        while(it != list_observer_.end()) {
            (*it)->Update(message_);
            ++it;
        }
    }

    void CreateMessage(std::string message = "Empty") {
        this->message_ = message;
        Notify();
    }

    void HowManyObserver() {
        std::cout << "There are " << list_observer_.size() << " observers" << std::endl;
    }

    void SomeBusinessLogic() {
        this->message_ = "change message message";
        Notify();
    }

private:
    std::list<IObserver *> list_observer_;
    std::string message_;
};

class Observer : public IObserver {
public:
    Observer(Subject & subject) : subject_(subject) {
        this->subject_.Attach(this);
        std::cout << "Hi, I'm the Observer " << ++Observer::static_number_ << std::endl;
        this->number_ = Observer::static_number_;
    }
    virtual ~Observer(){
        std::cout << "Bye I'm the Observer " << this->number_ << std::endl;
    }

    void Update(const std::string & message_from_subject) override {
        message_from_subject_ = message_from_subject;
        PrintInfo();
    }
    void RemoveMeFromTheList() {
        subject_.Detach(this);
        std::cout << "Observer " << number_ << " removed from the list\n";
    }
    void PrintInfo() {
        std::cout << "Observer " << this->number_ << " : a message available " << this->message_from_subject_ << std::endl;
    }

private:
    std::string message_from_subject_;
    Subject & subject_;
    static int static_number_;
    int number_;
};

int Observer::static_number_ = 0;










#endif