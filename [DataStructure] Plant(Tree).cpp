/* Problem Number: 2261						 */
/* URL: https://www.acmicpc.net/problem/2261 */
/* Date: 2017.07.02							 */
/* Purpose: Data Structure Construction(Tree)*/

#include <stdio.h>
#include <iostream>
#include <math.h>

int indent = 0;

class Node {
private:
	float x;
	float y;
	float r;
	int id;
	bool is_global;

	Node* child;
	Node* sibling;

public:
	Node(int new_id,float new_x, float new_y, float new_r,bool global = false) {
		x = new_x;
		y = new_y;
		r = new_r;
		id = new_id;

		is_global = global;
		child = nullptr;
		sibling = nullptr;
	}

	int getId(void) {
		return id;
	}

	Node* getChild(void) {
		return child;
	}

	Node* getSibling(void) {
		return sibling;
	}

	float getDistance(Node& dest) {
		return sqrt((x-dest.x)*(x-dest.x) + (y-dest.y)*(y-dest.y));
	}
	
	bool insertNode(Node& node) {
		if (coverSpace(node)) { //대상 node가 이 노드에 포함될 때
			if (child) {
				bool inserted_in_child = child->insertNode(node);

				if (!inserted_in_child) {
					Node* stay_child[50];
					Node* move_child[50];
					int stay_idx=0, move_idx=0;
					Node* ptr = child;

					while (ptr) {
						if (node.coverSpace(*ptr))
							move_child[move_idx++] = ptr;
						else
							stay_child[stay_idx++] = ptr;

						ptr = ptr->sibling;
					}

					for (int i = 0;i < move_idx-1;i++) {
						move_child[i]->sibling = move_child[i + 1];
					}
					
					if (move_idx == 0)
						node.child = nullptr;
					else {
						move_child[move_idx - 1]->sibling = nullptr;
						node.child = move_child[0];
					}

					for (int i = 0;i < stay_idx - 1;i++) {
						stay_child[i]->sibling = stay_child[i + 1];
					}
					
					if (stay_idx == 0)
						child = nullptr;
					else {
						stay_child[stay_idx - 1]->sibling = nullptr;
						child = stay_child[0];
					}

					node.sibling = child;
					child = &node;
				}
				return true;
			}
			else {
				child = &node; // 자식이 없을때 자식으로 insert
				return true;
			}
		}
		else {
			if (sibling) {
				return sibling->insertNode(node);
			}
			else return false;
		}
	}
		
	bool coverPoint(float x, float y) {
		Node temp(0, x, y, 0);

		return (getDistance(temp) < r) || is_global;
	}

	bool coverSpace(Node& node) {
		float dist = getDistance(node);
		return ((dist + node.r < r) && (r > node.r)) || is_global;
	}

	void printTree(void) {
		for (int i = 0;i < indent;i++) {
			printf(" ");
		}
		printf("[%d](%f,%f) - r: %f\n",id, x, y, r);
		indent++;
		if (child) {
			child->printTree();
		}
		indent--;
		if (sibling) {
			sibling->printTree();
		}
	}
};

int make_surround_array(Node* global_node,float x,float y,int arr[]) {
	int idx = 0;
	
	Node* ptr = global_node;

	while (ptr) {
		if (ptr->coverPoint(x, y)) {
			arr[idx] = ptr->getId();
			idx = idx + 1;

			ptr = ptr->getChild();
		}
		else {
			ptr = ptr->getSibling();
		}
	}

	return idx; //return size
}

int main(void) {
	int T, n;
	float s_x, s_y, d_x, d_y;
	float x, y, r;

	scanf("%d", &T);
	for (int i = 0;i < T;i++) {
		int surround_s_array[50] = { 0 };
		int surround_d_array[50] = { 0 };

		scanf("%f %f %f %f", &s_x, &s_y, &d_x, &d_y);

		Node globalSpace(0, 0, 0, 0, true);

		scanf("%d", &n);
		for (int j = 0;j < n;j++) {
			scanf("%f %f %f", &x, &y, &r);
			Node *in_node = new Node(j+1,x, y, r);

			bool result = globalSpace.insertNode(*in_node);
		}
		int size_s = make_surround_array(&globalSpace, s_x, s_y, surround_s_array);
		int size_d = make_surround_array(&globalSpace, d_x, d_y, surround_d_array);

		int big_size = (size_s > size_d) ? size_s : size_d;
		int same_count=0;

		for (int k = 0;k < big_size;k++) {
			if (surround_s_array[k] == surround_d_array[k])
				same_count++;
			else break;
		}

		printf("%d\n", size_s + size_d - 2 * same_count);
	}


	return 0;

}