#include "citiesReader.h"
#include "arbreCouvrantMin.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*
void saveGraph(ListOfCities * cities){
  FILE* fileOut = NULL;
  fileOut = fopen("resuGraph.dat", "w");
  for(int i=0; i<cities->number; i++){
    for(int j=0; j<i; j++){
      fprintf(fileOut, "%i %i\n", i, j);
    }
  }
  fclose(fileOut);
}
*/
void saveGraph(tasbinaire_t *MST){
  FILE* fileOut = NULL;
  fileOut = fopen("resuGraph.dat", "w");
  for(int i=0; i<MST->capacity; i++){
    fprintf(fileOut, "%d %d\n", MST->adj[i].u, MST->adj[i].v);

  }
  fclose(fileOut);
}

int main(int argc, char ** argv) {

  if( argc != 2 ){
    perror("Veuillez passer une population minimale en paramètre du programme");
    return EXIT_FAILURE;
  }
//-----------------------------------------------------------------
//--- READING cities
//-----------------------------------------------------------------

  int popMin = atoi(argv[1]);

  ListOfCities* cities;
  cities = citiesReader(popMin);

  // ... just to check! This line can be removed.
  for(int i=0; i<cities->number; i++){
    printf("%s %i %f %f\n", cities->name[i], cities->pop[i], cities->lon[i], cities->lat[i]);
  }

//-----------------------------------------------------------------
//--- COMPUTING complete graph
//-----------------------------------------------------------------



  int nombre_arete = (cities->number * (cities->number-1))/2;
  int nombre_arete_MST, sommet_source = 0;

  tasbinaire_t *heap = tasbinaire_create(nombre_arete);

  //dans un arbre couvrant minimal, il y a nbSommet - 1 aretes
  nombre_arete_MST = cities->number - 1;

  tasbinaire_t *MST = tasbinaire_create(nombre_arete_MST);




  definir_binaryHeap_longueur_arete(heap, popMin);
  printf("\n\n");
  afficher_binaryHeap_longueur_arete(heap, popMin, nombre_arete);
  printf("\n\n");
  prim(heap, cities->number, nombre_arete, sommet_source, MST);

  printf("\n Voici notre arbre couvrant minimal : \n\n");
  afficher_binaryHeap_longueur_arete(MST, popMin, nombre_arete_MST);
  printf("\n\n");
  printf("\n le cout total de notre arbre couvrant minimal est de %d km \n\n", cout_total(MST));



  /*
   Écriture du graphe (chaque ligne correspond à une arête)
   !!! Ci-dessous, on écrit le graphe complet pour l'exemple.
   Dans votre rendu, cette fonction prendra un graphe en argument,
   pas une liste de villes.
  */
  //saveGraph(cities);
  saveGraph(MST);

  tasbinaire_destroy(heap);
  tasbinaire_destroy(MST);
  freeListOfCities(cities);

  return 0;
}
