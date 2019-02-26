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

HashClientes hasht;

// 0 - 25 == A-Z mais facil na hash, nao e preciso guardar key
int upperCaseToInt (char c) {
  return (c-'0'-17);
}

char intToUpperCase(int x) {
  return (x+'0'+17);
}

void addToHash(Clientes *pt, char *string) {
  if ((*pt)->info == USADO) {
    while(*pt) {
      pt = &((*pt)->next);
    }
    *pt = malloc(sizeof(struct clientes));
  }
  (*pt)->str = strdup(string); 
  (*pt)->info = USADO;
  (*pt)->next = NULL;
}

void printHashIndex(Clientes *cliente) {
  int quantos = 0;
  while((*cliente) && (*cliente)->info == USADO) {
    printf("%s\n", (*cliente)->str);
    quantos++;
    cliente = &((*cliente)->next);
  }
  printf("Foram lidos %d válidos\n", quantos);
}

int isValidClient (char *s) {
    int result = atoi(s+1);
    int x = upperCaseToInt(s[0]);
    return (x>=0 && x<=25 && result>=1000 && result <=5000);
}
// transforma clientes em hash de A--Ẑ
void criaHash (char *clientes, HashClientes hasht){
  char primeiro;
  primeiro = clientes[0];
  if (isValidClient(clientes)) addToHash(&hasht[primeiro % 'A'],clientes);
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
  char *x;
  int i = 0;

  fp = fopen(buffer,"r");
  if (!fp) exit(1);
  while (fgets(s,size,fp)){
    x = strdup (strtok(s,"\n\r"));
    criaHash(x,hasht);
    *maior = strlen(s) > (*maior) ? strlen(s) : (*maior); // Problema: Lê '\n' not anymore
  }  
  fclose(fp);
  *lidos = i;

}

int main () {
  
  char str[15] = "Clientes";
  char** array = malloc(sizeof(char)*CLIEN*FILE_SIZE);
  int lidos = 0, maior = 0;
  for (int i =0; i<HSIZE;i++) {
    hasht[i] = malloc(sizeof(struct clientes));
    hasht[i]->info = N_USADO;
    hasht[i]->next = NULL;
  }
  readFile (array,str,&lidos,&maior);  
  printHashIndex(&hasht[3]); // 0--25 A--Z
  free(array);
  for (int i = 0; i<HSIZE; i++) {
    free(hasht[i]);
  }
  return 0;
}
