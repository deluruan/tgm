//普通函数形式：

#if 0
#include <string> 
#include <iostream> 
void printstring(const std::string& str)  
{     
    std::cout << str << std::endl; 
} 
int main() 
{     
    std::string str("Hello World");     
    printstring(str); 
    return 0; 
}//输出：Hello World 
#endif

//模板函数形式：

#if 0
#include <string> 
#include <iostream> 
using namespace std; 
template<typename T> void print(const T& var) 
{     
    cout << var << endl; 
} 
int main() 
{     
    string str("Hello World");     
    const int num=1234; 
    print(str); 
    print(num); 
    return 0; 
} 
//输出：Hello World  
//       1234 
#endif

#include <iostream> 
#include <string>
#include <cstring>

using namespace std; 


//#include <>
using namespace std; 
// 定义函数模板，找出三个值中最小的值，与数据类型无关 
    template <class T> 
T min(T ii, T jj, T kk) 
{ 
    T temp; 
    if((ii<jj)&&(ii<kk)){        temp=ii;    } 
    else if((jj<ii)&&(jj<kk)){        temp=jj;    } 
    else    {        temp=kk;    } 
    return temp; 
} 
//非模板函数重载 
const char* min(const char* ch1, const char* ch2,const char* ch3) 
{ 
    const char* temp; 
    int result1 = strcmp(ch1,ch2); 
    int result2 = strcmp(ch1,ch3); 
    int result3 = strcmp(ch2,ch1); 
    int result4 = strcmp(ch2,ch3); 
    if((result1<0)&&(result2<0))    {        temp = ch1;    } 
    else if((result3<0)&&(result4<0))    {        temp=ch2;    } 
    else    {        temp=ch3;    } 
    return temp; 
} 

int main() 
{ 
    cout<<min(100,20,30)<<endl; 
    cout<<min(10.60,10.64,53.21)<<endl; 
    cout<<min('c','a','C')<<endl;     
    cout<<min("anderson","Washington","Smith")<<endl; 
    return 0;
} 


