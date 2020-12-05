#include "citiesReader.h"

#ifndef ARBRE_COUVRANT_MIN
#define ARBRE_COUVRANT_MIN



//structure arête d'un arbre couvrant minimum
typedef struct arete
{
	int u; //premier sommet
	int v; //deuxieme sommet
	int longueur; //longueur de l'arete du couple (u,v)
}arete;

//structure de tas binaire minimale
struct node{
  struct node *next;
  int valeur; //taille
  int longueur;
};
typedef struct node node_t;


void node_destroy(node_t **noeud);

void initialiser_tab_of_node(node_t **tab, int taille);

void tasbinaire_append(arete * tas, int taille, arete edge);

arete extraire_min(arete *tas, int taille);



node_t *ajouter_arete(node_t *noeud, int sommet, int longueur);

//definir longueur d'une arete
void definir_binaryHeap_listAdjacence(node_t **heap, ListOfCities* cities);

void afficher_listeAdjacence(node_t **heap, int popMin, int nbSommet);

void prim(node_t **liste_adj, int nbSommet, int nbArete, int sommet_source, node_t **MST);

int tout_visiter(int *visited, int taille);

int cout_total(node_t **MST, int nbSommet);

#endif
