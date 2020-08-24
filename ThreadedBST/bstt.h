/*bstt.h*/

//
// << Birhanu Mihretie >>
// U. of Illinois, Chicago
// CS 251: Spring 2020
// Project #04: Threaded binary search tree

//
//  Threaded binary search tree:
//  A threaded BST takes advantage of the observation that half the pointers in a tree are nullptr;
//  that’s a lot of wasted space. Instead, we re-use theright pointers as follows: if that pointer is nullptr,
//  we re-use as a thread to the next inorder key; see the dashed links below. Threads make it possible to 
//  traverse a tree in key order without recursion or a stack. So, in this project, it is implmented a threaded
//  binary search tree to store the (key,value0 pairs in a thredaed manner). And when we use inorder traveral or insert
//  or serach and dump we took the advantage of threaded BST. 
//

#pragma once

#include <iostream>

using namespace std;

template<typename KeyT, typename ValueT>
class bstt
{
private:
  struct NODE
  {
    KeyT   Key;
    ValueT Value;
    NODE*  Left;
    NODE*  Right;
    bool   isThreaded;
  };

  NODE* Root;  // pointer to root node of tree (nullptr if empty)
  int   Size;  // # of nodes in the tree (0 if empty)
  NODE* leftMost; //the far left begin key which is the start key for inorder traversal
  


  // 
  // _inorder helper function does the actual inorder traversal and output 
  // to the stream.  
  //
  void _inorder(ostream& output, NODE* cur) const
  {
  
     if (cur == nullptr)
         return;
	 
     else
     { 
	    
	     //if the node is threaded and THREAD denotes the next inorder key, output  (key,value,THREAD) 
		if(cur->isThreaded && cur->Right != nullptr){
		
			  _inorder(output, cur->Left);
			  output << "(" << cur->Key << "," << cur->Value << "," << cur->Right->Key << ")" << endl;

		 }
		 
		//if the node is not threaded OR thread==nullptr, output (key,value) 
		else {
		
			 _inorder(output,cur->Left);
			 output << "(" << cur->Key << "," << cur->Value << ")" << endl;
			_inorder(output,cur->Right);
			
		 }
	
     } // end of the first else 
	 
	 
  } // end of _inorder helper method
  
  
  
  //
  // _copytree:
  //
  // Given a tree, inserts the (key, value) pairs into *this* tree.
  //
  void _copytree(NODE* cur)
  {
  
    if (cur == nullptr)
      return;
	  
    else
    {
      //
      // to copy and build an exact copy, we need to "visit" cur
      // first and insert that (key, value) pair first.  That way
      // all the nodes to the left will properly go to the left,
      // all the node to the right will properly go to the right.
      // In this case we also check if cur is threaded or not 
      // 
	 insert(cur->Key, cur->Value);
	 _copytree(cur->Left);
		
	  //check on the right subtree if it is threaded or not 
		if(cur->isThreaded)
			 cur = nullptr;
		else
			_copytree(cur->Right);
			
     }
	 
	
} // end of copytree function



 //
 //_postorder_del:
 //
 // traverse a post order traversal and free meomory until the root become null
 // it's a helper function for destructor to free the memory allocated
void _postorder_del(NODE* cur){

	if(cur == NULL)
		return;
		

	else {
	     
		 //if cur is not threaded delete recursively left and right since we can have nodes
		 //on both left and right
         if(!(cur->isThreaded)){
		 
			 _postorder_del(cur->Left);
			 _postorder_del(cur->Right);
			 
		  }
		 
		 //if cur is threaded we don't have cur->right we use dvantage of threaded and 
		 //delte only Left 
		 else {
			 
			 _postorder_del(cur->Left);
		 
		 }
		 
	//finally delete the root		
	delete cur;	
	
	}

	

} // end of postorder helper method 


public:
  //
  // default constructor:
  //
  // Creates an empty tree.
  //
  bstt()
  {
    Root = nullptr;
    Size = 0;
  }

  //
  // copy constructor
  //copies the tree using the helper function
  bstt(const bstt& other)
  {
    
   Root = nullptr;
   Size = 0;
   
   _copytree(other.Root); //calling copy helper function for deep copy
   
  } 
  
  
  //
  // destructor:
  //
  // Called automatically by system when tree is about to be destroyed;
  // this is our last chance to free any resources / memory used by
  // this tree.
  //
  virtual ~bstt()
  {
   
   clear(); //deletes all and free any resources/ memory uysed by the tree
   //_postorder_del(Root);
   
  }



  //
  // operator=
  //
  // Clears "this" tree and then makes a copy of the "other" tree.
  //
  bstt& operator=(const bstt& other)
  {
    
    clear(); //deletes all and free any resources/ memory uysed by the tree
	
	_copytree(other.Root); //calling copy helper function for deep copy
	
    
	return *this;
	
  }



  // 
  // size:
  //
  // Returns the # of nodes in the tree, 0 if empty.
  //
  // Time complexity:  O(1) 
  //
  int size() const
  {
  
    return Size;
	
  }



  // 
  // search:
  //
  // Searches the tree for the given key, returning true if found
  // and false if not.  If the key is found, the corresponding value
  // is returned via the reference parameter.
  //
  // Time complexity:  O(lgN) on average
  //
  bool search(KeyT key, ValueT& value) const
  {
   
    NODE* cur = Root;
	
    while (cur != nullptr)
    {
	  // if the key is already in the tree return by reference the value 
	  // and bool = true
	  if (key == cur->Key){
	  
	       value = cur->Value;  
		   return true;
	  }
       
      if (key < cur->Key)  //if the key is less than cur->Key search onleft subtree:
		  cur = cur->Left;
		
      else //check on the right subtree and check it is threaded or not
      {
		  
		if(cur->isThreaded)
			 cur = NULL;
		else
			cur = cur->Right;
      }
		
    }//while  

    // if get here, key is not found return false
	return false;
	
	
  } // end of bool search method
  
  

  //
  // insert
  //
  // Inserts the given key into the tree; if the key has already been insert then
  // the function returns without changing the tree.
  //
  // Time complexity:  O(lgN) on average
  //
  void insert(KeyT key, ValueT value)
  {
    
    NODE* prev = nullptr;
    NODE* cur = Root;

    //
    // 1. Search to see if tree already contains key:
    //
    while (cur != nullptr)
    {
	  prev = cur; // updating the root
	  
      if (key == cur->Key)  // if the key is already in tree don't duplicate or overwrite
		   return;
		
       
      if (key < cur->Key)  // if the key is less than cur->Key search onleft subtree:
		cur = cur->Left;
		
      else // check on the right subtree and check if it is threaded or not
      {
		  
		if(cur->isThreaded)
			 cur = NULL;
		else
			cur = cur->Right;
      }
		
	 
    } // end of while

    //
    // 2. if we get here, key is not in the tree, so allocate
    // a new node to insert:
    // 
    NODE* newNode = new NODE();
    newNode->Key = key;
    newNode->Value = value;
	newNode->isThreaded = true;
    newNode->Left = nullptr;
    newNode->Right = nullptr;

    //
    // 3. link in the new node:
    //
    // NOTE: cur is null, and prev denotes node where
    // we fell out of the tree.  if prev is null, then
    // the tree is empty and the Root pointer needs 
    // to be updated.
    //
    if (prev == nullptr){
	
      Root = newNode; //newNode becomes the root
	  
	}
	  
    else if (key < prev->Key){
	
      newNode->Right = prev; //set it for threaded purpose and traversal
      prev->Left = newNode; //set the new node to become the Root->Left
	
	}
	  
    else { //if key > Root->Key
		
	  newNode->Right = prev->Right;
	  prev->Right = newNode; //set the new node to become the Root->Right
	  prev->isThreaded = false; //prev is not threaded now
	  
    }
  
    // 
    // 4. update size:
    //
   Size++;
   
   
} // end of insert method 

 

  //
  // []
  //
  // Returns the value for the given key; if the key is not found,
  // the default value ValueT{} is returned.
  //
  // Time complexity:  O(lgN) on average
  //
  ValueT operator[](KeyT key) const
  {
    
	//use the serach function to search the tree, if the key is found
	// return the corresponding value and bool == true
    ValueT value;
    if(search(key,value) == true)
		return value;
		
     //if the key is not found, the default value ValueT{} is returned.
	 return ValueT{ };
  
  } // end of ValueT operator method 
  
  

  //
  // ()
  //
  // Finds the key in the tree, and returns the key to the "right".
  // If the right is threaded, this will be the next inorder key.
  // if the right is not threaded, it will be the key of whatever
  // node is immediately to the right.
  //
  // If no such key exists, or there is no key to the "right", the
  // default key value KeyT{} is returned.
  //
  // Time complexity:  O(lgN) on average
  //
  KeyT operator()(KeyT key) const
  {
      NODE* cur = Root;

    //
    // 1. Search to see if tree already contains key:
    //
    while (cur != nullptr)
    {
	
      // if the key is already in tree check if it is threaded or not 
      if (key == cur->Key){  
		     
		if(cur->Right != NULL) { //if it is not threaded and if there is cur-> right key
			
			return cur->Right->Key; 
			
		 }		
		    
		else
			return KeyT{ }; //return the default value

      } // end of if key == cur->Key
	  
	 
	 if (key < cur->Key)  // if the key is less than cur->Key search onleft subtree:
		cur = cur->Left;
		
      else //check on the right subtree and check if it is threaded or not 
      {
		  
		if(cur->isThreaded)
			 cur = NULL;
		else
			cur = cur->Right;
      }
	  
	 } // end of while
	 
    // if we get here return the default key value 
	return KeyT{ };
	
  } // end of KeyT operator method 
  
  

  //
  // begin
  //
  // Resets internal state for an inorder traversal.  After the 
  // call to begin(), the internal state denotes the first inorder
  // key; this ensure that first call to next() function returns
  // the first inorder key.
  //
  // Space complexity: O(1)
  // Time complexity:  O(lgN) on average
  //
  // Example usage:
  //    tree.begin();
  //    while (tree.next(key))
  //      cout << key << endl;
  //
  void begin()
  {
    //if the Root is NULL the leftmost begin key should be null
	if(Root == NULL){
	
		leftMost  = NULL;
		return;
	 }
	 
	 //if the Root->Left is NULL the leftmost begin key should be null
	 if(Root->Left == NULL){
		leftMost  = Root;
		return;
	 }
	 
	NODE* temp = Root; //a pointer for the Root
	//the loop finds us the let most key which will be used as a bgining key for traversal
	while(temp->Left != NULL){ 
	
		temp = temp->Left; // go all the way left
		
	}
	
	//set the first far left key  as begin key and make it  ready for traversal
	leftMost  = temp; 
	
  
  } // end of begin method
  
  

  //
  // next
  //
  // Uses the internal state to return the next inorder key, and 
  // then advances the internal state in anticipation of future
  // calls.  If a key is in fact returned (via the reference 
  // parameter), true is also returned.
  //
  // False is returned when the internal state has reached null,
  // meaning no more keys are available.  This is the end of the
  // inorder traversal.
  //
  // Space complexity: O(1)
  // Time complexity:  O(lgN) on average
  //
  // Example usage:
  //    tree.begin();
  //    while (tree.next(key))
  //      cout << key << endl;
  //
  bool next(KeyT& key)
  {
   
   //check if the far let or begin key is not null
    if(leftMost != nullptr){
	
		key = leftMost->Key; // this start of the first key that we got from begin()
		
		//check if it is not threaded and if there is a key in cur->Right traverse to such key
		if(!(leftMost->isThreaded)){
		
			if(leftMost->Right != nullptr){

			leftMost  = leftMost->Right;
            //if there is a Left->key in the leftMost->Right go all the way left unil it is null 
			//and start getting the next right key
			while(leftMost->Left != nullptr) 
				leftMost  = leftMost->Left;
			}
				
			return true;
			
			} //end of if(!(leftMost->isThreaded) 
	
	else {
	
	    //check if it is threaded and return the next inorder key and bool == true
	    //if(leftMost->isThreaded){
			leftMost  = leftMost->Right;
			return true;
		 //}
		 
// 		else
// 			return false;
	
     } //end of last else
	 
  
  } // end of if(leftMost != nullptr)
  
  
  //if we get here there is no inorder key found
  return false;
  
} // end of bool next method

  
  
  
  //
  // clear:
  //
  // Clears the contents of the tree, resetting the tree to empty.
  //
  void clear()
  {
   
    //Clears the contents of the tree using postorder delete traversal
    _postorder_del(Root);
	
	// Re-initialize root pointer and size to "empty":
    Root = nullptr;
    Size = 0;
	
  } // end of clear method
  
  


  //
  // dump
  // 
  // Dumps the contents of the tree to the output stream, using a
  // recursive inorder traversal.
  //
  void dump(ostream& output) const
  {
    output << "**************************************************" << endl;
    output << "********************* BSTT ***********************" << endl;

    output << "** size: " << this->size() << endl;
	
    //
    // inorder traversal, with one output per line: 
    // (key,value) if the node is not threaded OR thread==nullptr
    // (key,value,THREAD) if the node is threaded and THREAD denotes the next inorder key
    //
     _inorder(output,Root); //inordertraversal helper function to dump the contents of tree
	 
    output << "**************************************************" << endl;
  }
	
};

