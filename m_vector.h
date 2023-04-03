#ifndef M_VECTOR_H
#define M_VECTOR_H

#include <stdexcept>
#include <initializer_list>

class m_vectorException: public std::runtime_error
{
public:
    explicit m_vectorException(const char* message) : std::runtime_error(message){}
};

template<typename Type>
class m_vector
{
private:
    Type *m_vec;
    int amount;
public:
    m_vector(int length); // Конструктор по длине
    m_vector(const m_vector<Type> &vect); // Копирование
    m_vector(m_vector<Type> &&vect); // Перенос ака move(a2)
    explicit m_vector(std::initializer_list<Type> lst); // конструктор со списком инициализации
    ~m_vector(); // Деструктор, удаление вектора
    m_vector<Type> &operator =(const m_vector<Type>& lst); // Присваивание вектора другому вектору
    Type &operator[](int index); // получить элемент как массив a[1]
    int get_length() const;
    void set_elem(int index, const Type &elem);
    Type &get_elem(int index);
    //Type[] to_array();
    m_vector<Type>& operator+=(const m_vector<Type>& vect);
};

template<typename Type>
m_vector<Type> &m_vector<Type>::operator+=(const m_vector<Type> &vect){
    m_vector<Type> local = *this;
    amount = local.amount + vect.amount;
    m_vec = new Type[amount]{};
    for(int i = 0; i < local.amount; i++)
        m_vec[i] = local.m_vec[i];
    for(int i = 0; i < vect.amount; i++)
        m_vec[local.amount+i] = vect.m_vec[i];
    return *this;
}

//template<typename Type>
//friend std::ostream& m_vector<Type>::operator<<(std::ostream& os, const m_vector<Type>&lst){

//}

//template<typename Type>
//Type[] m_vector<Type>::to_array()
//{

//}

template<typename Type>
Type &m_vector<Type>::get_elem(int index)
{
    if(index < 0 || amount < index)
        throw m_vectorException("Wrong index of m_vector");
    return m_vec[index];
}

template<typename Type>
void m_vector<Type>::set_elem(int index, const Type &elem)
{
    if(index < 0 || amount < index)
        throw m_vectorException("Wrong index of m_vector");
    m_vec[index] = elem;
}

template<typename Type>
int m_vector<Type>::get_length() const
{
    return amount;
}

template<typename Type>
m_vector<Type>::m_vector(int length) : amount(length)
{
    if(length <= 0)
        throw m_vectorException("Bad length of m_vector");
    m_vec = new Type[length]{};
}

template<typename Type>
m_vector<Type>::m_vector(const m_vector<Type> &vect)
{
    amount = vect.amount;
    m_vec = new Type[amount];
    for(int i = 0; i < amount; i++)
        m_vec[i] = vect.m_vec[i];
}

template<typename Type>
m_vector<Type>::m_vector(m_vector<Type> &&vect)
{
    m_vec = vect.m_vec;
    amount = vect.amount;
    vect.amount = 0;
    vect.m_vec = nullptr;
}

template<typename Type>
m_vector<Type>::m_vector(std::initializer_list<Type> lst) : amount(lst.size())
{
    if(amount <= 0)
        throw m_vectorException("Bad length of m_vector");
    m_vec = new Type[amount]{};
    int i = 0;
    for(Type item : lst)
        m_vec[i++] = item;
}

template<typename Type>
m_vector<Type>::~m_vector()
{
    delete[] m_vec;
}

template<typename Type>
m_vector<Type> &m_vector<Type>::operator=(const m_vector<Type> &lst)
{
    m_vec = new Type[lst.amount]{};
    amount = lst.amount;
    for(int i = 0; i < lst.amount; i++)
        m_vec[i] = lst.m_vec[i];

    return *this; // возвращает объект, который сгенерировал вызов
}

template<typename Type>
Type &m_vector<Type>::operator[](int index)
{
    if(index < 0 || amount < index)
        throw m_vectorException("Wrong index of m_vector");
    return *(m_vec + index);
}

#endif // M_VECTOR_H
