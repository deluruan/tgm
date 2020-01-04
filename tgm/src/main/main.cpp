//���̷����� 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <errno.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#define defHhtOpsPort 12345    // �����˿� 
#define BACKLOG 5     // �������ӿͻ������� 
#define BUF_SIZE 200 
int fd_A[BACKLOG];    // ���ӵ�FD���� 
int conn_amount;    // ��ǰ���ӵ����� 

void showclient() 
{ 
    int i; 
    printf("client amount: %d\n", conn_amount); 
    for (i = 0; i < BACKLOG; i++) 
    { 
        printf("[%d]:%d  ", i, fd_A[i]); 
    } 
    printf("\n\n"); 
} 

int createTcpSock(void)
{
    int fd_tcp_listen=-1;               // ����fd_tcp_listen
    struct sockaddr_in server_addr;    // server address information 
    int yes = 1; 
    //��������Socket
    //while(1)
    {
        if ((fd_tcp_listen = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        {
            printf("rdl_0003;hhhhh001\n");
            perror("Create listening socket error!");

            //sleep(30);
            //continue;
            return -1;
        }
        //else
        //break;
    }

    //��������Socket 
    //SO_REUSEADDR BOOL �����׽ӿں�һ������ʹ���еĵ�ַ���� 
    if (setsockopt(fd_tcp_listen, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) 
    { 
        perror("setsockopt error!");
        return -1;
    } 

    server_addr.sin_family = AF_INET;         // host byte order 
    server_addr.sin_port = htons(defHhtOpsPort);     // short, network byte order 
    server_addr.sin_addr.s_addr = INADDR_ANY; // automatically fill with my IP 
    memset(server_addr.sin_zero, '\0', sizeof(server_addr.sin_zero)); 
    //���´�����Socket��ָ����IP�Ͷ˿� 
    if (bind(fd_tcp_listen, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) 
    { 
        perror("bind error!"); 
        return -1;
    } 
    //��ʼ���������������ΪBACKLOG 
    if (listen(fd_tcp_listen, BACKLOG) == -1) 
    { 
        perror("listen error!"); 
        return -1;
    } 
    printf("listen port %d\n", defHhtOpsPort); 

    return fd_tcp_listen;
}

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

void* sock_tcp_svr(void* pdata)
{ 
    int fd_tcp_listen, new_fd;               // ����fd_tcp_listen, ������new_fd 
    //struct sockaddr_in server_addr;    // server address information 
    socklen_t sin_size; 
    char buf[BUF_SIZE]; 
    int ret; 
    int i; 
    printf("rdl_0001;hhhhh001\n");

    while(true)
    {
        fd_tcp_listen =createTcpSock();
        if(fd_tcp_listen<0)
        {
            sleep(10);
            continue;
        }
    }

    struct sockaddr_in client_addr;    // connector's address information 
    //����ļ����������� 
    fd_set fdsr; 
    //����ļ������������������ļ��� 
    int maxsock; 
    //Select��ʱ���ص�ʱ�䡣 
    struct timeval tv; 
    conn_amount = 0; 
    sin_size = sizeof(client_addr); 
    maxsock = fd_tcp_listen; 
    while (1) 
    {
        printf("rdl_0002;hhhhh001\n");

        // ��ʼ���ļ����������� initialize file descriptor set 
        FD_ZERO(&fdsr); 
        // ��Sock_fd���뵽�ļ����������� 
        FD_SET(fd_tcp_listen, &fdsr); 
        // ��ʱ����30�� 
        tv.tv_sec = 30; 
        tv.tv_usec = 0; 
        // �ѻ��socket�ľ�����뵽�ļ������������� 
        for (i = 0; i < BACKLOG; i++) 
        { 
            if (fd_A[i] != 0) 
            { 
                FD_SET(fd_A[i], &fdsr);
                maxsock=MAX(maxsock,fd_A[i]);
            } 
        } 
        //Select ����ԭ�� 
        //int select��nfds�� readfds�� writefds�� exceptfds�� timeout�� 
        //nfds: select���ӵ��ļ������,�ӽ����д򿪵��ļ���������һ����Ϊ��Ҫ���Ӹ��ļ��е� 
        //����ļ��ż�һ 
        //readfds:select���ӵĿɶ��ļ�������� 
        //writefds:select���ӵĿ�д�ļ�������ϡ� 
        //exceptfds:select���ӵ��쳣�ļ�������ϡ� 
        //timeout:����select�ĳ�ʱ����ʱ�䡣 
        ret = select(maxsock + 1, &fdsr, NULL, NULL, &tv); 
        if (ret < 0) 
        { 
            perror("select error!"); 
            break; 
        } 
        else if (ret == 0) 
        { 
            printf("timeout\n");
            continue; 
        } 
        // ��ѯ�����ļ���������socket�� 
        for (i = 0; i < conn_amount; i++) 
        { 
            //FD_ISSET��int fd�� fdset *fdset�������fdset��ϵ���ļ����fd�Ƿ�ɶ�д�� 
            // >0��ʾ�ɶ�д�� 
            if (FD_ISSET(fd_A[i], &fdsr)) 
            { 
                //�������� 
                ret = recv(fd_A[i], buf, sizeof(buf), 0); 
                if (ret <= 0) //�������ݳ��� 
                {        
                    printf("client[%d] close\n", i); 
                    close(fd_A[i]); 
                    FD_CLR(fd_A[i], &fdsr); 
                    fd_A[i] = 0; 
                } 
                else  // ���ݽ��ճɹ� 
                {   
                    //���������ݵ����һλ��0 
                    if (ret < BUF_SIZE) 
                        memset(&buf[ret], '\0', 1); 
                    printf("client[%d] send:%s\n", i, buf); 
                    char sndbuf[30];
                    sprintf(sndbuf,"fd[%d];%s",i,buf);
                    send(fd_A[i], sndbuf, strlen(sndbuf), 0); 
                } 
            } 
        } 
        // ����Ƿ��������ӽ���������������ӽ������������ӣ�������socket�� 
        //�����뵽����ļ������������С� 
        if (FD_ISSET(fd_tcp_listen, &fdsr)) 
        { 
            //�������� 
            new_fd = accept(fd_tcp_listen, (struct sockaddr *)&client_addr, &sin_size); 
            if (new_fd <= 0) 
            { 
                perror("accept socket error!"); 
                continue; 
            } 
            // ���µ����Ӽ��뵽����ļ����������� 
            if (conn_amount < BACKLOG) 
            { 
                fd_A[conn_amount++] = new_fd; 
                printf("new connection client[%d] %s:%d\n", conn_amount,inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port)); 
                //if (new_fd > maxsock) 
                //  maxsock = new_fd; 
            } 
            else 
            { 
                printf("max connections arrive, exit\n"); 
                send(new_fd, "bye", 4, 0); 
                close(new_fd); 
                break; 
            } 
        } 
        showclient(); 
    } 
    // �ر��������� 
    for (i = 0; i < BACKLOG; i++) 
    { 
        if (fd_A[i] != 0) 
        { 
            close(fd_A[i]); 
        } 
    } 
    return NULL;

}

#include <stdio.h>
int radlineandprt()
{	int i,n;	
    char a[1024];	
    FILE *fp;	
    //gets(a);	
    strcpy(a,"/home/rdlhht/work/srcipc/tgm/logbak-sharp-getevent-gesture/ses-downward-one-002.log");
    strcpy(a,"/home/rdlhht/work/srcipc/tgm/logbak-sharp-getevent-gesture/ses-downward-three-002.log");
    if((fp=fopen(a,"r"))==NULL)	
    {		
        printf("File Name Error.a=%s\n",a);		
        return 0;	
    }	
    //scanf("%d",&n);	
    i=0;	
    printf("\n");
    while(!feof(fp))	
    {		
        if(fgets(a,1000,fp))		
        {			
            i++;	
            char s1[100];
            char s2[100];
            char s3[100];
            //char s4[100];
            int npos;

            sscanf(a,"%s %s %s %x",s1,s2,s3,&npos); 
            //if(memcmp(s2,"EV_ABS",6)==0)
            if(memcmp(s3,"ABS_MT_TRACKING_ID",strlen("ABS_MT_TRACKING_ID"))==0)
            {
                printf("% 5d;",npos);
                //printf("i=% 4d;% 5d;",i,npos);
            }
            if(memcmp(s3,"ABS_MT_POSITION_X",strlen("ABS_MT_POSITION_X"))==0)
            {
                printf("% 5d;",npos);
            }
            if(memcmp(s3,"ABS_MT_POSITION_Y",strlen("ABS_MT_POSITION_Y"))==0)
            {
                printf("% 5d;----",npos);
            }
            if(memcmp(s3,"SYN_REPORT",strlen("SYN_REPORT"))==0)
            {
                printf("\n",npos);
            }

            //printf("%s %s %s %05d %04x\n",s1,s2,s3,npos,npos); 
            //if(i==n)			
            {				
                //puts(a);				
                //fclose(fp);				
                //return 0;			
            }		
        }
        else
        {			
            //break;		
        }	
    }	
    printf("\n");
    //printf("Line No Error.\n");    
    fclose(fp);
    sleep(2);
    return 0;
}


int mainhhh()
{
    int i; 
    unsigned int j; 
    char input[ ]="10 0x1b aaaaaaaa bbbbbbbb"; 
    char s[5]; 
    sscanf(input,"%d %x %5[a-z] %*s %f",&i,&j,s,s); 
    printf("%d %d %s\n",i,j,s); 
    radlineandprt();
    //sock_tcp_svr(NULL);
}
//Test.cpp

#include <iostream>

using std::cout;

using std::endl;

//����һ������ģ��,�����Ƚ������������ͬ�������͵Ĳ����Ĵ�С��classҲ���Ա�typename���棬

//T���Ա��κ���ĸ�������ִ��档

template <class T>

T min(T x,T y)

{ return(x<y)?x:y;}

int main( )
{

     int n1=2,n2=10;

     double d1=1.5,d2=5.6;

     cout<< "��С����:"<<min(n1,n2)<<endl;

     cout<< "��Сʵ��:"<<min(d1,d2)<<endl;
	 printf("");

     system("PAUSE");
     return 0;

}




