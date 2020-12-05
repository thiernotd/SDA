
#include "citiesReader.h"
#include "arbreCouvrantMin.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>



void saveGraph(node_t **MST, int nbSommet){
  FILE* fileOut = NULL;
  fileOut = fopen("resuGraph.dat", "w");
  for(int i=0; i<nbSommet; i++)
  {
    node_t *tmp = MST[i];
    while(tmp != NULL)
    {
      fprintf(fileOut, "%d %d\n", i, tmp->valeur);
      tmp=tmp->next;
    }


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
  node_t *liste_adj[cities->number+1];
  node_t *ACM[cities->number+1];

  initialiser_tab_of_node(liste_adj, cities->number);
  initialiser_tab_of_node(ACM, cities->number);

  //dans un arbre couvrant minimal, il y a nbSommet - 1 aretes
  nombre_arete_MST = cities->number - 1;


  definir_binaryHeap_listAdjacence(liste_adj, cities);
  printf("\n\n");

  //si on veut afficher la liste d'adjacence, decommenter la ligne suivante
  //printf("Voici votre liste d'adjacence :\n");
  //afficher_listeAdjacence(liste_adj, popMin, cities->number);

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
  prim(liste_adj, cities->number, nombre_arete, sommet_source, ACM);
  clock_gettime(clk_id, &after);




  //printf("\n Voici votre arbre couvrant minimal : \n\n");
  //afficher_listeAdjacence(ACM, popMin, cities->number);
  printf("\n\n");
  printf("\n le cout total de notre arbre couvrant minimal est de %d km \n\n", cout_total(ACM, cities->number));

  //on convertit les nanoseconde en milliseconde donc *10^-6
  printf("Le temps d'exécution de votre fonction PRIM est de %f millisecondes \n\n", (long)(after.tv_nsec - before.tv_nsec)*0.000001);


  /*
   Écriture du graphe (chaque ligne correspond à une arête)
   !!! Ci-dessous, on écrit le graphe complet pour l'exemple.
   Dans votre rendu, cette fonction prendra un graphe en argument,
   pas une liste de villes.
  */
  //saveGraph(cities);
  saveGraph(ACM, cities->number);

  node_destroy(liste_adj);
  node_destroy(ACM);
  freeListOfCities(cities);

  return 0;
}
