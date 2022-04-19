#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define fast_io ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
using pii = pair<int,int>;
using ll = long long;
int N, max_ans, min_ans = 1e9;

int cnt_odd(const string& num) {
   int val, cnt = 0;
   for (auto c : num) {
       val = c - '0';
       if (val % 2) cnt++;
   }
   return cnt;
}
//�ش� num�� 0~l, l+1~r, r+1~�� �ɰ����� ��� �� string���� ��ȯ
string cut_paper(const string& num, int l, int r) {
   string num1 = num.substr(0,l+1);
   string num2 = num.substr(l+1, r-l);
   string num3 = num.substr(r+1);
   return to_string(stoi(num1) + stoi(num2) + stoi(num3));
}

void solve(string num, int cnt) {
   if (num.length() == 1) {
       max_ans = max(max_ans, cnt);
       min_ans = min(min_ans, cnt);
       return;
   }
   if (num.length() == 2) {
       int l = num[0] - '0';
       int r = num[1] - '0';

       int tmp = cnt_odd(to_string(l+r));
       solve(to_string(l+r), cnt+tmp);
   }else {
       for (int i = 0; i < num.length()-2; i++) {
           for (int j = i+1; j < num.length()-1; j++) {
               string new_val = cut_paper(num, i, j);
               solve(new_val, cnt + cnt_odd(new_val));
           }
       }
   }
}

int main() {
   fast_io;
   cin >> N;
   string num = to_string(N);

   int cnt = cnt_odd(num);
   solve(num, cnt);

   cout << min_ans << ' ' << max_ans;
}