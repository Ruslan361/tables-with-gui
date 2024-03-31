#include <gtest.h>
#include <orderedmapvector.h>

TEST(TOrderedMapVector, SearchExistingKey)
{
	TOrderedMapVector<int, std::string> map(10);
	map.Add(1, "one");
	std::string value;
	EXPECT_TRUE(map.Search(1, value));
	EXPECT_EQ(value, "one");
}

TEST(TOrderedMapVector, SearchNonExistingKey)
{
	TOrderedMapVector<int, std::string> map(10);
	std::string value;
	EXPECT_FALSE(map.Search(1, value));
}

TEST(TOrderedMapVector, AddKey)
{
	TOrderedMapVector<int, std::string> map(10);
	map.Add(1, "one");
	std::string value;
	EXPECT_TRUE(map.Search(1, value));
	EXPECT_EQ(value, "one");
}

TEST(TOrderedMapVector, AddExistingKey)
{
	TOrderedMapVector<int, std::string> map(10);
	map.Add(1, "one");
	EXPECT_THROW(map.Add(1, "two"), std::invalid_argument);
}

TEST(TOrderedMapVector, RemoveExistingKey)
{
	TOrderedMapVector<int, std::string> map(10);
	map.Add(1, "one");
	map.Remove(1);
	std::string value;
	EXPECT_FALSE(map.Search(1, value));
}

TEST(TOrderedMapVector, RemoveNonExistingKey)
{
	TOrderedMapVector<int, std::string> map(10);
	map.Remove(1);
	// No exception is thrown, should pass
	EXPECT_TRUE(true);
}

TEST(TOrderedMapVector, AddKeys)
{
	TOrderedMapVector<int, std::string> map(10);
	for (int i = 0; i < 100; i++)
	{
		map.Add(i, "one");
	}
	std::string value;
	EXPECT_TRUE(map.Search(1, value));
	EXPECT_EQ(value, "one");
}
TEST(TOrderedMapVector, SearchKeys)
{
	TOrderedMapVector<int, std::string> map(10);
	for (int i = 0; i < 100; i++)
	{
		map.Add(i, "one");
	}
	std::string value;
	EXPECT_TRUE(map.Search(1, value));
	EXPECT_EQ(value, "one");
	EXPECT_TRUE(map.Search(30, value));
	EXPECT_EQ(value, "one");
}