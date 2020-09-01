#ifndef GENERATOR_H
#define GENERATOR_H

#include "system.h"

const size_t MAX_AXIOM_SIZE = 6e9;

void generate_system(LSystem * system, unsigned int num_iterations);
void rewrite_symbols(LSystem * system);

#endif