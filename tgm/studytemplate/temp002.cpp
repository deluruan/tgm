#include <iostream> 
#include <typeinfo> 

using namespace std; 
template<class T>void g1(T a, T b){cout<<"hansu g1()"<<typeid(T).name()<<endl;} 

template<class T1,class T2,class T3>T1 g2(T2 a,T3 b) 
{T1 c=a;cout<<"hansug2()"<<typeid(T1).name()<<typeid(T2).name()<<typeid(T3).name()<<endl; return c;} 

template<class T1,class T2> void g3 ( T1 a ) {cout<<"hansu g3()"<<typeid(T1).name()<<typeid(T2).name()<<endl;} 

template<class T1,int a> void g4(T1 b, double c){cout<<"hansu g4()"<<typeid(T1).name()<<typeid(a).name()<<endl;} 

template<class T1,class T2> class A{public:void g();}; 

//模板显示实例化示例。 
//因为模板的声明或定义不能在局部范围或函数内进行。所以模板实例化都应在全局范围内进行。 
template void g1<double>(double a,double b); //把函数模板显示实例化为int型。 
template class A<double,double>; //显示实例化类模板，注意后面没有对象名，也没有{}大括号。 
//template class A<int,int>{};  //错误，显示实例化类模板后面不能有大括号{}。 
//template class A<int,int> m;  //错误，显示实例化类模板后面不能有对象名。 
//main函数开始
 
int main() 
{
    //显示模板实参示例。显示模板实参适合于函数模板 
    //1、显示模板实参用于同一个模板形参的类型不一致的情况。函数g1形式为template<class T>void g1(T a, T b) 
    g1<double>(2,3.2);//输出"hansu g1() int"两个实参类型不一致，第一个为int第二个为double。但这里用显示模板实参把类型形参T指定为double，所以第一个int型的实参数值2被转换为double类型。 
    //g1(2,3.2);错误，这里没有用显式模板实参。所以两个实参类型不一致。 
    //2、用于函数模板的反回类型中。函数g2形式为template<class T1,class T2,class T3> T1 g2(T2 a,T3 b) 
    //g2(2,3);错误，无法推演类型形参T1。 
    //int g2(2,3);错误，不能以这种方法试图推导类型形参T1为int型。 
    //int a=g2(2,3);错误，以这种方式试图推演出T1的类型为int也是错误的。 
    g2<int,int,int>(2,3);//正确，将T1，T2，T3 显示指定为int型。输出"hansu g2() intintint" 
    //3、应用于模板函数的参数中没有出现模板形参的情况其中包括省略的用法，函数g3的形式为template<class T1,class T2> void g3(T1 a) 
    //g3(2);错误，无法为函数模板的类型形参T2推演出正确的类型 
    //g3(2,3);错误，岂图以这种方式为T2指定int型是错误的，因为函数只有一个参数。 
    //g3<,int>(2);错误，这里起图用数值2来推演出T1为int型,而省略掉第一个的显示模板实参，这种方法是错误的。在用显示模板实参时，只能省略掉尾部的实参。 
    //g3<int>(2);错误，虽然用了显示模板实参方法，省略掉了尾部的实参，但该方法只是把T1指定为int型，仍然无法为T2推演正确的类型。 
    g3<int,int>(2);//正确，显示指定T1和T2的类型都为int型。 
    //4、用于函数模板的非类型形参。g4函数的形式为template<class T1,int a> void g4(T1 b,double c) 
    //g4(3,3.2);错误，虽然指定了两个参数，但是这里仍然无法为函数模板的非类型形参int a推演出正确的实参。因为第二个函数参数x.2是传递给函数的参数double c的，而不是函数模板的非类型形参int a。 
    //g4(3,2);错误，起图以整型值把实参传递给函数模板的非类型形参是不行的，这里数值2会传递给函数形参double c并把int型转换为double型。所以非类型形参int a仍然无实参。 
    //int d=1; g4<int ,d >(3,3.2); //错误，调用方法正确，但对于非类型形参要求实参是一个常量表达式，而局部变量c是非常量表达式，不能做为非类型形参的实参，所以错误。 
    g4<int,1>(2,3.2);//正确，用显示模板实参，把函数模板的类型形参T1设为int型，把数值1传给非类型形参int a，并把a设为1，把数值2 传给函数的第一个形参T1 b并把b设为2，数值?.2传给函数的第二个形参double c并把c设为?.2。 
    const int d=1; g4<int,d>(2,3.2);//正确，这里变量d是const常量，能作为非类型形参的实参，这里参数的传递方法同上面的语句。 
    return 0; 
} 
