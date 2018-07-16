//
// Created by wangpengyu6 on 18-7-16.
//
#include "filters.h"

int startWith(ColumnVector *vector, long rowId, FILTER *filter) {
    const int len = vector->childColumns->lengthData[rowId];
    int cmpLen = filter->size;
    if (cmpLen > len) {
        return false;
    }

    const long offset = vector->childColumns->offsetData[rowId];
    const char *src = vector->childColumns->data + offset;
    const char *des = filter->value;
    if (cmpLen > 32) {
        return avx256_cmpeq(src, des, cmpLen);
    } else if (cmpLen > 16) {
        return avx128_cmpeq(src, des, cmpLen);
    } else {
        return byte_cmp(src, des, cmpLen);
    }
}