/*
 * AStarLight.cpp
 *
 *  Created on: 21 avr. 2012
 *      Author: Koudja
 */

#include "AStarLight.h"


AStarLight::AStarLight() {
	this->map = new Map();

	this->openList = new NodeQueue();
	this->closedList = new NodeQueue();
}

AStarLight::AStarLight(Map* map) {
	this->map = map;

	this->openList = new NodeQueue();
	this->closedList = new NodeQueue();
}

AStarLight::~AStarLight() {

}

Node* AStarLight::getBestNode() {
	Node *result = NULL;

	Node *tmp = NULL;

	if(this->openList->size() > 0) {
		for(int i=0 ; i < this->openList->size() ; i++) {
			tmp = this->openList->get(i);
			if(tmp->getCost() < result->getCost()) {
				result = tmp;
			}
		}
	}

	return result;
}

bool AStarLight::compute(Node* begin, Node* end) {
	bool result = false;

	Node* currentNode = NULL;
	Node* bestNode = NULL;

	Node** neighbors = NULL;
	Node* currentNeighbor = NULL;

	int i = 0;
	int neighborsCount = 0;
	int currentCost = 0;

	//Reset des listes pour une nouvelle recherche
	this->openList = new NodeQueue();
	this->closedList = new NodeQueue();

	//On commence à partir du début
	currentNode = begin;
	//Le noeud où on est est forcement dans la liste fermée car obligatoirement un point de passage : on l'ajotue donc
	this->closedList->push(begin);

	//Tant que la destination n'est pas atteinte
	while(currentNode != end) {
		//Récuperer les noeuds adjacents et leur nombres
		neighbors = this->map->getNeighbors(currentNode->getX(), currentNode->getY());
		neighborsCount = this->map->getNeighborsCount(currentNode->getX(), currentNode->getY());

		//Pour chaque voisins
		for(i = 0 ; i < neighborsCount ; i++) {
			currentNeighbor = neighbors[i];

			//Calcul du cout pour ce noeud - Celui de son parent + sa distance par rapport à l'arrivée
			currentCost = currentNode->getCost() + sqrt((currentNeighbor->getX() - end->getX())*(currentNeighbor->getX() - end->getX()) + (currentNeighbor->getY() - end->getY())*(currentNeighbor->getY() - end->getY()));

			//Si le noeud est un obstacle
			if(currentNeighbor->isBlocked()) {
				//On l'oublie
			//Sinon si le noeud est un voisin déjà présent dans la liste fermée
			} else if(this->closedList->contains(currentNeighbor)) {
				//On l'oublie
			//Sinon si le noeud est déjà présent dans la liste ouverte
			} else if(this->openList->contains(currentNeighbor)) {
				//Si le noeud avait une moins bonne qualité, on met à jour la qualité et le parent
				if(currentNeighbor->getCost() > currentCost) {
					currentNeighbor->setParent(currentNode);
					currentNeighbor->setCost(currentCost);
				}

			//Sinon
			} else {
				//On ajout le noeud dans la liste ouverte
				currentNeighbor->setParent(currentNode);
				currentNeighbor->setCost(currentCost);
				this->openList->push(currentNeighbor);

			}
			//FinSi
		}
		//FinPour

		//Chercher le meilleur noeud de la liste ouverte et le mettre dans la liste fermée
		bestNode = this->getBestNode();

		//Si pas de solutions
		if(bestNode == NULL) {
			//Fin de la boucle - Erreur, destination impossible
			break;
		//Sinon
		} else {
			//Retirer ce noeud de la liste ouverte
			this->openList->remove(bestNode);

			//Ajouter ce noeud dans la liste fermée
			this->closedList->push(bestNode);

			//Changer le noeud courant par le noeud ajoutée
			currentNode = bestNode;
		}
		//FinSi

	}
	//FinTq

	//Si il y a eu une solution
	if(currentNode == end) {
		//Renvoyer le premier noeud
		result = true;
	}

	return result;
}
