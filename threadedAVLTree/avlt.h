



/*avlt.h*/

//
//<< Birhanu Mihretie >>
// U. of Illinois, Chicago
// CS 251: Spring 2020
// Project #05: Threaded AVL: avlt<KeyT, ValueT>  

//
//  Threaded AVL: avlt<KeyT, ValueT>:
//  A threaded AVL takes advantage of the observation that half the pointers in a tree are nullptr;
//  that’s a lot of wasted space. Instead, we re-use theright pointers as follows: if that pointer is nullptr,
//  we re-use as a thread to the next inorder key; see the dashed links below. Threads make it possible to 
//  traverse a tree in key order without recursion or a stack. So, in this project, it is implmented a threaded
//  binary search tree to store the (key,value0 pairs in a thredaed manner). And when we use inorder traveral or insert
//  or serach and dump we took the advantage of threaded AVL. This project also includes rotation of the avl tree 
//  when the balance factor of AVL > 1 or < -1.Once tthe AVL is broken we will fix it inside insert fucntion by calling the
//  Right rotation and Left Rotation based on the four cases of avl Rotation. We also fix the height once we fix the rotation.
//  The project also includes a range search function to output the keys in the range of upper and lower keys.
//  
//

#pragma once

#include <iostream>
#include <algorithm>  // std::max
#include <cstdlib>    // std::abs
#include <stack>
#include <vector>
#include <cassert>

using namespace std;

template<typename KeyT, typename ValueT>
class avlt
{
private:
  struct NODE
  {
    KeyT   Key;
    ValueT Value;
    NODE*  Left;
    NODE*  Right;
    bool   isThreaded; // true => Right is a thread, false => non-threaded
    int    Height;     // height of tree rooted at this node
  };

  NODE* Root;  // pointer to root node of tree (nullptr if empty)
  int   Size;  // # of nodes in the tree (0 if empty)
  NODE* leftMost; //the far left begin key which is the start key for inorder traversal
  
  
  //
  // _insertHelper for copy constructor with out rotation
  //
  // Inserts the given (key, value) pair into the tree; if the key has 
  // already been inserted then the function returns without changing 
  // the tree.
  //
 void _insertHelper(KeyT key, ValueT value)
  {
   
    NODE* prev = nullptr;
    NODE* cur = Root;
	
	//
    // stack the nodes we visit so we can walk back up
    // the search path later, adjusting heights:
    //
    stack<NODE*> nodesStack;

    //
    // 1. Search to see if tree already contains key:
    //
    while (cur != nullptr)
    {
	  prev = cur; // updating the root
	  
      if (key == cur->Key)  // if the key is already in tree don't duplicate or overwrite
		   return;
		   
	  nodesStack.push(cur);  // stack so we can return later:
		
       
      if (key < cur->Key)  // if the key is less than cur->Key search onleft subtree:
		cur = cur->Left;
		
      else // check on the right subtree and check if it is threaded or not
      {
		  
		if(cur->isThreaded)
			 cur = nullptr;
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
	newNode->Height = 0;

    //
    // 3. link in the new node:
    //
    // NOTE: cur is null, and prev denotes node where
    // we fell out of the tree.  if prev is null, then
    // the tree is empty and the Root pointer needs 
    // to be updated.
    //
    if (prev == nullptr)
      Root = newNode; //newNode becomes the root	 
	  
    else if (key < prev->Key){
	
      newNode->Right = prev; //set it for threaded purpose and traversal
      prev->Left = newNode; //set the new node to become the Root->Left
	
	}
	  
    else { //if key > prev->Key
		
	  newNode->Right = prev->Right;
	  prev->Right = newNode; //set the new node to become the Root->Right
	  prev->isThreaded = false; //prev is not threaded now
	  
    }
  
    // 
    // 4. update size:
    //
   Size++;
   
   
    // 5. walk back up tree using stack and update heights.
    //
    while (!nodesStack.empty())
    {
      cur = nodesStack.top();
	  nodesStack.pop();
	  
	  int hL = (cur->Left == nullptr) ? -1 : cur->Left->Height;
      int hR = ((cur->Right == nullptr) || (cur->isThreaded)) ? -1 : cur->Right->Height;
      int hCur = 1 + std::max(hL, hR);

      if (cur->Height == hCur)// didn't change, so no need to go further:
		  break;
	 
      else if (std::abs(hL - hR ) <=1){// height changed, update and keep going:
	  
		   cur->Height = hCur;
	      
	  } 
    
      
    }// end of while loop


    
  } // end of insertHelper method
  
  
  
  //helper method for dump inorder traversal of the tree
  void _inorder(ostream& output, NODE* cur) const
  {

     if (cur == nullptr)
         return;
	 
     else
     { 
	    
	     //if the node is threaded and THREAD denotes the next inorder key, output  (key,value,THREAD) 
		if((cur->isThreaded == true) && (cur->Right != nullptr )){
		
			  _inorder(output, cur->Left);
			  output << "(" << cur->Key << "," << cur->Value << "," << cur->Height <<  "," << cur->Right->Key << ")" << endl;
			  
		 }
		 
	
		//if the node is not threaded OR thread==nullptr, output (key,value) 
		else {
		     
			 _inorder(output,cur->Left);
			 output << "(" << cur->Key << "," << cur->Value << "," << cur->Height << ")" << endl;
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
	
	 _insertHelper(cur->Key, cur->Value);
	_copytree(cur->Left);
		
	  //check on the right subtree if it is threaded or not 
		if(cur->isThreaded)
			 cur = nullptr;
		else
			_copytree(cur->Right);
			
			
     }
	 
	
} // end of copytree method



  //
  // _RightRotate
  //
  // Rotates the tree around the node N, where Parent is N's parent.  Note that
  // Parent could be null, which means N is the root of the entire tree.  If 
  // Parent denotes a node, note that N could be to the left of Parent, or to
  // the right.we take all this into account when linking in the new root after 
  // the rotation.  The function also update the heights after the rotation.
  //
  void _RightRotate(NODE* Parent, NODE* N)
  {
	 // check if the pre-conditions: N and L exists
     assert(N != nullptr); 
     assert(N->Left != nullptr);

    //label the components for right rotation
     NODE* L = N->Left;
	 NODE* A = L->Left;
     NODE* B = L->Right;
	 NODE* C = N->Right;
	
	//Rotate the tree to the right
	 L->Right = N;
	 L->Left = A;
	 N->Right = C;
	 N->Left = B;
	 
	 if(L->isThreaded)
		 N->Left = NULL;
		 
	 L->isThreaded = false;
	
    
   //updating or linking the root and the new sub tree of L
    if(Parent == NULL) //when parent is null
       Root = L;  
	   
    else if(L->Key < Parent->Key) // is the right rotated key less than the parent key?
        Parent->Left = L;
		
    else
       Parent->Right = L;

   //updating the height of the N sub tree
    int hL = (N->Left == NULL) ? -1 : N->Left->Height;
	int hR = (N->Right == NULL || N->isThreaded) ? -1 : N->Right->Height;
	N->Height = 1 + std::max(hL,hR); 
	
	//updating the height of the L sub tree
	int lL = (L->Left == NULL) ? -1 : L->Left->Height;
	L->Height = 1 + std::max(lL,N->Height);
	
	
  } // end of right rotate method
  
  
  
  //
  // _LeftRotate
  //
  // Rotates the tree around the node N, where Parent is N's parent.  Note that
  // Parent could be null, which means N is the root of the entire tree.  If 
  // Parent denotes a node, note that N could be to the left of Parent, or to
  // the right. we take all this into account when linking in the
  // new root after the rotation. The function also update the heights after the rotation.
  void _LeftRotate(NODE* Parent, NODE* N)
  {
    // check if the pre-conditions: N and R exists
    assert(N != nullptr);  
    assert(N->Right != nullptr);
    
    //label the components for left rotation
    NODE* R = N->Right; 
    NODE* B = R->Left;
	NODE* A = N->Left;
	NODE* C = R->Right;
	
	//Rotate the tree to the left
    N->Right = B;
    R->Left  = N;
	R->Right = C;
	N->Left = A;
	
	if(A == nullptr)
		N->Left = NULL;
		
   if(B == nullptr){
	    N->Right = R;
		N->isThreaded = true;
	}	
	
    //updating or linking the root and the new sub tree of R
    if(Parent == nullptr)
       Root = R;
	  
    else if(Parent->Key > R->Key) // is the left rotated key less than the parent key?
        Parent->Left = R;
       
    else
       Parent->Right = R;
	 
    //updating the height of the N sub tree
	int hL = (N->Left == NULL) ? -1 : N->Left->Height;
	int hR = (N->Right == NULL || N->isThreaded) ? -1 : N->Right->Height;
	N->Height = 1 + std::max(hL,hR); 
	
	//updating the height of the R sub tree
	
    int rR = (R->Right== NULL || R->isThreaded) ? -1 : R->Right->Height;
	R->Height = 1 + std::max(N->Height,rR);
	

  } //  end of Left Rotate method
  
  
  
//the functions which fixes avl tree when it is broken or the the avl balance factor
//is > 1 or < -1. this fucntion uses two helper methods right and left rotation 
void _rotateToFix(NODE* Parent, NODE* N){
	
	assert(N != nullptr);
	
	int hL = (N->Left == nullptr) ? -1 : N->Left->Height;
	int hR = (N->Right == nullptr || N->isThreaded) ? -1 : N->Right->Height;
	
	assert(std::abs(hL - hR) > 1); //check if avl broken by using balance factor
	
	
	if(hL > hR){ //leaning to the left 
	
		int hll = (N->Left->Left == nullptr) ? -1 : N->Left->Left->Height;
	    int hlr = (N->Left->Right == nullptr || N->Left->isThreaded) ? -1 : N->Left->Right->Height;
	
		if(hll > hlr){ // far left(casee 1) , rotate to the right
		
			 _RightRotate(Parent, N);
		
		}
		
		else { // middle left (case 2) , do double rotation
			
				 _LeftRotate(N, N->Left);
				 _RightRotate(Parent, N);
			
		}
		
	
	} // end of left leaning rotation
	
	
	else{ // right leaning
	
		
	    int hrl= (N->Right->Left == nullptr) ? -1 : N->Right->Left->Height;
	    int hrr = (N->Right->Right == nullptr || N->Right->isThreaded) ? -1 : N->Right->Right->Height;
		
	
		if(hrr > hrl){ // case 4, rotate to the left
		
			_LeftRotate(Parent, N);
			
		}
		
		else { // case 3, do double rotation
				
				_RightRotate(N, N->Right);
			    _LeftRotate(Parent, N);
			
			}

	}// end of right leaning rotation
	

} // end of right rotate fix method



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

// 	if (cur == nullptr)
// 		return;
	 
//    else
//    {
   
// 	_postorder_del(cur->Left);
//      if (!(cur->isThreaded))
// 	  _postorder_del(cur->Right);
	  
//   }
    
//    delete cur;

} // end of postorder delete helper method



public:



  //
  // default constructor:
  //
  // Creates an empty tree.
  //
  avlt()
  {
    Root = nullptr;
    Size = 0;
	leftMost = nullptr;
  }



  //
  // copy constructor
  //
  // NOTE: makes an exact copy of the "other" tree, such that making the
  // copy requires no rotations.
  //
  avlt (const avlt& other)
  {
    
    
    Root = nullptr;
    Size = 0;
	leftMost = nullptr;
   
   _copytree(other.Root); //calling copy helper function for deep copy
    
   this->leftMost= other.leftMost;  // to be safe copy this state as well
 
   
  }



  //
  // destructor:
  //
  // Called automatically by system when tree is about to be destroyed;
  // this is our last chance to free any resources / memory used by
  // this tree.
  //
  virtual ~avlt()
  {
  
   _postorder_del(Root); //deletes all and free any resources/ memory uysed by the tree
   
  }



  //
  // operator=
  //
  // Clears "this" tree and then makes a copy of the "other" tree.
  //
  // NOTE: makes an exact copy of the "other" tree, such that making the
  // copy requires no rotations.
  //
  avlt& operator=(const avlt& other)
  {
    
    
    clear(); //deletes all and free any resources/ memory uysed by the tree
	
	_copytree(other.Root); //calling copy helper function for deep copy
    this->leftMost = other.leftMost;
	
	
	return *this;
	
  } // end of avlt&operator 



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
    leftMost = nullptr;
	
  } //end of clear method



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
	
  } // end of size method



  // 
  // height:
  //
  // Returns the height of the tree, -1 if empty.
  //
  // Time complexity:  O(1) 
  //
  int height() const
  {
  
    if (Root == nullptr)
      return -1;
    else
      return Root->Height;
	  
  } // end of height method
  
  
  
  // 
  // search:
  //
  // Searches the tree for the given key, returning true if found
  // and false if not.  If the key is found, the corresponding value
  // is returned via the reference parameter.
  //
  // Time complexity:  O(lgN) worst-case
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
	
  } // end of search method


  // range_search
  //
  // Searches the tree for all keys in the range [lower..upper], inclusive.
  // It is assumed that lower <= upper.  The keys are returned in a vector;
  // if no keys are found, then the returned vector is empty.
  //
  // Time complexity: O(lgN + M), where M is the # of keys in the range
  // [lower..upper], inclusive.
  //
  // NOTE: do not simply traverse the entire tree and select the keys
  // that fall within the range.  That would be O(N), and thus invalid.
  // Be smarter, you have the technology.
  //
  vector<KeyT> range_search(KeyT lower, KeyT upper)
  {
    vector<KeyT>  keys;
	KeyT   key;
	NODE* cur = Root;
	NODE* prev = nullptr;
	
      //if the root is nullptr return empty vector
	  if(Root == nullptr)
		  return keys;
	   //if upper is smaller than lower dont't raverse the tree and return empty vector
	  if(upper < lower)
		  return keys;
		  
	   // a loop which traverses the tree to find the lower keys	  
	  while(cur != nullptr){
	  
		  if(cur->Key == lower) // here we find the lower in the tree
			  break;
			  
		   //update the root for next traversal
			prev = cur;
		   
		  if(lower < cur->Key) //traverse left
			  cur = cur->Left;
			   
		    else { // traverse right
			
				if(cur->isThreaded )
					cur = NULL;
				else
					cur = cur->Right;
		    }
			

			
	   } // end of while loop
	   
	    //we didn't find the key in the tree, then take the next closet number in 
	    //the range which is greater than lower key and smaller than or equal to upper key
	    if(cur == NULL){  
	   
			if(prev->Key > lower)
				leftMost = prev;
				
			else {
			
			  if ((prev->Right != nullptr)  && (prev->Right->Key > lower)) 
					leftMost = prev->Right;
            //here prev < lower, then check if prev parent exist and > lower 
// 			else if ((prev->Right != nullptr)  && (prev->Right->Key > lower)) 
// 					leftMost = prev->Right;
			  else
				return keys;
	         }
	       }
		 
	   //here we find the lower in the tree, then set cur as lower  
	   else 
		 leftMost = cur;
	   

	   //find the range of keys using Next method and push the range of keys
	   //between lower and upper  to the vector	  
		while(next(key)){
		
	      if(key > upper)
			  break;
		  
		  keys.push_back(key);

		}


    return keys;
	

   } // end of range_search method
   
   

  //
  // insert
  //
  // Inserts the given key into the tree; if the key has already been insert then
  // the function returns without changing the tree.  Rotations are performed
  // as necessary to keep the tree balanced according to AVL definition.
  //
  // Time complexity:  O(lgN) worst-case
  //
  void insert(KeyT key, ValueT value)
  {
    
    NODE* prev = nullptr;
    NODE* cur = Root;
	
	//
    // stack the nodes we visit so we can walk back up
    // the search path later, adjusting heights:
    //
    stack<NODE*> nodesStack;

    //
    // 1. Search to see if tree already contains key:
    //
    while (cur != nullptr)
    {
	  prev = cur; // updating the root
	  
      if (key == cur->Key)  // if the key is already in tree don't duplicate or overwrite
		   return;
		   
	  nodesStack.push(cur);  // stack so we can return later:
		
       
      if (key < cur->Key)  // if the key is less than cur->Key search onleft subtree:
		cur = cur->Left;
		
      else // check on the right subtree and check if it is threaded or not
      {
		  
		if(cur->isThreaded)
			 cur = nullptr;
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
	newNode->Height = 0;

    //
    // 3. link in the new node:
    //
    // NOTE: cur is null, and prev denotes node where
    // we fell out of the tree.  if prev is null, then
    // the tree is empty and the Root pointer needs 
    // to be updated.
    //
    if (prev == nullptr)
      Root = newNode; //newNode becomes the root
	 
    else if (key < prev->Key){
	
      newNode->Right = prev; //set it for threaded purpose and traversal
      prev->Left = newNode; //set the new node to become the Root->Left
	
	}
	  
    else { //if key > prev->Key
		
	  newNode->Right = prev->Right;
	  prev->Right = newNode; //set the new node to become the Root->Right
	  prev->isThreaded = false; //prev is not threaded now
	  
    }
  
    // 
    // 4. update size:
    //
   Size++;
   
   
    // 5. walk back up tree using stack and update heights.
    //
    while (!nodesStack.empty())
    {
      cur = nodesStack.top();
	  nodesStack.pop();
	  
	  int hL = (cur->Left == nullptr) ? -1 : cur->Left->Height;
      int hR = ((cur->Right == nullptr) || (cur->isThreaded)) ? -1 : cur->Right->Height;
      int hCur = 1 + std::max(hL, hR);

      if (cur->Height == hCur){ // didn't change, so no need to go further
	  
		  break;
	  
	  } 
        
      else if (std::abs(hL - hR ) <=1){ // height changed, update and keep going:
	  
		   cur->Height = hCur;
	      
	  } 
       
	  // here the avl tree is broken so we need to fix the tree
	  //  by rebalancing and updating heights. To do so call RotateToFix function
	  //  the rotateToFix will call either right or left rotate based on the condition or cases
	  else{
	  
		  if(nodesStack.empty()){
		  
			  _rotateToFix(nullptr,cur); //when the avl is broken at the root the parent to the root will be null
		  
		  }
		  
		  else {
		 
		  
			  _rotateToFix(nodesStack.top(),cur); //if the node is not empty parent equals the top of node element
		  
		  }
	   
	   break;
	  
      
	  }
	  
    } // end of while

    return;
  
    }  // end of insert Method 



  //
  // []
  //
  // Returns the value for the given key; if the key is not found,
  // the default value ValueT{} is returned.
  //
  // Time complexity:  O(lgN) worst-case
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

   

 } // end of ValueT operator[] 



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
  // Time complexity:  O(lgN) worst-case
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
	
  
    } // end of KeyT operator()



  //
  // %
  //
  // Returns the height stored in the node that contains key; if key is
  // not found, -1 is returned.
  //
  // Example:  cout << tree%12345 << endl;
  //
  // Time complexity:  O(lgN) worst-case
  //
  int operator%(KeyT key) const
  {

    NODE* cur = Root;
	//int Height;
	
    while (cur != nullptr)
    {
	  // if the key is already in the tree return by reference the value 
	  // and bool = true
	  if (key == cur->Key){
	  
	       //value = cur->Value; 
		   return cur->Height;
		   //return Height;
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
		
    } //while  
	
	return -1;
	
  }  // end of Height operator%(KeyT key)  
  
  
  
  //
  // begin
  //
  // Resets internal state for an inorder traversal.  After the 
  // call to begin(), the internal state denotes the first inorder
  // key; this ensure that first call to next() function returns
  // the first inorder key.
  //
  // Space complexity: O(1)
  // Time complexity:  O(lgN) worst-case
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
	
  } // end of Begin method
  
  

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
  // Time complexity:  O(lgN) worst-case
  //
  // Example usage:
  //    tree.begin();
  //    while (tree.next(key))
  //      cout << key << endl;
  //
  bool next(KeyT& key)
  {
    //
 
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
	     leftMost  = leftMost->Right;
	     return true;
		 
     } 
	 
  
  } // end of if(leftMost != nullptr)
  
  
  //if we get here there is no inorder key found
  return false;

  } // end of bool Next method
  
  

  //
  // dump
  // 
  // Dumps the contents of the tree to the output stream, using a
  // recursive inorder traversal.
  //
  void dump(ostream& output) const
  {
    output << "**************************************************" << endl;
    output << "********************* AVLT ***********************" << endl;

    output << "** size: " << this->size() << endl;
    output << "** height: " << this->height() << endl;

    //
    // inorder traversal, with one output per line: either 
    // (key,value,height) or (key,value,height,THREAD)
    //
    // (key,value,height) if the node is not threaded OR thread==nullptr
    // (key,value,height,THREAD) if the node is threaded and THREAD denotes the next inorder key
  
    _inorder(output,Root); //inordertraversal helper function to dump the contents of tree
    output << "**************************************************" << endl;
  } // end of dump method
  
	
}; // end of the class avlt

