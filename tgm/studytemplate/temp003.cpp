

#include <iostream>

using namespace std;

template<typename T>
class A
{
    private:
        typedef int (T::*delegateFun)(int);
        T * _This;
        delegateFun _deleGate;

    public:   

        //This被代理的对象, delegateFun被代理的方法

        A(T * This, int (T::*delegateFun)(int))
        {
            _This = This;
            _deleGate = delegateFun;
        }

        //c被代理的参数
        int execue(int c)
        {
            return (_This->*_deleGate)(c);
        }

};


class B
{
    public:
        int FunA(int a) {return a + 10;}
        int FunB(int a) {return a - 10;}
        B()
        {
        }
};

int main(int argc, char* argv[])
{
    B *objB = new B();

    A<B>  delegateObj1(objB, (&B::FunA));
    A<B>  delegateObj2(objB, (&B::FunB));

    cout << delegateObj1.execue(10) <<endl;
    cout << delegateObj2.execue(20) <<endl;

    return 0;
}



