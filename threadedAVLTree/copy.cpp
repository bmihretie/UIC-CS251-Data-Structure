/*avlt.h*/

//
// Threaded AVL tree
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
  
  
  void _inorder(ostream& output, NODE* cur) const
  {
  
// 	   if (cur == nullptr)
		   
// 	   else
// 	   {

// 		  _inorder(output,cur->Left);
// 		  output<< "(" << cur->Key << "," << cur->Value << "," << cur->Height << ")" << " " << endl;
// 		  _inorder(output,cur->Right);



// 		 if (cur->isThreaded){
		 
// 		 return;
// 		 }
// 		   //return;
// 		 else{
// 		 _inorder(output, cur->Left);
// 		 cout << "(" << cur->Key << "," << cur->Value << "," << cur->Height << ")" << " " << endl;
// 		 }
		 
// 	   }
  
     if (cur == nullptr)
         return;
	 
     else
     { 
	    
	     //if the node is threaded and THREAD denotes the next inorder key, output  (key,value,THREAD) 
		if(cur->isThreaded && cur->Right != nullptr){
		
			  _inorder(output, cur->Left);
			  output << "(" << cur->Key << "," << cur->Value << "," << cur->Height << ")" << " ";
			  //output << "(" << cur->Key << "," << cur->Value << "," << cur->Right->Key << ")" << endl;

		 }
		 
		//if the node is not threaded OR thread==nullptr, output (key,value) 
		else {
		
			 _inorder(output,cur->Left);
			 //output << "(" << cur->Key << "," << cur->Value << ")" << endl;
			 output << "(" << cur->Key << "," << cur->Value << "," << cur->Height << ")" << " ";
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
  // _RightRotate
  // _LeftRotate
  //
  // Rotates the tree around the node N, where Parent is N's parent.  Note that
  // Parent could be null, which means N is the root of the entire tree.  If 
  // Parent denotes a node, note that N could be to the left of Parent, or to
  // the right.  You'll need to take all this into account when linking in the
  // new root after the rotation.  Don't forget to update the heights as well.
  //
  void _RightRotate(NODE* Parent, NODE* N)
  {
    assert(N != nullptr);  // pre-conditions: N and L must exist
    assert(N->Left != nullptr);

    //assigning pointers and repositioning the tree
    NODE* L = N->Left;
    NODE* B = L->Right;
	//NODE* C = N->Right;
	

    N->Left = B;
    L->Right = N;
// 	//new code
// 	if(C == NULL){
// 	 N->Right = Parent;
//      N->isThreaded = true;
// 	}
	
// 	else {
// 	 C->Right = Parent;
//      C->isThreaded = true;
// 	 C->isThreaded = false;
	
// 	}
    
   //updating or linking the root and the new sub tree of L
    if(Parent == NULL){
       
       Root = L;
	  // L->isThreaded = false;
       
       }
       
    else if(L->Key < Parent->Key){ // is the right rotated key less than the parent key?
       
        Parent->Left = L;
		//Parent->isThreaded = true;
       
       }
       
    else{
       
       Parent->Right = L;
	   L->isThreaded = false;
// 	   if(N->Right == NULL)
// 	     N->isThreaded = false;
// 	   else 
// 	   N->isThreaded = true;
// 	   N->Right = Parent;
    }
   
   
   //updating the height of the N sub tree
    int hL = (N->Left == NULL) ? -1 : N->Left->Height;
	int hR = (N->Right == NULL || N->Right->isThreaded) ? -1 : N->Right->Height;
	N->Height = 1 + std::max(hL,hR); 
	
	//updating the height of the L sub tree
	int lL = (L->Left == NULL) ? -1 : L->Left->Height;
	//int lR = (L->Right== NULL) ? -1 : L->Right->Height;
	int lR = (L->Right== NULL || L->Right->isThreaded) ? -1 : L->Right->Height;
	L->Height = 1 + std::max(lL,lR);
	

    
  } // end of right rotate function
  
  
  //Left rotate function
  void _LeftRotate(NODE* Parent, NODE* N)
  {
    assert(N != nullptr);  // pre-conditions: N and R must exist
    assert(N->Right != nullptr);
    
    //Assigning pointers and repostioning the tree by left rotatioin
    NODE* R = N->Right; 
    NODE* B = R->Left;
    N->Right = B;
    R->Left  = N;
    
    //updating or linking the root and the new sub tree of R
    if(Parent == NULL){
       
       Root = R;
       
       }
       
    else if(Parent->Key > R->Key){ // is the left rotated key less than the parent key?
       
        Parent->Left = R;
        //R->isThreaded = true;
       
       }
       
    else{
       
       Parent->Right = R;
	   R->isThreaded = true;
       
    }
   
    //updating the height of the N sub tree
	int hL = (N->Left == NULL) ? -1 : N->Left->Height;
	int hR = (N->Right == NULL || N->Right->isThreaded) ? -1 : N->Right->Height;
// 	int hR = (N->Right == NULL || N->isThreaded) ? -1 : N->Right->Height;
	N->Height = 1 + std::max(hL,hR); 
	
	//updating the height of the r sub tree
	int rL = (R->Left == NULL) ? -1 : R->Left->Height;
	int rR = (R->Right== NULL || R->Right->isThreaded) ? -1 : R->Right->Height;
// 	int rR = (R->Right== NULL || R->isThreaded) ? -1 : R->Right->Height;
	R->Height = 1 + std::max(rL,rR);
	

  } //  end of Left Rotate function

//the functions which fixes avl tree when it is broken
void _rotateToFix(NODE* Parent, NODE* N){
	
	assert(N != nullptr);
	
	int hL = (N->Left == nullptr) ? -1 : N->Left->Height;
	//int hR = (N->Right == nullptr || N->Right->isThreaded) ? -1 : N->Right->Height;
	int hR = (N->Right == nullptr || N->isThreaded) ? -1 : N->Right->Height;
	
	assert(std::abs(hL - hR) > 1); //check if avl broken  or if  the height difference is 2
	
	
	if(hL > hR){ //leaning to the left 
	
		int hll = (N->Left->Left == nullptr) ? -1 : N->Left->Left->Height;
		//int hlr = (N->Left->Right == nullptr || N->Left->Right->isThreaded) ? -1 : N->Left->Right->Height;
		//int hlr = (N->Left->Right == nullptr || N->isThreaded) ? -1 : N->Left->Right->Height;
		//int hlr = (N->Left->Right == nullptr) ? -1 : N->Left->Right->Height;
	    int hlr = (N->Left->Right == nullptr || N->Left->isThreaded) ? -1 : N->Left->Right->Height;
	
		if(hll > hlr){ // far left(casee 1) , rotate to the right
		
			 _RightRotate(Parent, N);
		
		}
		
		else { // middle left (case 2) , do double rotation
			
				 _LeftRotate(N, N->Left);
				 _RightRotate(Parent, N);
			
		}
		
	
	}// end of left leaning rotation
	
	
	else{ // right leaning
	
		
	    int hrl= (N->Right->Left == nullptr) ? -1 : N->Right->Left->Height;
	    int hrr = (N->Right->Right== nullptr || N->Right->isThreaded) ? -1 : N->Right->Right->Height;
		//int hrr = (N->Right->Right== nullptr || N->isThreaded) ? -1 : N->Right->Right->Height;
	
		if(hrr > hrl){ // middle right (case 3), rotate to the left
		
			_LeftRotate(Parent, N);
			
		}
		
		else { // far right (case 4 ) , do double rotation
				
				_RightRotate(N, N->Right);
			    _LeftRotate(Parent, N);
			
			}

	}// end of right leaning rotation

} // right rotate fix function

 //
 //_postorder_del:
 //
 // traverse a post order traversal and free meomory until the root become null
 // it's a helper function for destructor to free the memory allocated
void _postorder_del(NODE* cur){

if (cur == nullptr)
     return;
   else
   {
     _postorder_del(cur->Left);

     if (cur->isThreaded)
       return;
     else
       _postorder_del(cur->Right);

     delete cur;
   }


// 	if(cur == NULL)
// 		return;
		

// 	else {
	     
// 		 //if cur is not threaded delete recursively left and right since we can have nodes
// 		 //on both left and right
//          if(!(cur->isThreaded)){
		 
// 			 _postorder_del(cur->Left);
// 			 _postorder_del(cur->Right);
			 
// 		  }
		 
// 		 //if cur is threaded we don't have cur->right we use dvantage of threaded and 
// 		 //delte only Left 
// 		 else {
			 
// 			 _postorder_del(cur->Left);
		 
// 		 }
		 
// 	//finally delete the root		
// 	delete cur;	
	
// 	}
}

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
  }

  //
  // copy constructor
  //
  // NOTE: makes an exact copy of the "other" tree, such that making the
  // copy requires no rotations.
  //
  avlt (const avlt& other)
  {
    //
    // TODO
    //
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
  virtual ~avlt()
  {
    //
    // TODO
    //
    clear(); //deletes all and free any resources/ memory uysed by the tree
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
    //
    // TODO:????????????????????
    
    clear(); //deletes all and free any resources/ memory uysed by the tree
	
	_copytree(other.Root); //calling copy helper function for deep copy
	
    
	return *this;
	
  }

  //
  // clear:
  //
  // Clears the contents of the tree, resetting the tree to empty.
  //
  void clear()
  {
    //
    // TODO
    //
    //Clears the contents of the tree using postorder delete traversal
    _postorder_del(Root);
	
	// Re-initialize root pointer and size to "empty":
    Root = nullptr;
    Size = 0;
    
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
  }

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
    //
    // TODO
    //
    
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
	
   
  }

  //
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

    //
    // TODO
    //

    return keys;
  }

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
    //
    // TODO
    //
     
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
   
   
    // 5. walk back up tree using stack and update heights.
    //
    while (!nodesStack.empty())
    {
      cur = nodesStack.top();
	  nodesStack.pop();
	  
	  int hL = (cur->Left == nullptr) ? -1 : cur->Left->Height;
      int hR = ((cur->Right == nullptr) || (cur->isThreaded)) ? -1 : cur->Right->Height;
      int hCur = 1 + std::max(hL, hR);

      if (cur->Height == hCur){ // didn't change, so no need to go further:
	  
		  break;
	  
	  } 
        
      else if (std::abs(hL - hR ) <=1){// height changed, update and keep going:
	  
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
	  
    }// end of while

   
    return;

  }

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
    //
    // TODO
    //use the serach function to search the tree, if the key is found
	// return the corresponding value and bool == true
    ValueT value;
    if(search(key,value) == true)
		return value;
		
     //if the key is not found, the default value ValueT{} is returned.
	 return ValueT{ };

    }

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
    //
    // TODO
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
	
  }

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
    //
    // TODO
    //

    return -1;
  }

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
    //
    // TODO
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
	
  }

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
    // TODO
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

  }

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
    //

    //
    // TODO
    _inorder(output,Root); //inordertraversal helper function to dump the contents of tree
    output << endl;
    output << "**************************************************" << endl;
  }
	
};

