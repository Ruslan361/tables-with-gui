#include <gtest.h>
#include "orderedmaplist.h"

TEST(TOrderedMapList, SearchExistingKey)
{
	TOrderedMapList<int, std::string> map;
	map.Add(1, "one");
	std::string value;
	EXPECT_TRUE(map.Search(1, value));
	EXPECT_EQ(value, "one");
}

TEST(TOrderedMapList, SearchNonExistingKey)
{
	TOrderedMapList<int, std::string> map;
	std::string value;
	EXPECT_FALSE(map.Search(1, value));
}

TEST(TOrderedMapList, AddKey)
{
	TOrderedMapList<int, std::string> map;
	map.Add(1, "one");
	std::string value;
	EXPECT_TRUE(map.Search(1, value));
	EXPECT_EQ(value, "one");
}

TEST(TOrderedMapList, AddExistingKey)
{
	TOrderedMapList<int, std::string> map;
	map.Add(1, "one");
	EXPECT_THROW(map.Add(1, "two"), std::invalid_argument);
}

TEST(TOrderedMapList, RemoveExistingKey)
{
	TOrderedMapList<int, std::string> map;
	map.Add(1, "one");
	map.Remove(1);
	std::string value;
	EXPECT_FALSE(map.Search(1, value));
}

TEST(TOrderedMapList, RemoveNonExistingKey)
{
	TOrderedMapList<int, std::string> map;
	map.Remove(1);
	// No exception is thrown, should pass
	EXPECT_TRUE(true);
}

TEST(TOrderedMapList, AddKeys)
{
	TOrderedMapList<int, std::string> map;
	for (int i = 0; i < 100; i++)
	{
		map.Add(i, "one");
	}
	std::string value;
	EXPECT_TRUE(map.Search(1, value));
	EXPECT_EQ(value, "one");
}
TEST(TOrderedMapList, SearchKeys)
{
	TOrderedMapList<int, std::string> map;
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