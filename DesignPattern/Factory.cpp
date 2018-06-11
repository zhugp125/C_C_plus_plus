/*************************************************************************
	> File Name: Factory.cpp
	> Author: 
	> Mail: 
	> Created Time: 日  6/10 21:38:34 2018
    > 工厂模式
 ************************************************************************/

#include<iostream>
using namespace std;

enum FactoryType
{
    FT_A,
    FT_B,
};

class Show
{
public:
    virtual ~Show() {}
    virtual void show() = 0;
};

class ShowA : public Show
{
public:
    ~ShowA() {}
    void show() { cout << "show A\n"; }
};

class ShowB : public Show
{
public:
    ~ShowB() {}
    void show() { cout << "show B\n"; }
};

class FactoryShow
{
public:
    Show* createShow(FactoryType t)
    {
        if (t == FT_A)
        {
            return new ShowA;
        }
        else if (t == FT_B)
        {
            return new ShowB;
        }
        return NULL;
    }
};

int main()
{
    FactoryShow fs;
    Show* sa = fs.createShow(FT_A);
    if (NULL != sa)
    {
        sa->show();
        delete sa;
    }

    Show* sb = fs.createShow(FT_B);
    if (NULL != sb)
    {
        sb->show();
        delete sb;
    }
    return 0;
}
