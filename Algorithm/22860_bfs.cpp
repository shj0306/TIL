#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define fast_io ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
using pii = pair<int,int>;
using ll = long long;
int N, M, Q, c;
string P, F;
unordered_map<string, int> Folds, Files;
vector<vector<pii>> tree;
void bfs(int x) {
    int file_cnt = 0;
    set<int> files;
    queue<int> q;

    q.push(x);
    while(!q.empty()) {
        int cur = q.front();
        q.pop();

        for (auto [ch, type] : tree[cur]) {
            if (type) {
                q.push(ch);
            }else {
                file_cnt++;
                files.insert(ch);
            }
        }
    }
    cout << files.size() << ' ' << file_cnt << '\n';
}


int main() {
    fast_io;
    cin >> N >> M;
    tree.resize(N+1);

    int fold_cnt = 0, file_cnt = 0;
    for (int i = 0; i < N+M; i++) {
        cin >> P >> F >> c;
        if (Folds.count(P) == 0) Folds[P] = fold_cnt++;
        int p_idx = Folds[P];
        if (c) {
            if (Folds.count(F) == 0) Folds[F] = fold_cnt++;
            int c_idx = Folds[F];
            tree[p_idx].emplace_back(c_idx, 1);
        }else {
            if (Files.count(F) == 0) Files[F] = file_cnt++;
            int c_idx = Files[F];
            tree[p_idx].emplace_back(c_idx, 0);
        }
    }

    cin >> Q;
    for (int i = 0; i < Q; i++) {
        string path; cin >> path;
        string parse = "";

        for (auto c : path) {
            parse += c;
            if (c == '/') parse.clear();
        }

        bfs(Folds[parse]);
    }
}