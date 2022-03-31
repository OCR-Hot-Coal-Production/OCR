#include "../../include/neural_network/neural_network.h"
#include "../../include/neural_network/save_and_load.h"
#include "../../include/neural_network/XOR.h"
#include "../../include/neural_network/data_set.h"
#include <stdio.h>
#include <math.h>

int main(){
	
	//load_image();
	//load_label();

	
	unsigned int sizes[] = {2,2,1};
	Network* network = initNetwork(sizes, sizeof(sizes)/sizeof(unsigned int));
	//Network* network = loadNetwork("test1");
	//saveNetwork(network, "test1");
	

	XOR_trainning(network, 0.4, 4000);
	//feedforward(network, inputs);
	//saveNetwork(network, "test1");
	freeNetwork(network);
	return 0;
}
