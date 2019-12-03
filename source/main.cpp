#include "trie.hpp"
#include "treap.hpp"
#include <bits/stdc++.h>

using namespace std;

#ifdef ACMTUYO
struct RTC{~RTC(){cerr << "Time: " << clock() * 1.0 / CLOCKS_PER_SEC <<" seconds\n";}} runtimecount;
#define DBG(X) cerr << #X << " = " << X << '\n';
#endif

#define value first
#define index second
typedef tuple<int,int,int,int> phrase_range;
//(value, index, a, b)
struct Suggest {
  trie ds;
  treap st;

  void insert(const string &str, int weight) {
    ds.insertar(str, weight);
  }

  void build() {
    st.linear_build(ds.obtenerPesos());
  }

  void build(const string &filename) {
    ifstream in(filename);
    string keyword;
    int value;
    while (in >> keyword >> value) {
      insert(keyword, value);
    }
    in.close();
    build();
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

  void add(string key, int weight) {
    if (ds.buscar(key) != trie::nullvalue) {
      cout << "Entry found in the set, updating its value" << endl;
      int position = ds.posicion(key);
      ds.actualizar(key, weight);
      st.update(position, weight);
    } else {
      cout << "Adding the new entry" << endl;
      insert(key, weight);
      //ds.mostrar();
      int position = ds.posicion(key);
      st.insert(position, weight);
    }
  }
};

void print(Suggest &sug) {
  sug.ds.mostrar();
}

int main(int argc, char const *argv[]) {
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
      sug.add(keyword, value);
    }
  }
  /*Suggest sug;
  sug.build("generatedDataSet.txt");
  cout << "DS builded" << endl;
  string prefix;
  int k;
  while (cin >> prefix >> k) {
    auto indexes = sug.query(prefix, k);
    for (int index: indexes) {
      phrase res = sug.get(index);
      cout << res.str << ' ' << res.weight << ' ';
    }
    cout << endl;
  }
  cout << "ALL OK" << endl;*/
  return 0;
}
