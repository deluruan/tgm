
#include <cstdio>
#include <iostream>
#include <list>

using namespace std;

//class A;

//void (A::*GFUNC)(void);



class A
{
#if 1
typedef struct{
    int u8CmdType;
    void (A::*PFUNC)(void);

    //PFUNC pFunc;
} ST_UART_PC_T;
#endif


    private:
        ST_UART_PC_T m_uart_pc[20];
        list<ST_UART_PC_T> m_lst_cmd;

    public:
        A(int i)
        {
            //p2 = (i==1)?(&A::funa):(&A::funb);
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
            ST_UART_PC_T m_uart;

            PFUNC = (i==1)?(&A::funa):(&A::funb);
            (this->*PFUNC)();

            m_uart_pc[0].u8CmdType=8;
            m_uart_pc[0].PFUNC=&A::funa;
            m_lst_cmd.push_back(m_uart_pc[0]);

            m_uart_pc[1].u8CmdType=8;
            m_uart_pc[1].PFUNC=&A::funb;
            m_lst_cmd.push_back(m_uart_pc[1]);

            m_uart_pc[2].u8CmdType=0x0FF;
            m_uart_pc[2].PFUNC=NULL;
            m_lst_cmd.push_back(m_uart_pc[2]);

            m_uart.u8CmdType=8;
            m_uart.PFUNC=&A::func;
            m_lst_cmd.push_back(m_uart);

            int ncount;
            for(ncount=0;ncount<20;ncount++)
            {
                if(m_uart_pc[ncount].u8CmdType==0x0FF)
                    break;
                (this->*m_uart_pc[ncount].PFUNC)();
#if 0
                PFUNC =   m_uart_pc[ncount].PFUNC;
                (this->*PFUNC)();
#endif
                //(this->*p2)();
            }
            puts("============");

            list<ST_UART_PC_T>::iterator itmUartCmd;
            for(itmUartCmd=m_lst_cmd.begin(); itmUartCmd != m_lst_cmd.end(); ++itmUartCmd)
            {
                cout << itmUartCmd->u8CmdType << endl <<" ";
                if(itmUartCmd->PFUNC!=NULL)
                {
                    (this->*itmUartCmd->PFUNC)();
                }
            }
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

