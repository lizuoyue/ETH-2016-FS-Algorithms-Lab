#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

void moving_books() {

	int n, m;
	cin >> n >> m;

	vector<int> people(n);
	multiset<int, greater<int> > book;
	for (int i = 0; i < n; i++) {
		cin >> people[i];
	}
	for (int i = 0; i < m; i++) {
		int w; cin >> w;
		book.insert(w);
	}

	sort(people.begin(), people.end(), greater<int>());

	if(people[0] < *book.begin()) {
		cout << "impossible" << endl;
		return;
	}

	int count = 0;
	while (book.size() > 0) {
		int i;
		for (i = 0; i < n; ++i) {
			multiset<int>::iterator choice = book.lower_bound(people[i]);
			if (choice == book.end()) {
				++count;
				break;
			} else {
				//cout << i << " choose " << *choice << endl;
				book.erase(choice);
			}
		}
		count += (i == n);
	}

	cout << count * 3 - 1 << endl;
}

int main(void) {
	std::ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		moving_books();
	}
}