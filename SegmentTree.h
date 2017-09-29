#include <iostream>
#include <math.h>
#include <vector>
#include <functional>
#include <queue> 

#ifndef SegmentTree_H
#define SegmentTree_H

template <typename T> class SegmentTree {
	struct Node;
	struct Node{
		Node *left, *right;
		T data; 
	};

	Node *root; 
	std::vector<T> arr;
	T (*c)(T, T); 
	T build_tree(int start, int end, Node* cur){
		if (start == end) cur->data = arr[start];
		else {
			int mid = start + ((end - start)/2);
			cur->left = new Node; cur->left->left = NULL; cur->left->right = NULL;
			cur->right = new Node; cur->right->left = NULL; cur->right->right = NULL;
			cur->data = c(build_tree(start, mid,cur->left),build_tree(mid+1, end, cur->right));
		}
		return cur->data;
	}
	public:
		SegmentTree(T (*comp_func)(T, T), std::vector<T> input_elements){
			c = comp_func;
			arr = input_elements;
			int arr_size = input_elements.size();
			root = new Node;
			build_tree(0, arr_size-1, root);
		}
		/*  c_i --> current_index 
			c_s/c_e --> start and end index represented by the current_index of the segment tree 
			start/end --> the start and end of the current query */ 
		T query(int start, int end){
			struct Optional {
				T value;
				bool empty; 
			};
			//Exits if input out of range of array
			if (start < 0 || end >= arr.size()){
				std::cout << "Invalid input, exiting..." << std::endl;
				return -1;
			}
			std::function<Optional(Node*, int, int)> helper;
			helper = [this,start, end, &helper](Node* cur, int c_s, int c_e)->Optional {
				Optional empty_optional; empty_optional.empty = true;
				Optional nonempty_optional; nonempty_optional.empty = false;
 				//Case 1: the node is unassigned or the query-range is outside the range of the given node:	
 				if (!cur || start > c_e || end < c_s){
 					return empty_optional;
 				}
				//Case2: query contained in node
				if (start <= c_s && end >= c_e){
					nonempty_optional.value = cur->data;
					return nonempty_optional;
				}
				//Otherwise there's some overlap
				int mid = c_s + ((c_e - c_s)/2);
				Optional left = helper(cur->left, c_s, mid);
				Optional right = helper(cur->right, mid+1, c_e);
				if (!left.empty && !right.empty) nonempty_optional.value = c(left.value, right.value);
				else if (!left.empty && right.empty) nonempty_optional.value = left.value;
				else if (!right.empty) nonempty_optional.value = right.value;
				else return empty_optional;
				return nonempty_optional;

			};
			Optional x = helper(root,0,arr.size()-1);
			if (!x.empty) return x.value;
			else {
				std::cout << "Logical error, exiting..." << std::endl;
				return -1;
			}
		}
};

int e_sum(int e1, int e2){
	return e1 + e2; 
}

int main(){
	std::vector<int> x = {1,2,3,4, 5, 6 ,7 ,8 ,9, 10};
	SegmentTree<int> st = SegmentTree<int>(&e_sum, x);
	std::cout << st.query(3,7) << std::endl;
	return 0;
}

#endif