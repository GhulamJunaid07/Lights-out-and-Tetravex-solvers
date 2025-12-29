#include <bits/stdc++.h>
using namespace std;

const int N = 7; // max reasonable size of grid 

int n, mat[N][N], ans[N][N], placed, dist[N][N];
vector<int> vec[N * N], who[10][4];
bool vis[N * N];
vector<pair<int, int>> order;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

bool valid(int x, int y){
    return (x >= 0 and y >= 0 and x < n and y < n);
}

void dfs(int v, int x, int y){
    // cout << "Putting " << v << " at " << x << ", " << y << endl;

    for (int d = 0; d < 4; d ++){
        int nx = x + dx[d];
        int ny = y + dy[d];
        if (!valid(nx, ny) or !mat[nx][ny]) continue;

        if (vec[mat[nx][ny]][(d + 2) % 4] != vec[v][d]){
            cout << "!@#!@@$#@$!@#$!#@$!#@$!@#$!@#$!@#$!@#$!@#$!@#$!@#$!@#$!@#$" << endl;
            cout << "Error Occured while placing " << v << " at " << x << " " << y << endl;
        }
    }

    // if answer found then just stop recursion.
    if (ans[0][0]) return;

    mat[x][y] = v;
    vis[v] = 1;
    placed++;

    if (placed == n * n){
        // if everything is placed then answer is found.
        cout << "yes!! found" << endl;
        for (int i = 0; i < n; i ++)
            for (int j = 0; j < n; j ++)
                ans[i][j] = mat[i][j];
        return;
    }

    for (auto [nx, ny] : order){
        if (mat[nx][ny]) continue;

        // cout << "possibilities for " << nx << " " << ny << " are : " << endl;
        bool other[n * n + 1], poss[n * n + 1];
        for (int nv = 1; nv <= n * n; nv ++)
            poss[nv] = 1;
        for (int d = 0; d < 4; d ++){
            int ax = nx + dx[d];
            int ay = ny + dy[d];
            if (!valid(ax, ay) or !mat[ax][ay]) continue;
            // cout << "finding from neighbour " << ax << " " << ay << " " << mat[ax][ay] << endl;
            for (int nv = 1; nv <= n * n; nv ++)
                other[nv] = 1;
            for (int u : who[vec[mat[ax][ay]][(d + 2) % 4]][d])
                other[u] = 0;
            for (int nv = 1; nv <= n * n; nv ++)
                if (other[nv])
                    poss[nv] = 0;
        }

        // for (int nv = 1; nv <= n * n; nv ++)
        //     if (poss[nv] and !vis[nv])
        //         cout << nv << " ";
        // cout << endl; 

        for (int nv = 1; nv <= n * n; nv ++)
            if (poss[nv] and !vis[nv])
                dfs(nv, nx, ny);

        break;
    }

    placed--;
    vis[v] = 0;
    mat[x][y] = 0;
}

int main(){
    cin >> n;
    for (int i = 1; i <= n * n; i ++){
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        vec[i] = {a, b, c, d};
        
        // 'a' appears in i-th tile as the number at top (0).
        who[a][0].push_back(i);
        // 'b' appears in i-th tile as the number at right (1) 
        who[b][1].push_back(i);
        // 'c' appears in i-th tile as the number at down (2) 
        who[c][2].push_back(i);
        // 'd' appears in i-th tile as the number at left (3) 
        who[d][3].push_back(i);
    }

    for (int i = 0; i < n; i ++)
        for (int j = 0; j < n; j ++)
            dist[i][j] = abs(i - n / 2) + abs(j - n / 2);
    for (int i = 0; i < n * n; i ++)
        for (int x = 0; x < n; x ++)
            for (int y = 0; y < n; y ++)
                if (dist[x][y] == i)
                    order.push_back({x, y});
    // putting tiles in order from their distance 
    // from centre, so that the possibilities are 
    // reduced faster.

    for (int i = 1; i <= n * n; i ++){
        memset(vis, 0, sizeof vis);
        // cout << "Trying to check from " << i << endl;
        // try to put the i-th tile at the centre
        // and see if it gives a solution or not.
        dfs(i, n / 2, n / 2);
    }

    if (!ans[0][0]){
        cout << "There is no solution" << endl;
        return 0;
    }

    // order of tiles in which they should be placed, starting from what should be placed as the first tile.
    cout << endl << "Order : " << endl;
    for (int i = 0; i < n; i ++){
        for (int j = 0; j < n; j ++)
            cout << ans[i][j] << " ";
        cout << endl;
    }

    // representing the tiles with their numbers in the solution.
    cout << endl << "Solution : " << endl;
    for (int i = 0; i < n; i ++){
        for (int j = 0; j < n; j ++){
            for (int x : vec[ans[i][j]])
                cout << x << " ";
            cout << endl;
        }
    }
}

/*
Some test cases and their outputs.

4
1 9 4 2
7 8 6 1
6 9 3 8
0 1 2 1
9 2 3 1
4 1 0 1
0 3 7 9
3 7 0 1
2 9 5 9
3 1 4 9
8 6 2 8
3 3 9 0
5 1 1 3
7 8 3 0
2 5 6 3
6 0 3 6

expected : 
2 11 16 14 
3 9 10 8
12 13 6 4
5 1 7 15

6
6 3 6 1
6 8 9 2
5 4 4 7
2 4 4 8
8 2 4 7
0 2 9 7
3 6 2 3
4 1 4 5
0 3 7 4
9 6 4 4 
5 4 3 6
4 3 9 6
0 2 8 8
4 1 6 6
8 5 1 8
9 9 5 3
6 7 9 2
9 2 6 1
6 1 5 8
7 8 7 4
7 3 0 5
9 1 0 1
6 7 4 3
4 4 1 7
5 7 7 2
4 7 1 1
7 6 4 7
3 2 6 4
7 0 6 2
5 2 8 6
6 6 5 8
4 8 7 3
9 3 8 2
4 1 6 4
6 8 8 4
5 2 5 0


5
7 3 5 5
2 8 4 0
9 7 1 8
9 6 0 3
2 5 0 8
7 6 2 4
2 7 6 4
4 1 2 0
3 6 4 2
0 3 5 0
0 3 6 4
6 0 7 7
3 0 2 6
5 3 4 0
2 2 7 8
7 8 3 1
3 6 2 7
4 3 3 2
7 1 2 3
4 4 9 3
3 8 2 6
2 0 4 1
5 4 7 3
6 8 3 1
3 1 3 3

Solution : 
25 16 5 1 4 
9 13 10 23 11 
8 22 14 19 24 
15 18 20 7 17 
6 21 3 12 2 

Solution : 
3 1 3 3 
7 8 3 1 
2 5 0 8 
7 3 5 5 
9 6 0 3 
3 6 4 2 
3 0 2 6 
0 3 5 0 
5 4 7 3 
0 3 6 4 
4 1 2 0 
2 0 4 1 
5 3 4 0 
7 1 2 3 
6 8 3 1 
2 2 7 8 
4 3 3 2 
4 4 9 3 
2 7 6 4 
3 6 2 7 
7 6 2 4 
3 8 2 6 
9 7 1 8 
6 0 7 7 
2 8 4 0 


*/
