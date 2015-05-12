#include <iostream>
#include <string>
#include <cstdio>
#include <cassert>
//#include <assert.h>


using namespace std;

class A;

typedef int (A::*PFUNC)(int,int);//指针名前一定要加上所属类型类名 A::的限定

typedef struct{
	int u8CmdType;
	PFUNC pFunc;
} ST_UART_PC_T;

class A
{
    public:

        static A* GetInstance();


        int func(int x,int y)
        {
            //A a;                  
            //因为成员函数地址的解引用必须要附驻与某个对象的地址，所以我们必须创建某个对象。
            
            //PFUNC fun=&A::func;
            //cout<<"min:"<<(A::GetInstance().*fun)(4,5)<<endl;

            printf("A::func:x=%d,y=%d/n",x,y);
            return (x<y?x:y);
        }

        int hht(int x,int y)
        {
            printf("A::func:x=%d,y=%d/n",x,y);
            return (x<y?x:y);
        }

    public:
        A();
        ~A();

    private:
        static A* m_pInstance;

};

A::A()
{

}

A::~A()
{


}

A* A::m_pInstance = NULL;
A* A::GetInstance(void)
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new (std::nothrow) A;
		assert(m_pInstance);
	}
	return m_pInstance;
}

int main()
{
    PFUNC fun=&A::func;
    A a;                  
    //因为成员函数地址的解引用必须要附驻与某个对象的地址，所以我们必须创建某个对象。
    cout<<"min:"<<(a.*fun)(4,5)<<endl;


    return 0;
}

