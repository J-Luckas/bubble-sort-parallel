#include <omp.h>
#include <stdlib.h>
#include <stdio.h>

int is_impar( int n )
{
  return n % 2;
}
/* ----------- PARALELO -------- */
// Tempo de execucao: 25.187856
// 25.038235 

/* ----------- SERIAL -------- */
// Tempo de execucao: 25.212298
void bubble_sort_paralelo( int lista[], int num_elems ) {
  int i, j, aux, ini;
  for (i = 0; i < num_elems - 1; i++) {
    
    ini = is_impar( i );
    #pragma omp parallel for
    for (j = ini; j < num_elems - 1; j += 2) {
      if (lista[j] > lista[j + 1]) {
        aux = lista[j];
        lista[j] = lista[j + 1];
        lista[j + 1] = aux;
      }
    }
  }
}

void preencher_lista( int lista[], int num_elems ) {
  int i;
  for (i = 0; i < num_elems; i++) {
    lista[i] = rand() % 100;
  }
}

void exibir_lista( int lista[], int num_elems ) {
  int i;
  for (i = 0; i < num_elems; i++) {
    printf("%d ", lista[i]);
  }
  printf(" | ");
}

int main(){
  
  const int NUM_ELEMS = 100000;
  double tini, tfim;
  int l[ NUM_ELEMS ];

  preencher_lista( l, NUM_ELEMS );

  tini = omp_get_wtime();

  bubble_sort_paralelo( l, NUM_ELEMS );

  tfim = omp_get_wtime();

  exibir_lista( l, NUM_ELEMS );

  printf( "\nTempo de execucao: %fs\n", tfim - tini );

  return 0;
}