#ifndef PATTERNS_H_INCLUDED
#define PATTERNS_H_INCLUDED
#include <vector>

using namespace std;
const int MaxSize = 50;
template<typename A>
class Iterator
{
protected:
    Iterator()
    {
    }
public:
    virtual ~Iterator(){}
    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool IsDone() const = 0;
    virtual A GetCurrent() const = 0;
};
template <typename A>
class Containers {
public:
    virtual ~Containers() {}
    virtual bool IsEmpty() const = 0;
    virtual size_t Size() const = 0;
    virtual A IndexElement(size_t index) const = 0;
    virtual Iterator<A>* GetIterator() = 0;
};
template<typename A>
class StackIterator:public Iterator<A>
{
private:
    const Containers<A> *StackContainer;
    size_t Pos;
public:
    StackIterator(const Containers<A>* container)
    : StackContainer(container), Pos(0) {}

    void First() override { Pos = 0; }
    void Next() override { Pos++; }
    bool IsDone() const override { return (Pos >= StackContainer->Size()); }
    A GetCurrent() const override { return StackContainer->IndexElement(Pos); }
};
template<typename A>
class Stack:public Containers<A>
{
private:
    A Massive [MaxSize];
    size_t End ;
public:
    bool IsEmpty() const
    {
        return (End==0);
    }
    size_t Size() const
    {
        return End;
    }
    void Push (A newItem)
    {
        Massive[End++]= newItem;
    }
    A Pop()
    {
        return Massive[--End];
    }
    A operator[](size_t index) const
    {
        return Massive[index];
    }
    A IndexElement(size_t index) const
    {
        return Massive[index];
    };
    Iterator<A>* GetIterator() override {
        return new StackIterator<A>(this);
    }
    Stack() : End(0) {}
};
template<typename A>
class VectorIterator:public Iterator<A>
{
private:
    const Containers<A> *VectorContainer;
    size_t Pos;
public:
    VectorIterator(const Containers<A> *container)
    : VectorContainer(container), Pos(0) {}

    void First() override { Pos = 0; }
    void Next() override { Pos++; }
    bool IsDone() const override { return (Pos >= VectorContainer->Size()); }
    A GetCurrent() const override { return VectorContainer->IndexElement(Pos); }
};
template<typename A>
class VectorStack :public Containers<A>
{
private:
    vector <A> data;

public:
    VectorStack() {};

    bool IsEmpty() const override
    {
        return data.empty();
    }

    size_t Size() const override
    {
        return data.size();
    }

    void Push(const A& newItem)
    {
        data.push_back(newItem);
    }
    A Top() const
    {
        return data.back();
    }

    A IndexElement(size_t index) const override
    {
        return data[index];
    };
    Iterator<A>* GetIterator() override {
        return new VectorIterator<A>(this);
    }
};
template<typename A>
class IteratorDecorator : public Iterator<A>
{
protected:
    Iterator<A> *It;

public:
    IteratorDecorator(Iterator<A> *it) : It(it) {}
    virtual ~IteratorDecorator() { delete It; }
    virtual void First() { It->First(); }
    virtual void Next() { It->Next(); }
    virtual bool IsDone() const { return It->IsDone(); }
    virtual A GetCurrent() const { return It->GetCurrent(); }
};
template<typename ContainerType, typename ItemType>
class ConstIteratorAdapter : public Iterator<ItemType>
{
protected:
    ContainerType *Container;
    typename ContainerType::const_iterator It;

public:
    ConstIteratorAdapter(ContainerType *container)
    : Container(container)
    {
        It = Container->begin();
    }

    virtual ~ConstIteratorAdapter() {}
    virtual void First() { It = Container->begin(); }
    virtual void Next() { It++; }
    virtual bool IsDone() const { return (It == Container->end()); }
    virtual ItemType GetCurrent() const { return *It; }
};
#endif //PATTERNS_H_INCLUDED
