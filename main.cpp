#include <iostream>
#include <m_vector.h>
#define MESSAGE endl << "[m_vector::" << __FUNCTION__ << "]" << endl

using namespace std;

void test_set_elem();
void test_constructor();
void test_copy();
void test_transfer();
void test_init_list();
void test_get_elem();
void test_operator_eq();
void test_cout();
void test_to_array();
void test_sub();
void test_multiple();
void test_devide();
void test_plus();
void test_minus();
void test_multiple_solo();
void test_devide_solo();
void test_iterator();

int main()
{
    cout << "Hello Epta!" << endl;
//    test_constructor();
//    test_copy();
//    test_transfer();
//    test_init_list();
//    test_set_elem();
//    test_get_elem();
//    test_operator_eq();
//    test_cout();
//    test_sub();
//    test_multiple();
//    test_devide();
//    test_plus();
//    test_minus();
//    test_multiple_solo();
//    test_devide_solo();
    test_iterator();
    return 0;
}

void test_iterator()
{
    try {
        m_vector<int> a{4,5,6,3};
        m_vector<int>::Iterator it = a.iterator_begin();
        cout << MESSAGE << it.value() << endl;
    } catch(m_vectorException &e) {
        cout << "Exception says: " << e.what() << endl;
    }
}

void test_devide_solo()
{
    try {
        m_vector<int> a{4,5,6,3};
        m_vector<int> a2 = a / 4;
        cout << MESSAGE << a2 << endl;
    } catch(m_vectorException &e) {
        cout << "Exception says: " << e.what() << endl;
    }
}

void test_multiple_solo()
{
    try {
        m_vector<int> a{4,5,6,3};
        m_vector<int> a2 = a * 4;
        cout << MESSAGE << a2 << endl;
    } catch(m_vectorException &e) {
        cout << "Exception says: " << e.what() << endl;
    }
}

void test_minus()
{
    try {
        m_vector<int> a1{4,5,6,3,4};
        m_vector<int> a2{4,5,6,3};
        m_vector<int> a3 = a1 - a2;
        cout << MESSAGE << a3 << endl;
    } catch(m_vectorException &e) {
        cout << "Exception says: " << e.what() << endl;
    }
}

void test_plus()
{
    try {
        m_vector<int> a1{4,5,6,3};
        m_vector<int> a2{4,5,6,3};
        m_vector<int> a3 = a1 + a2;
        cout << MESSAGE << a3 << endl;
    } catch(m_vectorException &e) {
        cout << "Exception says: " << e.what() << endl;
    }
}

void test_devide()
{
    try {
        m_vector<int> a{4,5,6,3};
        a /= 4;
        cout << MESSAGE << a << endl;
    } catch(m_vectorException &e) {
        cout << "Exception says: " << e.what() << endl;
    }
}

void test_multiple()
{
    try {
        m_vector<int> a{4,5,6,3};
        a *= 4;
        cout << MESSAGE << a << endl;
    } catch(m_vectorException &e) {
        cout << "Exception says: " << e.what() << endl;
    }
}

void test_sub()
{
    try {
        m_vector<int> a{4,5,6,3};
        m_vector<int> a1{1, 1, 1, 45, 1};
        a -= a1;
        cout << MESSAGE << a << endl;
    } catch(m_vectorException &e) {
        cout << "Exception says: " << e.what() << endl;
    }
}

void test_to_array()
{
 // TODO:
}

void test_cout()
{
    m_vector<int> a{4, 5, 4, 5};
    cout << a << endl;
}

void test_operator_eq()
{
    try {
        m_vector<int> a{4,5,6,3};
        m_vector<int> a1{1, 1, 1};
        a += a1;
        cout << MESSAGE << a << endl;
    } catch(m_vectorException &e) {
        cout << "Exception says: " << e.what() << endl;
    }
}

void test_get_elem()
{
    try {
        m_vector<int> a{4,5,6,3};
        cout << MESSAGE << a << endl;
        int get_elem = a.get_elem(2);
        cout << MESSAGE << "get_elem:" << get_elem << endl;
        get_elem = a.get_elem(-2);
        cout << MESSAGE << "get_elem:" << get_elem << endl;
    } catch(m_vectorException &e) {
        cout << "Exception says: " << e.what() << endl;
    }
}

void test_init_list()
{
    m_vector<int> a{0,1,2,3};
    cout << MESSAGE << a << endl;
}

void test_transfer()
{
    try{
        m_vector<int> a(2);
        m_vector<int> a2 = std::move(a);
        cout << MESSAGE << a2 << endl;
    } catch(m_vectorException &e) {
        cout << "Exception says: " << e.what() << endl;
    }
}

void test_copy()
{
    try{
        m_vector<int> a(2);
        m_vector<int> a2 = a;
        cout << MESSAGE << a2 << endl;
    } catch(m_vectorException &e) {
        cout << "Exception says: " << e.what() << endl;
    }
}

void test_constructor()
{
    try {
        m_vector<int> a(2);
        cout << MESSAGE << a << endl;
        m_vector<int> a1(-1);
        m_vector<int> a2(0); // не доходит до сюда
    } catch(m_vectorException &e) {
        cout << "Exception says: " << e.what() << endl;
    }
}

void test_set_elem()
{
    try {
        m_vector<int> a(5);
        cout << MESSAGE << a << endl;
        a.set_elem(3, 45);
        cout << MESSAGE << a << endl;
        a.set_elem(99, 45);
        cout << MESSAGE << a << endl;
    } catch(m_vectorException &e) {
        cout << "Exception says: " << e.what() << endl;
    }
}
