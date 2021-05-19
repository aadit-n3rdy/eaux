#include "eaux.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main() {
	struct eaux_perceptron *ptron = malloc(sizeof(struct eaux_perceptron));
	if (ptron == NULL) {
		printf("well shit\n");
		return -1;
	}
	unsigned int layer_sizes[] = {3, 4, 3};
	printf("%u %u %u\n", layer_sizes[0], layer_sizes[1], layer_sizes[2]);
	unsigned int layer_count = 3;
	printf("Trying to init\n");
	eaux_perceptron_init(ptron, layer_sizes, layer_count, 5);
	float input[3] = {1, 2, 3};
	float output[3] = {0, 0, 0};
	eaux_perceptron_calc(ptron, &input[0], &output[0]);
	printf("Calc done\n");
	printf("%f %f %f\n", output[0], output[1], output[2]);
	eaux_perceptron_print_debug_info(ptron);
	eaux_perceptron_free(ptron);
	free(ptron);
	return 0;
}
