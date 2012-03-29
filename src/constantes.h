#ifndef __CONSTANTES__
#define __CONSTANTES__


typedef char position;
enum{VIDE, OBSTACLE, CD, ROBOT};

//Tableau de conversion entre la valeur du capteur et la distance reelle
const int capteur_conversion[12][2] = {
{130, 87},
{120, 95},
{110,105},
{100,115},
{90, 131},
{80, 144},
{70, 170},
{60, 195},
{50, 235},
{40, 296},
{30, 384},
{20, 492}};

//Pins : 
#define PIN_CAPTEUR_COULEUR  1 //Le numero du pin où il y a le capteur (au hasard pour l'instant)
#define PIN_SERVO_EPAULE     2 
#define PIN_SERVO_COUDE      3 
#define PIN_SERVO_VOLET1     4 
#define PIN_SERVO_VOLET2     5 



#endif