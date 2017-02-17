#include <iostream>
#include <vector>

using namespace std;

void search_snippets() {
	int n;
	cin >> n;

	vector<int> word_count(n);
	for (int i = 0; i < n; i++) {
		cin >> word_count[i];
	}

	vector< vector<int> > word_position(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < word_count[i]; j++) {
			int temp;
			cin >> temp;
			word_position[i].push_back(temp);
		}
	}

	vector<int> word_pointer(n, 0);
	vector<int> min_heap, min_heap_idx;
	int max = 0, max_idx = 0;
	
	for (int i = 0; i < n; i++) {
		min_heap.push_back(word_position[i][0]);
		min_heap_idx.push_back(i);
		int child = i;
		int parent = (i - 1) / 2;
		while (parent >= 0 && min_heap[child] < min_heap[parent]) {
			int temp = min_heap[parent];
			min_heap[parent] = min_heap[child];
			min_heap[child] = temp;

			temp = min_heap_idx[parent];
			min_heap_idx[parent] = min_heap_idx[child];
			min_heap_idx[child] = temp;

			child = parent;
			parent = (child - 1) / 2;
		}
		if (word_position[i][0] > max) {
			max = word_position[i][0];
			max_idx = i;
		}
	}
	//cout << min_heap[0] << " " << max << endl;
	int length = max - min_heap[0] + 1;
	int min_idx = min_heap_idx[0];
	word_pointer[min_idx] += 1;

	while(word_pointer[min_idx] < word_count[min_idx]) {

		if (word_position[min_idx][word_pointer[min_idx]] > max) {
			max = word_position[min_idx][word_pointer[min_idx]];
			max_idx = min_idx;
		}

		min_heap[0] = word_position[min_idx][word_pointer[min_idx]];
		int parent = 0;
		int left_child = 1;
		int right_child = 2;
		while (left_child < n) {
			int flag = 0;
			if (right_child < n) {
				if (min_heap[left_child] < min_heap[right_child]) {
					if (min_heap[left_child] < min_heap[parent]) {
						flag = -1;
					}
				} else {
					if (min_heap[right_child] < min_heap[parent]) {
						flag = 1;
					}
				}
			} else {
				if (min_heap[left_child] < min_heap[parent]) {
					flag = -1;
				}
			}

			if (flag == -1) {
				int temp = min_heap[parent];
				min_heap[parent] = min_heap[left_child];
				min_heap[left_child] = temp;

				temp = min_heap_idx[parent];
				min_heap_idx[parent] = min_heap_idx[left_child];
				min_heap_idx[left_child] = temp;

				parent = left_child;
				left_child = 2 * parent + 1;
				right_child = 2 * parent + 2;
			} else if (flag == 1) {
				int temp = min_heap[parent];
				min_heap[parent] = min_heap[right_child];
				min_heap[right_child] = temp;

				temp = min_heap_idx[parent];
				min_heap_idx[parent] = min_heap_idx[right_child];
				min_heap_idx[right_child] = temp;

				parent = right_child;
				left_child = 2 * parent + 1;
				right_child = 2 * parent + 2;
			} else {
				break;
			}
		}

		int temp = max - min_heap[0] + 1;
		if (temp < length) {
			length = temp;
		}

		min_idx = min_heap_idx[0];
		word_pointer[min_idx] += 1;
	}
	cout << length << endl;
}

int main(void) {
	std::ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		search_snippets();
	}
	return 0;
}