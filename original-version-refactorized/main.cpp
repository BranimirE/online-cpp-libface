#include <bits/stdc++.h>

using namespace std;

#ifdef ACMTUYO
struct RTC{~RTC(){cerr << "Time: " << clock() * 1.0 / CLOCKS_PER_SEC <<" seconds\n";}} runtimecount;
#endif

const char SEPARATOR = ' ';

typedef pair<string,int> phrase;
#define str first
#define weight second

typedef pair<int,int> range;

struct Comp {
  bool operator()(string const& prefix, phrase const &target) {
    const int ppos = target.str.compare(0, prefix.size(), prefix);
    return ppos > 0;
  }
  bool operator()(phrase const &target, string const& prefix) {
    const int ppos = target.str.compare(0, prefix.size(), prefix);
    return ppos < 0;
  }
};

struct data_store {
  vector<phrase> data;//(str, weight)
  void insert(const string &str) {
    auto found = str.find(SEPARATOR);
    if (found != string::npos) {
      insert(str.substr(0, found), atoi(str.substr(found).c_str()));
    } else {
      insert(str, 0);
    }
  }
  void insert(const string &str, int weight) {
    data.emplace_back(str, weight);
  }
  void build() {
    sort(data.begin(), data.end());
  }
  range query(const string &prefix) const {
    auto its = equal_range(data.begin(), data.end(), prefix, Comp());
    return make_pair(its.first - data.begin(), its.second - data.begin());
  }
  phrase get(int index) const {
    return data[index];
  }
};
//------------------------------------ TESTS -------------------------------------------
void print(const data_store &ds) {
  for (int i = 0, sz = ds.data.size(); i < sz; i++) {
    cout << "[" << i << "] \t" << ds.data[i].str << " -> " << ds.data[i].weight << endl;
  }
}

pair<int,int> naive_query(const data_store &ds, const string &prefix) {
  auto it = ds.data.begin();
  while (it != ds.data.end() and it->str.substr(0, prefix.size()) < prefix) {
    it++;    
  }
  int low = it - ds.data.begin();
  while (it != ds.data.end() and it->str.substr(0, prefix.size()) == prefix) {
    it++;
  }
  int up = it - ds.data.begin();
  return make_pair(low, up);
}

void ds_test() {
  data_store ds;

  ds.insert("duckduckgo", 1);
  ds.insert("duckduckgeese", 2);
  ds.insert("duckduckgoose", 1);
  ds.insert("duckduckgoo", 9);
  ds.insert("duckgo", 10);
  ds.insert("dukgo", 3);
  ds.insert("luckkuckgo", 2);
  ds.insert("chuckchuckgo", 5);
  ds.insert("dilli - no one killed jessica", 15);
  ds.insert("aaitbaar - no one killed jessica", 11);
  ds.insert("alibaba", 14);
  ds.insert("alabama", 12);
  ds.insert("informatica", 4);
  ds.insert("dugon", 421);
  ds.insert("parazetamol", 43);
  ds.insert("paraiso", 43);
  

  ds.build();

  assert(naive_query(ds, "a") == ds.query("a"));
  assert(naive_query(ds, "al") == ds.query("al"));
  assert(naive_query(ds, "b") == ds.query("b"));
  assert(naive_query(ds, "c") == ds.query("c"));
  assert(naive_query(ds, "d") == ds.query("d"));
  assert(naive_query(ds, "fa") == ds.query("fa"));
  assert(naive_query(ds, "duck") == ds.query("duck"));
  assert(naive_query(ds, "duckgo") == ds.query("duckgo"));
  assert(naive_query(ds, "ka") == ds.query("ka"));
  assert(naive_query(ds, "para") == ds.query("para"));

  cout << "Data Store OK" << endl;
}
//------------------------------------ END TESTS ------------------------------------ 
#define value first
#define index second
struct segment_tree {
  typedef pair<int,int> node;//pairs(value, index)

  const node neutral = make_pair(INT_MIN, -1);
  vector<node> t;
  int n;//Original array's size

  void init(const vector<int> &arr) {
    n = arr.size();
    //next pow of 2
    int next_pow_of_2 = (n and (n&(n-1)) == 0)?n:(1<<(32-__builtin_clz(n)));
    t.assign(next_pow_of_2 * 2, neutral);
    build(0, n, 1, arr);
  }

  node build(int l, int r, int u, const vector<int> &arr) {
    if (l >= r) return neutral;
    if (l+1 == r) return t[u] = node(arr[l], l);
    int m = (l+r)>>1;
    return t[u] = max(build(l, m, 2*u, arr), build(m, r, 2*u+1, arr));
  }

  //It returns max query on range [i, j)
  node query(int i, int j) {
    return query(i, j, 1, 0, n);
  }

  node query(int i, int j, int u, int l, int r) {
    if (i >= r or l >= j) return neutral;
    if (i <= l and r <= j) return t[u];
    int m = (l+r)>>1; 
    return max(query(i,j,2*u,l,m), query(i,j,2*u+1,m,r));
  }
};

void st_test() {
  segment_tree st;
  for (int n = 0; n <= 1025; n++) {
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
      v[i] = rand();
    }
    st.init(v);
    cout << "Initialized " << n << endl;
    for (int i = 0; i < n; i++) {
      pair<int,int> ans(v[i], i);
      for (int j = i+1; j <= n; j++) {
        if (v[j-1] >= ans.first) {
          ans = pair<int,int>(v[j-1], j-1);
        }
        assert(ans == st.query(i, j));
      }
    }
  }
  cout << "Segment Tree OK" << endl;
}





typedef tuple<int,int,int,int> phrase_range;
//(value, index, a, b)
struct Suggest {
  data_store ds;
  segment_tree st;

  void insert(const string &str, int weight) {
    ds.insert(str, weight);
  }
  void build() {
    ds.build();
    print(ds);
    vector<int> weights;
    for (phrase &item: ds.data) {
      weights.push_back(item.weight);
    }
    st.init(weights);
  }

  void build(const string &filename) {
    ifstream in(filename);
    string line;
    while (getline(in, line)) {
      ds.insert(line);
    } 
    ds.build();
    //print(ds);
    vector<int> weights;
    for (phrase &item: ds.data) {
      weights.push_back(item.weight);
    }
    st.init(weights);
  }

  vector<int> query(const string &prefix, int k) {
    range r = ds.query(prefix);//[first, second)
    vector<int> answer;
    if (r.first == r.second) {
      return answer;
    }

    priority_queue<phrase_range> pq;
    pair<int,int> best = st.query(r.first, r.second);
    pq.emplace(best.value, best.index, r.first, r.second);

    while ((int)answer.size() < k && !pq.empty()) {
      int index, low, up;
      tie(std::ignore, index, low, up) = pq.top();

      pq.pop();

      answer.push_back(index);

      if (low < index) {
        best = st.query(low, index);
        pq.emplace(best.value, best.index, low, index);
      }

      if (index+1 < up) {
        best = st.query(index+1, up);
        pq.emplace(best.value, best.index, index+1, up);
      }
    }
    return answer;
  }
  
  phrase get(int index) {
    return ds.get(index);
  }
};


vector<int> naive_suggest(const data_store &ds, const string &prefix, int n) {
  range r = ds.query(prefix);
  vector<int> answer;
  vector<pair<int,int> > arr;//(value, index)
  for (int i=r.first; i<r.second; i++) {
    arr.emplace_back(ds.get(i).second, i);
  }
  sort(arr.begin(), arr.end());
  for (int i=arr.size()-1; i>=0 and n>0; i--, n--) {
    answer.push_back(arr[i].second);
  }
  return answer;
}

void printArr(vector<int> v) {
  for (int e: v) {
    cout << e << ' ';
  }
  cout << endl;
}

void data_structure_test() {
  Suggest sug;
  sug.insert("duckduckgo", 1);
  sug.insert("duckduckgeese", 2);
  sug.insert("duckduckgoose", 1);
  sug.insert("duckduckgoo", 9);
  sug.insert("duckgo", 10);
  sug.insert("dukgo", 3);
  sug.insert("luckkuckgo", 2);
  sug.insert("chuckchuckgo", 5);
  sug.insert("dilli - no one killed jessica", 15);
  sug.insert("aaitbaar - no one killed jessica", 11);
  sug.insert("alibaba", 14);
  sug.insert("alabama", 12);
  sug.insert("informatica", 4);
  sug.insert("dugon", 421);
  sug.insert("parazetamol", 43);
  sug.insert("paraiso", 43);
  
  sug.build();
  vector<string> tests = {
    "a",
    "al",
    "b",
    "c",
    "d",
    "fa",
    "duck",
    "duckgo",
    "ka",
    "para"
  };
  for (string test: tests) {
    for (int k = 0; k <= 16; k++) {
      assert(naive_suggest(sug.ds, test, k) == sug.query(test, k));
    }
  }
  cout << "DATA_STRUCTURE PASSED ALL INITIAL TESTS" << endl;
}
int main(int argc, char const *argv[]) {
  //TODO: change this by an efficient way to read a file, receive the name of the file as a parameter
  /*data_store ds;
    ifstream in("input");
    string line;
    while (getline(in, line)) {
    ds.insert(line);
    }
    ds.build();
    print(ds);

    while (getline(cin, line)) {
    auto res = ds.query(line);
    cout << res.first << " " << res.second << endl; 
    }*/
  /*ds_test();
    st_test();*/
  /*Suggest sug;
  sug.build("generatedDataSet.txt");
  cout << "DS builded" << endl;
  string prefix;
  int k;
  //int line_number = 0;
  while (cin >> prefix >> k) {
    auto indexes = sug.query(prefix, k);
    for (int index: indexes) {
      phrase res = sug.get(index);
      cout << res.str << ' ' << res.weight << ' ';
    }
    cout << endl;
  }
  cout << "ALL OK" << endl;*/
  Suggest sug;
  if (argc > 1) {
    string filename(argv[1]);
    sug.build(filename);
    cout << "DS builded using " <<  filename << " file." << endl;
    //print(sug);
  } else {
    cout << "Data structure empty, not using a dataset." << endl;
  }
  string command;
  while (cin >> command) {
    char type = toupper(command[0]);
    string keyword;
    int value;
    cin >> keyword >> value;
    if (type == 'Q') {//query
      auto indexes = sug.query(keyword, value);
      for (int index: indexes) {
        phrase res = sug.get(index);
        cout << index << ":" << res.str << '(' << res.weight << ") ";
      }
      cout << endl;
    } else {//add or update
      //sug.add(keyword, value);
    }
  }
  return 0;
}
