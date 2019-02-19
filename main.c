#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 10
#define FILE_SIZE 200000

void lerFicheiro (char* s[]){
  FILE *fp = fopen ("/Produtos.txt","r");

  while (fgets (s ,BUFFER ,fp));
  fclose (fp);
}

int main(){
    char prod[FILE_SIZE];
    lerFicheiro (&prod);
    printf("%s" , prod);
    return 0;

}
