
#include <cstdio>
#include <iostream>
#include <list>
using namespace std;

class A
{
    typedef struct{
        int u8CmdType;
        void (A::*PFUNC)(void);
    } ST_UART_PC_T;

    private:

    public:
    A(int i)
    {
    }
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
    public:
    void hht002(int i)
    {
        void (A::*PFUNC)(void)=NULL;
        PFUNC = (i==1)?(&A::funa):(&A::funb);
        if(PFUNC!=NULL)
            (this->*PFUNC)();
    }
    void hht001()
    {
        list<ST_UART_PC_T> m_lst_cmd;
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
            cout << itmUartCmd->u8CmdType << endl;
            if(itmUartCmd->PFUNC!=NULL)
            {
                (this->*itmUartCmd->PFUNC)();
            }
        }
        puts("============02");
    }
};

int test_func(A a)
{
    void (A::*GFUNC)(void)=NULL;
    GFUNC =&A::funa;
    if(GFUNC!=NULL)
        (a.*GFUNC)();
    return 0;
}

int main()
{
    const int g_ulSlopX=4290;
    const int g_ulSlopY=4260;
    const int g_ulOffsetX=768;
    const int g_ulOffsetY=768;

    int xpos=16000;
    int ypos=1000;

	int ulXtmp = (g_ulSlopX*xpos)>>12;
	//ulYtmp = (g_ulSlopY*Contact_Info[Index].Y_Raw)>>12;

	if (ulXtmp > g_ulOffsetX)
	{
		xpos = ulXtmp - g_ulOffsetX;
	}
	else
	{
		xpos = 0;
	}

	if ( xpos> 0x7fff)
	{
		xpos = 0x7fff;
	}

    printf("xpos=%d\n",xpos);

#if 0
    A a(2);
    a.hht002(2);
    a.hht001();
    test_func(a);
#endif
    return 0;
}

