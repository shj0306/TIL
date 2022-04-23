#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define fast_io ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
using pii = pair<int,int>;
using ll = long long;
string html;

string ret_title(int idx) {
    string title;
    while(html[idx] != '"') {
        title += html[idx++];
    }
    return title;
}

string ret_content(int s, int e) {
    string content;
    int idx = s; bool prev_blank = false;
    while(idx < e) {
        if (html[idx] == ' ') {
            if (!prev_blank) {
                content += ' ';
                prev_blank = true;
            }
        }
        else if (html[idx] == '<') {
            while(html[++idx] != '>') {}
        }else {
            content += html[idx];
            prev_blank = false;
        }
        ++idx;
    }

    if (content[0] == ' ') {
        idx = 0;
        while(content[idx++] == ' ') {}
        content.erase(0, idx);
    }

    int N = (int)content.size()-1;
    if (content[N] == ' ') {
        idx = N;
        while(content[idx] == ' ') {
            idx--;
        }
        content.erase(N, N-idx);
    }
    return content;
}

void ret_paragraph(int s, int e) {

    int p_s = s, p_e = s;
    while(p_s < e) {
        p_s = (int)html.find("<p>", p_s);
        p_e = (int)html.find("</p>", p_s);
        if (p_s >= e || p_s == string::npos) break;

        cout << ret_content(p_s+3, p_e) << '\n';
        p_s += 3;
    }
}

int main() {
    fast_io;
    getline(cin, html);

    int idx = 0;
    while(idx < html.length()) {
        int div_s = (int)html.find("title=", idx);
        int div_e = (int)html.find("</div>", div_s);

        if (div_s == string::npos) break;

        //title
        cout << "title : " << ret_title(div_s+7) << '\n';
        // paragraph content
        ret_paragraph(div_s,div_e);

        idx = div_s+1;
    }
}