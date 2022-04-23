#include <bits/stdc++.h>
#include <unordered_map>
#define all(x) (x).begin(), (x).end()
#define fast_io ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
using pii = pair<int,int>;
using ll = long long;
int N, M, Q, c;
string P, F;
unordered_map<string, int> Folds, Files;
vector<vector<pii>> tree;
int cnt;
set<int> files;

void dfs(int root) {

    if (tree[root].empty()) return;
    for (auto [ch, type] : tree[root]) {
        if (type) { //folder
            dfs(ch);
        }else { //file
            cnt++;
            files.insert(ch);
        }
    }
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
        istringstream  iss(path);
        vector<int> tmp;
        string buf;
        while(getline(iss, buf, '/')) {
            tmp.push_back(Folds[buf]);
        }

        int dir = tmp[tmp.size()-1];
        dfs(dir);
        cout << files.size() << ' ' << cnt << '\n';
        files.clear(); cnt = 0;
    }

}