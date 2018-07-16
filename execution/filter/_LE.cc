//
// Created by wangpengyu6 on 18-7-16.
//

#include "filters.h"


template<typename t>
inline int lessOrEqual(ColumnVector *vector, long rowId, FILTER *filter) {
    const t *src = (t *) vector->data;
    return src[rowId] <= *(t *) filter->value;
}


//inline int lessOrEqualInt16(ColumnVector *vector, long rowId, FILTER *filter) {
//    short *src = (short *) vector->data;
//    return src[rowId] <= *(short *) filter->value;
//}
//
//inline int lessOrEqualInt32(ColumnVector *vector, long rowId, FILTER *filter) {
//    int *src = (int *) vector->data;
//    return src[rowId] <= *(int *) filter->value;
//}
//
//inline int lessOrEqualInt64(ColumnVector *vector, long rowId, FILTER *filter) {
//    long *src = (long *) vector->data;
//    return src[rowId] <= *(long *) filter->value;
//}
//
//inline int lessOrEqualFloat(ColumnVector *vector, long rowId, FILTER *filter) {
//    float *src = (float *) vector->data;
//    return src[rowId] <= *(float *) filter->value;
//}
//
//inline int lessOrEqualDouble(ColumnVector *vector, long rowId, FILTER *filter) {
//    double *src = (double *) vector->data;
//    return src[rowId] <= *(double *) filter->value;
//}

inline int lessOrEqualBinary(ColumnVector *vector, long rowId, FILTER *filter) {
    int len = vector->childColumns->lengthData[rowId];
    int cmpLen = min(len, filter->size);
    int offset = vector->childColumns->offsetData[rowId];

    const char *src = vector->childColumns->data + offset;
    int lessOrEqual = byte_cmp(src, static_cast<const char *>(filter->value), cmpLen);
    if (lessOrEqual == 0) {
        lessOrEqual = len <= cmpLen;
    }
    return lessOrEqual;
}