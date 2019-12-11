#include <bits/stdc++.h>

using namespace std;

#ifdef ACMTUYO
struct RTC{~RTC(){cerr << "Time: " << clock() * 1.0 / CLOCKS_PER_SEC <<" seconds\n";}} runtimecount;
#define DBG(X) cerr << #X << " = " << X << '\n';
#else
struct RTC{};
#define DBG(X)
#endif

#define fast_io() ios_base::sync_with_stdio(false)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define eb emplace_back
#define sz(x) ((int)(x).size())
#define all(c) (c).begin(),(c).end()
#define forn(i, n) for (int i = 0; i < (n); i++)
typedef long long int number;
vector<string> tokenize(string &ss) {
  ss.push_back('$');
  vector<string> answer;
  string current = "";
  for (char c: ss) {
    if (isalpha(c)) {
      current.pb(toupper(c));
    } else {
      if (sz(current) > 0) {
        answer.pb(current);
        current = "";
      }
    }
  }
  return answer;
}
int main() {
  string line;
  set<string> myset;
  while (getline(cin, line)) {
    auto tokens = tokenize(line);
    for (string token: tokens) {
      myset.insert(token);
    }
  }
  for (string keyword: myset) {
    cout << keyword << ' ' << rand()%sz(myset)+1 << endl;
  }
  return 0;
}
