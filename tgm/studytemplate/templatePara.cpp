#include <iostream>
#include <list>
#include <vector>

using std::cout;
using std::endl;
using std::list;
using std::vector;


template <typename T> void print(T v)
{
    typename T::iterator itor;
    for (itor = v.begin(); itor != v.end(); ++itor)
    {
        cout << *itor << " ";
    }
    cout << endl;
}

int main(int argc, char **argv){
    list<int> l;
    l.push_back(1);
    l.push_front(2);
    if(!l.empty())
        print(l);
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(6);
    if(!vec.empty())
        print(vec);
    return 0;
}

