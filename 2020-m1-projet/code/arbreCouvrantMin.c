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

tasbinaire_t * tasbinaire_create(int nbarete){
  tasbinaire_t * res = (tasbinaire_t *) malloc( sizeof(tasbinaire_t) );
  res->adj = (arete *) malloc( sizeof(arete) * nbarete );
  res->capacity = nbarete;
  res->nbElement = 0;
  return res;
}

void tasbinaire_destroy(tasbinaire_t * a){
  if( a != NULL ){
    if( a->adj != NULL )
      free( a->adj );
    free( a );
  }
}


//enqueue pour ajouter dans la file prioritaire
void tasbinaire_append(tasbinaire_t * a, int u, int v, int longueur)
{

    if (a->capacity <= a->nbElement || a->capacity == 0)
    {
      printf("Le tas est plein \n");
    }else
    {
      a->adj[a->nbElement].u = u;
		  a->adj[a->nbElement].v = v;
			a->adj[a->nbElement].longueur = longueur;

      int position_pere = (a->nbElement-1)/2;
      int position_fils = a->nbElement;

      while(position_pere >= 0 && a->adj[position_pere].longueur > longueur)
      {

        arete temp = a->adj[position_pere];
        a->adj[position_pere] =  a->adj[position_fils];
        a->adj[position_fils] = temp;

        position_fils = position_pere;
        position_pere = (position_pere-1)/2;


      }
      a->nbElement++;


    }

}

arete extraire_min(tasbinaire_t * tas)
{
	if (tas->nbElement < 1)
	{
		printf("erreur, tas vide");
		exit(1);
	}
	int position_min = 0;
	int nbEchange = 0;

	arete min = tas->adj[0];

	tas->adj[0] = tas->adj[tas->nbElement-1];
	tas->nbElement = tas->nbElement - 1;


	int i = 0;
	while(i < tas->nbElement && 2*i+1 < tas->nbElement && 2*i+2 < tas->nbElement)
	{
		if(tas->adj[2*i+1].longueur <= tas->adj[2*i+2].longueur)
		{


			position_min = 2*i+1;
		}
		else
		{

			position_min = 2*i+2;
		}
		if(tas->adj[i].longueur > tas->adj[position_min].longueur)
		{

			arete temp = tas->adj[i];
		  tas->adj[i] = tas->adj[position_min];
		  tas->adj[position_min] = temp;
		  nbEchange = nbEchange+1;


		}
		i = position_min;
	}

	return min;
}




//definir longueur d'une arete
/*
void definir_longueur_arete(int u, int v)
{
	arete* edge = creer_arete(u,v);
	double latitudeU, latitudeV;

	int R = 6371;

	ListOfCities* cities;
	cities = citiesReader(250000);
	//si u > nb-1 ou v > nb-1 -> erreur
	if(u > cities->number-1 || u<0 || v > cities->number-1 || v<0)
	{
		printf("erreur, sommets inexistants");

	}

	//convertir degre en radian : formule -> latitude x π/180


	latitudeU = cities->lat[u] * M_PI/180;

	latitudeV = cities->lat[v] * M_PI/180;

	//definition de la longueur de l'arete (u,v)
	edge->longueur = R*acos(sin(latitudeU)*sin(latitudeV) + cos(latitudeU-latitudeV)*cos(latitudeU)*cos(latitudeV));

}
*/

void ajouter_arete(tasbinaire_t *a, int u, int v, int longueur)
{
	 	a->adj[a->nbElement].u = u;
		a->adj[a->nbElement].v = v;
		a->adj[a->nbElement].longueur = longueur;
		a->nbElement++;
}

void definir_binaryHeap_longueur_arete(tasbinaire_t *heap, int popMin)
{

	double latitudeI, latitudeJ, longitudeI, longitudeJ, longueur;


	int R = 6371;

	ListOfCities* cities;
	cities = citiesReader(popMin);




	//si u > nb-1 ou v > nb-1 -> erreur
	for(int i =0; i<cities->number; i++)

		for(int j=0; j<i; j++)
		{




			//on converti les degrés en radian : formule -> latitude x π/180  | longitude x π/180
			latitudeI = cities->lat[i] * M_PI/180;

			latitudeJ = cities->lat[j] * M_PI/180;

			longitudeI = cities->lon[i] * M_PI/180;

			longitudeJ = cities->lon[j] * M_PI/180;
			/*heap->adj[heap->nbElement].u = i;
			heap->adj[heap->nbElement].v = j;
			heap->adj[heap->nbElement].longueur = R*acos(sin(latitudeI)*sin(latitudeJ) + cos(longitudeJ-longitudeI)*cos(latitudeI)*cos(latitudeJ));
			heap->nbElement++;*/
			longueur = R*acos(sin(latitudeI)*sin(latitudeJ) + cos(longitudeJ-longitudeI)*cos(latitudeI)*cos(latitudeJ));


			ajouter_arete(heap, i, j, longueur);

			//definition de la longueur de l'arete (i,j)
			//cost[i][j] = R*acos(sin(latitudeI)*sin(latitudeJ) + cos(longitudeJ-longitudeI)*cos(latitudeI)*cos(latitudeJ));
			//printf("%d->%d: %d\n  ",i,j, cost[i][j]);

		}
	freeListOfCities(cities);
}

void afficher_binaryHeap_longueur_arete(tasbinaire_t *heap, int popMin, int nombre_arete )
{
	int i;

	for(i =0; i<nombre_arete; i++)
	{

			printf("%d->%d: %d \n",heap->adj[i].u, heap->adj[i].v, heap->adj[i].longueur);

	}
}

void prim(tasbinaire_t *a, int nbSommet, int nombre_arete, int sommet_source, tasbinaire_t * MST)
{
	//le sommet actuel, celui qui est visité et le sommet adjacent à actuel
	int adjacent, actuel = sommet_source;
	//compte le nombre de sommets adjacents à actuel
	int nbSommet_adjacent=0;

	tasbinaire_t * file_prioritaire = tasbinaire_create(nombre_arete);
	int visited[nbSommet];
	int i, u, v, longueur, k=0;


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

			//pour toutes les aretes
			for(i =0; i<nombre_arete; i++)
			{
				/* on compte le nombre de sommets adjacents à actuel.
				si u est le sommet actuel alors v est son sommet adjacent et vice versa,
				et donc dans ce cas on incrémente nbSommet_adjacent
				Aussi, on enregistre la position de chaque sommet adjacent à actuel pour pouvoir
				acceder aux sommets adjacents à actuel à partir du tableau a->adj
				*/

				if(a->adj[i].u == actuel || a->adj[i].v == actuel)
				{
					nbSommet_adjacent++;
				}
			}

			//tableau contenant la position de chaque sommets adjacents à actuel
			int position_sommet_adjacent[nbSommet_adjacent];
			for(i =0; i<nombre_arete; i++)
			{
				if(a->adj[i].u == actuel || a->adj[i].v == actuel)
				{
					position_sommet_adjacent[k] = i;
					k++;
				}
			}
			k = 0;



			//pour tous les sommets adjacents à actuel
			for(i =0; i<nbSommet_adjacent; i++)
			{

				u = a->adj[position_sommet_adjacent[i]].u;
				v = a->adj[position_sommet_adjacent[i]].v;
				longueur = a->adj[position_sommet_adjacent[i]].longueur;

				/* si u est le sommet actuel et son sommet adjacent v n'est pas visité,
				ou si v est le sommet actuel et son sommet adjacent u n'est pas visité,
				alors on ajoute dans la file de priorité les sommets u, v ainsi que sa longueur*/
				if((u == actuel && visited[v] == 0) || (v == actuel && visited[u] == 0) )
					tasbinaire_append(file_prioritaire, u, v, longueur);

			}
			nbSommet_adjacent = 0;


			printf("\n avant extraction if\n");
			afficher_binaryHeap_longueur_arete(file_prioritaire, 250000, nombre_arete);

			min = extraire_min(file_prioritaire);
			printf("\napres extraction if \n");
			afficher_binaryHeap_longueur_arete(file_prioritaire, 250000, nombre_arete);

			printf("\n sommet adjacent min %d->%d\n", min.u, min.v);

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

			printf("\n sommet adjacent %d->%d", actuel, adjacent);
			//si le sommet adjacent au sommet actuel dans l'arete min n'est pas visité, alors on ajoute l'arete min à notre MST
			if(visited[adjacent] == 0)
			{
			 	ajouter_arete(MST, actuel, adjacent, min.longueur);
			}


			//on recommence la boucle while avec le sommet adjacent
			//if(adjacent == )
			actuel = adjacent;

		}
		else
		{
			printf("\n avant extraction else\n");
			afficher_binaryHeap_longueur_arete(file_prioritaire, 250000, nombre_arete);

			min = extraire_min(file_prioritaire);
			printf("\napres extraction else \n");
			afficher_binaryHeap_longueur_arete(file_prioritaire, 250000, nombre_arete);

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
				ajouter_arete(MST, actuel, adjacent, min.longueur);
			}


			//on recommence la boucle while avec le sommet adjacent
			actuel = adjacent;

		}
	}

		tasbinaire_destroy(file_prioritaire);
		/*
		free(visited);
		free(position_sommet_adjacent);*/
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

int cout_total(tasbinaire_t *MST)
{
	int cout_total = 0;
	for(int i=0;i<MST->capacity;i++)
	{
		cout_total = cout_total + MST->adj[i].longueur;
	}
	return cout_total;
}
