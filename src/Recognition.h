/*
 * Recognition.h
 *
 *  Created on: 1 mai 2012
 *      Author: claude
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#include "Sensor.h"
#include "Pin.h"

class Recognition {
    public:
        Recognition();

        void getValues();
        bool environEgal(int value1, int value2, int ecartmax);
        bool comprisEntre(int min, int max, int value);
        int* getObstacles();
        void analyse(int* distancesObstacle[]);

    private:
        Sensor* captorBL;
        Sensor* captorBM;
        Sensor* captorBR;

        Sensor* captorTL;
        Sensor* captorTM;
        Sensor* captorTR;

        int* valeur;
        int* distancesObstacles;

};

#endif /* SENSOR_H_ */
