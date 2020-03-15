#include <iostream>
#include <set>
using namespace std;

struct Node {
	int val;
	Node* left;
	Node* right;
	Node() {
		val = 0;
		left = NULL;
		right = NULL;
	}
};

string preOrder(Node* root) {
	string ans = "";
	ans += 'V';
	if (root->left) {
		ans += 'L';
		ans += preOrder(root->left);
		ans += 'l';
	}
	if (root->right) {
		ans += 'R';
		ans += preOrder(root->right);
		ans += 'r';
	}
	ans += 'v';

	return ans;
}

int n, m;
int input[50];

int main() {
	cin >> n >> m;
	set<string> s;
	while (n-- > 0) {
		for (int i = 0; i < m; i++) {
			cin >> input[i];
		}

		Node* root = new Node();
		root->val = input[0];
		for (int i = 1; i < m; i++) {
			Node* curr = root;
			while (true) {
				if (curr->val > input[i]) {
					if (curr->left == NULL) {
						curr->left = new Node();
						curr->left->val = input[i];
						break;
					}else
						curr = curr->left;
				}
				else if (curr->val < input[i]) {
					if (curr->right == NULL) {
						curr->right = new Node();
						curr->right->val = input[i];
						break;
					}
					else
						curr = curr->right;
				}
			}
		}
		
		s.insert(preOrder(root));
	}

	cout << s.size() << "\n";
	system("pause");
}