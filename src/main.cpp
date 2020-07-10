#include "trie.hpp"
#include "treap.hpp"
#include <bits/stdc++.h>
#include <chrono>

using namespace std;
using milli_s = std::chrono::milliseconds;
using micro_s = std::chrono::microseconds;
using nano_s = std::chrono::nanoseconds;

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
      int position = ds.posicion(key);
      st.insert(position, weight);
    }
  }

  int size() {
    return st.size();
  }
};

void print(Suggest &sug) {
  sug.ds.mostrar();
}

void menu() {
   string out = "Queries format:\n"
     "Q PREFIX K\n"
     "Example:\n"
     "Q HELL 5\n\n"
     "Add format:\n"
     "A STRING VALUE\n"
     "Example:\n"
     "A HELL 1232\n\n"
     "Update format:\n"
     "U STRING VALUE\n"
     "Example:\n"
     "U HELL 8765\n\n";
   cout << out << endl;

}

int main(int argc, char const *argv[]) {
  Suggest sug;
  if (argc > 1) {
    
    auto t1 = std::chrono::steady_clock::now();
    string filename(argv[1]);
    sug.build(filename);
    auto t2 = std::chrono::steady_clock::now();
    cout << "Data Structure builded using " <<  filename << " file." << endl;
    cout << sug.size() << " strings builded in " << std::chrono::duration_cast<milli_s>( t2 - t1 ).count() << " milliseconds.\n" << endl;
  } else {
    cout << "Data structure empty, not using a dataset." << endl;
  }
  menu();
  string command;
  while (cin >> command) {
    char type = toupper(command[0]);
    string keyword;
    int value;
    cin >> keyword >> value;

    auto t1 = std::chrono::steady_clock::now();
    if (type == 'Q') {//query
      auto indexes = sug.query(keyword, value);
      for (int index: indexes) {
        phrase res = sug.get(index);
        cout << index << ":" << res.str << '(' << res.weight << ") ";
      }
      cout << endl;
    } else {//add or update
      sug.add(keyword, value);
      sug.query(keyword, 1);
    }
    auto t2 = std::chrono::steady_clock::now();
    cout << "Operation finished in " << std::chrono::duration_cast<milli_s>( t2 - t1 ).count() << " milliseconds = "
    << std::chrono::duration_cast<micro_s>( t2 - t1 ).count() << " microseconds = "
    << std::chrono::duration_cast<nano_s>( t2 - t1 ).count() << " nanoseconds. \n" << endl;

  }
  return 0;
}
