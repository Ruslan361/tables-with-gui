#include <gtest.h>
#include "hashtable.h"

TEST(THashTable, SearchExistingKey)
{
    THashTable<int, std::string> map;
    map.Add(1, "one");
    std::string value;
    EXPECT_TRUE(map.Search(1, value));
    EXPECT_EQ(value, "one");
}

TEST(THashTable, SearchNonExistingKey)
{
    THashTable<int, std::string> map;
    std::string value;
    EXPECT_FALSE(map.Search(1, value));
}

TEST(THashTable, AddKey)
{
    THashTable<int, std::string> map;
    map.Add(1, "one");
    std::string value;
    EXPECT_TRUE(map.Search(1, value));
    EXPECT_EQ(value, "one");
}

TEST(THashTable, AddExistingKey)
{
    THashTable<int, std::string> map;
    map.Add(1, "one");
    EXPECT_THROW(map.Add(1, "two"), std::invalid_argument);
}

TEST(THashTable, RemoveExistingKey)
{
    THashTable<int, std::string> map;
    map.Add(1, "one");
    map.Remove(1);
    std::string value;
    EXPECT_FALSE(map.Search(1, value));
}

TEST(THashTable, RemoveNonExistingKey)
{
    THashTable<int, std::string> map;
    map.Remove(1);
    // No exception is thrown, should pass
    EXPECT_TRUE(true);
}

TEST(THashTable, AddKeys)
{
    THashTable<int, std::string> map;
    for (int i = 0; i < 100; i++)
    {
        map.Add(i, "one");
    }
    std::string value;
    EXPECT_TRUE(map.Search(1, value));
    EXPECT_EQ(value, "one");
}
TEST(THashTable, SearchKeys)
{
    THashTable<int, std::string> map;
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
