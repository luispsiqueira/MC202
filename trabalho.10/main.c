#include <stdlib.h>
#include <stdio.h>
#include <errno.h>


//para a lista de entrada, ou seja, a sequencia que devera ser realizada --> A
struct lista {
  int data;
  struct lista* next;
};
typedef struct lista lista;
struct li {
  lista* head;
};
typedef struct li li;


//para a lista que sera feita, ou seja, para a lista de inteiros [1, 2, ... N] --> L
struct sequencia {
  int data;
  struct sequencia* next;
};
typedef struct sequencia sequencia;
struct se {
  sequencia* head;
};
typedef struct se se;


//aloca uma lista vazia para A
li* lista_alloc();
li* lista_alloc() {
  return calloc(1,sizeof(li));
}


//aloca uma lista vazia para L
se* sequencia_alloc();
se* sequencia_alloc() {
  return calloc(1,sizeof(se));
}


//cria a lista [1, 2, 3, ... maior(inserido na entrada)]
int sequencia_x(se* L, int maior);
int sequencia_x(se* L, int maior){
  sequencia* n = malloc(sizeof(sequencia));
  if(n == NULL){
    return 0;
  }
  
  n->data = 1;
  L->head = n;
  n->next = NULL;
  n = n->next;

  int o = 2;
  sequencia* p = L->head;
  while (o <= maior) {
    sequencia* n = malloc(sizeof(sequencia));
    n->data = o;
    p->next = n;
    n->next = NULL;
    p = p->next;
    o++;
  }

  return 1;
}


//funcao que ira inserir os numeros no final da lista, assim a lista A ficara igual a lista de entrada
int lista_insert(li* L, int data, int i);
int lista_insert(li* L, int data, int i) {

  lista* n = malloc(sizeof(lista));
  if (n == NULL){
    return 0;
  }
  if (i == 0) {
    n->data = data;
    L->head = n;
    n->next = NULL;
  }
  else {
    lista* p = L->head;
    while (p->next != NULL) {
      p = p->next;
    }
    n->data = data;
    p->next = n;
    n->next = NULL;
  }

  return 1;
}

//funcao que ira remover o numero que esta na a->data, na posicao correta a partir da lista L
int remove_at(se* L, int c) {
  int i = 0;
  sequencia* p = L->head;
  
  while (i < c - 2) {
    p = p->next;
    i++;
  }

  sequencia* r = p->next;
  p->next = r->next;
  free(r);

  return 1;
}


//funcao que ira adicionar o numero removido no comeco
int add_inicio(se*L, int c);
int add_inicio(se*L, int c){
  sequencia* n = malloc(sizeof(sequencia));
  if (n == NULL){
    return 0;
  }
  n->data = c;
  n->next = L->head;
  L->head = n;
  return 1;
}


//funcao que troca o numero apontado por n->data pelo proximo e o n->netx->data pelo anterior
int troca_de_lugar(se*L, int c, int x);
int troca_de_lugar(se*L, int c, int x){
  int i = 0, y = 0;
  sequencia* n = L->head;
  while (i < c - 2) {
    n = n->next;
    i++;
  }
  y = n->data;
  n->data = x;
  n = n->next;
  n->data = y;
  n = L->head;

  return 1;
}


//funcao que ira fazer o move to front, ela leva para mais duas funoces, uma ira revocer o numero e a outra ira adiciona-lo no comeco
int lista_MTF(se*L, li*A);
int lista_MTF(se*L, li*A){
  int custo = 0;
  lista* a = A->head;
  sequencia* l = L->head;
  int c = 1;
  while(a != NULL){
    l = L->head;
    c = 1;
    while(l != NULL){
      if(a->data == l->data){
        custo = custo + c;
        if(c > 1){
          remove_at(L, c);
          add_inicio(L, a->data);
          break;
        }  
      }
      l = l->next;
      c++;
    }
    
    a = a->next;
  }
  return custo;
}


//funcao transpose, troca o numero pedido com o numero anterior, se nao estiver em primeiro na fila
int transpose(se*L, li*A);
int transpose(se*L, li*A){
  int custo = 0;
  lista* a = A->head;
  sequencia* l = L->head;
  int c = 1;
  while(a != NULL){
    l = L->head;
    c = 1;
    while(l != NULL){
      if(a->data == l->data){
        custo = custo + c;
        if(c > 1){
          troca_de_lugar(L, c, a->data);
          break;
        }
      }
      l = l->next;
      c++;
    }
    
    a = a->next;
  }

  return custo;
}


//funcao arrumar_count (arrumar a lista e o vetor de inteiros contator[])
int arrumar_count(se*L, int*contador, int r, int m);
int arrumar_count(se*L, int*contador, int r, int m){
  int d = 0, e = 0, x = 0, y = 0, i = 0;
  while(r > 0){
    if((contador[r] >= contador[r - 1]) && (contador[r] == m)){
      d = contador[r];  
      e = contador[r - 1];
      contador[r] = e;
      contador[r - 1] = d; 


      i = 0;
      y = 0;
      sequencia* n = L->head;
      while (i < r - 1) {
        n = n->next;
        i++;
      }
      y = n->data;
      x = n->next->data;
      n->data = x;
      n->next->data = y;
      n = L->head;

    }
   r--;
  }

  return 1;
}


//funcao count, organiza a lista A segundo a quantidade de vezes que os numeros apareceram, guarda os numeros no vetor de inteiros (contador)
int count(se*L, li*A, int* contador, int maior);
int count(se*L, li*A, int* contador, int maior){
  int custo = 0;
  lista* a = A->head;
  sequencia* l = L->head;
  int c = 1, r = 0;
  while(a != NULL){
    l = L->head;
    c = 1;
    while(l != NULL){
      if(a->data == l->data){
        custo = custo + c;
        if(c == 1){
          contador[0] = contador[0] + 1;
        }
        else{
          contador[c - 1] = contador[c - 1] + 1;
          r = c - 1;
          arrumar_count(L, contador, r, contador[r]);
          break;
        }
      }
      l = l->next;
      c++;
    }
    a = a->next;
  }

  return custo;
}


//apaga todos os dados da lista L
void sequencia_free(se* L);
void sequencia_free(se* L) {
  sequencia* a = L->head;
  sequencia* b = NULL;
  while (a != NULL) {
    b = a->next;
    free(a);
    a = b;
  }
  free(L);
}


int main(void) {
  int maior, tamanho;

  scanf(" %d\n", &maior);
  scanf(" %d\n", &tamanho);

  li* A = lista_alloc();
  if (A == NULL){
    exit(errno);
  }
  se* L = sequencia_alloc();
  if(L == NULL){
    exit(errno);
  }
   
  int i = 0;
  while (i < tamanho) {
    int n;
    scanf("%d ",&n);
    int st = lista_insert(A,n, i);
    if (!st) exit(errno);
    i++;
  }

  int contador[tamanho];
  int g = 0;
  while(g < tamanho){
    contador[g] = 0;
    g++;
  }
  
  int custo1, custo2, custo3;

  sequencia_x(L, maior);
  custo1 = lista_MTF(L,A);//gera o resultado da MTF e traz para a funcao main
  //sequencia_free(L);

  sequencia_x(L, maior);
  custo2 = transpose(L, A);//gera o resultado da transpose e traz para a funcao main
  //sequencia_free(L);

  sequencia_x(L, maior);
  custo3 = count(L, A, contador, maior);//gera o resultado da count e traz para a funcao main

  //imprime os resultados obtidos
  printf("MTF: %d\n", custo1);
  printf("Transpose: %d\n", custo2);
  printf("Count: %d\n", custo3);

  return 0;
}
