#ifndef M_VECTOR_H
#define M_VECTOR_H

#define THROW_BAD_VEC_IF(val) if (val) throw m_vectorException("Bad m_vector")

#include <stdexcept>
#include <initializer_list>

class m_vectorException: public std::exception
{
private:
    char *message;
public:
    explicit m_vectorException(const char *msg) : std::exception(){message = (char *)msg;}
    const char *what() const noexcept{return message;}
};

template<typename Type>
class m_vector
{
private:
    Type *m_vec;
    int amount;
public:
    class Iterator
    {
    private:
        m_vector<Type> it_m_vector;
        int it_m_vector_index = -1;
    public:
        Iterator(m_vector<Type> container_obj);
        Iterator next();
        Type value();
        bool is_end();
        Iterator &operator++();
        Type &operator*();
        bool operator ==(Iterator &b);
        bool operator !=(Iterator &b);
    };
    m_vector(int length); // Конструктор по длине
    m_vector(const m_vector<Type> &vect); // Копирование
    m_vector(m_vector<Type> &&vect); // Перенос ака move(a2)
    explicit m_vector(std::initializer_list<Type> lst); // конструктор со списком инициализации // [!] Дыра в безопаности
    ~m_vector(); // Деструктор, удаление вектора
    m_vector<Type> &operator =(const m_vector<Type> &lst); // Присваивание вектора другому вектору
    Type &operator[](int index); // получить элемент как массив a[1]
    int get_length() const;
    void set_elem(int index, const Type &elem);
    Type &get_elem(int index);
    Type *to_array();
    template <class X> friend std::ostream &operator<<(std::ostream &os, const m_vector<X> &lst);
    m_vector<Type> &operator+=(const m_vector<Type> &vect);
    m_vector<Type> &operator -=(const m_vector<Type> &vect);
    m_vector<Type> &operator *=(const Type &val);
    m_vector<Type> &operator /=(const Type &val);
    template<typename _T> friend m_vector<_T> operator+(const m_vector<_T> &v1, const m_vector<_T> &v2);
    template<typename _T> friend m_vector<_T> operator-(const m_vector<_T> &v1, const m_vector<_T> &v2);
    template<typename _T, typename T> friend m_vector<_T> operator*(const m_vector<_T> &v1, const T &val);
    template<typename _T, typename T> friend m_vector<_T> operator/(const m_vector<_T> &v1, const T &val);
    Iterator iterator_begin();
    Iterator iterator_end();
};

template <typename Type>
bool m_vector<Type>::Iterator::operator!=(Iterator &b)
{
    return (it_m_vector_index != b.it_m_vector_index)
            && (it_m_vector[it_m_vector_index] != b.it_m_vector[b.it_m_vector_index]);
}

template <typename Type>
bool m_vector<Type>::Iterator::operator==(Iterator &b)
{
    return (it_m_vector_index == b.it_m_vector_index)
            && (it_m_vector[it_m_vector_index] == b.it_m_vector[b.it_m_vector_index]);
}

template <typename Type>
Type &m_vector<Type>::Iterator::operator*()
{
    return it_m_vector.m_vec[it_m_vector_index];
}

template <typename Type>
typename m_vector<Type>::Iterator &m_vector<Type>::Iterator::operator++()
{
    if(it_m_vector_index == -1)
        throw m_vectorException("Iterator doesn not exist");
    if(it_m_vector_index + 1 > it_m_vector.get_length())
        throw m_vectorException("Iterator out of range");
    it_m_vector_index += 1;
    return *this;
}

template <typename Type>
bool m_vector<Type>::Iterator::is_end()
{
    if(it_m_vector_index == it_m_vector.get_length()-1)
        return true;
    else
        return false;
}

template <typename Type>
typename m_vector<Type>::Iterator m_vector<Type>::Iterator::next()
{
    if(it_m_vector_index == -1)
        throw m_vectorException("Iterator doesn not exist");
    if(it_m_vector_index + 1 > it_m_vector.get_length())
        throw m_vectorException("Iterator out of range");
    it_m_vector_index += 1;
    return *this;
}

template <typename Type>
Type m_vector<Type>::Iterator::value()
{
    return it_m_vector.m_vec[it_m_vector_index];
}

template <typename Type>
m_vector<Type>::Iterator::Iterator(m_vector<Type> container_obj) : it_m_vector(container_obj), it_m_vector_index(0)
{
    while(!(*this).is_end())
        (*this).next();
    it_m_vector_index = 0;
}

template<typename Type>
typename m_vector<Type>::Iterator m_vector<Type>::iterator_begin()
{
    return m_vector<Type>::Iterator(*this);
}

template<typename Type>
typename m_vector<Type>::Iterator m_vector<Type>::iterator_end()
{
    m_vector<Type>::Iterator it = m_vector<Type>::Iterator(*this);
    while(!it.is_end())
        it.next();
    return it;
}

template<typename _T, typename T>
m_vector<_T> operator/(const m_vector<_T> &v1, const T &val)
{
    THROW_BAD_VEC_IF(v1.amount == 0);
    if(val == 0)
        throw m_vectorException("devide to zero");
    for(int i = 0; i < v1.amount; i++)
        v1.m_vec[i] /= val;
    return v1;
}

template<typename _T, typename T>
m_vector<_T> operator*(const m_vector<_T>& v1, const T &val)
{
    THROW_BAD_VEC_IF(v1.amount == 0);
    for(int i = 0; i < v1.amount; i++)
        v1.m_vec[i] *= val;
    return v1;
}

template<typename _T>
m_vector<_T> operator-(const m_vector<_T> &v1, const m_vector<_T> &v2)
{
    THROW_BAD_VEC_IF(v1.amount == 0);
    THROW_BAD_VEC_IF(v2.amount == 0);
    m_vector<_T> local(std::max(v1.amount, v2.amount));
    for(int i = 0; i < local.amount; i++)
        local[i] = ((i < v1.amount) ? v1.m_vec[i] : 0) - ((i < v2.amount) ? v2.m_vec[i] : 0);
    return local;
}

template<typename _T>
m_vector<_T> operator+(const m_vector<_T>& v1, const m_vector<_T>&v2)
{
    THROW_BAD_VEC_IF(v1.amount == 0);
    THROW_BAD_VEC_IF(v2.amount == 0);
    m_vector<_T> local(v1.amount + v2.amount);
    for(int i = 0; i < v1.amount; i++)
        local[i] = v1.m_vec[i];
    for(int i = 0; i < v2.amount; i++)
        local[v1.amount+i] = v2.m_vec[i];
    return local;
}

template<typename Type>
m_vector<Type>& m_vector<Type>::operator /=(const Type &val)
{
    THROW_BAD_VEC_IF(amount == 0);
    if(val == 0)
        throw m_vectorException("devide to zero");
    for(int i = 0; i < amount; i++)
        m_vec[i] /= val;
    return *this;
}

template<typename Type>
m_vector<Type>& m_vector<Type>::operator *=(const Type& val)
{
    THROW_BAD_VEC_IF(amount == 0);
    for(int i = 0; i < amount; i++)
        m_vec[i] *= val;
    return *this;
}

template<typename Type>
m_vector<Type>& m_vector<Type>::operator -=(const m_vector<Type>& vect)
{
    THROW_BAD_VEC_IF(vect.amount == 0);
    m_vector<Type> local = *this;
    amount = std::max(local.amount, vect.amount);
    m_vec = new Type[amount]{};
    for(int i = 0; i < amount; i++)
        m_vec[i] = ((i < local.amount) ? local.m_vec[i] : 0) - ((i < vect.amount) ? vect.m_vec[i] : 0);
    return *this;
}

template<typename Type>
m_vector<Type> &m_vector<Type>::operator+=(const m_vector<Type> &vect)
{
    THROW_BAD_VEC_IF(vect.amount == 0);
    m_vector<Type> local = *this;
    amount = local.amount + vect.amount;
    m_vec = new Type[amount]{};
    for(int i = 0; i < local.amount; i++)
        m_vec[i] = local.m_vec[i];
    for(int i = 0; i < vect.amount; i++)
        m_vec[local.amount+i] = vect.m_vec[i];
    return *this;
}

template<typename Type>
std::ostream &operator<<(std::ostream& os, const m_vector<Type> &lst)
{
    std::string container = "m_vector{amount: " + std::to_string(lst.amount) + ", list: [";
    for(int i = 0; i < lst.amount; i++)
        container += std::to_string(lst.m_vec[i]) + ", ";
    container = container.substr(0, container.size()-2); // Удалить два лишних ", "
    container += "]}";
    return os << container;
}

template<typename Type>
Type *m_vector<Type>::to_array()
{
    THROW_BAD_VEC_IF(amount == 0);
    Type array[amount];
    for(int i =0; i < amount; i++)
        array[i] = m_vec[i];
    return array;
}

template<typename Type>
Type &m_vector<Type>::get_elem(int index)
{
    THROW_BAD_VEC_IF(amount == 0);
    if(index < 0 || amount < index)
        throw m_vectorException("Wrong index of m_vector");
    return m_vec[index];
}

template<typename Type>
void m_vector<Type>::set_elem(int index, const Type &elem)
{
    THROW_BAD_VEC_IF(amount == 0);
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
m_vector<Type>::m_vector(int length)
{
    if(length <= 0)
        throw m_vectorException("Bad length of m_vector");
    amount = length;
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
    THROW_BAD_VEC_IF(amount == 0);
    if(index < 0 || amount < index)
        throw m_vectorException("Wrong index of m_vector");
    return *(m_vec + index);
}

#endif // M_VECTOR_H
