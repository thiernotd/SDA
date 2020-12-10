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
#define INF 9999

void destroy_adj(int **adj, int taille)
{
  for(int i=0; i<taille; i++)
  {
    free(adj[i]);
  }
  free(adj);
}

void init_adjacence(ListOfCities* cities, int **adj)
{

	double latitudeI, latitudeJ, longitudeI, longitudeJ, longueur;


	int R = 6371;






	//si u > nb-1 ou v > nb-1 -> erreur
	for(int i =0; i<cities->number; i++)

		for(int j=0; j<i; j++)
		{




			//on converti les degrés en radian : formule -> latitude x π/180  | longitude x π/180
			latitudeI = cities->lat[i] * M_PI/180;

			latitudeJ = cities->lat[j] * M_PI/180;

			longitudeI = cities->lon[i] * M_PI/180;

			longitudeJ = cities->lon[j] * M_PI/180;


			longueur = R*acos(sin(latitudeI)*sin(latitudeJ) + cos(longitudeJ-longitudeI)*cos(latitudeI)*cos(latitudeJ));


			adj[i][j] = longueur;
      adj[j][i] = longueur;


		}

}

void afficher_adj(int nbSommet, int **heap)
{
	int i;

	for(i =0; i<nbSommet; i++)
	{
    for(int j =0; j<i; j++)

			printf("%d->%d: %d \n",i, j, heap[i][j]);

	}
}

void afficher_heap(int nbSommet, arete heap[nbSommet])
{
	int i;

	for(i =0; i<nbSommet; i++)
	{

			printf("%d->%d: %d \n",heap[i].u, heap[i].v, heap[i].longueur);

	}
}

int prim(int nbSommet, arete heap[nbSommet], int sommet_source, int **adj)
{
  int cpt=0, cout_total=0, i, u,v, longueur;
	//le sommet actuel, celui qui est visité et le sommet adjacent à actuel
	int adjacent, actuel = sommet_source;
	//compte le nombre de sommets adjacents à actuel
	int nbSommet_adjacent=0;
  int min;
	int nombre_arete = nbSommet*(nbSommet-1)/2;
  node_t noeud[nbSommet];

  for(i =0; i<nbSommet; i++)
  {
    noeud[i].visited = 0;
    noeud[i].longueur = INF;
    noeud[i].parent = -1;
  }
  noeud[actuel].visited = 1;
  noeud[actuel].longueur = 0;
  noeud[actuel].parent = actuel;
  /*for(i =0; i<nbSommet; i++)
  {
    printf("%d %d %d\n",noeud[i].visited, noeud[i].longueur, adj[actuel][i]);
  }*/

	//tant qu'au moins un sommet n'est pas visité
	while(tout_visiter(nbSommet, noeud) == 0)
	{

    for(i =0; i<nbSommet; i++)
    {
  		//si le sommet actuel n'est pas visité
      if(actuel != i)
      {
        if(adj[actuel][i] > 0 && noeud[i].visited == 0)
    		{
          if( adj[actuel][i] < noeud[i].longueur)
          {
            noeud[i].parent = actuel;
            noeud[i].longueur = adj[actuel][i];


          }
        }
      }

    }
    min = INF;

    for(i =0; i<nbSommet; i++)
    {
      if(noeud[i].visited == 0 && noeud[i].longueur < min )
      {
        min = noeud[i].longueur;
        actuel = i;
      }

    }
    noeud[actuel].visited = 1;
    u= noeud[actuel].parent;
    v = actuel;
    longueur = noeud[actuel].longueur;
    heap[cpt].u = u;
    heap[cpt].v = v;
    heap[cpt].longueur = longueur;

    cout_total = cout_total + longueur;

    cpt++;
  }
	return cout_total;
}


int tout_visiter( int taille, node_t noeud[taille])
{
          int i;
          for(i=0;i<taille;i++)
					//si au moins un sommet n'est pas visité, renvoie 0
             if(noeud[i].visited == 0 )
                 return 0;
					//sinon cela veut dire que tous les sommets sont visités, on renvoi donc 1
          return 1;
}
