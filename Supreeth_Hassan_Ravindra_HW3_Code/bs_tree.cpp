#include "bs_tree.h"
#include <list>
#include <iostream>

using namespace std;

/*
 * constructor/destructor
 */
 
// question 1: Implementation of a binary-search tree with the corresponding functionality as the given Red-Black tree and not to allow insertion of duplicate values.

bs_tree::bs_tree()
{ 
    T_root = nullptr;
} 

bs_tree::~bs_tree()
{ 
    remove_all(T_root);
} 

void bs_tree::insert(int key, bs_tree_i_info& t_info)
{ 
    bs_tree_node* z;
    z = new bs_tree_node;
    z->key = key;
    z->left=nullptr;
    z->right = nullptr;
    
    bs_tree_node* x;
    bs_tree_node* y;
    
    y=nullptr;
    x= T_root;
    while(x!= nullptr)
    {
        y=x;
        if(z->key < x->key)
        {
            x = x->left;
        }
        else if(z->key > x->key)
        {
            x = x->right;
        }
        else
        {
            t_info.i_duplicate++;          //Found the duplicate values, hence increment the i_duplicate counter
            return;
        }
    }
    z->p = y;
    if(y == nullptr)
    {
        T_root =z;
    }
    else 
    {
        if (z->key < y->key)
        {
           y->left = z;
        }
        else if(z->key > y-> key)
        {
           y->right = z;
        }

    }
}

void bs_tree::remove_all(bs_tree_node* x)
{
  if(x!=nullptr)
  {
    remove_all(x->left);
    remove_all(x->right);
    delete x;
 }
} 

// question 2:  modified inorder tree walk method to save the sorted numbers in the first argument: int* array.

int bs_tree::convert(int* array, int n)
{
    int i=0;
    bs_tree_node* T_node = T_root;
    inorder_tree_walk(T_node,array,i);              // inorder_tree_walk(T_node,array,i) is called to traverses the tree (using recursion) in order
                                                    // to copy its elements back to an array, in a sorted ascending order.
    for (int j = i; j < n; j++) {
        array[j] = 0;  // set the remaining elements to some default value (e.g., 0)
    }
    return i;           // returning the n' number of elements copied into the array (i.e. original size of the array - no. of duplicates)
}

void bs_tree::inorder_tree_walk(bs_tree_node* T_node,int* array,int& i)
{
   if(T_node!= nullptr)
   {
      inorder_tree_walk(T_node->left,array,i);
      array[(i)] = T_node->key;
      i = i + 1;
      inorder_tree_walk(T_node->right,array,i);
   }
}