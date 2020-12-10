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
void saveGraph(int nbSommet, arete heap[nbSommet], char agr[10]){
  FILE* fileOut = NULL;
  char nomdefichier[100]="resuGraph";
  strcat(nomdefichier, agr);
  strcat(nomdefichier, ".dat");
  fileOut = fopen(nomdefichier, "w");
  for(int i=0; i<nbSommet; i++){
    fprintf(fileOut, "%d %d\n", heap[i].u, heap[i].v);

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
  cities = citiesReader(popMin,argv[1]);

  // ... just to check! This line can be removed.
/*  for(int i=0; i<cities->number; i++){
    printf("%s %i %f %f\n", cities->name[i], cities->pop[i], cities->lon[i], cities->lat[i]);
  }*/

//-----------------------------------------------------------------
//--- COMPUTING complete graph
//-----------------------------------------------------------------


  /*struct timespec before, after;
  clockid_t clk_id = CLOCK_REALTIME;*/

  int nombre_arete = (cities->number * (cities->number-1))/2;
  int nombre_arete_MST;
  int sommet_source, cout_total;

  if(cities->number <=0 )
  {
    printf("Erreur, il n'existe pas de ville avec une telle population en France\n");
    return -1;
  }
  //int adj[cities->number][cities->number];
  int **adj = (int **)malloc(cities->number * sizeof(int*));
  for(int i = 0; i < cities->number; i++)
    adj[i] = (int *)malloc(cities->number * sizeof(int));

  arete heap[cities->number];

  init_adjacence(cities, adj);

  printf("\n\n");



  printf("Veuillez choisir votre sommet source, celui-ci doit être compris entre 0 et %d\n\n", (cities->number-1));
  scanf("%d", &sommet_source);

  while(sommet_source < 0 || sommet_source >= cities->number )
  {
    printf("Erreur, votre sommet doit être compris entre 0 et %d, veuillez réessayez\n\n", (cities->number-1));
    scanf("%d", &sommet_source);

  }


  //afficher_adj(cities->number, adj);

  printf("Vous avez choisi [%d] comme sommet source\n\n", sommet_source);
  clock_t begin = clock();

  // Ajout d'un élément et mesure du temps pris par l'opération.
  //clock_gettime(clk_id, &before);
  cout_total = prim(cities->number, heap, sommet_source, adj);
  //clock_gettime(clk_id, &after);

  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  //printf("\n Voici votre arbre couvrant minimal : \n\n");
  //afficher_heap(cities->number-1, heap);




  //printf("\n Voici votre arbre couvrant minimal : \n\n");
  //afficher_binaryHeap_longueur_arete(MST, popMin, nombre_arete_MST);
  printf("\n\n");
  printf("\n le cout total de notre arbre couvrant minimal est de %d km \n\n", cout_total);

  //on convertit les nanoseconde en milliseconde donc *10^-6
  printf("Le temps d'exécution de votre fonction PRIM est de %f secondes \n\n", time_spent);


  /*
   Écriture du graphe (chaque ligne correspond à une arête)
   !!! Ci-dessous, on écrit le graphe complet pour l'exemple.
   Dans votre rendu, cette fonction prendra un graphe en argument,
   pas une liste de villes.
  */
  //saveGraph(cities);
  saveGraph(cities->number-1, heap,argv[1]);

  destroy_adj(adj, cities->number);
  freeListOfCities(cities);

  return 0;
}
