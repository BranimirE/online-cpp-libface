#include <bits/stdc++.h>

using namespace std;

#define fast_io() ios_base::sync_with_stdio(false)
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define eb emplace_back
#define sz(x) ((int)(x).size())
#define all(c) (c).begin(),(c).end()
#define forn(i, n) for (int i = 0; i < (n); i++)
typedef long long int number;

#define value first
#define index second
typedef struct _node {
  int value, y, cnt;
  pair<int,int> maxi;//(value, index)
  _node *l, *r;
  _node(int _value) : value(_value), y((rand() << 16) ^ rand()), cnt(1), maxi(_value, 0), l(nullptr), r(nullptr) {}
  ~_node() {delete l; delete r;}
  void recalc() {
    cnt = 1;
    maxi = make_pair(value, l?l->cnt:0);
    if (l) {
      cnt += l->cnt;
      maxi = max(maxi, l->maxi);
    }
    if (r) {
      cnt += r->cnt;
      maxi = max(maxi, make_pair(r->maxi.first, (l?l->cnt:0) + 1 + r->maxi.second));
    }
  }

} *node;

bool operator < (const _node &a, const _node &b) {
  return a.maxi < b.maxi;
}
struct treap {
  treap(): root(nullptr) {}
  ~treap() {delete root;}
  node root;
  /*
     Divide el arbol que tiene como raiz a "t", guarda en 
     L los primeros "x" elementos del array
     R el primer elemento de R es el elemento en posicion x(indexado desde 0) del array
     t es destruido/modificado
     L = [0, x)
     R = [x, n)
   */
  void split(node t, int x, node &L, node &R) {
    if (t == nullptr) {L = R = nullptr; return;}
    int curIndex = cnt(t->l);
    if (x <= curIndex) {
      split(t->l, x, L, t->l);
      R = t;
    } else {
      split(t->r, x - curIndex - 1, t->r, R);
      L = t;
    }
    t->recalc();
  }

  /*
     Une los dos nodos L y R en un solo arbol y los devuelve.
     L y R son modificados
   */
  node merge(node L, node R) {
    if (L == nullptr) return R;
    if (R == nullptr) return L;
    if (L->y > R->y) {
      L->r = merge(L->r, R);
      L->recalc();
      return L;
    } else {
      R->l = merge(L, R->l);
      R->recalc();
      return R;
    }
  }
  // Inserta "value" en la posicion "pos"(indexado desde 0) recorre todos los elementos a la derecha desde la posicion pos
  void insert(int pos, int value) {
    node L, R;
    split(root, pos, L, R);//en R esta pos
    root = merge(merge(L, new _node(value)), R);
  }
  // Borra el elemento la posicion pos
  void erase(int pos) {
    node L, m, R;
    split(root, pos, L, R);
    split(R, 1, m, R);
    root = merge(L, R);
  }
  int cnt(node t) const {
    return t ? t->cnt : 0;
  }
  int size() const {
    return cnt(root);
  }

  //Retorna el elemento almacenado en la posicion "pos"
  int get(int pos) {
    node L, m, R;
    split(root, pos, L, R);
    split(R, 1, m, R);
    int ret = m->value;
    root = merge(merge(L, m), R);
    return ret;
  }

  //Actualiza el valor asiado en la posicion "pos"
  void update(int pos, int value) {
    node L, m, R;
    split(root, pos, L, R);
    split(R, 1, m, R);
    m->value = value;
    root = merge(merge(L, m), R);
  }

  //Retorna el maximo elemento en el rango [a, b)
  //Retorna (value, index) donde value el maximo elemento
  //en el rango [a, b) e index es su indice
  //Si es que existieran varios elementos con ese mismo valor
  //se retornara el que se encuentre mas a la derecha
  pair<int,int> maxInRange(int a, int b) {//el rango es [a, b)
    node L, m, R;
    split(root, a, L, R);
    split(R, b - a, m, R);
    pair<int,int> ret = m->maxi;
    ret.second += a;
    root = merge(merge(L, m), R);
    return ret;
  }

  pair<int,int> query(int a, int b) {
    return maxInRange(a, b);
  }

  // Imprime todos los elementos del treap
  void print() {
    for (int i = 0, tam = size(); i < tam; i++) {
      cout << get(i) << " ";
    }
    cout << endl;
  }

  void build(const vector<int>& v) {
    for (int i = 0; i < (int)v.size(); i++) {
      insert(i, v[i]);
    }
  }

  void linear_build(const vector<int> &v) {
    int n = v.size();
    int next_pow_2 = 1;
    while (next_pow_2 <= n) next_pow_2 *= 2;
    int jump = max(INT_MAX/2, n) / next_pow_2;
    root = _build(0, n, v, next_pow_2, 1, jump);
  }

  node _build(int a, int b, const vector<int> &v, int N, int id, int jump) {
    if (a == b) return nullptr;
    int mid = (a + b) / 2;
    node m  = new _node(v[mid]);
    m->l = _build(a, mid, v, N, 2 * id, jump);
    m->r = _build(mid + 1, b, v, N, 2 * id + 1, jump);
    m->y = (N - id) * jump;
    m->recalc();
    assert(m->y > (m->l==nullptr?0:m->l->y));
    assert(m->y > (m->r==nullptr?0:m->r->y));
    return m;
  }
};

pair<int,int> naive_maxi(vector<int> &vec, int a, int b) {
  pair<int,int> sol = mp(vec[a], a);
  for (int i = a; i < b; i++) {
    sol = max(sol, mp(vec[i], i));
  }
  return sol;
}

template <typename T, typename S> 
ostream& operator<<(ostream& os, const pair<T, S>& v) { 
    os << "("<< v.first << ", " << v.second << ")"; 
    return os; 
} 

#define DBG(X) cerr << #X << " = " << X << '\n';

void treap_test() {
  const int N = 2000;
  srand(time(nullptr));
  treap t;
  //vector<int> vec = {3, 5, 2, 7, 4};

  //First we'll use the linear time build
  vector<int> vec;
  forn (i, N) {
    vec.pb(rand());
  }
  t.linear_build(vec);

  //Check that all the results are correct
  for (int i = 0; i < sz(vec); i++) {
    for (int j = i + 1; j <= sz(vec); j++) {
      assert(t.maxInRange(i, j) == naive_maxi(vec, i, j));
    }
  }
  cout << "LINEAR BUILD IS WORKING GOOD" << endl;

  //We will add new values to random positions
  forn (i, N) {
    int position = rand() % (sz(t) + 1);
    int value = rand();
    t.insert(position, value);
    vec.insert(vec.begin() + position, value);
  }
  //Check that all is in their correct position
  forn (i, sz(vec)) {
    assert(vec[i] == t.get(i));
  }
  cout << "ALL THE ELEMENTS ARE IN THEIR CORRECT POSITION" << endl;

  //Check that all the results are correct
  for (int i = 0; i < sz(vec); i++) {
    for (int j = i + 1; j <= sz(vec); j++) {
      assert(t.maxInRange(i, j) == naive_maxi(vec, i, j));
    }
  }
  cout << "THE TREE IS STILL WORKING AFTER IT'S BEEN MODIFIED RANDOMLY" << endl;
  cout << "ALL OK" << endl;
}

/*int main() {
  treap_test();
  return 0;
}*/
