#ifdef _WIN32
#include <windows.h>
#endif

#include <stdio.h>

#include "vec.h"

int main(int argc, char* argv[]) {
    // array example
    int wholeNumbers[5];

    wholeNumbers[0] = 0;

    printf("%d\n", wholeNumbers[0]);

    // vec
    double* numbers = NULL;

    printf("Init vector!\n");
    vec_init(&numbers, 5, sizeof(double));

    for(int i = 0; i < 10; i++) {
        double num = i + 0.5;
        vec_add(&numbers, &num);
    }

    unsigned int count = vec_count(&numbers);
    for(int i = 0; i < count; i++) {
        printf("%lf\n",numbers[i]);
    }

    printf("Clear\n");
    vec_clear(&numbers);
    count = vec_count(&numbers);
    for(int i = 0; i < count; i++) {
        printf("%lf\n",numbers[i]);
    }

    vec_free(&numbers);
    return 0;
}
