// Cette fonction convertit les impulsions reçu des roues codeuse
// en distance parcouru par les roues en mm

//Paramètre : int compteurImpulsionRoueGauche , int compteurImpulsionRoueDroite (2 variables globales)

// Distance parcourue par chaque roue : pointeur distanceRoueGauche et distanceRoueDroite


void distanceParcouru(int compteurImpulsionRoueGauche, int compteurImpulsionRoueDroite, int *distanceRoueDroite, int *distanceRoueGauche)
{
	
	*distanceRoueDroite = (compteurImpulsionRoueDroite / 20.25 ) * 189.028 ;
	*distanceRoueGauche = (compteurImpulsionRoueGauche / 20.25 ) * 189.028 ;
	
	
}
