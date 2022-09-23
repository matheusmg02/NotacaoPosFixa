#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 200

typedef struct node{
  float valor;
  struct node *prox;
} Node;

float calcularExpressao(char x[]);
float operacao(float, float, char);
Node *inserir(Node *, float);
Node *retirar(Node **);

int main(){
  char expressao[MAX_LENGTH];
  printf("CALCULADORA DE NOTAÇÃO PÓS-FIXA\n");
  printf("Insira a expressão: ");
  fgets(expressao, 200, stdin);

  float resultado = calcularExpressao(expressao);

  printf("Resultado: %.2f", resultado);
}

float calcularExpressao(char x[]){
  char *pointer;
  float result;
  Node *n1, *n2, *pilha = NULL;

  pointer = strtok(x, " ");
  while (pointer){
    if (pointer[0] == '+' || pointer[0] == '-' || pointer[0] == '/' || pointer[0] == '*'){
      n1 = retirar(&pilha);
      n2 = retirar(&pilha);
      result = operacao(n2->valor, n1->valor, pointer[0]);
      pilha = inserir(pilha, result);
      free(n1);
      free(n2);
    }
    else{
      result = strtol(pointer, NULL, 10);
      pilha = inserir(pilha, result);
    }
    pointer = strtok(NULL, " ");
  }

  n1 = retirar(&pilha);
  result = n1->valor;
  free(n1);

  if (pilha){
    printf("Expressão inválida!\n");
    exit(1);
  }

  return result;
}

float operacao(float a, float b, char x){
  switch (x){
  case '+':
    return a + b;
    break;
  case '-':
    return a - b;
    break;
  case '/':
    return a / b;
    break;
  case '*':
    return a * b;
    break;
  default:
    return 0.0;
  }
}

Node *inserir(Node *pilha, float result){
  Node *novo = malloc(sizeof(Node));

  if (novo){
    novo->valor = result;
    novo->prox = pilha;
    return novo;
  }
  else
    printf("Erro de alocação.\n");

  return NULL;
}

Node *retirar(Node **pilha){
  Node *remover = NULL;

  if (*pilha){
    remover = *pilha;
    *pilha = remover->prox;
  }
  else
    printf("Expressão inválida!\n");

  return remover;
}