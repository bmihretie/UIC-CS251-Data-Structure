
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "bstt.h"


using namespace std;



int main()
{
bstt<int, int>  tree;
int key;
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
tree.insert(30,30);
tree.insert(15,15);
tree.insert(50,50);
tree.insert(70,70);
tree.insert(60,60);
tree.insert(15,10);
tree.insert(8,8);
tree.insert(25,25);
tree.insert(20,20);
tree.insert(28,28);
tree.insert(28,29);
	
/*alternative insert code 
//
//   int    k;
//   cout << "Enter a key to insert into tree (0 to stop inserting)> ";
//   cin >> k;
//   while (k > 0)
//   {
	  
//     tree.insert(k, k); 
// 	//cout << " Size: " << tree.size() << endl;
//     cout << "Enter a key to insert into tree (0 to stop inserting)> ";
//     cin >> k;
	  
//   }
	
// //  tree.clear();
*/

//test #7 key value operator test
cout << "Checking the ***Key value operator***expecting 28: " << tree[28] << endl;
cout << "Checking the ***Key value operator***expecting 15: " << tree[15] << endl;
cout << "Checking the ***Key value operator***expecting 60: " << tree[60] << endl;
cout << "Checking the ***Key value operator***expecting 30: " << tree[30] << endl;
cout << endl;


//test #8 next right key operator test
cout << "Checking the the *** Next right Key*** operator 8*15:  " << tree(8) << endl;
cout << "Checking the the *** Next right Key*** operator 15*25: " << tree(15) << endl;
cout << "Checking the the *** Next right Key*** operator 25*28: " << tree(25) << endl;
cout << "Checking the the *** Next right Key*** operator 20*25: " << tree(20) << endl;
cout << "Checking the the *** Next right Key*** operator 28*30: " << tree(28) << endl;
cout << "Checking the the *** Next right Key*** operator 30*50: " << tree(30) << endl;
cout << "Checking the the *** Next right Key*** operator 50*70: " << tree(50) << endl;
cout << "Checking the the *** Next right Key*** operator 60*70: " << tree(60) << endl;
cout << "Checking the the *** Next right Key*** operator 70*0:  "  << tree(70) << endl;

// cout << endl;

  
tree.begin();

   while(tree.next(key)){

		cout  << key << " ";
	}
	

  cout << " Size: " << tree.size() << endl;
 
  /*test #9 copy fucntion test
  bstt<int, int>  copyTree(tree);
  copyTree.begin();

   while(copyTree.next(key)){

		cout  << key  << " ";
	}
	
//   cout << endl;
  cout << " The Size of the copied tree is : " << copyTree.size() << endl;
  cout << endl;
 */
 //tree._inorder(output,Root);
tree.dump(cout);
 /*test 10 dump fucntion test
 tree.dump(cout);
 tree.inorder(output,Root);
	
*/
	
//test 11 memory leakage test
  //tree.clear();
//   cout << "After clear:" << endl;
//   cout << " Size: " << tree.size() << endl;
  
 
 //*/
  return 0;
	
}
