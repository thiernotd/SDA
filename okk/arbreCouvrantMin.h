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
typedef struct tasbinaire_s{
  arete * adj;
  int capacity; //taille
  int nbElement;
} tasbinaire_t;

tasbinaire_t *tasbinaire_create(int nbarete);

void tasbinaire_destroy(tasbinaire_t * a);

void tasbinaire_append(tasbinaire_t * a, int u, int v, int longueur);

arete extraire_min(tasbinaire_t * a);






void ajouter_arete(tasbinaire_t *a, int u, int v, int longueur);

//definir longueur d'une arete
void definir_binaryHeap_longueur_arete(tasbinaire_t *a, int popMin);

void afficher_binaryHeap_longueur_arete(tasbinaire_t *a, int popMin, int nombre_arete );

void prim(tasbinaire_t *a, int nbSommet, int sommet_source, tasbinaire_t * MST);

int tout_visiter(int *visited, int taille);

int cout_total(tasbinaire_t *MST);

#endif
