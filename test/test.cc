//
// Created by wpy on 18-7-15.
//

#include "column_vector.h"
#include <stdio.h>
#include <sys/param.h>
#include <cstring>
#include <set>
#include <filter/filters.h>
#include <row/row.h>
#include <vector>

void testRow(void) {

    int a[] = {1, 2, 3, 4, 5, 6, 7, 8};
    char b[] = {9, 10, 11, 14, 15, 16, 17, 18};
    float c[] = {50.0, 51.0, 53, 54, 55, 56, 57, 58};
    char d[][3] = {"aa", "bb", "cc", "dd", "ee", "ff", "gg", "hh"};

    void *row[4] = {};

    row[0] = a;
    row[1] = b;
    row[2] = c;
    row[3] = d;

    printf("%d\t", *(int *) row[0]);
    printf("%d\t", *(char *) row[1]);
    printf("%f\t", *(float *) row[2]);
    printf("%s\t", (char *) row[3]);
}

void testInSetFilter(void) {
    double test[70];
    int i;
    for (i = 0; i < 70; ++i) {
        test[i] = i;
    }

    ColumnVector *vector = allocateColumn(100, INT_64);

    batchUpdate(vector, 0, test, 50);
    printf("%lf\n", *(((double *) (vector->data)) + 49));

    std::set<double> s{1.0, 7.0, 34.0, 1.0};


    FILTER inSetFilter = {
            .size=1,
            .value = &s
    };
    printf("0x%lx\n", reinterpret_cast<unsigned long>(&inSetFilter));

    for (i = 0; i < 50; ++i) {
        if (baseFilters[DOUBLE][IN_SET](vector, i, &inSetFilter)) {
            double *src = (double *) vector->data;
            printf("%lf\t", src[i]);
        };
    }
}

void testBinary(void) {
    int i;

    ColumnVector *vector = allocateColumn(3, BINARY);
    char t[][6] = {"xxxxx", "yyyyy", "zzzz", ""};
    batchUpdate(vector, 0, t[0], 5);
    batchUpdate(vector, 1, t[1], 5);
    batchUpdate(vector, 2, t[2], 4);
    batchUpdate(vector, 3, t[3], 0);
    ColumnVector *col = vector->childColumns;
    char d[10] = {0};
    for (i = 0; i < 4; ++i) {
        printf("is null: %s\n", isset(col->nulls, i) == 0 ? "no" : "yes");
        int len = col->lengthData[i];
        printf("length: %d\n", len);
        int offset = col->offsetData[i];
        printf("offset: %d\n", offset);
        memcpy(d, col->data + offset, sizeof(char) * len);
        printf("data: %s\n\n", d);
        memset(d, 0, 10);
    }
}

int main() {
    testRow();

    testBinary();

}