#ifndef MAIN_H
#define MAIN_H

#include "job.h"

bool handle_job(Job job);
bool try_load_job(Job job, LSystem * system, MoveMap * move_map);
bool try_save_job(Job job, LSystem system, MoveMap move_map);

#endif