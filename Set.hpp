#ifndef _L_SET
#define _L_SET

template <class T> class Set {
protected:
    T cont[8];
    unsigned char size;
public:
    Set()
    {
        size = 0;
    }

    void add(T val);
    bool in(T val);
    bool del(T val);
    Set &operator = (const Set &right)
    {
        if (this == &right)
            return *this;
        size = right.size;
        for (int i=0; i<size; i++)
            cont[i] = right.cont[i];
        return *this;
    }
};

template <class T> void Set<T>::add(T val)
{
    bool flag = true;
    for (int i=0; i<size; i++)
        if (cont[i] == val) flag = false;
    if (flag) {
        cont[size] = val;
        size++;
    }
}

template <class T> bool Set<T>::in(T val)
{
    bool flag = false;
    for (int i=0; i<size; i++)
        if (cont[i] == val) flag = true;
    return flag;
}

template <class T> bool Set<T>::del(T val)
{
    for (int i=0; i<size; i++)
        if (cont[i] == val) {
            for (int j = i; j<size; j++) cont[j] = cont [j+1];
            size--;
            return true;
        }
    return false;
}

#endif
