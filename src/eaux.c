#include "eaux.h"

#include <mosaic.h>

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

float eaux_weight_range = 1;
float eaux_weight_adjust = 0.1;

float set_random(float dud) {
	float i = (float)(rand() % 100 - 50)/50.0 * eaux_weight_range;
	return i;
}

float activate(float val) {
	return -2.0/(1.0+exp(-val)) + 1.0;
}

int eaux_perceptron_init(struct eaux_perceptron *ptron,
		unsigned int *layer_sizes,
		unsigned int layer_count,
		float weight_range) {
	ptron->layer_count = layer_count;
	ptron->layer_sizes = malloc(sizeof(unsigned int) * layer_count);
	unsigned int i = 0;
	ptron->layers = malloc(sizeof(struct mosaic_matrix) * layer_count);
	ptron->weights = malloc(sizeof(struct mosaic_matrix) * (layer_count-1));
	eaux_weight_range = weight_range;
	while (i < layer_count-1) {
		ptron->layer_sizes[i] = layer_sizes[i];
		mosaic_matrix_init(&ptron->layers[i], 1, layer_sizes[i]);
		mosaic_matrix_init(&ptron->weights[i], layer_sizes[i], layer_sizes[i+1]);
		mosaic_matrix_apply(&ptron->weights[i], set_random);
		i++;
	}
	ptron->layer_sizes[layer_count-1] = layer_sizes[layer_count-1];
	mosaic_matrix_init(&ptron->layers[layer_count-1], 1, layer_sizes[layer_count-1]);
	return 0;
}

int eaux_perceptron_calc(struct eaux_perceptron *ptron,
		float *input, float *output) {
	struct mosaic_matrix output_matrix = {0, 0, 0};
	output_matrix.cols = 0;
	output_matrix.rows = 0;
	output_matrix.raw = NULL;
	mosaic_matrix_init(&output_matrix, ptron->layer_sizes[ptron->layer_count-1], 1);
	mosaic_matrix_assign(&ptron->layers[0], input);
	unsigned int i = 0;
	unsigned int output_count = ptron->layer_sizes[ptron->layer_count-1];
	unsigned int output_layer_index = ptron->layer_count-1;
	for (i = 0; i < output_layer_index; i++) {
		printf("Index %u\n", i);
		mosaic_matrix_multiply(&ptron->layers[i], &ptron->weights[i], &ptron->layers[i+1]);
		printf("Multipd\n");
		mosaic_matrix_apply(&ptron->layers[i+1], activate);
	}
	for (i = 0; i < output_count; i++) {
		output[i] = ptron->layers[output_layer_index].raw[i];
	}
	return 0;
}

int eaux_perceptron_print_debug_info(struct eaux_perceptron *ptron) {
	printf("PRINTING PERCEPTRON DEBUG INFO\n");
	unsigned int i = 0;
	unsigned int layer_count = ptron->layer_count;
	for (i = 0; i < layer_count-1; i++) {
		printf("LAYER %u :\n", i);
		mosaic_print(&ptron->layers[i]);
		printf("WEIGHTS %u :\n", i);
		mosaic_print(&ptron->weights[i]);
		printf("\n");
	}
	printf("LAYER %u :\n", layer_count-1);
	mosaic_print(&ptron->layers[layer_count-1]);
	printf("PERCEPTRON DEBUG INFO COMPLETE\n");
	return 0;
}

int eaux_perceptron_free(struct eaux_perceptron *ptron) {
	unsigned int layer_count = ptron->layer_count;
	unsigned int i = 0;
	for (i = 0; i < layer_count-1; i++) {
		mosaic_free(&ptron->layers[i]);
		mosaic_free(&ptron->weights[i]);
	}
	mosaic_free(&ptron->layers[layer_count-1]);
	free(ptron->layer_sizes);
	free(ptron->layers);
	free(ptron->weights);
	return 0;
}

int eaux_perceptron_cpy(struct eaux_perceptron *from, struct eaux_perceptron *to) {
	unsigned int *layer_sizes = from->layer_sizes;
	unsigned int weight_count = from->layer_count-1;
	eaux_perceptron_init(to, layer_sizes, weight_count+1, 0);
	unsigned int i = 0;
	for (i = 0; i < weight_count; i++) {
		mosaic_cpy(&from->weights[i], &to->weights[i]);
	}
	return 0;
}

