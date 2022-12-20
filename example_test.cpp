#include <gtest/gtest.h>
#include <string>
#include "bmstu_vektor.h"

TEST(GoogleTestCi, Foo) {
    ASSERT_TRUE(true);
}

TEST(ExampleTest, DmitriiLeonidovich) {
    std::string dml = "DmitriiLeonidovich";
    const char *dml_c = "DmitriiLeonidovich";
    ASSERT_STREQ(dml.c_str(), dml_c);
}

TEST(Vector, exact_symbol) {
    bmstu::vector<char> vektor{'B', 'A', 'N', 'A', 'N'};
    ASSERT_EQ(vektor[4], 'N');
    ASSERT_EQ(vektor[0], 'B');
}

TEST(Vector, resize_char) {
    bmstu::vector<char> vektor{'B', 'A', 'N', 'A', 'N'};
    vektor.resize(3);
    ASSERT_EQ(vektor.size(), 3);
    ASSERT_EQ(vektor.capacity(), 3);
}

TEST(Vector, resize_int) {
    bmstu::vector<int> vektor{1, 2, 3};
    vektor.resize(8);
    ASSERT_EQ(vektor.size(), 8);
    ASSERT_EQ(vektor.capacity(), 8);
}

TEST(Vector, swap) {
    bmstu::vector<char> vektor{'B', 'A', 'N', 'A', 'N'};
    bmstu::vector<char> vektor2{'C', 'O', 'O', 'K', 'I', 'E'};
    vektor.swap(vektor2);
    ASSERT_EQ(vektor.size(), 6);
}

TEST(Vector, reserve) {
    bmstu::vector<char> vektor{'B', 'A', 'N', 'A', 'N'};
    vektor.reserve(2);
    bmstu::vector<char> vektor2{'B', 'A'};
    ASSERT_EQ(vektor.size(), 2);
    ASSERT_EQ(vektor.capacity(), 2);
    ASSERT_EQ(vektor, vektor2);
}

TEST(Vector, reserve_more) {
    bmstu::vector<char> vektor{'B', 'A', 'N', 'A', 'N'};
    vektor.reserve(6);
    ASSERT_EQ(vektor.size(), 5);
    ASSERT_EQ(vektor.capacity(), 6);
}

TEST(Vector, iterator) {
    bmstu::vector<char> vektor{'B', 'A', 'N', 'A', 'N'};
    ASSERT_EQ(*(vektor.begin()), 'B');
    ASSERT_EQ(*(vektor.end() - 1), 'N');
    ASSERT_EQ(*(vektor.begin() + 2), *(vektor.end() - 3));
}

TEST(Vector, symbol_input) {
    bmstu::vector<char> vektor{'B', 'A', 'N', 'A', 'N'};
    vektor.insert(vektor.begin(), 'X');
    std::stringstream ss;
    ss << vektor;
    ASSERT_STREQ(ss.str().c_str(), "[X, B, A, N, A, N]");
    ASSERT_EQ(vektor.size(), 6);
}

TEST(Vector, symbol_back) {
    bmstu::vector<char> vektor{'B', 'A', 'N', 'A', 'N'};
    vektor.push_back('A');
    std::stringstream ss;
    ss << vektor;
    ASSERT_EQ(vektor.size(), 6);
    ASSERT_STREQ(ss.str().c_str(), "[B, A, N, A, N, A]");
}

TEST(Vector, operator_equal_char) {
    bmstu::vector<char> vektor{'B', 'A', 'N', 'A', 'N'};
    bmstu::vector<char> vektor2{'B', 'A', 'N', 'A', 'N'};
    ASSERT_EQ(vektor == vektor2, 1);
}

TEST(Vector, operator_equal_int) {
    bmstu::vector<int> vektor{1, 2};
    bmstu::vector<int> vektor2{1, 2};
    ASSERT_EQ(vektor == vektor2, 1);
}

TEST(Vector, operator_not_equal) {
    bmstu::vector<char> vektor{'B', 'A', 'N', 'A', 'N'};
    bmstu::vector<char> vektor2{'B', 'A', 'N', 'A', 'N', 'A'};
    ASSERT_EQ(vektor != vektor2, 1);
}

TEST(Vector, operator_more_not_equal) {
    bmstu::vector<char> vektor{'B', 'A', 'N', 'A', 'N'};
    bmstu::vector<char> vektor2{'B', 'A', 'N', 'A', 'N', 'X', 'X', 'X'};
    ASSERT_EQ(vektor != vektor2, 1);
}

TEST(Vector, operator_not_equal_int) {
    bmstu::vector<int> vektor{1, 2, 3};
    bmstu::vector<int> vektor2{1, 2};
    ASSERT_EQ(vektor != vektor2, 1);
}

TEST(Vector, operator_less) {
    bmstu::vector<char> vektor{'B', 'A', 'N', 'A', 'N'};
    bmstu::vector<char> vektor2{'B', 'A', 'N', 'A', 'O'};
    ASSERT_TRUE(vektor < vektor2);
}

TEST(Vector, operator_more) {
    bmstu::vector<char> vektor{'B', 'A', 'N', 'A', 'N'};
    bmstu::vector<char> vektor2{'B', 'A', 'N', 'A', 'M'};
    ASSERT_TRUE(vektor > vektor2);
}

TEST(Vector, operator_bigger) {
    bmstu::vector<char> vektor{'B', 'A', 'N', 'A', 'N', 'Q'};
    bmstu::vector<char> vektor2{'B', 'A', 'N', 'A', 'N'};
    ASSERT_TRUE(vektor > vektor2);
}

TEST(Vector, operator_less_size) {
    bmstu::vector<char> vektor{'B', 'A', 'N', 'A', 'N'};
    bmstu::vector<char> vektor2{'B', 'A', 'N', 'A', 'N', 'Q'};
    ASSERT_TRUE(vektor < vektor2);
}

TEST(Vector, operator_much_less_size) {
    bmstu::vector<char> vektor{'B', 'A', 'N', 'A', 'N'};
    bmstu::vector<char> vektor2{'B', 'A', 'N', 'A', 'N', 'X', 'X', 'X'};
    ASSERT_TRUE(vektor < vektor2);
}

TEST(Vector, operator_not_more) {
    bmstu::vector<char> vektor{'B', 'A', 'N', 'A', 'N'};
    bmstu::vector<char> vektor2{'B', 'A', 'N', 'A', 'N'};
    ASSERT_TRUE(vektor >= vektor2);
}

TEST(Vector, operator_not_less) {
    bmstu::vector<char> vektor{'B', 'A', 'N', 'A', 'N'};
    bmstu::vector<char> vektor2{'B', 'A', 'N', 'A', 'N'};
    ASSERT_TRUE(vektor <= vektor2);
}

TEST(Vector, operator_much_bigger) {
    bmstu::vector<char> vektor{'B', 'A', 'N', 'A', 'N', 'X', 'X', 'X'};
    bmstu::vector<char> vektor2{'B', 'A', 'N', 'A', 'N'};
    ASSERT_TRUE(vektor > vektor2);
}

TEST(Vector, empty) {
    bmstu::vector<char> vektor{'B', 'A', 'N', 'A', 'N'};
    vektor = vektor.empty();
    ASSERT_EQ(vektor, 0);
}
