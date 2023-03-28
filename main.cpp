#include <iostream>
#include <m_vector.h>

using namespace std;

int main()
{
    cout << "Hello World!" << endl;

    int len = 2;

    m_vector<int> a(len);
    m_vector<int> a2 = a;
    m_vector<int> a3 = std::move(a2);
    cout << "len: " << a.get_length() << endl;
    for(int i = 0; i < len; i++)
    {
        printf("1 %d\n", a[i]);
    }
    cout << "len: " << a3.get_length() << endl;
    for(int i = 0; i < len; i++)
    {
        printf("2 %d\n", a3[i]);
    }
    a2 = a3;
    cout << "len: " << a2.get_length() << endl;
    for(int i = 0; i < len; i++)
    {
        printf("3 %d\n", a2[i]);
    }

    m_vector<int> a4{0,1,2,3};
    cout << "len: " << a4.get_length() << endl;
    for(int i = 0; i < 4; i++)
    {
        printf("4 %d\n", a4[i]);
    }
    return 0;
}
