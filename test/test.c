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

    char t[][6] = {"xxxxx", "yyyyy", "zzzz"};
    vector = allocateColumn(3, BINARY);
    batchUpdate(vector, 0, t[0], 5);
    batchUpdate(vector, 1, t[1], 5);
    batchUpdate(vector, 2, t[2], 4);
    printf("%s\n", vector->childColumns->offsetData);
}