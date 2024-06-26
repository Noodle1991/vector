#pragma  once

#include <iostream>
#include "array_bundle.h"

namespace bmstu {

    template<typename Type>
    /* bmstu_vektor vs vector */
    /* лечим расстройство личности плиз */
    class dummy_vector {
    public:
        struct iterator {
            using value_type = Type;
            using pointer = Type *;
            using reference = Type &;
            using iterator_category = std::random_access_iterator_tag;
            using difference_type = std::ptrdiff_t;

            iterator(pointer ptr) : m_ptr(ptr) {

            }

            reference operator*() const {
                return *m_ptr;
            }

            pointer operator->() {
                return m_ptr;
            }

            iterator &operator++() {
                ++m_ptr;
                return *this;
            }

            iterator &operator--() {
                --m_ptr;
                return *this;
            }

            iterator &operator=(const iterator &other) {
                this->m_ptr = other.m_ptr;
                return *this;
            }

            iterator operator++(int) {
                iterator tmp = *this;
                ++(*this);
                return tmp;
            }

            iterator operator--(int) {
                iterator tmp = *this;
                --(*this);
                return tmp;
            }

            friend bool operator==(const iterator &a, const iterator &b) {
                return a.m_ptr == b.m_ptr;
            }

            friend bool operator!=(const iterator &a, const iterator &b) {
                return !(a == b);
            }

            friend ptrdiff_t operator-(const iterator &a, const iterator &b) {
                return a.m_ptr - b.m_ptr;
            }

            iterator &operator+(size_t n) noexcept {
                m_ptr = m_ptr + n;
                return *this;
            }

            iterator &operator-(size_t n) noexcept {
                m_ptr = m_ptr - n;
                return *this;
            }

        private:
            pointer m_ptr;
        };

        using const_iterator = const iterator;

        dummy_vector() noexcept = default;

        dummy_vector(size_t size, const Type &value = Type{}) :
                size_(size), capacity_(size), data_(size) {
            auto first = begin();
            auto last = end();
            for (; first != last; ++first) {
                *first = value;
            }
        }

        dummy_vector(const dummy_vector<Type> &other) : size_(other.size()), capacity_(other.capacity()), data_(size_) {
            std::copy(other.begin(), other.end(), begin());
        }

        dummy_vector(dummy_vector<Type> &&other) noexcept {
            this->swap(other);

        }

        dummy_vector(std::initializer_list<Type> ilist) : size_(ilist.size()), capacity_(ilist.size()), data_(ilist.size()) {
            std::copy(ilist.begin(), ilist.end(), begin());
        }

        void clear() noexcept {
            size_ = 0;
        }

        dummy_vector &operator=(const dummy_vector<Type> &other) {
            if (this != &other) {
                if (other.empty()) {
                    clear();
                } else {
                    auto copy(other);
                    this->swap(copy);
                }
            }
            return *this;
        }

        dummy_vector &operator=(const dummy_vector<Type> &&other) {
            if (this != &other) {
                if (other.empty()) {
                    clear();
                } else {
                    auto copy(std::move(other));
                    this->swap(copy);
                }
            }
            return *this;
        }

        iterator begin() noexcept {
            return data_.Get();
        }

        iterator end() noexcept {
            return data_.Get() + size_;
        }

        const_iterator begin() const noexcept {
            return data_.Get();
        }

        const_iterator end() const noexcept {
            return data_.Get() + size_;
        }

        const_iterator cbegin() const noexcept {
            return data_.Get();
        }

        const_iterator cend() const noexcept {
            return data_.Get() + size_;
        }

        typename iterator::reference operator[](size_t index) noexcept {
            return data_[index];
        }

        typename const_iterator::reference operator[](size_t index) const noexcept {
            return data_.Get()[index];
        }

        typename iterator::reference at(size_t index) {
            if (index > size_) {
                throw std::out_of_range("Invalid index");
            } else {
                return data_[index];
            }
        }

        typename const_iterator::reference at(size_t index) const {
            if (index > size_) {
                throw std::out_of_range("Invalid index");
            } else {
                return const_cast <typename const_iterator::value_type>(data_[index]);
            }

        }

        size_t size() const noexcept {
            return size_;
        }

        size_t capacity() const noexcept {
            return capacity_;
        }

        bool empty() const noexcept {
            return (size_ == 0);
        }

        void swap(dummy_vector &other) noexcept {
            std::swap(size_, other.size_);
            std::swap(capacity_, other.capacity_);
            data_.swap(other.data_);
        }

        friend void swap(dummy_vector<Type> &lhs, dummy_vector<Type> &rhs) {
            lhs.swap(rhs);
        }

        void resize(size_t new_size) {
            if (new_size > capacity_) {
                size_t new_capacity = std::max(new_size, capacity_ * 2);
                reserve(new_capacity);
                size_ = new_size;
            } else if (new_size < capacity_) {
                size_t new_capacity = std::min(new_size, capacity_ * 2);
                reserve(new_capacity);
                size_ = new_size;
            } else {
                std::fill(end(), begin() + new_size, Type{});
                size_ = new_size;
            }
        }

        void reserve(size_t new_capacity) {
            array_bundle<Type> tmp(new_capacity);
            auto first = begin();
            auto last = end();
            auto tmp_ptr = tmp.Get();
            for (; first != last; ++first, ++tmp_ptr) {
                *tmp_ptr = std::move(*first);
            }
            data_.swap(tmp);
            capacity_ = new_capacity;
            if (capacity_ < size_) size_ = capacity_;
        }

        iterator insert(const_iterator pos, Type &&value) {
            size_t n = pos - begin();
            if (capacity_ == 0) {
                reserve(1);
            }
            if (size_ == capacity_) {
                capacity_ *= 2;
            }
            array_bundle<Type> temp(capacity_);
            Type *temp_ptr = temp.Get();
            for (auto first = begin(); first != begin() + n; ++first, ++temp_ptr) {
                *temp_ptr = std::move(*first);
            }
            temp_ptr = nullptr;
            temp.Get()[n] = std::move(value);
            temp_ptr = temp.Get() + n + 1;
            for (auto first = begin() + n; first != end(); ++first, ++temp_ptr) {
                *temp_ptr = std::move(*first);
            }
            data_.swap(temp);
            size_++;
            return begin() + n;
        }

        iterator insert(const_iterator pos, const Type &value) {
            Type copy = value;
            return insert(pos, std::move(copy));
        }

        void push_back(const Type &value) {
            Type tmp = value;
            push_back(tmp);
        }

        void push_back(Type &&value) {
            insert(end(), std::move(value));
        }

        void pop_back() noexcept {
            if (!empty()) {
                --size_;
            }
        }

        friend bool operator==(const dummy_vector<Type> &l, const dummy_vector<Type> &r) {
            if (l.size_ == r.size_) {
                for (auto fl = l.begin(), fr = r.begin(); fl != l.end(); ++fl, ++fr) {
                    if (*fl != *fr) {
                        return false;
                    }
                }
                return true;
            }
            return false;
        }

        friend bool operator!=(const dummy_vector<Type> &l, const dummy_vector<Type> &r) {
            return not (l == r);
        }

        friend bool operator<(const dummy_vector<Type> &l, const dummy_vector<Type> &r) {
            return lexicographical_compare_(l, r);
        }

        friend bool operator>(const dummy_vector<Type> &l, const dummy_vector<Type> &r) {
            return (r < l);
        }

        friend bool operator<=(const dummy_vector<Type> &l, const dummy_vector<Type> &r) {
            return not (r < l);
        }

        friend bool operator>=(const dummy_vector<Type> &l, const dummy_vector<Type> &r) {
            return not (l < r);
        }

        friend std::ostream &operator<<(std::ostream &os, const dummy_vector<Type> &other) {
            os << "[";
            for (int i = 0; i < other.size_ - 1; ++i) {
                os << other[i] << ", ";
            }
            os << other[other.size_ - 1];
            os << "]";
            return os;
        }


    private:
        static bool lexicographical_compare_(const dummy_vector<Type> &l, const dummy_vector<Type> &r) {
            auto lf = l.begin(), rf = r.begin();
            for (size_t i = 0; (lf != l.end()) && (rf != r.end()); ++lf, ++rf, ++i) {
                if (*lf < *rf) {
                    return true;
                }
                if (*rf < *lf) {
                    return false;
                }
            }
            return (rf != r.end()) && (lf == l.end());
        }

        size_t size_ = 0;
        size_t capacity_ = 0;
        array_bundle<Type> data_;
    };
}
