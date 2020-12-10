#ifndef ARBRE_COUVRANT_MIN
#define ARBRE_COUVRANT_MIN
#include "citiesReader.h"


//structure arête d'un arbre couvrant minimum
typedef struct arete
{
	int u; //premier sommet
	int v; //deuxieme sommet
	int longueur; //longueur de l'arete du couple (u,v)
}arete;

//structure de tas binaire minimale
typedef struct node_t{
  int parent;
  int visited; //taille
  int longueur;
} node_t;


//definir longueur d'une arete
void init_adjacence(ListOfCities* cities, int **adj);

void afficher_heap(int nbSommet, arete heap[nbSommet]);

void afficher_adj(int nbSommet, int **heap);

int prim(int nbSommet, arete heap[nbSommet], int sommet_source, int **adj);

int tout_visiter(int taille, node_t noeud[taille]);

void destroy_adj(int **adj, int taille);


#endif
