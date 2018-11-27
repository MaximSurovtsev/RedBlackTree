#include <catch.hpp>

#include "RBT.hpp"

/*           10 B          */
TEST_CASE("insert1", "[root]") 
{
   Tree<int> tree;
   tree.insert(10);
   REQUIRE(tree.left(10) == nullptr);
   REQUIRE(tree.right(10) == nullptr);
   REQUIRE(tree.parent(10) == nullptr);
   REQUIRE(tree.color(10) == BLACK);
   REQUIRE(tree.root() == tree.search(10));
   REQUIRE(tree.count() == 1);
}

/*        10 B            
        /    \               
      9 R     12 R          
                              */
TEST_CASE("insert2", "[black parent]") 
{
   Tree<int> tree;
   tree.insert(10);
   tree.insert(9);
   tree.insert(12);
   REQUIRE(tree.left(10) == tree.search(9));
   REQUIRE(tree.right(10) == tree.search(12));
   REQUIRE(tree.parent(10) == nullptr);
   REQUIRE(tree.parent(9) == tree.search(10));
   REQUIRE(tree.parent(12) == tree.search(10));
   REQUIRE(tree.color(9) == RED);
   REQUIRE(tree.color(10) == BLACK);
   REQUIRE(tree.color(12) == RED);
   REQUIRE(tree.root() == tree.search(10));
   REQUIRE(tree.count() == 3);
}

/*        10 B                  10 B
        /    \                /     \
      7 R     12 R   ->     7 B      12 B
        \                     \
          9 R                   9 R          */
TEST_CASE("insert3", "[red parent, red uncle]") 
{
   Tree<int> tree;
   tree.insert(10);
   tree.insert(7);
   tree.insert(12);
   tree.insert(9);
   REQUIRE(tree.left(7) == nullptr);
   REQUIRE(tree.right(7) == tree.search(9));
   REQUIRE(tree.left(10) == tree.search(7));
   REQUIRE(tree.right(10) == tree.search(12));
   REQUIRE(tree.parent(10) == nullptr);
   REQUIRE(tree.parent(7) == tree.search(10));
   REQUIRE(tree.parent(9) == tree.search(7));
   REQUIRE(tree.parent(12) == tree.search(10));
   REQUIRE(tree.color(7) == BLACK);
   REQUIRE(tree.color(9) == RED);
   REQUIRE(tree.color(10) == BLACK);
   REQUIRE(tree.color(12) == BLACK);
   REQUIRE(tree.root() == tree.search(10));
   REQUIRE(tree.count() == 4);
}

/*        10 B                  10 B
        /    \                /     \
      7 B     12 B   ->     8 B      12 B
        \                  /   \
          9 R             7 R   9 R
         /                    
        8 R                   
                                              */
TEST_CASE("insert4", "[red parent, black uncle || !uncle (turn right, turn left)]") 
{
   Tree<int> tree;
   tree.insert(10);
   tree.insert(7);
   tree.insert(12);
   tree.insert(9);
   tree.insert(8);
   REQUIRE(tree.left(8) == tree.search(7));
   REQUIRE(tree.right(8) == tree.search(9));
   REQUIRE(tree.left(10) == tree.search(8));
   REQUIRE(tree.right(10) == tree.search(12));
   REQUIRE(tree.left(12) == nullptr);
   REQUIRE(tree.right(12) == nullptr);
   REQUIRE(tree.parent(10) == nullptr);
   REQUIRE(tree.parent(7) == tree.search(8));
   REQUIRE(tree.parent(8) == tree.search(10));
   REQUIRE(tree.parent(9) == tree.search(8));
   REQUIRE(tree.parent(12) == tree.search(10));
   REQUIRE(tree.color(7) == RED);
   REQUIRE(tree.color(8) == BLACK);
   REQUIRE(tree.color(9) == RED);
   REQUIRE(tree.color(10) == BLACK);
   REQUIRE(tree.color(12) == BLACK);
   REQUIRE(tree.root() == tree.search(10));
   REQUIRE(tree.count() == 5);
}

/*        10 B                  10 B
        /    \                /     \
      7 B     12 B   ->     8 B      12 B
        \                  /   \
          8 R             7 R   9 R
            \                   
             9 R                   
                                              */
TEST_CASE("insert5", "[red parent, black uncle || !uncle (turn left)]") 
{
   Tree<int> tree;
   tree.insert(10);
   tree.insert(7);
   tree.insert(12);
   tree.insert(8);
   tree.insert(9);
   REQUIRE(tree.left(8) == tree.search(7));
   REQUIRE(tree.right(8) == tree.search(9));
   REQUIRE(tree.left(10) == tree.search(8));
   REQUIRE(tree.right(10) == tree.search(12));
   REQUIRE(tree.parent(10) == nullptr);
   REQUIRE(tree.parent(7) == tree.search(8));
   REQUIRE(tree.parent(8) == tree.search(10));
   REQUIRE(tree.parent(9) == tree.search(8));
   REQUIRE(tree.parent(12) == tree.search(10));
   REQUIRE(tree.color(7) == RED);
   REQUIRE(tree.color(8) == BLACK);
   REQUIRE(tree.color(9) == RED);
   REQUIRE(tree.color(10) == BLACK);
   REQUIRE(tree.color(12) == BLACK);
   REQUIRE(tree.root() == tree.search(10));
   REQUIRE(tree.count() == 5);
}

/*        10 B                  10 B
        /    \                /     \
      7 B     13 B   ->     7 B      12 B
             /                      /   \
          11 R                    11 R   13 R
            \                   
             12 R                   
                                              */
TEST_CASE("insert6", "[red parent, black uncle || !uncle (turn left, turn right)]") 
{
   Tree<int> tree;
   tree.insert(10);
   tree.insert(7);
   tree.insert(13);
   tree.insert(11);
   tree.insert(12);
   REQUIRE(tree.left(10) == tree.search(7));
   REQUIRE(tree.right(10) == tree.search(12));
   REQUIRE(tree.left(12) == tree.search(11));
   REQUIRE(tree.right(12) == tree.search(13));
   REQUIRE(tree.parent(10) == nullptr);
   REQUIRE(tree.parent(7) == tree.search(10));
   REQUIRE(tree.parent(11) == tree.search(12));
   REQUIRE(tree.parent(12) == tree.search(10));
   REQUIRE(tree.parent(13) == tree.search(12));
   REQUIRE(tree.color(7) == BLACK);
   REQUIRE(tree.color(10) == BLACK);
   REQUIRE(tree.color(11) == RED);
   REQUIRE(tree.color(12) == BLACK);
   REQUIRE(tree.color(13) == RED);
   REQUIRE(tree.root() == tree.search(10));
   REQUIRE(tree.count() == 5);
}

/*        10 B                  10 B
        /    \                /     \
      7 B     13 B   ->     7 B      12 B
             /                      /   \
          12 R                    11 R   13 R
         /                     
        11 R                   
                                              */
TEST_CASE("insert7", "[red parent, black uncle || !uncle (turn right)]") 
{
   Tree<int> tree;
   tree.insert(10);
   tree.insert(7);
   tree.insert(13);
   tree.insert(12);
   tree.insert(11);
   REQUIRE(tree.left(10) == tree.search(7));
   REQUIRE(tree.right(10) == tree.search(12));
   REQUIRE(tree.left(12) == tree.search(11));
   REQUIRE(tree.right(12) == tree.search(13));
   REQUIRE(tree.parent(10) == nullptr);
   REQUIRE(tree.parent(7) == tree.search(10));
   REQUIRE(tree.parent(11) == tree.search(12));
   REQUIRE(tree.parent(12) == tree.search(10));
   REQUIRE(tree.parent(13) == tree.search(12));
   REQUIRE(tree.color(7) == BLACK);
   REQUIRE(tree.color(10) == BLACK);
   REQUIRE(tree.color(11) == RED);
   REQUIRE(tree.color(12) == BLACK);
   REQUIRE(tree.color(13) == RED);
   REQUIRE(tree.root() == tree.search(10));
   REQUIRE(tree.count() == 5);
}

/*           10 B
           /     \
         7 B      12 B
                 /   \
               11 R   13 R      */
TEST_CASE("delete1", "[]") 
{
   Tree<int> tree;
   tree.insert(10);
   tree.insert(7);
   tree.insert(13);
   tree.insert(12);
   tree.insert(11);
   tree.deleteElement(15);
   REQUIRE(tree.left(10) == tree.search(7));
   REQUIRE(tree.right(10) == tree.search(12));
   REQUIRE(tree.left(12) == tree.search(11));
   REQUIRE(tree.right(12) == tree.search(13));
   REQUIRE(tree.parent(10) == nullptr);
   REQUIRE(tree.parent(7) == tree.search(10));
   REQUIRE(tree.parent(11) == tree.search(12));
   REQUIRE(tree.parent(12) == tree.search(10));
   REQUIRE(tree.parent(13) == tree.search(12));
   REQUIRE(tree.color(7) == BLACK);
   REQUIRE(tree.color(10) == BLACK);
   REQUIRE(tree.color(11) == RED);
   REQUIRE(tree.color(12) == BLACK);
   REQUIRE(tree.color(13) == RED);
   REQUIRE(tree.root() == tree.search(10));
   REQUIRE(tree.count() == 5);
}

/*           10 B                         11 B
           /     \                      /     \
         7 B      13 R          ->    7 B      13 R 
                 /   \                        /   \
               12 B   14 B                  12 B   14 B 
              /             
            11 R                                              */
TEST_CASE("delete2", "[root || node->right]") 
{
   Tree<int> tree;
   tree.insert(10);
   tree.insert(7);
   tree.insert(14);
   tree.insert(12);
   tree.insert(13);
   tree.insert(11);
   tree.deleteElement(10);
   REQUIRE(tree.left(11) == tree.search(7));
   REQUIRE(tree.right(11) == tree.search(13));
   REQUIRE(tree.left(13) == tree.search(12));
   REQUIRE(tree.right(13) == tree.search(14));
   REQUIRE(tree.parent(11) == nullptr);
   REQUIRE(tree.parent(7) == tree.search(11));
   REQUIRE(tree.parent(13) == tree.search(11));
   REQUIRE(tree.parent(12) == tree.search(13));
   REQUIRE(tree.parent(14) == tree.search(13));
   REQUIRE(tree.color(7) == BLACK);
   REQUIRE(tree.color(11) == BLACK);
   REQUIRE(tree.color(12) == BLACK);
   REQUIRE(tree.color(13) == RED);
   REQUIRE(tree.color(14) == BLACK);
   REQUIRE(tree.root() == tree.search(11));
   REQUIRE(tree.count() == 5);
}

/*        10 B                  10 B
        /    \                /     \
      7 B     12 B   ->     7 B      12 B
             /   \                      \
          11 R    13 R                   13 R           
                                              */
TEST_CASE("delete3", "[leaf]") 
{
   Tree<int> tree;
   tree.insert(10);
   tree.insert(7);
   tree.insert(12);
   tree.insert(13);
   tree.insert(11);
   tree.deleteElement(11);
   REQUIRE(tree.left(10) == tree.search(7));
   REQUIRE(tree.right(10) == tree.search(12));
   REQUIRE(tree.left(12) == nullptr);
   REQUIRE(tree.right(12) == tree.search(13));
   REQUIRE(tree.parent(10) == nullptr);
   REQUIRE(tree.parent(7) == tree.search(10));
   REQUIRE(tree.parent(12) == tree.search(10));
   REQUIRE(tree.parent(13) == tree.search(12));
   REQUIRE(tree.color(7) == BLACK);
   REQUIRE(tree.color(10) == BLACK);
   REQUIRE(tree.color(12) == BLACK);
   REQUIRE(tree.color(13) == RED);
   REQUIRE(tree.root() == tree.search(10));
   REQUIRE(tree.count() == 4);
}

/*        10 B                  10 B
        /    \                /     \
      7 B     12 B   ->     7 B      11 B
             /                       
          11 R                                 */
TEST_CASE("delete4", "[node->left]") 
{
   Tree<int> tree;
   tree.insert(10);
   tree.insert(7);
   tree.insert(12);
   tree.insert(11);
   tree.deleteElement(12);
   REQUIRE(tree.left(10) == tree.search(7));
   REQUIRE(tree.right(10) == tree.search(11));
   REQUIRE(tree.parent(10) == nullptr);
   REQUIRE(tree.parent(7) == tree.search(10));
   REQUIRE(tree.parent(11) == tree.search(10));
   REQUIRE(tree.color(7) == BLACK);
   REQUIRE(tree.color(10) == BLACK);
   REQUIRE(tree.color(11) == BLACK);
   REQUIRE(tree.root() == tree.search(10));
   REQUIRE(tree.count() == 3);
}

