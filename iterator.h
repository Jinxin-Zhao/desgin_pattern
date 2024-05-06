#ifndef  __ITERATOR_H_
#define  __ITERATOR_H_

#include "common.h"

// 迭代器模式是一种行为设计模式，让你能在不暴露集合底层表现形式(列表、栈和树等)的情况下
// 遍历集合中所有的元素

// 迭代器模式的主要思想是将集合的遍历行为抽取为单独的迭代器对象。
// 所有迭代器必须实现相同的接口。 这样一来， 只要有合适的迭代器，
// 客户端代码就能兼容任何类型的集合或遍历算法。 如果你需要采用特殊方式来遍历集合，
// 只需创建一个新的迭代器类即可， 无需对集合或客户端进行修改。

// 迭代器可以通过导航方法 （例如 next和 previous等） 来轻松识别。
// 使用迭代器的客户端代码可能没有其所遍历的集合的直接访问权限。


// T: Type(数据类型)
// U: 容器(集合)
template <typename T, typename U>
class Iterator {
public:
    typedef typename std::vector<T>::iterator iter_type;
    Iterator(U * p_data, bool reverse = false) : m_pdata_(p_data){
        m_it_ = m_pdata_->m_data_.begin();
    }

    void First(){
        m_it_ = m_pdata_->m_data_.begin();
    }

    void Next(){
        m_it_++;
    }

    bool IsDone() {
        return (m_it_ == m_pdata_->m_data_.end());
    }
    iter_type Current() {
        return m_it_;
    }

private:
    U * m_pdata_;
    iter_type m_it_;
};


template <class T>
class Container {
    friend class Iterator<T, Container>;

public:
    void Add(T a){
        m_data_.push_back(a);
    }

    Iterator<T, Container> * CreateIterator(){
        return new Iterator<T, Container>(this);
    }

private:
    std::vector<T> m_data_;
};

class Data {
public:
    Data(int a = 0) : m_data_(a){}
    void set_data(int a) {
        m_data_ = a;
    }
    int data() {
        return m_data_;
    }

private:
    int m_data_;
};

#endif