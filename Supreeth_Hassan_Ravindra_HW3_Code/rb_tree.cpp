#include "rb_tree.h"
#include <list>
#include <iostream>

using namespace std;

/*
 * constructor/destructor
 */
rb_tree::rb_tree()
{ /*<<<*/
/*
 * create T_nil element
 */
  T_nil = new rb_tree_node();
  T_nil->color = RB_BLACK;
  T_nil->p = T_nil;
  T_nil->left = T_nil;
  T_nil->right = T_nil;
  rb_tree::countBlackNodes=0;

/*
 * root of rb tree
 */
  T_root = T_nil;
} /*>>>*/

rb_tree::~rb_tree()
{ /*<<<*/ 
/*
 * delete nil element and all other allocated nodes
 */
  remove_all(T_root);

  delete T_nil;
} /*>>>*/


void rb_tree::insert(int key, rb_tree_i_info& t_info)
{ /*<<<*/
/*
 * wrapper around insert
 * -> creates black node with key
 * -> inserts node
 */
  rb_tree_node* z;

  z = new rb_tree_node;
  z->color = RB_BLACK;
  z->key = key;

  insert(z, t_info);
} /*>>>*/

void rb_tree::insert(rb_tree_node* z, rb_tree_i_info& t_info)
{ /*<<<*/
/*
 * binary tree type insert 
 * -> search position, insert new node
 * -> fix properties after insert
 */
  rb_tree_node* x;
  rb_tree_node* y;

  y = T_nil;
  x = T_root;
  while (x != T_nil)
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
            //Found the duplicate value, hence increment the counter i_duplicate
            t_info.i_duplicate++;
            return;
        }
    }

  z->p = y;
  if (y == T_nil)
    T_root = z;
  else
    {
      if (z->key < y->key)
        y->left = z;
      else
          y->right = z;
    }

  z->left = T_nil;
  z->right = T_nil;
  z->color = RB_RED;

/*
 * after binary tree type insert we need to fix RB tree properties
 * -> update the info file
 */
  insert_fixup(z, t_info);
} /*>>>*/

void rb_tree::insert_fixup(rb_tree_node*& z, rb_tree_i_info& t_info)
{ /*<<<*/
/*
 * fix RB tree properties, after inserting a node
 * -> see book/slides for details on the cases
 */
  rb_tree_node* y;

  while (z->p->color == RB_RED)
    {
      if (z->p == z->p->p->left)
	{
	  y = z->p->p->right;

	  if (y->color == RB_RED)
	    {
	      z->p->color = RB_BLACK;		// Case 1
	      y->color = RB_BLACK;
	      z->p->p->color = RB_RED;
	      z = z->p->p;
	      t_info.i_case_1++;            // increment i_case_1 counter
	    }
	  else
	    {
	      if (z == z->p->right)
		{
		  z = z->p;	
		  t_info.i_case_2++;        // Case 2
		  left_rotate(z);
		  t_info.i_left_rotate++;       // increment i_case_2 and i_left_rotate counter
		}

	      z->p->color = RB_BLACK;		// Case 3
	      z->p->p->color = RB_RED;
	      t_info.i_case_3++;            //increment i_case_3 and i_right_rotate counter
	      right_rotate(z->p->p);
	      t_info.i_right_rotate++;
	    }
	}
      else
	{

	  y = z->p->p->left;

	  if (y->color == RB_RED)
	    {
	      z->p->color = RB_BLACK;		// Case 1
	      y->color = RB_BLACK;
	      z->p->p->color = RB_RED;
	      z = z->p->p;
	      t_info.i_case_1++;            // increment i_case_1 counter
	    }
	  else
	    {
	      if (z == z->p->left)
		{
		  z = z->p;	
		  t_info.i_case_2++;            // Case 2
		  right_rotate(z);
		  t_info.i_right_rotate++;      //increment i_case_2 and i_right_rotate counter
		}

	      z->p->color = RB_BLACK;		// Case 3
	      z->p->p->color = RB_RED;
	      t_info.i_case_3++;
	      left_rotate(z->p->p);
	      t_info.i_left_rotate++;       //increment i_case_3 and i_left_rotate counter
	    }
	}
    }

  T_root->color = RB_BLACK;
} /*>>>*/


void rb_tree::left_rotate(rb_tree_node* x)
{ /*<<<*/
/*
 * rotate left -> see book/slides
 */
  rb_tree_node* y;

  y = x->right;			// set y
  x->right = y->left;		// turn y's left subtree into x's right subtree
  if (y->left != T_nil)
    y->left->p = x;

  y->p = x->p;			// link x's parent to y
  if (x->p == T_nil)
    T_root = y;
  else
    {
      if (x == x->p->left)
	x->p->left = y;
      else
	x->p->right = y;
    }

  y->left = x;			// put x on y's left
  x->p = y;
} /*>>>*/

void rb_tree::right_rotate(rb_tree_node* x)
{ /*<<<*/
/*
 * rotate right -> see book/slides
 */
  rb_tree_node* y;

  y = x->left;			// set y
  x->left = y->right;		// turn y's right subtree into x's left subtree
  if (y->right != T_nil)
    y->right->p = x;

  y->p = x->p;			// link x's parent to y
  if (x->p == T_nil)
    T_root = y;
  else
    {
      if (x == x->p->right)
	x->p->right = y;
      else
	x->p->left = y;
    }

  y->right = x;			// put x on y's right
  x->p = y;
} /*>>>*/

void rb_tree::inorder_output(rb_tree_node* x, int level)
{ /*<<<*/
/*
 * in order walk through binary tree
 * -> see book or slides
 */
  if (x != T_nil)
    {
      inorder_output(x->left, level+1);
      cout << "(" << x->key << "," << level << "," 
	   << ((x->color == RB_RED) ? "R" : "B") << ")" << endl;
      inorder_output(x->right, level+1); 
    }
} /*>>>*/

void rb_tree::output(rb_tree_node* x, int r_level)
{ /*<<<*/
/*
 * some structured output
 */
  list< pair<rb_tree_node*,int> > l_nodes;
  pair<rb_tree_node*,int> c_node;
  int c_level;

  c_level = r_level;
  l_nodes.insert(l_nodes.end(), pair<rb_tree_node*,int>(x, r_level));

  while (!l_nodes.empty())
    {
      c_node = *(l_nodes.begin());

      if (c_level < c_node.second)
	{
	  cout << endl;
	  c_level = c_node.second;
	}

      cout << "(" << c_node.first->key << "," 
	   << ((c_node.first->color == RB_RED) ? "R" : "B");

      if (c_node.first->p == T_nil)
	cout << ",ROOT) ";
      else
        cout << ",P:" << c_node.first->p->key << ") ";

      if (c_node.first->left != T_nil)
	l_nodes.insert(l_nodes.end(), pair<rb_tree_node*,int>(c_node.first->left, 
							      c_node.second+1));
      if (c_node.first->right != T_nil)
	l_nodes.insert(l_nodes.end(), pair<rb_tree_node*,int>(c_node.first->right, 
							      c_node.second+1));
      l_nodes.erase(l_nodes.begin());
    }

  cout << endl;
} /*>>>*/

void rb_tree::remove_all(rb_tree_node* x)
{ /*<<<*/
/*
 * recursively remove all tree elements
 */
  if (x != T_nil)
    {
      remove_all(x->left);
      remove_all(x->right);

      delete x;
    }
} /*>>>*/

// question 2: modified inorder tree walk method to save the sorted numbers in the first argument: int* array.
int rb_tree::convert(int* array, int n)
{
    int i=0;
    rb_tree_node* T_node = T_root;    
    inorder_tree_walk(T_node,array,i);      // inorder_tree_walk(T_node,array,i) is called to traverses the tree (using recursion) in order
                                            // to copy its elements back to an array, in a sorted ascending order.
    for (int j = i; j < n; j++) {
        array[j] = 0;  // set the remaining elements to some default value (e.g., 0)
    }
    return i;               // returning the n' number of elements copied into the array (i.e. original size of the array - no. of duplicates)
}

void rb_tree::inorder_tree_walk(rb_tree_node* T_node,int* array,int& i)
{
   if(T_node!= T_nil)
   {
      inorder_tree_walk(T_node->left,array,i);
      array[(i)] = T_node->key;
      i = i + 1;
      inorder_tree_walk(T_node->right,array,i);
   }
}


//question 4: A test function for red-black trees to count the number of black nodes on the path to the leaves.
int rb_tree::check_black_height()
{
  rb_tree_node* T_node = T_root;
  get_black_nodes(T_node,countBlackNodes);      // using recursion to get the countBlackNodes value
  return rb_tree::countBlackNodes;
}

void rb_tree::get_black_nodes(rb_tree_node* T_node, int countBlackNodes)
{
    if(T_node == T_nil)
      return;
   
    get_black_nodes(T_node->left,countBlackNodes);
    if(T_node->color == RB_BLACK)
    {
      rb_tree::countBlackNodes++;
    }
    get_black_nodes(T_node->right,countBlackNodes);
}



