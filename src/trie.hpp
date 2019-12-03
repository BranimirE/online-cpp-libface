#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> range;

typedef pair<string,int> phrase;
#define str first
#define weight second

struct trie {
  const static int R = 26;//tamaño alfabeto(A - Z)
  const static int nullvalue = INT_MAX;
  struct nodo {
    int val, cnt;
    nodo* sig[R];
    nodo() : val(nullvalue), cnt(0) {
      for (int i = 0; i < R; i++) sig[i] = nullptr;
    }
  };

  nodo* raiz = nullptr;
  trie () {
    raiz = new nodo();
  }

  //Almacena la cadena key dentro del trie, asociado al valor val
  //Precondición: key no se encuentra dentro del trie
  void insertar(const string &key, int value) {
    nodo* x = raiz;
    for (int d = 0; d < (int)key.length(); d++) {
      int c = key[d]-'A';
      if (x->sig[c] == nullptr) x->sig[c] = new nodo();
      x = x->sig[c];
      x->cnt++;
    }
    x->val = value;
  }

  //Retorna el valor asociado a key en el trie
  //Ó nullvalue si el key no se encuentra en el trie
  int buscar(const string &key) {
    nodo* x = raiz;
    for (int d = 0; d < (int)key.length(); d++) {
      int c = key[d]-'A';
      if (x->sig[c] != nullptr) x = x->sig[c];
      else return nullvalue;
    }
    return x->val;
  }

  //Actualiza el valor de asociado a key con val
  //Precondición: key se encuentra almacenado en el trie
  void actualizar(string key, int val) {
    nodo* x = raiz;
    for (int d = 0; d < (int)key.length(); d++)
      x = x->sig[(int)key[d]-'A'];
    x->val = val;
  }

  //Muestra por pantalla todas las cadenas almacenadas
  //en el trie en orden lexicografico
  void mostrar() {
    int printed = 0;
    mostrar(raiz, "", printed);
  }
  void mostrar(nodo* x, string key, int &cnt) {
    if (x->val != nullvalue) {
      printf("[%d] %s -> %d\n", cnt, key.c_str(), x->val);
      cnt++;
    }
    for (int i = 0; i < R; i++)
      if (x->sig[i] != nullptr) {
        mostrar(x->sig[i], key + char('A'+i), cnt);
      }
  }

  vector<int> obtenerPesos() {
    vector<int> ret;
    recorrer(raiz, ret);
    return ret;
  }
  
  void recorrer(nodo* x, vector<int> &ret) {
    if (x->val != nullvalue) {
      ret.push_back(x->val);
    }
    for (int i = 0; i < R; i++)
      if (x->sig[i] != nullptr)
        recorrer(x->sig[i], ret);
  }
  /*
     Calcula el rango de indices en el trie si este
     representara un array ordenado de cadenas, tal que
     todas las cadenas en el rango tienen a prefix como
     prefijo
     */
  range query(const string &prefix) const {
    nodo* x = raiz;
    int cnt = 0;
    for (int d = 0; d < (int)prefix.length(); d++) {
      int c = prefix[d] - 'A';

      //El prefijo no existe en el trie
      if (x->sig[c] == nullptr) {
        //cout << "NA" << endl;
        return make_pair(-1, -1);
      }

      //Contamos la cantidad de cadenas
      //lexicograficamente menores
      for (int i = 0; i < c; i++)
        if (x->sig[i] != nullptr)
          cnt += x->sig[i]->cnt;

      if (x->val != nullvalue)
        cnt++;

      x = x->sig[c];
    }
    return make_pair(cnt, cnt + x->cnt);
  }

  /*
     Obtiene la i-esima cadena(y su valor asociado) lexicografica
     dentro del trie si este estuviera indexado desde 0
     Precondición: 0 <= i < numero de cadenas en el trie
  */
  phrase get(int i) {
    i++;
    int cnt = 0;
    string keyword;

    nodo* x = raiz;
    bool found = false;
    while (!found) {
      bool path_found = false;
      for (int c = 0; c < R and !path_found; c++) {
        if (x->sig[c] != nullptr) {
          int s = x->sig[c]->cnt;
          if (cnt + s < i) {
            cnt += s;
          } else {
            keyword += char('A' + c);
            x = x->sig[c];
            path_found = true;
          }
        }
      }
      if (path_found) {
        if (x->val != nullvalue)
          cnt++;
        if (cnt == i)
          found = true;
      } else {
        return phrase("Not found", -1);
      }
    }
    return phrase(keyword, x->val);
  }

  // Calcula la posicion en la que se encontraria key
  // si todas las cadenas del trie formaran un vector
  // ordenado lexicograficamente 
  // Precondición: key se encuentra en el trie
  int posicion(string key) {
    nodo* x = raiz;
    int cnt = 0;
    for (int d = 0; d < (int)key.length(); d++) {
      int c = key[d]-'A';
      for (int i = 0; i < c; i++)
        if (x->sig[i] != nullptr)
          cnt += x->sig[i]->cnt;
      x = x->sig[c];
      if (x->val != nullvalue)
        cnt++;
    }
    return cnt-1;
  }
};

/*void trie_test() {
  trie t;
  t.insertar("BOLIVIA", 5);
  t.insertar("BOLIVIANO", 3);
  t.insertar("BOLICHE", 9);
  t.insertar("AMERICA", 1);
  t.insertar("AMERICO", 9);
  t.insertar("BULLDOG", 23);
  t.insertar("HELADO", 5);
  t.insertar("HERMANO", 2);
  t.insertar("NACIONAL", 8);
  t.insertar("A", 5);
  t.insertar("B", 8);
  t.mostrar();
  cout << "***********" << endl;
  t.insertar("AMENO", 23);
  t.mostrar();
}

int main() {
  trie_test();
}*/
