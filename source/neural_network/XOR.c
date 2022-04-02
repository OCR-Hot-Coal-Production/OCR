#include "../../include/neural_network/XOR.h"

double XOR_front_propagation(Network* network, double inputs[]){
	// add the inputs in the neural network
	for(unsigned int i = 0; i < network->layers[0]->nb_neurons; i++){
		network->layers[0]->neurons[i]->activation = inputs[i];
	}

	// proceed to the feedforward
	double sum = 0;
	for(unsigned int i = 1; i < network->nb_layers; i++){
		for(unsigned int j = 0; j < network->layers[i]->nb_neurons; j++){
			for(unsigned int l = 0;
				       	l < network->layers[i]->neurons[j]->nb_weights;l++){
				sum += network->layers[i-1]->neurons[l]->activation *
					network->layers[i]->neurons[j]->weights[l];
			}
			sum += network->layers[i]->neurons[j]->bias;
			network->layers[i]->neurons[j]->activation = sigmoid(sum);
			sum = 0;
		}
	}

	// return the activation of the output neuron
	//printf("the activation of the neuron is: %f\n",
	//	       	network->layers[network->nb_layers - 1]->neurons[0]->activation);
	return network->layers[network->nb_layers - 1]->neurons[0]->activation;
}


void XOR_trainning(Network* network, double eta, unsigned int epochs){
	double inputsList[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
	double expectedList[] = {0, 1, 1, 0};
	double cost = 0;

	for(unsigned int i = 0; i < epochs; i++){
		for(unsigned int j = 0; j < 4; j++){
			XOR_front_propagation(network, inputsList[j]);
			double expected[1] = {expectedList[j]};
			cost += cost_function(network, expected) / 4;
			back_propagation(network, expected);
			update(network, eta);
		}
		if(i % 1000 == 0){
			printf("EPOCH NUMBER %i/%i\n", i, epochs);
			for(unsigned int j = 0; j < 4; j++){
				printf("%f XOR %f | result: %f | expected: %f\n",
				inputsList[j][0], inputsList[j][1], XOR_front_propagation(network,
				inputsList[j]), expectedList[j]);
 			}
			printf("the cost of the neural network is: %f\n\n", cost);
		}
		cost = 0;
	}
	printf("EPOCH NUMBER %i/%i\n", epochs, epochs);
		for(unsigned int j = 0; j < 4; j++){
			printf("%f XOR %f | result: %f | expected: %f\n",
			inputsList[j][0], inputsList[j][1], XOR_front_propagation(network,
			inputsList[j]), expectedList[j]);
			double expected[1] = {expectedList[j]};
			cost += cost_function(network, expected) / 4;
 		}
		printf("the cost of the neural network is: %f\n", cost);
}
