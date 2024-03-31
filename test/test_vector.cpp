#include "vector.h"
#include <gtest.h>

// Тестирование конструктора по умолчанию
TEST(Vector, DefaultConstructor) {
	Vector<int> v;
	ASSERT_EQ(0, v.getSize());
}
TEST(Vector, InsertTest)
{
	Vector<int> v;

	v.Insert(0, 1);
	EXPECT_EQ(v[0], 1); // Ожидаем, что значение 1 было добавлено в начало

	v.Insert(1, 2);
	EXPECT_EQ(v[1], 2); // Ожидаем, что значение 2 было добавлено вторым элементом

	v.Insert(1, 3);
	EXPECT_EQ(v[1], 3); // Ожидаем, что значение 3 было добавлено вторым элементом (значение 2 должно быть сдвинуто на одну позицию вперед)

	// Добавим элемент в позицию size (равно размеру)
	v.Insert(v.getSize(), 4);
	EXPECT_EQ(v[v.getSize() - 1], 4); // Ожидаем, что значение 4 было добавлено в конец

	// Попытка вставить элемент в позицию больше, чем size
	ASSERT_THROW(v.Insert(v.getSize() + 1, 5), std::out_of_range); // Ожидаем, что будет выброшено исключение out_of_range
}
// Тестирование конструктора с параметром
TEST(Vector, ConstructorWithSize) {
	Vector<int> v(5);
	ASSERT_EQ(5, v.getSize());
}

// Другие тесты для остальных методов класса Vector

// Пример тестирования метода push_back
TEST(Vector, PushBack) {
	Vector<int> v;
	v.push_back(10);
	ASSERT_EQ(1, v.getSize());
	ASSERT_EQ(10, v.getBack());
}

// Пример тестирования перегруженного оператора []
TEST(Vector, IndexOperator) {
	Vector<int> v(3);
	v[0] = 1;
	v[1] = 2;
	v[2] = 3;
	ASSERT_EQ(2, v[1]);
}
// Тестирование конструктора копирования Vector(const Vector<T>& _vector)
TEST(Vector, CopyConstructor) {
	Vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	Vector<int> v2 = v1;

	ASSERT_EQ(v1.getSize(), v2.getSize());
	ASSERT_EQ(v1.at(0), v2.at(0));
	ASSERT_EQ(v1.at(1), v2.at(1));
}

// Тестирование функции at(size_t index)
TEST(Vector, AccessElementAt) {
	Vector<int> v;
	v.push_back(10);
	v.push_back(20);

	ASSERT_EQ(10, v.at(0));
	ASSERT_EQ(20, v.at(1));
}
TEST(Vector, GetFront) {
	Vector<int> v;
	v.push_back(10);
	v.push_back(20);

	ASSERT_EQ(10, v.getFront());
}

TEST(Vector, OperatorEquality) {
	Vector<int> v1(3);
	Vector<int> v2(3);

	v1[0] = 1;
	v1[1] = 2;
	v1[2] = 3;

	v2[0] = 1;
	v2[1] = 2;
	v2[2] = 3;

	ASSERT_TRUE(v1 == v2);
}

TEST(Vector, Resize) {
	Vector<int> v(3);
	v.resize(5);

	ASSERT_EQ(5, v.getSize());
}
TEST(Vector, NotEqual) {
	Vector<int> v1 = std::vector<int>({ 1, 2, 3 });
	Vector<int> v2 = std::vector<int>{ 4, 5, 6 };
	ASSERT_TRUE(v1 != v2);
}

TEST(Vector, MinusEqual) {
	Vector<int> v1 = std::vector<int>{ 1, 2, 3 };
	Vector<int> v2 = std::vector<int>{ 4, 5, 6 };
	v1 -= v2;
	Vector<int> expected = std::vector<int>{ -3, -3, -3 };
	ASSERT_EQ(v1, expected);
}

TEST(Vector, Equal) {
	Vector<int> v1 = std::vector<int>{ 1, 2, 3 };
	Vector<int> v2 = std::vector<int>{ 4, 5, 6 };
	v1 = v2;
	ASSERT_EQ(v1, v2);
}

TEST(Vector, LessEqual) {
	Vector<int> v1 = std::vector<int>{ 1, 2, 3 };
	Vector<int> v2 = std::vector<int>{ 1, 2, 4 };
	ASSERT_TRUE(v1 <= v2);
}

TEST(Vector, GreaterEqual) {
	Vector<int> v1 = std::vector<int>{ 1, 2, 3 };
	Vector<int> v2 = std::vector<int>{ 1, 2, 2 };
	ASSERT_TRUE(v1 >= v2);
}

TEST(Vector, Less) {
	Vector<int> v1 = std::vector<int>{ 1, 2, 3 };
	Vector<int> v2 = std::vector<int>{ 1, 2, 4 };
	ASSERT_TRUE(v1 < v2);
}

TEST(Vector, Greater) {
	Vector<int> v1 = std::vector<int>{ 1, 2, 3 };
	Vector<int> v2 = std::vector<int>{ 1, 2, 2 };
	ASSERT_TRUE(v1 > v2);
}

TEST(Vector, Plus) {
	Vector<int> v1 = std::vector<int>{ 1, 2, 3 };
	Vector<int> v2 = std::vector<int>{ 4, 5, 6 };
	Vector<int> result = v1 + v2;
	Vector<int> expected = std::vector<int>{ 5, 7, 9 };
	ASSERT_EQ(result, expected);
}

TEST(Vector, MultiplyScalar) {
	Vector<int> v = std::vector<int>{ 1, 2, 3 };
	int scalar = 2;
	Vector<int> result = v * scalar;
	Vector<int> expected = std::vector<int>{ 2, 4, 6 };
	ASSERT_EQ(result, expected);
}

TEST(Vector, Minus) {
	Vector<int> v1 = std::vector<int>{ 4, 5, 6 };
	Vector<int> v2 = std::vector<int>{ 1, 2, 3 };
	Vector<int> result = v1 - v2;
	Vector<int> expected = std::vector<int>{ 3, 3, 3 };
	ASSERT_EQ(result, expected);
}

TEST(Vector, DivideScalar) {
	Vector<int> v = std::vector<int>{ 2, 4, 6 };
	int scalar = 2;
	Vector<int> result = v / scalar;
	Vector<int> expected = std::vector<int>{ 1, 2, 3 };
	ASSERT_EQ(result, expected);
}

TEST(Vector, MultiplyEqual) {
	Vector<int> v = std::vector<int>{ 1, 2, 3 };
	int scalar = 2;
	v *= scalar;
	Vector<int> expected = std::vector<int>{ 2, 4, 6 };
	ASSERT_EQ(v, expected);
}

TEST(Vector, PlusEqual) {
	Vector<int> v1 = std::vector<int>{ 1, 2, 3 };
	Vector<int> v2 = std::vector<int>{ 4, 5, 6 };
	v1 += v2;
	Vector<int> expected = std::vector<int>{ 5, 7, 9 };
	ASSERT_EQ(v1, expected);
}

TEST(Vector, DivideEqual) {
	Vector<int> v = std::vector<int>{ 2, 4, 6 };
	int scalar = 2;
	v /= scalar;
	Vector<int> expected = std::vector<int>{ 1, 2, 3 };
	ASSERT_EQ(v, expected);
}

TEST(Vector, PreIncrement) {
	Vector<int> v = std::vector<int>{ 1, 2, 3 };
	++v;
	Vector<int> expected = std::vector<int>{ 2, 3, 4 };
	ASSERT_EQ(v, expected);
}

TEST(Vector, PostIncrement) {
	Vector<int> v = std::vector<int>{ 1, 2, 3 };
	Vector<int> copy = v++;
	Vector<int> expected = std::vector<int>{ 1, 2, 3 };
	ASSERT_EQ(copy, expected);
}

TEST(Vector, DotProduct) {
	Vector<int> v1 = std::vector<int>{ 1, 2, 3 };
	Vector<int> v2 = std::vector<int>{ 4, 5, 6 };
	int result = v1 * v2;
	int expected = 32;
	ASSERT_EQ(result, expected);
}

TEST(Vector, IndexOperator1) {
	Vector<int> v = std::vector<int>{ 1, 2, 3 };
	ASSERT_EQ(v[1], 2);
}

TEST(Vector, SearchElementInVector)
{
	Vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);

	ASSERT_EQ(vec.Search(1), 0);
	ASSERT_EQ(vec.Search(2), 1);
	ASSERT_EQ(vec.Search(3), 2);
	ASSERT_EQ(vec.Search(4), -1);
}

TEST(Vector, RemoveElementFromVector)
{
	Vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);

	vec.Remove(2);

	ASSERT_EQ(vec.Search(1), 0);
	ASSERT_EQ(vec.Search(2), -1);
	ASSERT_EQ(vec.Search(3), 1);
}

TEST(Vector, RemoveNonExistingElementFromVector)
{
	Vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);

	vec.Remove(4);

	ASSERT_EQ(vec.Search(1), 0);
	ASSERT_EQ(vec.Search(2), 1);
	ASSERT_EQ(vec.Search(3), 2);
}

TEST(Vector, SetCopacity) {
	Vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);

	v.setCopacity(10);

	EXPECT_EQ(10, v.getCopacity());
	EXPECT_EQ(3, v.getSize());
}

TEST(Vector, Remove)
{
	Vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);

	vec.Remove((size_t) 1);

	EXPECT_EQ(vec[0], 1);
	EXPECT_EQ(vec[1], 3);
	EXPECT_EQ(vec.getSize(), 2);
}