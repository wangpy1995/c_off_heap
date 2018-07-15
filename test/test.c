//
// Created by wpy on 18-7-15.
//

#include <column_vector.h>
#include <stdio.h>

int main(void) {

    double test[70];
    int i;
    for (i = 0; i < 70; ++i) {
        test[i] = i;
    }


    ColumnVector *vector = allocateColumn(100, INT_64);

    batchUpdate(vector, 0, test, 50);
    printf("%lf\n", *(((double *) (vector->data)) + 49));
}