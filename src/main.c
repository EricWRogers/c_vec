#include "vec.h"

#include <stdio.h>

int main() {
    double* numbers = NULL;

    vec_init(&numbers, 10, sizeof(double));

    // load vec
    for(int i = 0; i < 20; i++) {
        double d = i + 0.5;
        printf("%lf\n", d);
        vec_add(&numbers, &d);
    }

    // print vec
    unsigned int count = vec_count(&numbers);
    for(int i = 0; i < count; i++) {
        printf("%lf\n", numbers[i]);
    }

    // sort
    printf("\nSelection Sort\n");
    vec_selection_sort(&numbers, DoubleDescending);

    // print vec
    for(int i = 0; i < count; i++) {
        printf("%lf\n", numbers[i]);
    }

    // sort
    printf("\nBubble Sort\n");
    vec_bubble_sort(&numbers, DoubleAscending);

    // print vec
    for(int i = 0; i < count; i++) {
        printf("%lf\n", numbers[i]);
    }

    vec_free(&numbers);
}
