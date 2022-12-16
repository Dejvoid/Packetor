#ifndef ARRAY_H_
#define ARRAY_H_

#include <vector>
#include <memory>
#include <iostream>

template <typename T>
class Array{
private:
    static constexpr size_t BLOCK_SIZE = 10;
    std::vector<std::unique_ptr<T[]>> data_;
    const size_t block_size_;
    size_t element_count_ = 0;
    void alloc_block();
    inline const T& get(size_t index);
public:
    Array(size_t block_size = BLOCK_SIZE);
    void push_back(const T& item);
    void push_back(T&& item);
    void pop_back();
    inline size_t size() const { return element_count_; }
    void print(std::ostream& os = std::cout) const;
    T& at(size_t index);
    const T& at(size_t index) const;
    T& operator[](size_t index);
    const T operator[](size_t index) const;
};

//class Exception{
//    public: 
//        Exception(const std::string& text);
//        Exception(std::string&& text);
//};
//
//class OutOfRangeException : public Exception{
//    using Exception::Exception(const std::string& text);
//    using Exception::Exception(std::string&& text);
//};
//
//class EmptyArrayException : public Exception{
//    using Exception::Exception(const std::string& text);
//    using Exception::Exception(std::string&& text);
//};
//
//class UnavailableMemoryException{
//    using Exception::Exception(const std::string& text);
//    using Exception::Exception(std::string&& text);
//};

template <typename T>
Array<T>::Array(size_t block_size) : block_size_(block_size)
{
};

template <typename T>
void Array<T>::alloc_block(){
    //auto block = std::unique_ptr<T[]>(new T[block_size_]);
    //data_.push_back(std::move(block));
    try
    {
        data_.push_back(std::make_unique<T[]>(block_size_));
    }
    catch(const std::bad_alloc)
    {
        //throw UnavailableMemoryException;
    }
    
};

template<typename T>
void Array<T>::push_back(const T& item){
    if (element_count_ % block_size_ == 0){
        alloc_block();
    }
    data_[element_count_ / block_size_][element_count_ % block_size_] = item;
    ++element_count_;
};

template<typename T>
void Array<T>::push_back(T&& item){
    if (element_count_ % block_size_ == 0){
        alloc_block();
    }
    data_[element_count_ / block_size_][element_count_ % block_size_] = item;
    ++element_count_;
};

template<typename T>
void Array<T>::pop_back(){
    data_[element_count_ / block_size_][element_count_ % block_size_].~T();
    --element_count_;
    if (element_count_ % block_size_ == 0){
        data_.pop_back();
    }
};

template<typename T>
void Array<T>::print(std::ostream& os) const{
    os << "[";
    for (size_t i = 0; i < element_count_; i++){
        os << data_[i / block_size_][i % block_size_];
        if (i != element_count_ - 1)
            os << ", ";
    }
    os << "]";
};

template<typename T>
const T& Array<T>::get(size_t index){
    return data_[index / block_size_][index % block_size_];
};

template<typename T>
T& Array<T>::at(size_t index) {
    return const_cast<T>(get(index));
};

template<typename T>
const T& Array<T>::at(size_t index) const {
    return get(index);
};

template<typename T>
T& Array<T>::operator[](size_t index){
    return const_cast<T>(get(index));
};

template<typename T>
const T Array<T>::operator[](size_t index) const{
    return get(index);
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Array<T>& array){
    array.print(os);
    return os;
};

#endif