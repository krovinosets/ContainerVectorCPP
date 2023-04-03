#include <iostream>
#include <m_vector.h>

using namespace std;

void test_set_elem();
void test_constructor();
void test_copy();
void test_transfer();
void test_init_list();
void test_get_elem();
void test_operator_eq();

template<typename Type>
void print_m_vector(const char *message, m_vector<Type> vect){
    printf("\n[%s]\n", message);
    for(int i = 0; i < vect.get_length(); i++)
        printf("| m_vector[%d] = %d\n", i, vect[i]);
    printf("[END]\n");
}

int main()
{
    cout << "Hello World!" << endl;
    test_constructor();
    test_copy();
    test_transfer();
    test_init_list();
    test_set_elem();
    test_get_elem();
    test_operator_eq();

    return 0;
}

void test_operator_eq()
{
    try {
        m_vector<int> a{4,5,6,3};
        m_vector<int> a1{1, 1, 1};
        a += a1;
        print_m_vector("m_vector[operator_eq a] Print", a);
    } catch(m_vectorException &e) {
        cout << "Exception says: " << e.what() << endl;
    }
}

void test_get_elem()
{
    try {
        m_vector<int> a{4,5,6,3};
        print_m_vector("m_vector[get elem a] Print", a);
        int get_elem = a.get_elem(2);
        printf("get_elem: %d\n", get_elem);
        get_elem = a.get_elem(-2);
        printf("get_elem: %d\n", get_elem);
    } catch(m_vectorException &e) {
        cout << "Exception says: " << e.what() << endl;
    }
}

void test_init_list()
{
    m_vector<int> a{0,1,2,3};
    print_m_vector("m_vector[init list a] Print", a);
}

void test_transfer()
{
    try{
        m_vector<int> a(2);
        m_vector<int> a2 = std::move(a);
        print_m_vector("m_vector[Moved a2] Print", a2);
    } catch(m_vectorException &e) {
        cout << "Exception says: " << e.what() << endl;
    }
}

void test_copy()
{
    try{
        m_vector<int> a(2);
        m_vector<int> a2 = a;
        print_m_vector("m_vector[Copied a] Print", a2);
    } catch(m_vectorException &e) {
        cout << "Exception says: " << e.what() << endl;
    }
}

void test_constructor()
{
    try {
        m_vector<int> a(2);
        print_m_vector("m_vector[a] Print", a);
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
        print_m_vector("m_vector[set_elem_test] Print",a);
        a.set_elem(3, 45);
        print_m_vector("m_vector[set_elem_test] Print",a);
        a.set_elem(99, 45);
        print_m_vector("m_vector[set_elem_test] Print",a);
    } catch(m_vectorException &e) {
        cout << "Exception says: " << e.what() << endl;
    }
}
