#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "avlt.h"

using namespace std;


int main()
{
  avlt<int, int>  avl;
  //avltree<int, int,int>  avl1;
  int    k;
  //int key;
	
  //avlt<int, int>  tree;
   // int key;
//tree.insert(30,1);
//int x = 15; 
//bool isthere = tree.search(30, x); 
//cout << "X should be 1, equals " << x << endl; 

//test #2
//tree.insert(5,2);
//tree.insert(4,3);
//tree.insert(2,4);

//test #3
// tree.insert(2,5);
// //tree.insert(15,6);
// tree.insert(4,7);
// tree.insert(5,8);
	
//test # 4
//
// tree.insert(10,5);
// //tree.insert(15,6);
// tree.insert(8,7);
// tree.insert(9,8);
// tree.insert(7,8);
// 
// test #5
// tree.insert(10,5);
// //tree.insert(15,6);
// tree.insert(6,7);
// tree.insert(9,8);
// tree.insert(8,8);
// tree.insert(2,8);

//test #6
// avl.insert(30,30);
// avl.insert(15,15);
// avl.insert(50,50);
// avl.insert(70,70);
// avl.insert(60,60);
// avl.insert(15,10);
// avl.insert(8,8);
// avl.insert(25,25);
// avl.insert(20,20);
// avl.insert(28,28);
// avl.insert(28,29);
	
// //test #8 next right key operator test
// cout << "Checking the the *** Next right Key*** operator 8*15:  " << avl(8) << endl;
// cout << "Checking the the *** Next right Key*** operator 15*25: " << avl(15) << endl;
// cout << "Checking the the *** Next right Key*** operator 20*25: " << avl(20) << endl;
// cout << "Checking the the *** Next right Key*** operator 25*28: " << avl(25) << endl;
// //cout << "Checking the the *** Next right Key*** operator 20*25: " << tree(20) << endl;
// cout << "Checking the the *** Next right Key*** operator 28*30: " << avl(28) << endl;
// cout << "Checking the the *** Next right Key*** operator 30*50: " << avl(30) << endl;
// cout << "Checking the the *** Next right Key*** operator 50*70: " << avl(50) << endl;
// cout << "Checking the the *** Next right Key*** operator 60*70: " << avl(60) << endl;
// cout << "Checking the the *** Next right Key*** operator 70*0:  "  << avl(70) << endl;
//  cout << endl;
	

// cout << "copy constructor" << endl;
	
// avlt<int, int>  tree(avl);	
// tree.begin();

//    while(tree.next(key)){

// 		cout  << key << " ";
// 	}
	
  //int    k1;
  //int    k2;
  
  //int distance = 0;

//   cout << "Enter a key to insert into tree (0 to stop inserting)> ";
//   cin >> k;
  

//   while (k > 0)
//   {
//     avl.insert(k, k);
// 	   //cout << endl;
// 	   cout << "Size: " << avl.size() << endl;
// 	   cout << "Height: " << avl.height() << endl;
// 	   avl.dump(std::cout);
// 	   cout << endl;
//        //cout << "Distance: " << avl.distance(10,30) << endl; 
// 	  //distance = avl.distance(100,300);
//     cout << "Enter a key to insert into tree (0 to stop inserting)> ";
//     cin >> k;
//   }

//   
// test for range search  
avl.insert(30,30);
avl.insert(60,60);
avl.insert(80,80);
avl.insert(40,40);
avl.insert(50,50);
avl.insert(20,20);
avl.insert(10,10);

  
// 	//tree.insert(30,1);
// int x = 15; 
// bool isthere = avl.search(30, x); 
// cout << "X should be 1, equals " << x << endl; 
	//avl.search(100,100);
// //avlt<int, int>  avl2;
// avlt<int, int>  avl2(avl);
// cout << "Copy size: " << avl2.size();
//avl2.dump(cout);
//avl2.begin();

//    while(avl2.next(key)){

// 		cout  << key  << " ";
// 	}
//cout << "Copy size: " << avl2.size() << endl;
//avl2.dump(std::cout);
// cout << "Checking the ***Key value operator***expecting 28: " << avl[28] << endl;
// cout << "Checking the ***Key value operator***expecting 15: " << avl[15] << endl;
// cout << "Checking the ***Key value operator***expecting 60: " << avl[60] << endl;
// cout << "Checking the ***Key value operator***expecting 30: " << avl[30] << endl;
// cout << endl;
//   cout << endl;
  vector <int> keys;
	//int i = 0;
  keys = avl.range_search(12,100);
  cout << keys.size();
  cout << endl;
  for (size_t i = 0; i < keys.size(); i++){
	  cout << keys[i] << " ";
	  //i++;
	  
  }
  
  cout << endl;
	
 
	
//  avl.clear();
  
//   cout << "After clear:" << endl;
//   cout << " Size: " << avl.size() << endl;
//   cout << " Height: " << avl.height() << endl;

	
  
  return 0;
	
};
