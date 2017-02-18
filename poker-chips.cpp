#include <iostream>
#include <vector>
#include <map>

using namespace std;

void chips() {

	int nStack;
	cin >> nStack;

	vector<int> stackLen(5, 0);
	for (int i = 0; i < nStack; i++) {
		cin >> stackLen[i];
	}

	vector< vector<int> > color(5);
	for (int i = 0; i < nStack; i++) {
		vector<int> tempStack(stackLen[i]);
		for (int j = 0; j < stackLen[i]; j++) {
			cin >> tempStack[j];
		}
		color[i] = tempStack;
	}

	vector< vector< vector< vector< vector<int> > > > > score(
		stackLen[0] + 1, vector< vector< vector< vector<int> > > >(
		stackLen[1] + 1, vector< vector< vector<int> > >(
		stackLen[2] + 1, vector< vector<int> >(
		stackLen[3] + 1, vector<int>(
		stackLen[4] + 1, 0
	)))));

	vector<int> state(5);
	for (state[0] = 0; state[0] <= stackLen[0]; state[0]++) {
		for (state[1] = 0; state[1] <= stackLen[1]; state[1]++) {
			for (state[2] = 0; state[2] <= stackLen[2]; state[2]++) {
				for (state[3] = 0; state[3] <= stackLen[3]; state[3]++) {
					for (state[4] = 0; state[4] <= stackLen[4]; state[4]++) {

						int tempScore = 0;

						map<int, vector<int> > lastEle;
						for (int i = 0; i < 5; i++) {
							if (state[i] > 0) {
								lastEle[color[i][state[i] - 1]].push_back(i);
							}
						}

						for(map<int, vector<int> >::iterator i = lastEle.begin(); i != lastEle.end(); i++) {
							int last = i -> first;
							vector<int> idx = i -> second;
							for (int s = 0; s < (1 << idx.size()); s++) {
								vector<int> tempState = state;
								int current = 0;
								for (int n = 0; n < idx.size(); n++) {
									if (s & (1 << n)) {
										tempState[idx[n]]--;
										current++;
									}
								}
								if (current == 1) {current = 0;}
								else if (current > 1) {current = (1 << (current - 2));}

								tempScore = max(tempScore, score[tempState[0]][tempState[1]][tempState[2]][tempState[3]][tempState[4]] + current);
							}
						}

						score[state[0]][state[1]][state[2]][state[3]][state[4]] = tempScore;
					}
				}
			}
		}
	}

	cout << score[stackLen[0]][stackLen[1]][stackLen[2]][stackLen[3]][stackLen[4]] << endl;
}

int main(void) {
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		chips();
	}
	return 0;
}