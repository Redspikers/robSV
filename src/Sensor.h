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

        void getValues();
        bool environEgal(int value1, int value2, int ecartmax);
        bool comprisEntre(int min, int max, int value);
        int* getObstacles();
        void analyse(int* distancesObstacle[]);

    private:
        Captor* captorBL;
        Captor* captorBM;
        Captor* captorBR;

        Captor* captorTL;
        Captor* captorTM;
        Captor* captorTR;

        int* valeur;
        int* distancesObstacles;

};

#endif /* SENSOR_H_ */
