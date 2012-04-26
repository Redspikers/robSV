// Cette fonction convertit les impulsions reçu des roues codeuse
// en distance parcouru par les roues en mm depuis le début du match

//Paramètre : int compteurImpulsionRoueGauche , int compteurImpulsionRoueDroite (2 variables globales)

// Distance totale parcourue par chaque roue depuis le début du match : pointeur distanceRoueGauche et distanceRoueDroite


void distanceTotaleParcourue(int compteurImpulsionRoueGauche, int compteurImpulsionRoueDroite, int *distanceTotaleRoueDroite, int *distanceTotaleRoueGauche)
{
	
	*distanceTotaleRoueDroite = (compteurImpulsionRoueDroite / 20.25 ) * 189.028 ;
	*distanceTotaleRoueGauche = (compteurImpulsionRoueGauche / 20.25 ) * 189.028 ;
	
	
}

// Convertit le nb d'impulsions des roues codeuse en distancez parcourue
// par les roues depuis le dernier appel à cette fonction

void distanceParcourue(int compteurImpulsionRoueDroite, int compteurImpulsionRoueGauche, int *distanceRoueDroite, int *distanceRoueGauche) 
{
	
	
	*distanceRoueDroite = (( compteurImpulsionRoueDroite - *nbImpulsionDroite ) / 20.25 ) * 189.028 ;
	*distanceRoueGauche = (( compteurImpulsionRoueGauche - *nbImpulsionGauche ) / 20.25 ) * 189.028 ;
	
	
	
	// nbImpulsion(Gauche et Droite) reçoivent le nb d'impulsion. Ainsi a l' occurence n+1 de cette fonction
	// ces variables seront le nb d'impulsion lors de l'occurence n de cette fonction
	*nbImpulsionDroite = compteurImpulsionRoueDroite;
	*nbImpulsionGauche = compteurImpulsionRoueGauche;
	
	
}
