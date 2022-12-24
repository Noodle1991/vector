#include <gtest/gtest.h>
#include <string>
#include "bmstu_vektor.h"
#include <algorithm>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <list>
#include <numeric>
#include <random>
#include <vector>

/* что это ?
TEST(GoogleTestCi, Foo) {
    ASSERT_TRUE(true);
}

TEST(ExampleTest, DmitriiLeonidovich) {
    std::string dml = "DmitriiLeonidovich";
    const char *dml_c = "DmitriiLeonidovich";
    ASSERT_STREQ(dml.c_str(), dml_c);
}
*/
TEST(Vector, exact_symbol) {
    bmstu::dummy_vector<char> vektor{'B', 'A', 'N', 'A', 'N'};
    ASSERT_EQ(vektor[4], 'N');
    ASSERT_EQ(vektor[0], 'B');
}

TEST(Vector, resize_char) {
    bmstu::dummy_vector<char> vektor{'B', 'A', 'N', 'A', 'N'};
    vektor.resize(3);
    ASSERT_EQ(vektor.size(), 3);
    ASSERT_EQ(vektor.capacity(), 3);
}

TEST(Vector, resize_int) {
    bmstu::dummy_vector<int> vektor{1, 2, 3};
    vektor.resize(8);
    ASSERT_EQ(vektor.size(), 8);
    ASSERT_EQ(vektor.capacity(), 8);
}

TEST(Vector, swap) {
    bmstu::dummy_vector<char> vektor{'B', 'A', 'N', 'A', 'N'};
    bmstu::dummy_vector<char> vektor2{'C', 'O', 'O', 'K', 'I', 'E'};
    vektor.swap(vektor2);
    ASSERT_EQ(vektor.size(), 6);
}

TEST(Vector, reserve) {
    bmstu::dummy_vector<char> vektor{'B', 'A', 'N', 'A', 'N'};
    vektor.reserve(2);
    bmstu::dummy_vector<char> vektor2{'B', 'A'};
    ASSERT_EQ(vektor.size(), 2);
    ASSERT_EQ(vektor.capacity(), 2);
    ASSERT_EQ(vektor, vektor2);
}

TEST(Vector, reserve_more) {
    bmstu::dummy_vector<char> vektor{'B', 'A', 'N', 'A', 'N'};
    vektor.reserve(6);
    ASSERT_EQ(vektor.size(), 5);
    ASSERT_EQ(vektor.capacity(), 6);
}

TEST(Vector, iterator) {
    bmstu::dummy_vector<char> vektor{'B', 'A', 'N', 'A', 'N'};
    ASSERT_EQ(*(vektor.begin()), 'B');
    ASSERT_EQ(*(vektor.end() - 1), 'N');
    ASSERT_EQ(*(vektor.begin() + 2), *(vektor.end() - 3));
}

TEST(Vector, symbol_input) {
    bmstu::dummy_vector<char> vektor{'B', 'A', 'N', 'A', 'N'};
    vektor.insert(vektor.begin(), 'X');
    std::stringstream ss;
    ss << vektor;
    ASSERT_STREQ(ss.str().c_str(), "[X, B, A, N, A, N]");
    ASSERT_EQ(vektor.size(), 6);
}

TEST(Vector, symbol_back) {
    bmstu::dummy_vector<char> vektor{'B', 'A', 'N', 'A', 'N'};
    vektor.push_back('A');
    std::stringstream ss;
    ss << vektor;
    ASSERT_EQ(vektor.size(), 6);
    ASSERT_STREQ(ss.str().c_str(), "[B, A, N, A, N, A]");
}

TEST(Vector, operator_equal_char) {
    bmstu::dummy_vector<char> vektor{'B', 'A', 'N', 'A', 'N'};
    bmstu::dummy_vector<char> vektor2{'B', 'A', 'N', 'A', 'N'};
    ASSERT_EQ(vektor == vektor2, 1);
}

TEST(Vector, operator_equal_int) {
    bmstu::dummy_vector<int> vektor{1, 2};
    bmstu::dummy_vector<int> vektor2{1, 2};
    ASSERT_EQ(vektor == vektor2, 1);
}

TEST(Vector, operator_not_equal) {
    bmstu::dummy_vector<char> vektor{'B', 'A', 'N', 'A', 'N'};
    bmstu::dummy_vector<char> vektor2{'B', 'A', 'N', 'A', 'N', 'A'};
    ASSERT_EQ(vektor != vektor2, 1);
}

TEST(Vector, operator_more_not_equal) {
    bmstu::dummy_vector<char> vektor{'B', 'A', 'N', 'A', 'N'};
    bmstu::dummy_vector<char> vektor2{'B', 'A', 'N', 'A', 'N', 'X', 'X', 'X'};
    ASSERT_EQ(vektor != vektor2, 1);
}

TEST(Vector, operator_not_equal_int) {
    bmstu::dummy_vector<int> vektor{1, 2, 3};
    bmstu::dummy_vector<int> vektor2{1, 2};
    ASSERT_EQ(vektor != vektor2, 1);
}

TEST(Vector, operator_less) {
    bmstu::dummy_vector<char> vektor{'B', 'A', 'N', 'A', 'N'};
    bmstu::dummy_vector<char> vektor2{'B', 'A', 'N', 'A', 'O'};
    ASSERT_TRUE(vektor < vektor2);
}

TEST(Vector, operator_more) {
    bmstu::dummy_vector<char> vektor{'B', 'A', 'N', 'A', 'N'};
    bmstu::dummy_vector<char> vektor2{'B', 'A', 'N', 'A', 'M'};
    ASSERT_TRUE(vektor > vektor2);
}

TEST(Vector, operator_bigger) {
    bmstu::dummy_vector<char> vektor{'B', 'A', 'N', 'A', 'N', 'Q'};
    bmstu::dummy_vector<char> vektor2{'B', 'A', 'N', 'A', 'N'};
    ASSERT_TRUE(vektor > vektor2);
}

TEST(Vector, operator_less_size) {
    bmstu::dummy_vector<char> vektor{'B', 'A', 'N', 'A', 'N'};
    bmstu::dummy_vector<char> vektor2{'B', 'A', 'N', 'A', 'N', 'Q'};
    ASSERT_TRUE(vektor < vektor2);
}

TEST(Vector, operator_much_less_size) {
    bmstu::dummy_vector<char> vektor{'B', 'A', 'N', 'A', 'N'};
    bmstu::dummy_vector<char> vektor2{'B', 'A', 'N', 'A', 'N', 'X', 'X', 'X'};
    ASSERT_TRUE(vektor < vektor2);
}

TEST(Vector, operator_not_more) {
    bmstu::dummy_vector<char> vektor{'B', 'A', 'N', 'A', 'N'};
    bmstu::dummy_vector<char> vektor2{'B', 'A', 'N', 'A', 'N'};
    ASSERT_TRUE(vektor >= vektor2);
}

TEST(Vector, operator_not_less) {
    bmstu::dummy_vector<char> vektor{'B', 'A', 'N', 'A', 'N'};
    bmstu::dummy_vector<char> vektor2{'B', 'A', 'N', 'A', 'N'};
    ASSERT_TRUE(vektor <= vektor2);
}

TEST(Vector, operator_much_bigger) {
    bmstu::dummy_vector<char> vektor{'B', 'A', 'N', 'A', 'N', 'X', 'X', 'X'};
    bmstu::dummy_vector<char> vektor2{'B', 'A', 'N', 'A', 'N'};
    ASSERT_TRUE(vektor > vektor2);
}

TEST(Vector, empty) {
    bmstu::dummy_vector<char> vektor{'B', 'A', 'N', 'A', 'N'};
    vektor = vektor.empty();
    ASSERT_EQ(vektor, 0);
}

TEST(DummyVector, Test) {
    std::vector<std::reference_wrapper<int>> a;
    bmstu::dummy_vector<int> vec({1, 2, 3, 4, 5});
    vec.push_back(2);
    vec.push_back(3);
}

TEST(DummyVector, one) {
    bmstu::dummy_vector<int> v;
    ASSERT_EQ(v.size(), 0u);
    ASSERT_TRUE(v.empty());
    ASSERT_EQ(v.capacity(), 0u);
}
//
//
TEST(DummyVector, Init) {
    // Инициализация вектора указанного размера
    bmstu::dummy_vector<int> v(5);
    ASSERT_EQ(v.size(), 5u);
    ASSERT_EQ(v.capacity(), 5u);
    ASSERT_TRUE(!v.empty());
    for (size_t i = 0; i < v.size(); ++i) {
        ASSERT_EQ(v[i], 0);
    }
}

TEST(DummyVector, Init2) {
    bmstu::dummy_vector<int> v(3, 42);
    ASSERT_EQ(v.size(), 3);
    ASSERT_EQ(v.capacity(), 3);
    for (size_t i = 0; i < v.size(); ++i) {
        ASSERT_EQ(v[i], 42);
    }
}
//
TEST(DummyVector, InitList) {
    bmstu::dummy_vector<int> v{1, 2, 3};
    ASSERT_EQ(v.size(), 3);
    ASSERT_EQ(v.capacity(), 3);
    ASSERT_EQ(v[2], 3);
}
//
TEST(DummyVector, At) {
    bmstu::dummy_vector<int> v(3);
    ASSERT_EQ(&v.at(2), &v[2]);
    try {
        v.at(3);
    } catch (std::out_of_range const &err) {
        EXPECT_EQ(err.what(), std::string("Invalid index"));
    }
}
//
TEST(DummyVector, Clear) {

    bmstu::dummy_vector<int> v(10);
    const size_t old_capacity = v.capacity();
    v.clear();
    ASSERT_EQ(v.size(), 0);
    ASSERT_EQ(v.capacity(), old_capacity);
}
//
TEST(DummyVector, Resize) {
    // Изменение размера
    {
        bmstu::dummy_vector<int> v(3);
        v[2] = 17;
        v.resize(7);
        ASSERT_EQ(v.size(), 7);
        ASSERT_TRUE(v.capacity() >= v.size());
        ASSERT_EQ(v[2], 17);
        ASSERT_EQ(v[3], 0);
    }
}
//
TEST(DummyVector, Resize1) {
    {
        bmstu::dummy_vector<int> v(3);
        v[0] = 42;
        v[1] = 55;
        const size_t old_capacity = v.capacity();
        v.resize(2);
        ASSERT_EQ(v.size(), 2);
        ASSERT_EQ(v.capacity(), old_capacity);
        ASSERT_EQ(v[0], 42);
        ASSERT_EQ(v[1], 55);
    }
}
//
TEST(DummyVector, Resize2) {

    const size_t old_size = 3;
    bmstu::dummy_vector<int> v(3);
    v.resize(old_size + 5);
    v[3] = 42;
    v.resize(old_size);
    ASSERT_EQ(v[2], 0);
    v.resize(old_size + 3);
    ASSERT_EQ(v[3], 0);
}
//
TEST(DummyVector, Constructors) {
    {

        bmstu::dummy_vector<int> v(5);
        v[0] = 1;
        v[1] = 2;
        v[2] = 3;
        v[3] = 4;
        v[4] = 5;
        bmstu::dummy_vector<int> c(v);
        ASSERT_EQ(v[2], v[2]);
    }
    {

        bmstu::dummy_vector<int> v(5);
        v[0] = 1;
        v[1] = 2;
        v[2] = 3;
        v[3] = 4;
        v[4] = 5;
        bmstu::dummy_vector<int> c(v);
        ASSERT_EQ(v[2], v[2]);
    }
    {

        bmstu::dummy_vector<int> v(1);
        v.push_back(1);
        ASSERT_EQ(v[0], 0);
        ASSERT_EQ(*(v.begin()) + 1, 1);
    }
}

TEST(DummyVector, Push) {
    bmstu::dummy_vector<int> v(1);
    v.push_back(42);
    ASSERT_EQ(v.size(), 2);
    ASSERT_TRUE(v.capacity() >= v.size());
    ASSERT_EQ(v[0], 0);
    ASSERT_EQ(v[1], 42);
}

TEST(DummyVector, CopyConstruct)
// Конструктор копирования
{
    bmstu::dummy_vector<int> numbers{1, 2};
    auto numbers_copy(numbers);
    ASSERT_TRUE(&numbers_copy[0] != &numbers[0]);
    ASSERT_EQ(numbers_copy.size(), numbers.size());
    for (size_t i = 0; i < numbers.size(); ++i) {
        ASSERT_EQ(numbers_copy[i], numbers[i]);
        ASSERT_TRUE(&numbers_copy[i] != &numbers[i]);
    }
}

TEST(DummyVector, PopBack) {
    // PopBack
    {
        bmstu::dummy_vector<int> v{0, 1, 2, 3};
        const size_t old_capacity = v.capacity();
        const auto old_begin = v.begin();
        v.pop_back();
        ASSERT_EQ(v.capacity(), old_capacity);
        ASSERT_EQ(v.begin(), old_begin);
        ASSERT_EQ(v, (bmstu::dummy_vector<int>{0, 1, 2}));
    }
}

TEST(DummyVector, Capacity) {

    bmstu::dummy_vector<int> v(2);
    v.resize(1);
    const size_t old_capacity = v.capacity();
    v.push_back(123);
    ASSERT_EQ(v.size(), 2);
    ASSERT_EQ(v.capacity(), old_capacity);
}

TEST(DummyVector, Iterate) {
    // Итерирование по bmstu::dummy_vector
    {
        // Пустой вектор
        {
            bmstu::dummy_vector<int> v;
            ASSERT_EQ(v.begin(), nullptr);
            ASSERT_EQ(v.end(), nullptr);
        }

        // Непустой вектор
        {
            bmstu::dummy_vector<int> v(10, 42);
//            ASSERT_TRUE(v.begin());
            ASSERT_EQ(*v.begin(), 42);
            ASSERT_EQ(v.end(), v.begin() + v.size());
        }
    }
}

TEST(DummyVector, Compare) {
    {
        ASSERT_TRUE((bmstu::dummy_vector{1, 2, 3} == bmstu::dummy_vector{1, 2, 3}));
        ASSERT_TRUE((bmstu::dummy_vector{1, 2, 3} != bmstu::dummy_vector{1, 2, 2}));

        ASSERT_TRUE((bmstu::dummy_vector{1, 2, 3} < bmstu::dummy_vector{1, 2, 3, 1}));
        ASSERT_TRUE((bmstu::dummy_vector{1, 2, 3} > bmstu::dummy_vector{1, 2, 2, 1}));

        ASSERT_TRUE((bmstu::dummy_vector{1, 2, 3} >= bmstu::dummy_vector{1, 2, 3}));
        ASSERT_TRUE((bmstu::dummy_vector{1, 2, 4} >= bmstu::dummy_vector{1, 2, 3}));
        ASSERT_TRUE((bmstu::dummy_vector{1, 2, 3} <= bmstu::dummy_vector{1, 2, 3}));
        ASSERT_TRUE((bmstu::dummy_vector{1, 2, 3} <= bmstu::dummy_vector{1, 2, 4}));
    }
}

TEST(DummyVector, Pushback2) {
    bmstu::dummy_vector<int> v2;
    v2.push_back(0);
    v2.push_back(1);
    v2.push_back(2);
    ASSERT_EQ(v2, (bmstu::dummy_vector<int>{0, 1, 2}));
}

TEST(DummyVector, Swap) {
    // Обмен значений векторов
    {
        bmstu::dummy_vector<int> v1{42, 666};
        bmstu::dummy_vector<int> v2;
        v2.push_back(0);
        v2.push_back(1);
        v2.push_back(2);
        const int *const begin1 = &v1[0];
        const int *const begin2 = &v2[0];

        const size_t capacity1 = v1.capacity();
        const size_t capacity2 = v2.capacity();

        const size_t size1 = v1.size();
        const size_t size2 = v2.size();

        v1.swap(v2);
        ASSERT_TRUE(&v2[0] == begin1);
        ASSERT_TRUE(&v1[0] == begin2);
        ASSERT_TRUE(v1.size() == size2);
        ASSERT_TRUE(v2.size() == size1);
        ASSERT_TRUE(v1.capacity() == capacity2);
        ASSERT_TRUE(v2.capacity() == capacity1);
    }
}

TEST(DummyVector, Test1) {
    {
        bmstu::dummy_vector<int> src_vector{1, 2, 3, 4};
        bmstu::dummy_vector<int> dst_vector{1, 2, 3, 4, 5, 6};
        dst_vector = src_vector;
        ASSERT_EQ(dst_vector, src_vector);
    }
}

TEST(DummyVector, Insert) {
    // Вставка элементов
    {
        bmstu::dummy_vector<int> v{1, 2, 3, 4};
        auto vit = v.begin() + 3;
        v.insert(v.begin() + 2, 42);
        ASSERT_EQ(v, (bmstu::dummy_vector<int>{1, 2, 42, 3, 4}));
    }
}

TEST(DummyVector, Insert2) {
    // Вставка элементов

    bmstu::dummy_vector<int> v;
    v.insert(v.begin(), 42);
    ASSERT_EQ(v, (bmstu::dummy_vector<int>{42}));
}

/// реализовать метод erase .. можете посмотреть как он работает в std::vector
//TEST(DummyVector, Erase) {
//    {
//        bmstu::dummy_vector<int> v{1, 2, 3, 4};
//        v.erase(v.begin() + 2);
//
//        ASSERT_EQ(v, (bmstu::dummy_vector<int>{1, 2, 4}));
//    }
//}

TEST(DummyVector, Reserve) {

    {
        bmstu::dummy_vector<int> v(5);
        ASSERT_EQ(v.capacity(), 5);
        ASSERT_FALSE(v.empty());
    }

    {
        bmstu::dummy_vector<int> v;
        // зарезервируем 5 мест в векторе
        v.reserve(5);
        ASSERT_EQ(v.capacity(), 5);
        ASSERT_TRUE(v.empty());

        // попытаемся уменьшить capacity до 1
        v.reserve(1);
        // capacity должно остаться прежним
        ASSERT_EQ(v.capacity(), 5);
        // поместим 10 элементов в вектор
        for (int i = 0; i < 10; ++i) {
            v.push_back(i);
        }
        ASSERT_EQ(v.size(), 10);
        // увеличим capacity до 100
        v.reserve(100);
        // проверим, что размер не поменялся
        ASSERT_EQ(v.size(), 10);
        ASSERT_EQ(v.capacity(), 100);
        // проверим, что элементы на месте
        for (int i = 0; i < 10; ++i) {
            ASSERT_EQ(v[i], i);
        }
    }
}

class X {
public:
    X()
            : X(5) {
    }
    X(size_t num)
            : x_(num) {
    }
    X(const X &other) = delete;
    X &operator=(const X &other) = delete;
    X(X &&other) {
        x_ = std::exchange(other.x_, 0);
    }
    X &operator=(X &&other) {
        x_ = std::exchange(other.x_, 0);
        return *this;
    }
    size_t GetX() const {
        return x_;
    }

private:
    size_t x_;
};

bmstu::dummy_vector<int> GenerateVector(size_t size) {
    bmstu::dummy_vector<int> v(size);
    std::iota(v.begin(), v.end(), 1);
    return v;
}

TEST(DummyVector, temporary) {
    const size_t size = 1000000;
    bmstu::dummy_vector<int> moved_vector(GenerateVector(size));
    ASSERT_EQ(moved_vector.size(), size);

}

TEST(DummyVector, moveconstructor) {
    const size_t size = 1000000;

    bmstu::dummy_vector<int> vector_to_move(GenerateVector(size));
    ASSERT_EQ(vector_to_move.size(), size);

    bmstu::dummy_vector<int> moved_vector(std::move(vector_to_move));
    ASSERT_EQ(moved_vector.size(), size);
    ASSERT_EQ(vector_to_move.size(), 0);

}

TEST(DummyVector, moveoperator) {
    const size_t size = 1000000;
    bmstu::dummy_vector<int> vector_to_move(GenerateVector(size));
    ASSERT_EQ(vector_to_move.size(), size);

    bmstu::dummy_vector<int> moved_vector = std::move(vector_to_move);
    ASSERT_EQ(moved_vector.size(), size);
    ASSERT_EQ(vector_to_move.size(), 0);

}


TEST(DummyVector, noncopybable2) {
    const size_t size = 5;
    bmstu::dummy_vector<X> vector_to_move;
    for (size_t i = 0; i < size; ++i) {
        vector_to_move.push_back(X(i));
    }
    for (size_t i = 0; i < size; ++i) {
        ASSERT_EQ(vector_to_move[i].GetX(), i);
    }

    bmstu::dummy_vector<X> moved_vector = std::move(vector_to_move);
    ASSERT_EQ(moved_vector.size(), size);
    ASSERT_EQ(vector_to_move.size(), 0);

    for (size_t i = 0; i < size; ++i) {
        ASSERT_EQ(moved_vector[i].GetX(), i);
    }
}

TEST(DummyVector, noncopypable3) {

    const size_t size = 5;
    bmstu::dummy_vector<X> v;
    for (size_t i = 0; i < size; ++i) {
        v.push_back(X(i));
    }

    ASSERT_EQ(v.size(), size);

    for (size_t i = 0; i < size; ++i) {
        ASSERT_EQ(v[i].GetX(), i);
    }

}

TEST(DummyVector, noncopiableinsert) {
    const size_t size = 5;
    bmstu::dummy_vector<X> v;
    for (size_t i = 0; i < size; ++i) {
        v.push_back(X(i));
    }

    // в начало
    v.insert(v.begin(), X(size + 1));
    ASSERT_EQ(v.size(), size + 1);
    ASSERT_EQ(v.begin()->GetX(), size + 1);
    // в конец
    v.insert(v.end(), X(size + 2));
    ASSERT_EQ(v.size(), size + 2);
    ASSERT_EQ((v.end() - 1)->GetX(), size + 2);
    // в середину
    v.insert(v.begin() + 3, X(size + 3));
    ASSERT_EQ(v.size(), size + 3);
    ASSERT_EQ((v.begin() + 3)->GetX(), size + 3);
}

//TEST(DummyVector, erasenoncopy) {
//    const size_t size = 3;
//
//    bmstu::dummy_vector<X> v;
//    for (size_t i = 0; i < size; ++i) {
//        v.push_back(X(i));
//    }
//
//    auto it = v.erase(v.begin());
//    assert(it->GetX() == 1);
//
//}

TEST(DummyVector, test_new_push) {
    bmstu::dummy_vector<int> v;
    ASSERT_EQ(v.capacity(), 0);
    ASSERT_EQ(v.size(), 0);
    v.push_back(1);
    ASSERT_EQ(v.capacity(), 1);
    ASSERT_EQ(v.size(), 1);
    v.push_back(2);
    ASSERT_EQ(v.size(), 2);
    ASSERT_EQ(v.capacity(), 2);
}