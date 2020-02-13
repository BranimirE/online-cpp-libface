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
typedef long long int ll;

int main() {
  int n = 0;
  ll sum = 0;
  int maxlen = 0, minlen = INT_MAX;
  map<int,int> cnt_by_size;

  string line;
  while (getline(cin, line)) {
    stringstream ss(line);
    string keyword;
    ss >> keyword;
    n++;
    sum += sz(keyword);
    maxlen = max(maxlen, sz(keyword));
    minlen = min(minlen, sz(keyword));
    cnt_by_size[sz(keyword)]++;
  }

  DBG(n);
  DBG(minlen);
  DBG(maxlen);
  cout << "mean = " << (sum / n) << endl;
  cout << "------ Number of kewords by size --------" << endl;
  for (auto e: cnt_by_size) {
    cout << e.first << " "  << e.second << endl;
  }
  
  return 0;
}

