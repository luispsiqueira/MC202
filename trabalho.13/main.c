#include <stdio.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <stdlib.h>

struct inserir{
  char n_inserido[251];
};

typedef struct inserir inserir;

struct hash{
  int timestamp;
  int chave;
  char frase[251];
};

typedef struct hash hash;

hash tabela_hash[6257 + 1]; //6257 e' o numero primo mais proximo de 6250, que por sua vez e' o numero necessario para que 5000 seja no maximo 80% da capacidade

//inicializa a tabela de hashing colocando o valor de -1 para mostrar que o espaco esta vazio 
void inicializar(){
  for(int i = 0; i < 6257; i++){
    tabela_hash[i].chave = -1;
  }
}

// retorna um numero bem grande da transformacao da string em numero
unsigned long djb2(unsigned char *str) {
  unsigned long hash = 5381;
  int c;
  
  while ((c = *str++)){
    hash = ((hash << 5) + hash) ^ c; 
    hash = hash * 33 ^ c;
  }
  
  return hash;
}

//busca a frase para ver se ela ja foi inserida
//retorna h se ja possui a frase e 0 se nao possui
int busca(int ch, char x[251]){
  int h, h1, h2, i;
  h = ch % 6257;
  if(ch < 0){
    h = h * (-1);
  }
  if(tabela_hash[h].chave == ch){
    return h;
  }

  i = 1;
  while(tabela_hash[h].chave != -1){
    h1 = ch % 6257;
    h2 = 1 + (ch % 6255);
    h = (h1 + (i*h2)) % 6257;
    if(tabela_hash[h].chave == ch){
      return h;
    }
    i++;
  }
  return 0;
}

//
int insert(int a,int ch, char x[251]){
  int h, h1, h2, i, j;
  h = ch % 6257;
  i = 1;
  j = 0;
  while(tabela_hash[h].chave >= 0){
    h1 = ch % 6257;
    h2 = 1 + (ch % 6255);
    h = (h1 + (i*h2)) % 6257;
    i++;
  } 
  if(tabela_hash[h].chave < 0){
    tabela_hash[h].timestamp = a;
    tabela_hash[h].chave = ch;
    while(j < strlen(x)){
      tabela_hash[h].frase[j] = x[j];
      j++;
    }
    return h;
  }

  return 0;
}


//insere a funcao caso ela nao esteja na tabela
int add_na_tabela(int a, int ch, char x[251]){
  int i = 0, j = 0;
  i = busca(ch, x);
  if(i == 0){
    insert(a, ch, x);
    printf("[");
    while(j < strlen(x)){
      printf("%c", x[j]);
      j++;
    }
    printf("] foi inserida\n");
    return 1;
  }
  else{
    printf("[");
    while(j < strlen(x)){
      printf("%c", x[j]);
      j++;
    }
    printf("] ja esta na tabela\n");
    return 0;
  }
}


//remover a frase dada ou retorna que a frase nao esta no hash
int remover_na_tabela(int ch, char x[251]){
  int b = 0, j = 0;
  b = busca(ch, x);
  if(b == 0){
    printf("[");
    while(j < strlen(x)){
      printf("%c", x[j]);
      j++;
    }
    printf("] nao esta na tabela\n");
    return 0;
  }
  else{
    tabela_hash[b].timestamp = -1;
    tabela_hash[b].chave = -2;
    tabela_hash[b].frase[0] = '\0';
    
    printf("[");
    while(j < strlen(x)){
      printf("%c", x[j]);
      j++;
    }
    printf("] foi removida\n");
    return 1;
  }
}


// funcao main
int main(){
  inicializar();
  int a = 0, ch = 0, i = 0, b = 0;
  char comando[2];
  char inserido[251];
  while(a != -1){
    scanf("%2c", comando);
    scanf("%[^\n]", inserido);
    
    if((comando[0] != 'i') && (comando[0] != 'b') && (comando[0] != 'r') && (comando[0] != 'f')){
      comando[0] = comando[1];
      i = 0;
      while(i < strlen(inserido) - 1){
        inserido[i] = inserido[i + 1];
        i++;
      }
      inserido[strlen(inserido) - 1] = '\0';
    }

    ch = djb2((unsigned char*) inserido);

    if(ch < 0){
      ch = ch * (-1);
    }
    
    if(comando[0] == 'i'){
      i = add_na_tabela(a, ch, inserido);
      if(i == 1){
        a++;
      }
    }

    else if(comando[0] == 'b'){
      b = busca(ch, inserido);
      i = 0;
      if(b == 0){
        printf("[");
        while(i < strlen(inserido)){
          printf("%c", inserido[i]);
          i++;
        }
        printf("] nao esta na tabela\n");
      }
      else{
        printf("[");
        while(i < strlen(inserido)){
          printf("%c", inserido[i]);
          i++;
        }
        printf("] esta na tabela, timestamp %d\n", tabela_hash[b].timestamp);
      }
    }

    else if(comando[0] == 'r'){
      remover_na_tabela(ch, inserido);
    }

    else if(comando[0] == 'f'){
      a = -1;
    }
    comando[0] = '\0';
    inserido[0] = '\0';
  }
  return 0;
}

