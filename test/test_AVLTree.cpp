#include "AVLTree.h"
#include <gtest.h>

//TEST(AVLTree, SearchExistingKey)
//{
//    AVLTree<int, std::string> map;
//    map.Add(1, "one");
//    std::string value;
//    EXPECT_TRUE(map.Search(1, value));
//    EXPECT_EQ(value, "one");
//}

//TEST(AVLTree, SearchNonExistingKey)
//{
//    AVLTree<int, std::string> map;
//    std::string value;
//    EXPECT_FALSE(map.Search(1, value));
//}

//TEST(AVLTree, AddKey)
//{
//    AVLTree<int, std::string> map;
//    map.Add(1, "one");
//    std::string value;
//    EXPECT_TRUE(map.Search(1, value));
//    EXPECT_EQ(value, "one");
//}

//TEST(AVLTree, AddExistingKey)
//{
//    AVLTree<int, std::string> map;
//    map.Add(1, "one");
//    EXPECT_THROW(map.Add(1, "two"), std::invalid_argument);
//}

TEST(AVLTree, RemoveExistingKey)
{
   AVLTree<int, std::string> map;
   map.Add(1, "one");
   map.Remove(1);
   std::string value;
   EXPECT_FALSE(map.Search(1, value));
}
TEST(AVLTree, RemoveExistingKeys)
{
    AVLTree<int, std::string> map;
    for (int i = 0; i < 10; i++)
    {
       map.Add(i, "one");
    }
    map.Remove(5);
    std::string value;
    EXPECT_FALSE(map.Search(5, value));
}


TEST(AVLTree, RemoveNonExistingKey)
{
    AVLTree<int, std::string> map;
    map.Remove(1);
    // No exception is thrown, should pass
    EXPECT_TRUE(true);
}

TEST(AVLTree, AddKeys)
{
    AVLTree<int, std::string> map;
    for (int i = 0; i < 100; i++)
    {
        map.Add(i, "one");
    }
    std::string value;
    EXPECT_TRUE(map.Search(1, value));
    EXPECT_EQ(value, "one");
    EXPECT_TRUE(map.Search(50, value));
    EXPECT_EQ(value, "one");
}
TEST(AVLTree, SearchKeys)
{
   AVLTree<int, std::string> map;
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
