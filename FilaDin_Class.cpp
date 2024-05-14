#include <iostream>
using namespace std;

typedef int TIPOCHAVE;

struct REGISTRO {
  TIPOCHAVE chave;
  // outros campos ...
};

struct ELEMENTO {
  REGISTRO reg;
  ELEMENTO *prox;
};

class FilaDin {
public:
  ELEMENTO *inicio;
  ELEMENTO *fim;

  FilaDin() {
    inicio = NULL;
    fim = NULL;
  }

  int tamanhoFila() {
    ELEMENTO *ender = inicio;
    int tam = 0;
    while (ender != NULL) {
      tam++;
      ender = ender->prox;
    }
    return tam;
  }

  void listaFila() {
    ELEMENTO *ender = inicio;
    cout << "Fila [ ";
    while (ender != NULL) {
      cout << ender->reg.chave << " ";
      ender = ender->prox;
    }
    cout << "]\n";
  }

  bool inserirFila(REGISTRO reg) {
    ELEMENTO *novo = new ELEMENTO;
    novo->reg = reg;
    novo->prox = NULL;
    if (inicio == NULL)
      inicio = novo;
    else
      fim->prox = novo;
    fim = novo;
    return true;
  }

  bool excluirFila(REGISTRO *reg) {
    if (inicio == NULL)
      return false;
    *reg = inicio->reg;
    ELEMENTO *apagar = inicio;
    inicio = inicio->prox;
    delete apagar;
    if (inicio == NULL)
      fim = NULL;
    return true;
  }

  void reinicializaFila() {
    ELEMENTO *ender = inicio;
    while (ender != NULL) {
      ELEMENTO *apagar = ender;
      ender = ender->prox;
      delete apagar;
    }
    inicio = NULL;
    fim = NULL;
  }
};
