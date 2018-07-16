//
// Created by wangpengyu6 on 18-7-16.
//
#include <stdbool.h>
#include "filters.h"

int endsWith(ColumnVector *vector, long rowId, FILTER *filter) {
    const int len = vector->childColumns->lengthData[rowId];
    int cmpLen = filter->size;
    if (cmpLen > len) {
        return false;
    }

    const long offset = vector->childColumns->offsetData[rowId];
    const char *des = filter->value;
    const char *src = vector->childColumns->data + offset + len;
    if (cmpLen > 32) {
        return avx256_cmpeq(src - cmpLen, des, cmpLen);
    } else if (cmpLen > 16) {
        return avx128_cmpeq(src - cmpLen, des, cmpLen);
    } else {
        return byte_cmp(src - cmpLen, des, cmpLen);
    }
}

