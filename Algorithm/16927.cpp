#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define fast_io ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
using pii = pair<int,int>;
using ll = long long;
int N, M, R, arr[301][301];

//https://nanyoungkim.tistory.com/79

int dr[] = {0,1,0,-1};
int dc[] = {1,0,-1,0};

void rotate(int s, int len) {
    int cnt = R % len;
    for (int i = 0; i < cnt; i++) {
        int sVal = arr[s][s];
        int r = s;
        int c = s;
        int k = 0;
        while(k < 4) {
            int nr = r + dr[k];
            int nc = c + dc[k];

            if (nr == s && nc == s) break;
            if (s <= nr && nr < N && s <= nc && nc < M-s) {
                arr[r][c] = arr[nr][nc];
                r = nr;
                c = nc;
            }else k++;
        }
        arr[s+1][s] = sVal;
    }
}

void print() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << arr[i][j] << ' ';
        }
        cout << '\n';
    }
}

int main() {
    fast_io;
    cin >> N >> M >> R;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> arr[i][j];
        }
    }

    int check = min(N, M) / 2;
    int n = N, m = M;

    for (int i = 0; i < check; i++) {
        rotate(i, n * 2 + m * 2 - 4);
        n -= 2;
        m -= 2;
    }

    print();
}
