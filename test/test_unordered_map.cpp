#include <gtest.h>
#include <unorderedmapvector.h>

TEST(TUnorderedMapVectorTest, SearchExistingKey)
{
	TUnorderedMapVector<int, std::string> map(10);
	map.Add(1, "one");
	std::string value;
	EXPECT_TRUE(map.Search(1, value));
	EXPECT_EQ(value, "one");
}

TEST(TUnorderedMapVectorTest, SearchNonExistingKey)
{
	TUnorderedMapVector<int, std::string> map(10);
	std::string value;
	EXPECT_FALSE(map.Search(1, value));
}

TEST(TUnorderedMapVectorTest, AddKey)
{
	TUnorderedMapVector<int, std::string> map(10);
	map.Add(1, "one");
	std::string value;
	EXPECT_TRUE(map.Search(1, value));
	EXPECT_EQ(value, "one");
}

TEST(TUnorderedMapVectorTest, AddExistingKey)
{
	TUnorderedMapVector<int, std::string> map(10);
	map.Add(1, "one");
	EXPECT_THROW(map.Add(1, "two"), std::invalid_argument);
}

TEST(TUnorderedMapVectorTest, RemoveExistingKey)
{
	TUnorderedMapVector<int, std::string> map(10);
	map.Add(1, "one");
	map.Remove(1);
	std::string value;
	EXPECT_FALSE(map.Search(1, value));
}

TEST(TUnorderedMapVectorTest, RemoveNonExistingKey)
{
	TUnorderedMapVector<int, std::string> map(10);
	map.Remove(1);
	// No exception is thrown, should pass
	EXPECT_TRUE(true);
}