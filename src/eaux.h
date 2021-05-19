#ifndef EAUX_PERCEPTRON_H
#define EAUX_PERCEPTRON_H

#include <mosaic.h>

struct eaux_perceptron {
	unsigned int *layer_sizes;
	unsigned int layer_count;
	struct mosaic_matrix *layers;
	struct mosaic_matrix *weights;
};

int eaux_perceptron_init(struct eaux_perceptron *ptron,
		unsigned int *layer_sizes,
		unsigned int layer_count,
		float weight_range);

int eaux_perceptron_calc(struct eaux_perceptron *ptron,
		float *input, float *output);

int eaux_perceptron_print_debug_info(struct eaux_perceptron *ptron);

int eaux_perceptron_free(struct eaux_perceptron *ptron);
#endif 
