#include <bits/stdc++.h>
using namespace std;

// solver for 5*5
const int N = 5;
int grid[N][N];

int ans[(1 << (N * N)) + 1]; 
// for each state stored as a bitmask integer, what's the min operations required.

pair<int,int> parent[(1 << (N * N)) + 1];
int it = 0;
int nodes = 0;

void bfs(){
    fill(ans, ans + (1 << (N * N)) + 1, (int)1e9);
    // initialising the distances to other states as very large number (10^9).

	queue<int> que;
    que.push(0);
	ans[0] = 0;
	parent[0].first = -1;
    // state 0, is the source. 

	while (que.size() > 0){
		int v = que.front();
		que.pop();
		nodes++;

		for (int i = 0; i < N * N; i++){
			it++;
			int u = v;
            // do a flip at the i-th cell in state v.

			u ^= (1 << i);
			if (i < 20)
				u ^= (1 << (i + 5));
			if (i > 4)
				u ^= (1 << (i - 5));
			if (i % 5 != 4)
				u ^= (1 << (i + 1));
			if (i % 5 != 0)
				u ^= (1 << (i - 1));
            // state u will be the next state

			if (ans[u] > ans[v] + 1){
				ans[u] = ans[v] + 1;
				parent[u].first = v;
				parent[u].second = i;
				que.push(u);
			}
		}
	}
}

int main(){
	bfs();
	
	int num = 0;
	for (int i = 0; i < 5; i++){
		for (int j = 0; j < 5; j++){
			cin >> grid[i][j];
			if (grid[i][j] == 1)
				num += (1 << (5 * i + j));
		}
    }

	if (ans[num] == (int)1e9){
        // state in the input can never reach 0 state.
		cout << "IMPOSSIBLE" << endl;
		return 0;
	}

	cout << endl << "it takes " << ans[num] << " steps." << endl << endl;

    // outputting each operation one by one, to reach 0 state from input state : 
	int step = 1;
	while (parent[num].first != -1){
		int clicked = parent[num].second;
		cout << "click on row " << clicked / N + 1 << " and column " << clicked % N + 1 << endl;
		cout << "Now the grid is : " << endl;
		num = parent[num].first;

		for (int i = 0; i < (N * N); i++){
			if (i % N==0)
				cout << endl;

			if ((1 << i) & num)
				cout << 1 << " ";
			else
				cout << 0 << " ";
		}
		cout << endl << endl;
	}

    // additional info for analysing complexity :
	cout << "total nodes in bfs tree : " << nodes << endl;
	cout << "total iterations taken  : " << it << endl;
}
