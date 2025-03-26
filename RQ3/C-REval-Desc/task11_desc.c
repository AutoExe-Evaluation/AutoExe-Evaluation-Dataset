#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void func(float* pair);

void find_closest_elements(float* numbers, int length) {
    float* closest_pair = NULL;
    float distance = -1;

    for (int idx = 0; idx < length; idx++) {
        for (int idx2 = 0; idx2 < length; idx2++) {
            if (idx != idx2) {
                float elem = numbers[idx];
                float elem2 = numbers[idx2];
                float new_distance = fabs(elem - elem2);
                
                if (distance < 0 || new_distance < distance) {
                    distance = new_distance;
                    closest_pair = (float*)malloc(2 * sizeof(float));
                    if (elem < elem2) {
                        closest_pair[0] = elem;
                        closest_pair[1] = elem2;
                    } else {
                        closest_pair[0] = elem2;
                        closest_pair[1] = elem;
                    }
                }
            }
        }
    }

    assert(closest_pair != NULL);
    func(closest_pair);  // POST: func is equivalent to: From a supplied list of numbers (of length at least two) select and return two that are the closest to each other and return them in order (smaller number, larger number).
    
    free(closest_pair);
}