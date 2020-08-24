 // copy constructor
  //
  // NOTE: makes an exact or deep copy of the "other" hash table
  //
  graph(const graph& other)
  {
    
   this->N = other.N;
   this->adjList = new list[other.N];
   
   //making a deep copy of index array
   for(int i = 0; i < other.N; i++){
   
	    if (other.list[i].ContainsData){
		
			this->adjList[i] = other.adjList[i];
		
		}
		
   } // end of for loop
   
  }// end of copy constructor
  
  
  
  //
  // operator =
  //
  // Clears "this" hashtable and then makes a copy of the "other" hashtable.
  //
  graph& operator=(const graph& other)
  {
		delete[] this->adjList; //deletes all and free any resources/ memory uysed by the hash table
		N = 0;
		
		this->N = other.N;
		this->adjList = new  list[other.N];
	   
  
	    // make a deep copy of the indexed array
		for(int i = 0; i < other.N; i++){
		
			if (other.adjList[i].ContainsData){

				this->adjList[i] = other.adjList[i];

			}
			
		} // end of for loop
   
	
	return *this;
	
  } // end of hashmap&operator
  
  
  
  
  //
  // constructor: N is the size of the underlying hash table
  //
  graph(int N)
  {
    this->N = N;
    this->adjList = new list[N];
  }
  
  
  //
  // destructor
  //
  virtual ~graph()
  {
    delete[] this->adjList;
  }

  