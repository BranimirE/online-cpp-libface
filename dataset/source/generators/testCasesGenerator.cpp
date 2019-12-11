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
int N_TC = 1000000;
int LEN_STR = 5;
int K = 16;
int main() {
  vector<string> strs;
  string line;
  while (getline(cin, line)) {
    stringstream ss(line);
    string keyword;
    ss >> keyword;
    strs.pb(keyword);
  }
  int tc = N_TC;
  while (tc--) {
    string str = strs[rand() % sz(strs)];
    cout << "Q " << str.substr(0, 1 + (rand() % sz(str))) << ' ' << (1 + rand() % K) << endl;
  }
  tc = N_TC;
  while (tc--) {
    int size = 1 + (rand() % LEN_STR);
    cout << "Q ";
    forn (i, size) {
      cout << (char)('A'+(rand()%26));
    }
    cout << ' ' << (1 + (rand() % K)) << endl;
  }
  return 0;
}
