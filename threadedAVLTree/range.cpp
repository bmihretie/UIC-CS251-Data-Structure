  
 vector<KeyT> range_search(KeyT lower, KeyT upper)
  {
    vector<KeyT>  keys;
	//ValueT Value;
	//int key;
	KeyT   key;
	NODE* cur = Root;
	NODE* prev = nullptr;
	
	  //If one or both of the keys is not in the tree return -1
// 	  if ((search(lower,Value) == false) && (search(upper,Value) == false)){
	  
// 		 return keys;
// 		 // keys.push_back(0);
// 		 //break;
		
// 	  }
// 	 
	  if(Root == nullptr)
		  return keys;
	 
	  if(upper < lower)
		  return keys;
		  
// 	  NODE* cur = Root;
// 	  NODE* prev = nullptr;
	  //KeyT  commonKey = cur->Key;//updating the the root key when we traverse to the left or right
// 	  KeyT  commonKey = cur->Key;//updating the the root key when we traverse to the left or right
			
		  
	  while(cur != nullptr){ // a loop which gets the final path distance between two keys
	  
	      prev = cur;
		   
		  //if(cur->Key == lower ){
		  if(cur->Key <= lower ){
		  
		  // leftMost = cur;
		   break;
		   //keys.push_back(leftMost->key);
		   //return;
		  
		  }
		  
		  //prev = cur;
// 		  else if(search(lower,Value) == false && prev != nullptr){
		  
// 		   leftMost = prev;
// 		   //keys.push_back(Key);
// 		   //return;
// 		   break;
		  
// 		  }
		   
		   
		   //prev = cur;
		   
		   if(lower < cur->Key)
			   cur = cur->Left;
			   
		    else {
			
				  
				if(cur->isThreaded)
					 cur = NULL;
				else
					cur = cur->Right;
		    }
	   } // end of first while loop
	   
	  
	   //if key one and key two are equal return height equals 0
	   if((lower == upper) && (cur->Key == lower)){
	  
// 	      if(cur->Key == lower){
			  keys.push_back(lower);
		      return keys;
		  }
		  
		  else{
		  
		  //break;
		 keys = {};
		 return  keys; 
		   
		  }
	
// 	  if(lower == upper){
	  
// 	      if(cur->Key == lower)
// 			  keys.push_back(lower);
// 		  return keys;
		  
// 		  }
		  
	  if(cur->Key == lower)
		  leftMost = cur;
		  
	  if(cur->Key <  lower)
		  leftMost = prev;
		  
	 
	  
		while(next(key)){
// 	      if(key > upper)
// 			  break;
		  
		  keys.push_back(key);


		}
	    
   for (size_t i = 0; i < keys.size(); i++){
	  cout << keys[i] << " ";
	  i++;
	  
  }
  

    return keys;
	
  }



vector<KeyT> range_search(KeyT lower, KeyT upper)
  {
    vector<KeyT>  keys;
	ValueT Value;
	
	  //If one or both of the keys is not in the tree return -1
	  if ((search(lower,Value) == false) || (search(upper,Value) == false)){
	  
		 //return 0;
		 // keys.push_back(0);
		 //break;
		
	  }
	  
	  
	  //if key one and key two are equal return height equals 0
	  if(lower == upper){
	  
		  keys.push_back(lower);
		  
		  }
		  
		  
	  NODE* cur = Root;
	  KeyT  commonKey = cur->Key;//updating the the root key when we traverse to the left or right
			
		  
	  while(cur != nullptr){ // a loop which gets the final path distance between two keys
	      
		  // if the key one and two are in opposite direction, traverse and calculate each path distance
		  // if((lower <= commonKey && upper >= commonKey) ||
		   // (lower >= commonKey && upper <= commonKey)){
		  if((lower <= commonKey && upper >= commonKey)){
		  
// 			  int lowerRange = _RangeHelper(cur,lower); //find the length or the distance for key one
// 			  keys.push_back(lowerRange);
// 			  int upperRange =  _RangeHelper(cur,upper);// find the length or distance for the second key
			  //keys.push_back(upperRange);
			  while(lower <= commonKey && upper >= commonKey))
			  
			 // return _pathFindeHelper(cur,k1) +  _pathFindeHelper(cur,k2); // return the sum of the disatnce of two keys
			  
		  }
	  
	      //check if both keys are to the left of the root, then update the root to the lower common ancestor
	      //then keep it ready for the loop to find the path length of the two keys
		  if(lower < commonKey && upper < commonKey){ 
		  
			  cur = cur->Left;
			  commonKey = cur->Key;//updating the root key

		  }
	  
	      //check if both keys are to the left of the root, then update the root to the lower common ancestor
	      //then keep it ready for the loop to find the path length of the two keys
		  else if(lower > commonKey && upper > commonKey){
		  
			  cur = cur->Right; 
			  commonKey = cur->Key; //updating the root key
			  
		  }
	  
      }
    

    return keys;
	
  }