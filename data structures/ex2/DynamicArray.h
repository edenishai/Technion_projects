//
// Created by ASUS on 09/06/2021.
//

#ifndef DATA_STRUCT_1_HW_1_DYNAMICARRAY_H
#define DATA_STRUCT_1_HW_1_DYNAMICARRAY_H

template<class T>
class DynamicArray {

private:
    T **arr;
    int count;
    int size;

public:
    DynamicArray();

    void add(T *data = nullptr);

    void growSize();

    void shrinkSize();

    T &operator[](int index);

    const T &operator[](int index) const;

    ~DynamicArray();
};

template<class T>
DynamicArray<T>::DynamicArray()
{
    arr = new T*[1];
    count = 0;
    size = 1;
}

template<class T>
void DynamicArray<T>::add(T *data)
{
    if (count == size) {
        growSize(); // make array size double
    }
    arr[count] = data;
    count++;
}

template<class T>
void DynamicArray<T>::growSize()
{
    T **temp = nullptr;
    if (count == size) {
        temp = new T *[size * 2];
        {
            for (int i = 0; i < size; i++) {

                temp[i] = arr[i];
            }
        }
    }
    size = size * 2;
    delete[] arr;
    arr = temp;
}

template<class T>
void DynamicArray<T>::shrinkSize()
{
    T *temp = nullptr;
    if (count > 0) {
        temp = new T *[count];
        for (int i = 0; i < count; i++) {
            temp[i] = arr[i];
        }

        size = count;
        delete[] arr;
        arr = temp;
    }
}

template<class T>
T &DynamicArray<T>::operator[](int index)
{
    return *arr[index];
}

template<class T>
const T &DynamicArray<T>::operator[](int index) const
{
    if (index > count)
        return nullptr;
    else {
        return *arr[index];
    }
}

template<class T>
DynamicArray<T>::~DynamicArray()
{
    for (int i = 0; i < count; ++i) {
        delete arr[i];
    }
    delete []arr;
}

#endif //DATA_STRUCT_1_HW_1_DYNAMICARRAY_H
