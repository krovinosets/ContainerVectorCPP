#ifndef M_VECTOR_H
#define M_VECTOR_H


#include <initializer_list>
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
};

template<typename Type>
int m_vector<Type>::get_length() const{
    return amount;
}

template<typename Type>
m_vector<Type>::m_vector(int length) : amount(length)
{
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
    return *(m_vec + index);
    int a; // udali potom
}

#endif // M_VECTOR_H
