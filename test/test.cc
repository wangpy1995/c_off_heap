//
// Created by wpy on 18-7-15.
//



#include "column_vector.h"
#include <cstdio>
#include <sys/param.h>
#include <cstring>
#include <filter/filters.h>
#include <set>
#include <iostream>

int inSetTest(ColumnVector *vector, long rowId, FILTER *filter) {
    double *src = (double *) vector->data;
    auto s = (std::set<double> *) filter->value;
    return s->find(src[rowId]) != s->end();
}

int main() {

    double test[70];
    int i;
    for (i = 0; i < 70; ++i) {
        test[i] = i;
    }

    ColumnVector *vector = allocateColumn(100, INT_64);

    batchUpdate(vector, 0, test, 50);
    printf("%lf\n", *(((double *) (vector->data)) + 49));

//    char t[][6] = {"xxxxx", "yyyyy", "zzzz", ""};
//    vector = allocateColumn(3, BINARY);
//    batchUpdate(vector, 0, t[0], 5);
//    batchUpdate(vector, 1, t[1], 5);
//    batchUpdate(vector, 2, t[2], 4);
//    batchUpdate(vector, 3, t[3], 0);
//    ColumnVector *col = vector->childColumns;
//    char d[10] = {0};
//    for (i = 0; i < 4; ++i) {
//        printf("is null: %s\n", isset(col->nulls, i) == 0 ? "no" : "yes");
//        int len = col->lengthData[i];
//        printf("length: %d\n", len);
//        int offset = col->offsetData[i];
//        printf("offset: %d\n", offset);
//        memcpy(d, col->data + offset, sizeof(char) * len);
//        printf("data: %s\n\n", d);
//        memset(d, 0, 10);
//    }

    std::set<double> s{1.0, 7.0, 34.0};


    FILTER inSetFilter = {
            .size=1,
            .value = &s
    };
    printf("0x%x\n", &inSetFilter);

    for (i = 0; i < 50; ++i) {
        if (baseFilters[DOUBLE][IN_SET](vector, i, &inSetFilter)) {
            double *src = (double *) vector->data;
            std::cout << src[i] << std::endl;
        };
    }
}