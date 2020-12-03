#include "citiesReader.h"
#include "arbreCouvrantMin.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


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


  struct timespec before, after;
  clockid_t clk_id = CLOCK_REALTIME;

  int nombre_arete = (cities->number * (cities->number-1))/2;
  int nombre_arete_MST;
  int sommet_source;

  if(cities->number <=0 )
  {
    printf("Erreur, il n'existe pas de ville avec une telle population en France\n");
    return -1;
  }
  tasbinaire_t *heap = tasbinaire_create(nombre_arete);

  //dans un arbre couvrant minimal, il y a nbSommet - 1 aretes
  nombre_arete_MST = cities->number - 1;

  tasbinaire_t *MST = tasbinaire_create(nombre_arete_MST);




  definir_binaryHeap_longueur_arete(heap, popMin);
  printf("\n\n");

  //printf("Voici votre matrice d'adjacence :\n");
  //affiche matrice d'adjacence pour une population donnée
  //afficher_binaryHeap_longueur_arete(heap, popMin, nombre_arete);
  printf("\n\n");


  printf("Veuillez choisir votre sommet source, celui-ci doit être compris entre 0 et %d\n\n", (cities->number-1));
  scanf("%d", &sommet_source);

  while(sommet_source < 0 || sommet_source >= cities->number )
  {
    printf("Erreur, votre sommet doit être compris entre 0 et %d, veuillez réessayez\n\n", (cities->number-1));
    scanf("%d", &sommet_source);

  }



  printf("Vous avez choisi [%d] comme sommet source\n\n", sommet_source);

  // Ajout d'un élément et mesure du temps pris par l'opération.
  clock_gettime(clk_id, &before);
  prim(heap, cities->number, sommet_source, MST);
  clock_gettime(clk_id, &after);




  printf("\n Voici votre arbre couvrant minimal : \n\n");
  afficher_binaryHeap_longueur_arete(MST, popMin, nombre_arete_MST);
  printf("\n\n");
  printf("\n le cout total de notre arbre couvrant minimal est de %d km \n\n", cout_total(MST));

  //on convertit les nanoseconde en milliseconde donc *10^-6
  printf("Le temps d'exécution de votre fonction PRIM est de %f millisecondes \n\n", (long)(after.tv_nsec - before.tv_nsec)*0.000001);


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
