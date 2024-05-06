#ifndef _STRATEGY_H_
#define _STRATEGY_H_

#include <vector>

// 问题引入: 一天， 你打算为游客们创建一款导游程序。 该程序的核心功能是提供美观的地图， 以帮助用户在任何城市中快速定位。
// 用户期待的程序新功能是自动路线规划： 他们希望输入地址后就能在地图上看到前往目的地的最快路线。
// 程序的首个版本只能规划公路路线。 驾车旅行的人们对此非常满意。 但很显然， 并非所有人都会在度假时开车。 因此你在下次更新时添加了规划步行路线的功能。
// 此后， 你又添加了规划公共交通路线的功能。
// 而这只是个开始。 不久后， 你又要为骑行者规划路线。 又过了一段时间， 你又要为游览城市中的所有景点规划路线。
// 尽管从商业角度来看， 这款应用非常成功， 但其技术部分却让你非常头疼： 每次添加新的路线规划算法后， 导游应用中主要类的体积就会增加一倍。 终于在某个时候， 你觉得自己没法继续维护这堆代码了。
// 无论是修复简单缺陷还是微调街道权重， 对某个算法进行任何修改都会影响整个类， 从而增加在已有正常运行代码中引入错误的风险。
// 此外， 团队合作将变得低效。 如果你在应用成功发布后招募了团队成员， 他们会抱怨在合并冲突的工作上花费了太多时间。 在实现新功能的过程中， 你的团队需要修改同一个巨大的类， 这样他们所编写的代码相互之间就可能会出现冲突。

class Strategy{
public:
    virtual ~Strategy(){}
    virtual std::string DoAlgorithm(const std::vector<std::string> & data) const = 0;
};

class Context {
private:
    Strategy * strategy_;
public:
    Context(Strategy * strategy = nullptr) : strategy_(strategy){}
    ~Context(){
        delete this->strategy_;
    }
    void set_strategy(Strategy * strategy){
        delete this->strategy_;
        this->strategy_ = strategy;
    }

    void DoSomeBusinessLogic() const {
        std::cout << "Context: Sorting data using the strategy\n";
        std::string result = this->strategy_->DoAlgorithm(std::vector<std::string>{"a","e","c","b","d"});
        std::cout << result << "\n";
    }
};

class ConcreteStrategyA : public Strategy {
public:
    std::string DoAlgorithm(const std::vector<std::string> & data) const override{
        std::string result;
        std::for_each(std::begin(data),std::end(data), [&result](const std::string & letter){
            result += letter;
        });
        std::sort(std::begin(result), std::end(result));
        return result;
    }
};

class ConcreteStrategyB : public Strategy {
public:
    std::string DoAlgorithm(const std::vector<std::string> & data) const override{
        std::string result;
        std::for_each(std::begin(data),std::end(data), [&result](const std::string & letter){
            result += letter;
        });
        std::sort(std::begin(result), std::end(result));
        for (int i = 0; i < result.size() / 2; i++) {
            std::swap(result[i], result[result.size() - i - 1]);
        }

        return result;
    }
};


#endif