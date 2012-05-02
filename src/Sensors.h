/*
 * Sensor.h
 *
 *  Created on: 1 mai 2012
 *      Author: claude
 */

#ifndef SENSOR_H_
#define SENSOR_H_
#include "Captor.h"
#include "Pin.h"

class Sensor {
    public:
        Sensor();
        void GetValues();
        boolean EnvironEgal();
        int* GetObstacles();
    private:
        Captor *HautDroit;
        Captor *HautGauche;
        Captor *Milieu;
        Captor *BasDroit;
        Captor *BasMilieu;
        Captor *BasGauche;

};

#endif /* SENSOR_H_ */
