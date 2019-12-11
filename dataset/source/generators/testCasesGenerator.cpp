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
int main(int argc, char const *argv[]) {
  srand(time(NULL));
  if (argc > 1) {
    N_TC = atoi(argv[1]);
  } else {
    cerr << "You forgot to pass the number of test cases to generate" << endl;
    return 0;
  }

  vector<string> strs;
  string line;
  while (getline(cin, line)) {
    stringstream ss(line);
    string keyword;
    ss >> keyword;
    strs.pb(keyword);
  }
  vector<string> test_cases;
  stringstream ss2;
  int tcA = N_TC / 2;
  while (tcA--) {
    string str = strs[rand() % sz(strs)];
    ss2 << "Q " << str.substr(0, 1 + (rand() % sz(str))) << ' ' << (1 + rand() % K) << endl;
    getline(ss2, line);
    test_cases.push_back(line);
  }
  int tcB = N_TC - (N_TC / 2);
  while (tcB--) {
    int size = 1 + (rand() % LEN_STR);
    ss2 << "Q ";
    forn (i, size) {
      ss2 << (char)('A'+(rand()%26));
    }
    ss2 << ' ' << (1 + (rand() % K)) << endl;
    getline(ss2, line);
    test_cases.push_back(line);
  }
  random_shuffle(all(test_cases));
  for (string test: test_cases) {
    cout << test << endl;
  }
  return 0;
}
