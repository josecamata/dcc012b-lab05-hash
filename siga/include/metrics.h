#ifndef METRICS_H
#define METRICS_H

#include <chrono>
using namespace std;

#include "config.h"

typedef chrono::high_resolution_clock Clock;

typedef struct {
    unsigned int n_comp;
    unsigned int n_mov;
    double time;
    string event;
} PerformanceMetrics;


void SetUpPerformanceMetrics(PerformanceMetrics* pm, string event);

void PerformanceMetricsCPUTime(PerformanceMetrics* pm, double time);

void PerformanceMetricsPrint(PerformanceMetrics* pm);






#endif /* METRICS_H */
