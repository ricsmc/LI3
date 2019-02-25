#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define VENDAS_SIZE 100
#define FILE_SIZE   10
#define CLIEN       20000
#define PROD        200000
#define VENDAS      1000000
#define HSIZE       26

#define USADO 1
#define N_USADO 0

typedef struct clientes{
  char* str;
  int info;
  struct clientes *next;
} *Clientes;

typedef Clientes HashClientes[HSIZE];


// 0 - 25 == A-Z mais facil na hash, nao e preciso guardar key
int upperCaseToInt (char c) {
  return (c-'0'-17);
}

char intToUpperCase(int x) {
  return (x+'0'+17);
}

// lligada add
void addToHash(Clientes *pt, char *string) {;
  //struct clientes *pt = client;
  if ((*pt)->info == USADO) {
    while(*pt) {
      pt = &((*pt)->next);
    }
    *pt = malloc(sizeof(struct clientes));
  }

  //pt = malloc(sizeof(struct clientes));
  (*pt)->str = strdup(string);
  (*pt)->info = USADO;
  (*pt)->next = NULL;
}

void printHashIndex(Clientes *cliente) {
  while((*cliente) && (*cliente)->info == USADO) {
    printf("%s", (*cliente)->str);
    cliente = &((*cliente)->next);
  }
}

// transforma clientes em hash de A--Ẑ
void criaHash (char **clientes, int* size, HashClientes hasht){
  char primeiro;
  int hashIndex;
    for (int i = 0; i<*size;i++) {
      primeiro = clientes[i][0];
      //printf("%c\n", primeiro); certo
      hashIndex=upperCaseToInt(primeiro);
      //printf("%s\n", clientes[i]); certo
      addToHash(&hasht[hashIndex],clientes[i]);

    }
    printHashIndex(&hasht[3]); // 0--25 == A--Z
    //printf("%s\n", hasht[0]->next->str);
}

void readFile(char** array, char* nomeF, int* lidos, int* maior){
  int size;
  if (strcmp(nomeF,"Vendas_1M"))
    size = FILE_SIZE;
  else
    size = VENDAS_SIZE;

  char buffer[20]; //ficheiro para abrir, necessário mudar quando for em pastas diferentes
  sprintf(buffer, "%s.txt", nomeF);

  FILE *fp;
  char s[size];
  int i = 0;

  fp = fopen(buffer,"r");
  while (fgets(s,size,fp)){
    array[i++] = strdup (s);
    *maior = strlen(s) > (*maior) ? strlen(s) : (*maior); // Problema: Lê '\n'
  }
  fclose(fp);
  *lidos = i;
}

int main () {
  /*int x = 25;
  printf("%c\n",intToUpperCase(x) );
  char c = 'Z';
  printf("%d\n", upperCaseToInt(c));
  char *str = strdup("OLA");
  char *str2 =strdup(str + 1);
  printf("%s\n", str2);
  */
  char str[15] = "Clientes";
  char** array = malloc(sizeof(char)*CLIEN*FILE_SIZE);
  int lidos = 0, maior = 0;
  readFile (array,str,&lidos,&maior);
  HashClientes hasht;
  for (int i =0; i<HSIZE;i++) {
    hasht[i] = malloc(sizeof(struct clientes));
    hasht[i]->info = N_USADO;
   // hasht[i]->str = strdup("NULL");
    hasht[i]->next = NULL;
  }
  //hasht[25]->str = strdup("A8442");
  //hasht[25]->next = malloc(sizeof(struct clientes));
  //hasht[25]->next->str = strdup("H8441");
  //hasht[25]->next->next = NULL;

  criaHash(array,&lidos,hasht);
  //printf("%s\n",hasht[25]->str);
  //printHashIndex(hasht[0]);
  free(array);
  for (int i = 0; i<HSIZE; i++) {
    free(hasht[i]);
  }
  return 0;
}
