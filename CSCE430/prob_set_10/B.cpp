#include <bits/stdc++.h>

using namespace std;

struct hole {
	int dx, dy, dt;
};

int BIG = 100000000;

int nrow, ncol;
int d[30 * 30 + 5];
// vector<vector <bool> > stones;
bool stones[30][30];
hole holes[30][30];

const int dx[] = { 0, 1, 0, -1 };
const int dy[] = { 1, 0, -1, 0 };


int bellman_ford(int s, int t) {
	int n = nrow * ncol, relaxed;
	for (int i = 1; i < n; i++) d[i] = BIG;
	d[s] = 0;
	for (int k = 0; k < n; k++) {
		relaxed = false;


		for (int i = 0; i < n - 1; i++){
			if (d[i] == BIG)
				continue;
			int cx = i / ncol, cy = i  % ncol;
			if (holes[cx][cy].dx != -1){
				int dest = holes[cx][cy].dx * ncol + holes[cx][cy].dy;
				if (d[dest] > d[i] + holes[cx][cy].dt) {
					d[dest] = d[i] + holes[cx][cy].dt;
					relaxed = true;
				}
			}
			else{
				for (int j = 0; j < 4; j++){
					int nx = cx + dx[j], ny = cy + dy[j];
					if (nx < 0 || ny < 0 || nx >= nrow || ny >= ncol || stones[nx][ny])
						continue;
					int dest = nx * ncol + ny;
					if (d[dest] > d[i] + 1) {
						d[dest] = d[i] + 1;
						relaxed = true;
					}
				}
			}
		}
		if (!relaxed) break;
	}


	return relaxed ? -BIG : d[t];
}

int main() {
  while (cin >> nrow >> ncol && nrow + ncol > 0) {
		int nstone, nhole, x, y;

    // hole temp;
    // temp.dx = 0;
    // temp.dy = 0;
    // temp.dt = 0;
    // stones.resize(30, vector<bool> (30, false));
    // holes.resize(30, vector<hole>(30, temp));
		memset(holes, -1, sizeof(holes));
    memset(stones, 0, sizeof(stones));


    cin >> nstone;
		for (int i = 0; i < nstone; i++){
      cin >> x >> y;
			stones[x][y] = true;
		}

    cin >> nhole;
		for (int i = 0; i < nhole; i++){
      cin >> x >> y;
      int _dx, _dy, _dt;
      cin >> _dx >> _dy >> _dt;
      holes[x][y].dx = _dx;
      holes[x][y].dy = _dy;
      holes[x][y].dt = _dt;
		}

		int ans = bellman_ford(0, nrow * ncol - 1);

		if (ans == -BIG) {
      cout << "Never" << endl;
    } else if (ans == BIG) {
      cout << "Impossible" << endl;
    } else {
      cout << ans << endl;
    }
	}


















	return 0;
}
