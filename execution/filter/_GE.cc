//
// Created by wangpengyu6 on 18-7-16.
//
#include "filters.h"

template<typename t>
inline int greaterOrEqual(ColumnVector *vector, long rowId, FILTER *filter) {
    t *src = (t *) vector->data;
    return src[rowId] >= *(t *) filter->value;
}

//inline int greaterOrEqualInt8(ColumnVector *vector, long rowId, FILTER *filter) {
//    return vector->data[rowId] >= *(char *) filter->value;
//}
//
//inline int greaterOrEqualInt16(ColumnVector *vector, long rowId, FILTER *filter) {
//    short *src = (short *) vector->data;
//    return src[rowId] >= *(short *) filter->value;
//}
//
//inline int greaterOrEqualInt32(ColumnVector *vector, long rowId, FILTER *filter) {
//    int *src = (int *) vector->data;
//    return src[rowId] >= *(int *) filter->value;
//}
//
//inline int greaterOrEqualInt64(ColumnVector *vector, long rowId, FILTER *filter) {
//    long *src = (long *) vector->data;
//    return src[rowId] >= *(long *) filter->value;
//}
//
//inline int greaterOrEqualFloat(ColumnVector *vector, long rowId, FILTER *filter) {
//    float *src = (float *) vector->data;
//    return src[rowId] >= *(float *) filter->value;
//}
//
//inline int greaterOrEqualDouble(ColumnVector *vector, long rowId, FILTER *filter) {
//    double *src = (double *) vector->data;
//    return src[rowId] >= *(double *) filter->value;
//}

inline int greaterOrEqualBinary(ColumnVector *vector, long rowId, FILTER *filter) {
    int len = vector->childColumns->lengthData[rowId];
    int cmpLen = min(len, filter->size);
    int offset = vector->childColumns->offsetData[rowId];

    const char *src = vector->childColumns->data + offset;
    int greaterOrEqual = byte_cmp(src, static_cast<const char *>(filter->value), cmpLen);
    if (greaterOrEqual == 0) {
        greaterOrEqual = len >= cmpLen ? true : false;
    }
    return greaterOrEqual;
}