#ifndef MAIN_H
#define MAIN_H

#include "job.h"

bool handle_job(Job job);
bool try_load_job(Job job, LSystem * system);
bool try_save_job(Job job, LSystem system);

#endif