#include <iostream>
#include <m_vector.h>

using namespace std;

int main()
{
    cout << "Hello World!" << endl;

    int len = 2;

    m_vector<int> a(len);
    m_vector<int> a2 = a;
    m_vector<int> a3 = move(a2);
    for(int i = 0; i < len; i++)
    {
        printf("1 %d\n", a[i]);
    }
    for(int i = 0; i < len; i++)
    {
        printf("2 %d\n", a3[i]);
    }

    a2 = a3;
    for(int i = 0; i < len; i++)
    {
        printf("3 %d\n", a2[i]);
    }

    m_vector<int> a4{0,1,2,3};
    for(int i = 0; i < 4; i++)
    {
        printf("3 %d\n", a4[i]);
    }
    return 0;
}
