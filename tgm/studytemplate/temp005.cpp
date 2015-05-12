
#include <stdio.h>

class A
{
    public:
        A(int i)
        {
            //p2 = (i==1)?(&A::funa):(&A::funb);
        }
        void (A::*p2)(void);
        void funa(void)
        {
            puts("A");
        }
        void funb(void)
        {
            puts("B");
        }

        void hht001(int i)
        {
            p2 = (i==1)?(&A::funa):(&A::funb);
            (this->*p2)();
            //p2();
        }

        /*

        void hht001(int i)
        {
            p2 = (i==1)?(&A::funa):(&A::funb);
        }
*/


};



int main()
{
    A a(2);
    a.hht001(2);
    void (A::*p)(void);
    p = a.p2;
    (a.*p)();
    return 0;
}

