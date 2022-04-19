#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define fast_io ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
using pii = pair<int,int>;
using ll = long long;
string str;
int check[101], num, N;

int ret_alphabet(int l, int r) {
   char min_c = str[l];
   int min_idx = l;
   for (int i = l; i < r; i++) {
       if (check[i]) continue;
       if (min_c > str[i]) {
           min_c = str[i];
           min_idx = i;
       }
   }
   return min_idx;
}

void dfs(int l, int r) {
   if (l >= r) return;
   int min_idx = ret_alphabet(l, r);
   check[min_idx] = ++num;
   dfs(min_idx+1, r);
   dfs(l, min_idx);
}

int main() {
   fast_io;
   cin >> str;
   N = (int) str.length();

   dfs(0, N);
   for (int i = 1; i <= N; i++) {
       for (int j = 0; j < N; j++) {
           if (check[j] <= i) cout << str[j];
       }
       cout << '\n';
   }
}