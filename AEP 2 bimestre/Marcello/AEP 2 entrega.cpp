#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include <string.h>

char pontos[11][30] = {
  "maua",
  "Morangueira",
  "Brasil",
  "Colombo",
  "Alexandre",
  "Sofia",
  "Gastao",
  "Cerro azul",
  "Laguna",
  "Tuiuti"
};

typedef struct tipoPonto {
  char ponto[30];
  struct tipoPonto * proximo;
}
TPonto;

typedef struct tipoLista {
  TPonto * inicio;
  TPonto * fim;
}
TLista;

TLista tabelaHashing[10];

void inicializar() {
  int i;
  for (i = 0; i < 10; i++) {
    tabelaHashing[i].inicio = NULL;
    tabelaHashing[i].fim = NULL;
  }
}

int hash(int soma) {
  return soma % 10;
}

void executar() {
  int quantasLetras=7;

  int j;

  for (j = 0; j < 10; j++) {
    int i;
    int soma = 0;
    for (i = 0; i < quantasLetras; i++) {
      soma = soma + pontos[j][i];
    }

    int indice = hash(soma);

    TPonto * novoPonto;
    novoPonto = new TPonto;

    strcpy(novoPonto -> ponto, pontos[j]);
    novoPonto -> proximo = NULL;

    if (tabelaHashing[indice].inicio == NULL) {
      tabelaHashing[indice].inicio = novoPonto;
      tabelaHashing[indice].fim = novoPonto;
    } else {
      tabelaHashing[indice].fim -> proximo = novoPonto;
      tabelaHashing[indice].fim = novoPonto;
    }
  }
}

void apresentar() {
  int i, colisao, indi, cont = 0;
  TPonto * aux;
  indi = 0;
  for (i = 0; i < 10; i++) {
    colisao = -1;
    printf("\n Indice: %d - ", i+1);
    aux = tabelaHashing[i].inicio;
    if (aux != NULL) {
      indi++;
      while (aux != NULL) {
        colisao++;
        if (colisao >= 1) {
          cont++;
        }
        printf("%s |", aux -> ponto);
        aux = aux -> proximo;
      }

    } else {
      printf(" .");
    }
  }
  printf("\n \n Colisoes contabilizadas: %d", cont);
  printf("\n Indices usados : %d \n", indi);
  
  system("pause");
}

int main() {
  int opcao;
  inicializar();

  do {
  	system("cls");
    printf("\n\n 1 - Executar hashing");
    printf("\n 2 - Apresentar tabela hashing");
    printf("\n 0 - Sair");
    printf("\n Escolha uma opcao : ");
    scanf("%d", & opcao);
    system("cls");
    switch (opcao) {
    case 1:
      executar();
      break;
    case 2:
      apresentar();
      break;
    }
  } while (opcao != 0);

  return 0;
}

