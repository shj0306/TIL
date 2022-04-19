#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define fast_io ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
using pii = pair<int,int>;
using ll = long long;
int H, W, height[501], area;
//https://hwan-shell.tistory.com/276
int main() {
   fast_io;
   cin >> H >> W;

   for (int i = 1; i <= W; i++) cin >> height[i];

   for (int i = 2; i < W; i++) {
       int l = 1, r = i+1, max_l = height[1], max_r = height[r];
       for (int j = 1; j < i; j++) {
           if (height[j] > max_l) {
               max_l = height[j];
               l = j;
           }
       }
       for (int j = i+1; j <= W; j++) {
           if (height[j] > max_r) {
               max_r = height[j];
               r = j;
           }
       }

       if (height[l] < height[r]) {
           area += max(0, height[l] - height[i]);
       }else {
           area += max(0, height[r] - height[i]);
       }
   }

   cout << area;
}