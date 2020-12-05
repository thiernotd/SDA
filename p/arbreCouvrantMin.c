

#include "arbreCouvrantMin.h"
#include "citiesReader.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//si la macro M_PI n'est pas defini
#ifndef M_PI
#define M_PI 3.1415926535897932
#endif

void node_destroy(node_t **noeud)
{
  node_t *next;
    for (node_t *curr = *noeud; curr; curr = next)
    {
        next = curr->next;
        free(curr);
    }

    *noeud = NULL;

}
void initialiser_tab_of_node(node_t **tab, int taille)
{
  for (int i = 0; i <= taille; i++)
  {
      tab[i] = NULL;
  }

}



//enqueue pour ajouter dans la file prioritaire
void tasbinaire_append(arete * tas, int taille, arete edge)
{

    //ajoute une arete a notre tableau d'arete de file prioritaire
    tas[taille] = edge;

    int position_pere = (taille-1)/2;
    int position_fils = taille;

    while(position_pere >= 0 && tas[position_pere].longueur > tas[position_fils].longueur)
    {

      arete temp = tas[position_pere];
      tas[position_pere] = tas[position_fils];
      tas[position_fils] = temp;

      position_fils = position_pere;
      position_pere = (position_pere-1)/2;


    }
}

arete extraire_min(arete *tas, int taille)
{
	/*if (tas->nbElement < 1)
	{
		printf("erreur, tas vide");
		exit(1);
	}*/

  int position_min = 0;


	arete min = tas[0];

	tas[0] = tas[taille-1];
	taille = taille-1;


	int i = 0;
	while(i < taille && 2*i+1 < taille && 2*i+2 < taille)
	{
		if(tas[2*i+1].longueur <= tas[2*i+2].longueur)
		{
      position_min = 2*i+1;
		}
		else
		{
      position_min = 2*i+2;
		}
		if(tas[i].longueur > tas[position_min].longueur)
		{

			arete temp = tas[i];
		  tas[i] = tas[position_min];
		  tas[position_min] = temp;



		}
		i = position_min;
	}

	return min;
}


node_t *ajouter_arete(node_t *noeud, int v, int longueur)
{
	 	node_t *tmp =  (node_t *) malloc(sizeof(node_t));
    tmp->valeur = v;
    tmp->next = noeud;
    tmp->longueur = longueur;

    noeud = tmp;
    return tmp;
}

void definir_binaryHeap_listAdjacence(node_t **heap, ListOfCities* cities)
{

	double latitudeI, latitudeJ, longitudeI, longitudeJ, longueur;


	int R = 6371;

	//si u > nb-1 ou v > nb-1 -> erreur
	for(int i =1; i<cities->number; i++)

		for(int j=0; j<i; j++)
		{




			//on converti les degrés en radian : formule -> latitude x π/180  | longitude x π/180
			latitudeI = cities->lat[i] * M_PI/180;

			latitudeJ = cities->lat[j] * M_PI/180;

			longitudeI = cities->lon[i] * M_PI/180;

			longitudeJ = cities->lon[j] * M_PI/180;

      //definition de la longueur de l'arete (i,j)
			longueur = R*acos(sin(latitudeI)*sin(latitudeJ) + cos(longitudeJ-longitudeI)*cos(latitudeI)*cos(latitudeJ));


			heap[i] = ajouter_arete(heap[i], j, longueur);
      heap[j] = ajouter_arete(heap[j], i, longueur);




		}

}

void afficher_listeAdjacence(node_t **heap, int popMin, int nbSommet )
{
	int i;


	for(i=1; i<=nbSommet; i++)
	{
    node_t *tmp = heap[i];
    while(tmp != NULL)
    {
      printf("%d->%d: %d \n",i, tmp->valeur, tmp->longueur);
      tmp = tmp->next;
    }
  }
}

void prim(node_t **liste_adj, int nbSommet, int nbArete, int sommet_source, node_t **MST)
{
	//le sommet actuel, celui qui est visité et le sommet adjacent à actuel
	int adjacent, actuel = sommet_source;
	//compte le nombre de sommets adjacents à actuel
	int nbSommet_adjacent=0;


	arete file_prioritaire[nbArete] ;
  int taille_file = 0;
	int visited[nbSommet];
	int i, u, v, longueur, k=0;
  arete edge;
  node_t *tmp;
	//contient le minimum de la file de priorité
	arete min;

	for(i =0; i<nbSommet; i++)
	{
		visited[i] = 0;
	}



	//tant qu'au moins un sommet n'est pas visité
	while(tout_visiter(visited, nbSommet) == 0)
	{

		//si le sommet actuel n'est pas visité
		if(visited[actuel] == 0)
		{
			//on marque le sommet comme étant visité
			visited[actuel] = 1;

			tmp = liste_adj[actuel];


      while(tmp != NULL)
      {

        edge.u = actuel;
        edge.v = tmp->valeur;
        edge.longueur = tmp->longueur;
        if(visited[edge.v] == 0)
        {
          tasbinaire_append(file_prioritaire, taille_file, edge);
          taille_file++;
        }
        tmp = tmp->next;
      }



			min = extraire_min(file_prioritaire, taille_file);
      taille_file--;

			//si le sommet actuel n'est pas present dans l'arete minimale
			if(min.u != actuel && min.v != actuel)
			{
				//si min.u n'est pas visité alors il s'agit du sommet adjacent et min.v est le sommet actuel
				if(visited[min.u] == 0 && visited[min.v] == 1)
				{
					adjacent = min.u;
					actuel = min.v;
				}
				//sinon min.u est le sommet actuel et min.v est le sommet adjacent
				else if(visited[min.u] == 1 && visited[min.v] == 0)
				{
					actuel = min.u;
					adjacent = min.v;
				}

			}


			if(min.u == actuel)
			{
				actuel = min.u;
				adjacent = min.v;
			}
			else if(min.v == actuel)
			{
				actuel = min.v;
				adjacent = min.u;
			}

			//si le sommet adjacent au sommet actuel dans l'arete min n'est pas visité, alors on ajoute l'arete min à notre MST
			if(visited[adjacent] == 0)
			{
			  MST[actuel]	= ajouter_arete(MST[actuel], adjacent, min.longueur);
			}


			//on recommence la boucle while avec le sommet adjacent
			actuel = adjacent;

		}
		else
		{

			min = extraire_min(file_prioritaire, taille_file);

			//si le sommet actuel n'est pas present dans l'arete minimale
			if(min.u != actuel && min.v != actuel)
			{
				//si min.u n'est pas visité alors il s'agit du sommet adjacent et min.v est le sommet actuel
				if(visited[min.u] == 0 && visited[min.v] == 1)
				{
					adjacent = min.u;
					actuel = min.v;
				}
				//sinon min.u est le sommet actuel et min.v est le sommet adjacent
				else if(visited[min.u] == 1 && visited[min.v] == 0)
				{
					actuel = min.u;
					adjacent = min.v;
				}

			}

			if(min.u == actuel)
			{
				actuel = min.u;
				adjacent = min.v;
			}
			else if(min.v == actuel)
			{
				actuel = min.v;
				adjacent = min.u;
			}


			//si le sommet adjacent au sommet actuel dans l'arete min n'est pas visité, alors on ajoute l'arete min à notre MST
			if(visited[adjacent] == 0)
			{
			  MST[actuel]	= ajouter_arete(MST[actuel], adjacent, min.longueur);
			}


			//on recommence la boucle while avec le sommet adjacent
			actuel = adjacent;

		}
	}

}


int tout_visiter(int *visited, int taille)
{
          int i;
          for(i=0;i<taille;i++)
					//si au moins un sommet n'est pas visité, renvoie 0
             if(visited[i] == 0 )
                 return 0;
					//sinon cela veut dire que tous les sommets sont visités, on renvoi donc 1
          return 1;
}

int cout_total(node_t **MST, int nbSommet)
{
	int cout_total = 0;

  for(int i=0; i<nbSommet; i++)
	{
    node_t *tmp = MST[i];
    while(tmp != NULL)
    {
      cout_total = cout_total + tmp->longueur;
      tmp = tmp->next;
    }
  }
	return cout_total;
}
