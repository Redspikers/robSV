/*
 * AStarLight.cpp
 *
 *  Created on: 21 avr. 2012
 *      Author: Koudja
 */

#include "AStarLight.h"


AStarLight::AStarLight(Map* map, int radius) {
	this->radius = radius;
	this->map = map;

	this->openList = NULL;
	this->closedList = NULL;
}

AStarLight::~AStarLight() {

}

Node* AStarLight::compute(Cell* begin, Cell* end) {
	/*
	 * 0 - Déclaration des variables (on ne le fait pas à la volée afin de réduire l'espace nécessaire)
	 */

	//1
	Node* currentNode = NULL;

	//2
	Cell** neighbors = NULL;
	int neighborsCount = 0;
	int i = 0;

	//3
	Cell* candidate = NULL;
	int candidateCost = 0;
	Node* candidateNode = NULL;
	Node* browseClosedList = NULL;
	bool inClosedList = false;
	Cell** candidateNeighbors = NULL;
	int candidateNeighborsCount = 0;
	bool blocked = false;
	int j = 0;

	//4
	NodeQueueItem* browseOpenList = NULL;
	Node* bestNode = NULL;

	/*
	 * 1 - Initialisation
	 */

	//Reset de la liste ouverte pour une nouvelle recherche
	this->openList = new NodeQueue();

	//On commence à partir du début - c'est le premier, donc pas de parent, pas de next
	currentNode = new Node(begin);
	currentNode->setParent(NULL);
	currentNode->setNext(NULL);
	this->closedList = currentNode;

	//Tant que la destination n'est pas atteinte
	do {
		/*
		 * 2 - Récupérer les voisins
		 */

		//Récuperer les cellules adjacents et leur nombres
		neighbors = this->map->getNeighbors(currentNode->getCell()->getX(), currentNode->getCell()->getY(), 1);
		neighborsCount = this->map->getNeighborsCount(currentNode->getCell()->getX(), currentNode->getCell()->getY(), 1);

		/*
		 * 3 - Chaque voisin est candidat en tant que noeud possible (i.e. openList)
		 */
		for(i = 0 ; i < neighborsCount ; i++) {
			candidate = neighbors[i];


			//Calcul du cout pour ce noeud - Celui de son parent + sa distance par rapport à l'arrivée
			//Attention, on ne prend volontairement pas de racine carrée pour garder l'exactitude (et ça prend moins de temps)
			candidateCost = currentNode->getCost() + (candidate->getX() - end->getX())*(candidate->getX() - end->getX()) + (candidate->getY() - end->getY())*(candidate->getY() - end->getY());

			//Recherche du candidat dans la closedList
			browseClosedList = this->closedList;
			inClosedList = false;
			while(browseClosedList != NULL && inClosedList == false) {
				if(browseClosedList->getCell() == candidate) {
					inClosedList = true;
				}
				browseClosedList = browseClosedList->getParent();
			}

			//Le noeud est joingnable (i.e. pas d'obstacles chez les voinsins
			candidateNeighbors = this->map->getNeighbors(candidate->getX(), candidate->getY(), this->radius);
			candidateNeighborsCount = this->map->getNeighborsCount(candidate->getX(), candidate->getY(), this->radius);
			blocked = false;
			for(j=0 ; (j < candidateNeighborsCount && !blocked) ; j++) {
				if(candidateNeighbors[j]->isBlocked()) {
					blocked = true;
				}
			}

			//Si le noeud est un obstacle ou fait parti de la closedList : on l'oublie, sinon on le traite
			if(!blocked && !inClosedList) {
				candidateNode = this->openList->getNode(candidate); // NULL if not in this list
				if(candidateNode != NULL) {
					//Si le noeud avait une moins bonne qualité, on met à jour la qualité et le parent
					if(candidateNode->getCost() > candidateCost) {
						candidateNode->setParent(currentNode);
						candidateNode->setCost(candidateCost);
					}

				//Sinon c'est que le noeud est un candidat légitime pour le chemin
				} else {
					//On ajoute le noeud dans la liste ouverte
					candidateNode = new Node(candidate);
					candidateNode->setParent(currentNode);
					candidateNode->setCost(candidateCost);

					this->openList->push(candidateNode);
				}
			}
		}

		/*
		 * 4 - Recherche du meilleur noeud dans la liste ouverte
		 */
		//Chercher le meilleur noeud de la liste ouverte et le mettre dans la liste fermée
		bestNode = NULL;
		browseOpenList = this->openList->getFirst();
		if(browseOpenList != NULL) {
			bestNode = browseOpenList->getNode();
			while(browseOpenList != NULL) {
				if(browseOpenList->getNode()->getCost() < bestNode->getCost()) {
					bestNode = browseOpenList->getNode();
				}
				browseOpenList = browseOpenList->getNext();
			}
		}
		//Retirer ce noeud de la liste ouverte
		this->openList->remove(bestNode);
		//Ajouter ce noeud dans la liste fermée
		this->closedList = bestNode;
		//Changer le noeud courant par le noeud ajoutée
		currentNode = bestNode;

	} while(currentNode->getCell() != end && this->openList->size() != 0);


	/*
	 * 5 - Solution de l'algorithme
	 */

	//Si il y a eu une solution - alors on retourne la solution (le premier noeud)
	//On construit le lien double de la liste de Node (jusqu'à présent, et pour le besoin de l'algorithme, on ne se servait que du lien montant (parnt)
	if(currentNode->getCell() == end) {
		browseClosedList = this->closedList;
		while(browseClosedList->getParent() != NULL) {
			browseClosedList->getParent()->setNext(browseClosedList);
			browseClosedList = browseClosedList->getParent();
		}
		return browseClosedList;
	}
	//Par défaut, on retourne NULL indiquant pas de solutions ou une erreur
	return NULL;
}
