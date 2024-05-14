#include <iostream>
#include "FilaDin_Class.cpp"
using namespace std;
typedef int TIPOPESO;

class ADJACENCIA {
private:
  int vertice;
  TIPOPESO peso;
  ADJACENCIA *prox;

public:
  int getVertice() { return vertice; }
  void setVertice(int vertice) { this->vertice = vertice; }
  void setPeso(TIPOPESO peso) { this->peso = peso; }
  TIPOPESO getPeso() { return peso; }
  void setProx(ADJACENCIA *prox) { this->prox = prox; }
  ADJACENCIA *getProx() { return prox; }
};

class VERTICE {
private:
  // outros dados
  int key;
  ADJACENCIA *cab;

public:
  void setCab(ADJACENCIA *cab) { this->cab = cab; }
  ADJACENCIA *getCab() { return cab; }
  void setKey(int key) {this->key = key;}
  int getKey() {return key;}
};

class GRAFO {
private: // no BFS ou DFS mudar para public ou implementar getter and setter
  int vertices;
  int arestas;
  VERTICE *adj;

public:
  GRAFO() {
    cout << "Necessario informar o numero de vertices" << endl;
    cout << "Programa sera encerrado" << endl << endl;
    exit(-1);
  }
  GRAFO(int v) {
    int i;
    vertices = v;
    arestas = 0;
    adj = new VERTICE[v];
    for (i = 0; i < v; i++) {
      adj[i].setCab(NULL);
      adj[i].setKey(NULL);
    }
  }

  int getVertices() { return vertices; }
  void setVertices(int vertices) { this->vertices = vertices; }
  int getArestas() { return arestas; }
  void setArestas(int arestas) { this->arestas = arestas; }
  VERTICE *getAdj() { return adj; }
  void setAdj(VERTICE *adj) { this->adj = adj; }

  ADJACENCIA *criaAdj(int v, int peso) {
    ADJACENCIA *temp = new ADJACENCIA;
    temp->setVertice(v);
    temp->setPeso(peso);
    temp->setProx(NULL);
    return (temp);
  }

  bool criaAresta(int vi, int vf, TIPOPESO p, int key = NULL) {
    /*if (!gr)
      return false;*/
    if ((vf < 0) || (vf >= vertices))
      return false;
    if ((vi < 0) || (vi >= vertices))
      return false;
    ADJACENCIA *novo = criaAdj(vf, p);
    novo->setProx(adj[vi].getCab());
    adj[vi].setCab(novo);
    if (adj[vi].getKey() == NULL)
        adj[vi].setKey(key);
    arestas++;
    return true;
  }

  void imprime() {
    int i;
    cout << "Vertices: " << vertices << ", Aresta: " << arestas << endl;
    for (i = 0; i < vertices; i++) {
      cout << "v" << i << ": ";
      ADJACENCIA *ad = adj[i].getCab();
      while (ad) {
        cout << "v" << ad->getVertice() << "(" << ad->getPeso() << ") ";
        ad = ad->getProx();
      }
      cout << endl;
    }
  }

  void exploreGraph(int keyToFind = NULL) {
      bool explored[this->vertices];

      int vertice;
      for (vertice= 0; vertice < this->vertices; vertice++)
          explored[vertice] = false;

      for (vertice = 0; vertice < this->vertices; vertice++) {
          if (!explored[vertice]) {
              if (visitGraph(vertice, explored, keyToFind))
                  break;
          }
      }
  }

  bool visitGraph(int startVertice, bool *explored, int keyToFind = NULL) {
    FilaDin queue = FilaDin();
    explored[startVertice] = true;
    REGISTRO *adjacents = (REGISTRO *)new REGISTRO();

    adjacents->chave = startVertice;
    queue.inserirFila(*adjacents);
    int foundKeyVertice = -1;

    while(queue.inicio) {
        queue.excluirFila(adjacents);
        ADJACENCIA *nextNeighbor = this->adj[adjacents->chave].getCab();
        int key = this->adj[adjacents->chave].getKey();

        while(nextNeighbor) {
            if (key == keyToFind) {
                foundKeyVertice = adjacents->chave;
                break;
            }
            if (!explored[nextNeighbor->getVertice()]) {
                explored[nextNeighbor->getVertice()] = true;
                adjacents->chave = nextNeighbor->getVertice();
                queue.inserirFila(*adjacents);
            }
            nextNeighbor = nextNeighbor->getProx();
        }
    }


    if (keyToFind != NULL) {
        if (foundKeyVertice != -1) {
            cout << "A chave " << keyToFind << " foi encontrada no vertice " << foundKeyVertice << endl;
            return true;
        }
        else {
            cout << "Nao foi possivel encontrar a chave informada (" << keyToFind << ")" << endl;
            return false;
        }
    }

    delete adjacents;

    return false;
  }
};

int main()
{
    GRAFO *gr = new GRAFO(5);
    gr->criaAresta(0, 1, 2, 1);
    gr->criaAresta(1, 2, 4, 3);
    gr->criaAresta(2, 0, 12, 6);
    gr->criaAresta(2, 4, 40, 6);
    gr->criaAresta(3, 1, 3, 9);
    gr->criaAresta(4, 3, 8, 12);
    gr->imprime();

    int keyToFind = NULL;
    cout << "Insira uma chave para buscar: ";
    cin >> keyToFind;
    cout << endl;
    gr->exploreGraph(keyToFind);

    return 0;
}