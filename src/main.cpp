#include "include.h"



int main(void) {
	setup();

	for (;;)
		loop();

	return 0;
}

void setup() {
	
	attachInterrupt(0, incrementation_roueCodeuseGauche, RISING);// 0 correspond à la pin digital 2. le signal de la roue codeuse doit y etre relié
	attachInterrupt(1, incrementation_roueCodeuseDroite, RISING);// 1 correspond à la pin digital 3
	

}



void loop() {
	
	

}

