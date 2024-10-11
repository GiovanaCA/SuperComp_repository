#include <omp.h>
#include <iostream>
#include <iomanip>
static long num_steps = 1024l*1024*1024*2;

#define MIN_BLK  1024*2*2

double sum = 0;

// PI_R_FOR_PARALLEL
void pi_r_for_parallel(long Nstart, long Nfinish, double step) {
    #pragma omp parallel for reduction(+:sum)
    for (long i = Nstart; i < Nfinish; i++){
        double x = (i+0.5)*step;
        sum += 4.0/(1.0+x*x); 
    }
}

int main () {
    long i;
    double step, pi;
    double init_time, final_time;
    step = 1.0/(double) num_steps;

    // PI_R_FOR_PARALLEL
    init_time = omp_get_wtime();
    pi_r_for_parallel(0, num_steps, step);
    pi = step * sum;
    final_time = omp_get_wtime() - init_time;
    std::cout << "for " << num_steps << " steps pi for parallel = " << std::setprecision(15) << pi << " in " << final_time << " secs\n";

    return 0;
}