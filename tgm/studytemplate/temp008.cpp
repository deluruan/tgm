
#include <cstdio>
#include <iostream>
#include <list>

using namespace std;

class A
{
#if 1
typedef struct{
    int u8CmdType;
    void (A::*PFUNC)(void);
} ST_UART_PC_T;
#endif
    private:
        list<ST_UART_PC_T> m_lst_cmd;
    public:
        A(int i)
        {
        }
        void (A::*PFUNC)(void);
        void funa(void)
        {
            puts("A");
        }
        void funb(void)
        {
            puts("B");
        }
        void func(void)
        {
            puts("C");
        }

        void hht001(int i)
        {
            PFUNC = (i==1)?(&A::funa):(&A::funb);
            (this->*PFUNC)();

            ST_UART_PC_T m_uart;
            m_uart.u8CmdType=8;
            m_uart.PFUNC=&A::funa;
            m_lst_cmd.push_back(m_uart);
            m_uart.u8CmdType=8;
            m_uart.PFUNC=&A::funb;
            m_lst_cmd.push_back(m_uart);
            m_uart.u8CmdType=0x0FF;
            m_uart.PFUNC=NULL;
            m_lst_cmd.push_back(m_uart);
            m_uart.u8CmdType=8;
            m_uart.PFUNC=&A::func;
            m_lst_cmd.push_back(m_uart);
            puts("============01");
            list<ST_UART_PC_T>::iterator itmUartCmd;
            for(itmUartCmd=m_lst_cmd.begin(); itmUartCmd != m_lst_cmd.end(); ++itmUartCmd)
            {
                cout << itmUartCmd->u8CmdType << endl <<" ";
                if(itmUartCmd->PFUNC!=NULL)
                {
                    (this->*itmUartCmd->PFUNC)();
                }
            }
            puts("============02");
        }




};



int main()
{
    A a(2);
    a.hht001(2);

    //GFUNC = a.PFUNC;
    //(a.*GFUNC)();
    return 0;
}

