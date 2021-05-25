/*
 * testAVLTree.cpp
 *
 *  Created on: 19 ���� 2013
 *      Author: shirel
 */

#include "AVL_tree.h"
#include <vector>
#include <ostream>
#include <random>
#include <chrono>
#include <algorithm>

int main(){
	AVLTree<int> tree;

	//Specific Cases

	/*correct output for the four next cases
	1 BF: 0 Height: 0
	2 BF: 0 Height: 1
	3 BF: 0 Height: 0 */

	//basic LL root change
	tree.insert(3);
	tree.insert(2);
	tree.insert(1);
	tree.display();
	tree.clear();

	//basic LR root change
	tree.insert(3);
	tree.insert(1);
	tree.insert(2);
	tree.display();
	tree.clear();

	//basic RR root change
	tree.insert(1);
	tree.insert(2);
	tree.insert(3);
	tree.display();
	tree.clear();

	//basic RL root change
	tree.insert(1);
	tree.insert(3);
	tree.insert(2);
	tree.display();
	tree.clear();

	//basic LR not root change
	/*correct output
	1 BF: 0 Height: 0
	2 BF: 0 Height: 1
	3 BF: 0 Height: 0
	4 BF: 1 Height: 2
	5 BF: 0 Height: 0
	6 BF: 1 Height: 3
	7 BF: 0 Height: 0
	8 BF: 1 Height: 1 */
	tree.insert(6);
	tree.insert(4);
	tree.insert(8);
	tree.insert(3);
	tree.insert(5);
	tree.insert(7);
	tree.insert(1);
	tree.insert(2);
	tree.display();
	tree.clear();

	//basic LL not root change
	/*correct output
	1 BF: 0 Height: 0
	2 BF: 0 Height: 1
	3 BF: 0 Height: 0
	4 BF: 1 Height: 2
	5 BF: 0 Height: 0
	6 BF: 1 Height: 3
	7 BF: 0 Height: 0
	8 BF: 1 Height: 1 */
	tree.insert(6);
	tree.insert(4);
	tree.insert(8);
	tree.insert(3);
	tree.insert(5);
	tree.insert(7);
	tree.insert(2);
	tree.insert(1);
	tree.display();
	tree.clear();

	//basic RR not root change
	/*correct output
	 * 1 BF: 0 Height: 0
	2 BF: 0 Height: 1
	3 BF: 0 Height: 0
	5 BF: 1 Height: 2
	7 BF: 0 Height: 0*/
	tree.insert(5);
	tree.insert(7);
	tree.insert(1);
	tree.insert(2);
	tree.insert(3);
	tree.display();
	tree.clear();

	//basic RL not root change
	/*correct output
	 * 1 BF: 0 Height: 0
	2 BF: 0 Height: 1
	3 BF: 0 Height: 0
	5 BF: 1 Height: 2
	7 BF: 0 Height: 0*/
	tree.insert(5);
	tree.insert(7);
	tree.insert(1);
	tree.insert(3);
	tree.insert(2);
	tree.display();
	tree.clear();

	//root deletion no roll successor is a neighbour
	/*correct output
	2 BF: 0 Height: 0
	3 BF: 1 Height: 1
	5 BF: 1 Height: 2
	6 BF: 0 Height: 0*/
	tree.insert(4);
	tree.insert(5);
	tree.insert(3);
	tree.insert(2);
	tree.insert(6);
	tree.remove(4);
	tree.display();
	tree.clear();

	//root deletion no roll successor is not a neighbour
	/*correct output
	2 BF: 0 Height: 0
	3 BF: 1 Height: 1
	5 BF: 0 Height: 2
	6 BF: 0 Height: 0
	7 BF: 0 Height: 1
	8 BF: 0 Height: 0 */
	tree.insert(4);
	tree.insert(3);
	tree.insert(7);
	tree.insert(2);
	tree.insert(5);
	tree.insert(8);
	tree.insert(6);
	tree.remove(4);
	tree.display();
	tree.clear();

	//node deletion no roll successor is a neighbour case7
	/*correct output
	1 BF: 0 Height: 0
	2 BF: 1 Height: 1
	4 BF: 1 Height: 2
	5 BF: 0 Height: 0
	7 BF: 1 Height: 3
	8 BF: -1 Height: 1
	9 BF: 0 Height: 0*/
	tree.insert(7);
	tree.insert(3);
	tree.insert(8);
	tree.insert(2);
	tree.insert(4);
	tree.insert(9);
	tree.insert(5);
	tree.insert(1);
	tree.remove(3);
	tree.display();
	tree.clear();

	//node deletion no roll successor is not a neighbour case8
	/*correct output
	1 BF: 0 Height: 0
	2 BF: 1 Height: 1
	5 BF: 0 Height: 2
	6 BF: 0 Height: 0
	7 BF: 0 Height: 1
	8 BF: 0 Height: 0
	9 BF: 0 Height: 3
	10 BF: 0 Height: 0
	12 BF: -1 Height: 2
	13 BF: -1 Height: 1
	14 BF: 0 Height: 0*/
	tree.insert(9);
	tree.insert(3);
	tree.insert(12);
	tree.insert(2);
	tree.insert(7);
	tree.insert(10);
	tree.insert(13);
	tree.insert(1);
	tree.insert(5);
	tree.insert(8);
	tree.insert(14);
	tree.insert(6);
	tree.remove(3);
	tree.display();
	tree.clear();
	
	
	std::vector<int> vector;
	 for (int i=1; i<=100; i++) vector.push_back(i);

	 //Randomly insert and removes nodes
	 for (int k = 0; k < 20; ++k) {
		 unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		 shuffle (vector.begin(), vector.end(), std::default_random_engine(seed));
		 for (std::vector<int>::iterator it = vector.begin() ; it != vector.end(); ++it){
				tree.insert(*it);

		 }
		 tree.display();
		 shuffle (vector.begin(), vector.end(), std::default_random_engine(seed));
		 for (std::vector<int>::iterator it = vector.begin() ; it != vector.end(); ++it){
			tree.remove(*it);
			tree.display();

		}
		 tree.clear();
		 tree.display();
		 std::cout << '\n';
	}

	return 0;
}

