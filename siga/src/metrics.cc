
#include <iostream>
#include "metrics.h"


void SetUpPerformanceMetrics(PerformanceMetrics* pm, string event)
{
    pm->n_comp = 0;
    pm->n_mov = 0;
    pm->time = 0;
    pm->event = event;
}   

void PerformanceMetricsPrint(PerformanceMetrics* pm)
{
#ifdef PRINT_METRICS
    cout << "Evento: " << pm->event << endl;
    cout << " Tempo de execução: "     << pm->time    << " segundos" << endl;
    cout << " Comparacoes: " << pm->n_comp << endl;
    cout << " Movimentacoes: "      << pm->n_mov << endl; 
#endif
}

void PerformanceMetricsCPUTime(PerformanceMetrics* pm, double time)
{
    pm->time = time;
}


