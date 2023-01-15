#ifndef ARRAY_H_
#define ARRAY_H_

#include <vector>
#include <memory>
#include <iostream>
#include <iterator>
#include "Exception.h"

namespace lib {
template <typename T>
class Array{
private:
    static constexpr size_t BLOCK_SIZE = 10;
    std::vector<std::unique_ptr<T[]>> data_;
    size_t block_size_;
    size_t element_count_;
    void alloc_block();
    inline const T& get(size_t index) const;
public:
    Array(size_t block_size = BLOCK_SIZE);
    Array(const Array<T>& array);
    Array(Array<T>&& array) noexcept;
    ~Array() = default;
    class iterator;
    void push_back(const T& item);
    void push_back(T&& item);
    void pop_back();
    inline size_t size() const { return element_count_; }
    void print(std::ostream& os = std::cout) const;
    T& at(size_t index) const;
    //const T& at(size_t index) const;
    T& operator[](size_t index) const;
    //const T operator[](size_t index) const;
    Array<T>& operator=(const Array<T>& array); // copy assignment
    Array<T>& operator=(Array<T>&& array) noexcept; // move assignment
    iterator begin() const;
    iterator end() const;
};

template <typename T>
class Array<T>::iterator {
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    const Array<T>* array_;
    size_t position_;
public:
    iterator(Array<T>* array, size_t position);
    iterator(const Array<T>* array, size_t position);
    bool operator==(const iterator& other) const;
    bool operator!=(const iterator& other) const;
    iterator& operator++();
    iterator operator++(int);
    iterator& operator--();
    iterator operator--(int);
    iterator operator+(const difference_type& movement) const;
    iterator operator-(const difference_type& movement) const;
    reference operator*() const;
    pointer operator->() const;
};

template<typename T>
Array<T>::iterator::iterator(Array<T>* array, size_t position){
    array_ = array;
    position_ = position;
};
template<typename T>
Array<T>::iterator::iterator(const Array<T>* array, size_t position) {
    array_ = array;
    position_ = position;
};
template<typename T>
bool Array<T>::iterator::operator==(const iterator& other) const{
    return position_ == other.position_;
};

template<typename T>
bool Array<T>::iterator::operator!=(const iterator& other) const {
    return position_ != other.position_;
};

template<typename T>
typename Array<T>::iterator& Array<T>::iterator::operator++(){
    ++position_;
    return *this;
};

template<typename T>
typename Array<T>::iterator Array<T>::iterator::operator++(int){
    auto ret = *this;
    ++position_;
    return ret;
};

template<typename T>
typename Array<T>::iterator& Array<T>::iterator::operator--(){
    --position_;
    return *this;
};

template<typename T>
typename Array<T>::iterator Array<T>::iterator::operator--(int){
    auto ret = *this;
    --position_;
    return ret;
};

template<typename T>
typename Array<T>::iterator Array<T>::iterator::operator+(const difference_type& movement) const{
    return iterator(this->array_, this->position_ + movement);
};

template<typename T>
typename Array<T>::iterator Array<T>::iterator::operator-(const difference_type& movement) const{
    return iterator(this->array_, this->position_ - movement);
};

template<typename T>
typename Array<T>::iterator::reference Array<T>::iterator::operator*() const{
    return array_->data_[position_ / array_->block_size_ ][position_ % array_->block_size_];
};

template<typename T>
typename Array<T>::iterator::pointer Array<T>::iterator::operator->() const{
    return &array_->data_[position_ / array_->block_size_][position_ % array_->block_size_];
};

template <typename T>
Array<T>::Array(size_t block_size) : block_size_(block_size), element_count_(0){
};

template <typename T>
Array<T>::Array(const Array<T>& array) : block_size_(array.block_size_), element_count_(0){
    //std::cout << "Copy ctor" << std::endl;
    for (size_t i = 0; i < array.data_.size(); ++i){
        alloc_block();
    }
    for (size_t i = 0; i < array.element_count_; ++i){
        data_[i / block_size_][i % block_size_] = array.data_[i / block_size_][i % block_size_]; 
    }
};

template <typename T>
Array<T>::Array(Array<T>&& array) noexcept : block_size_(BLOCK_SIZE), element_count_(0){
    //std::cout << "Move ctor" << std::endl;
    std::swap(block_size_, array.block_size_);
    std::swap(element_count_, array.element_count_);
    std::swap(data_, array.data_);
};

template <typename T>
void Array<T>::alloc_block(){
    //auto block = std::unique_ptr<T[]>(new T[block_size_]);
    //data_.push_back(std::move(block));
    try
    {
        data_.push_back(std::make_unique<T[]>(block_size_));
    }
    catch(const std::bad_alloc&)
    {
        throw UnavailableMemoryException("Not enough memory");
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
    if (element_count_ == 0)
        throw EmptyArrayException("Array empty");
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
const T& Array<T>::get(size_t index) const {
    return data_[index / block_size_][index % block_size_];
};

template<typename T>
T& Array<T>::at(size_t index) const {
    if (index >= element_count_)
        throw OutOfRangeException("Index out of range");
    return const_cast<T&>(get(index));
};

//template<typename T>
//const T& Array<T>::at(size_t index) const {
//    if (index >= element_count_)
//        throw OutOfRangeException("Index out of range");
//    return get(index);
//};

template<typename T>
T& Array<T>::operator[](size_t index) const{
    if (index >= element_count_)
        throw OutOfRangeException("Index out of range");
    return const_cast<T&>(get(index));
};

//template<typename T>
//const T Array<T>::operator[](size_t index) const{
//    if (index >= element_count_)
//        throw OutOfRangeException("Index out of range");
//    return get(index);
//};

template<typename T>
Array<T>& Array<T>::operator=(const Array<T>& array){
    // Copy assignment
    block_size_ = array.block_size_;
    for (size_t i = 0; i < element_count_; i++) {
        data_[i / block_size_][i % block_size_].~T(); 
    }
    if (element_count_ / block_size_ == array.element_count_ / block_size_){
        for (size_t i = 0; i < element_count_; i++) {
            data_[i / block_size_][i % block_size_] = array.data_[i / block_size_][i % block_size_]; 
        }
    }
    else {
        // Specify vectors
        data_.clear();
        for (size_t i = 0; i < array.element_count_; ++i){
            push_back(array.data_[i / block_size_][i % block_size_]); 
        }
    }
    element_count_ = array.element_count_;
    return *this;
}; 

template<typename T>
Array<T>& Array<T>::operator=(Array<T>&& array) noexcept{
    // Move assignment
    // vycistit this
    if (this != &array){
        std::swap(block_size_, array.block_size_);
        std::swap(element_count_, array.element_count_);
        std::swap(data_, array.data_);
    }
    return *this;
}; 

template<typename T>
typename Array<T>::iterator Array<T>::begin() const{
    if (element_count_ == 0)
        return iterator(this, element_count_ + 1);
    return iterator(this, 0);
};

template<typename T>
typename Array<T>::iterator Array<T>::end() const{
    if (element_count_ == 0)
        return iterator(this, element_count_ + 1);
    return iterator(this, element_count_);
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Array<T>& array){
    array.print(os);
    return os;
};
}
#endif