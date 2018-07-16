//
// Created by wangpengyu6 on 18-7-16.
//

#include "filters.h"

template<typename t>
inline int equals(ColumnVector *vector, long rowId, FILTER *filter) {
    t *src = (t *) vector->data;
    return src[rowId] == *(t *) filter->value;
}

//inline int equalInt8(ColumnVector *vector, long rowId, FILTER *filter) {
//    return vector->data[rowId] == *(char *) filter->value;
//}
//
//inline int equalInt16(ColumnVector *vector, long rowId, FILTER *filter) {
//    short *src = (short *) vector->data;
//    return src[rowId] == *(short *) filter->value;
//}
//
//inline int equalInt32(ColumnVector *vector, long rowId, FILTER *filter) {
//    int *src = (int *) vector->data;
//    return src[rowId] == *(int *) filter->value;
//}
//
//inline int equalInt64(ColumnVector *vector, long rowId, FILTER *filter) {
//    long *src = (long *) vector->data;
//    return src[rowId] == *(long *) filter->value;
//}
//
//inline int equalFloat(ColumnVector *vector, long rowId, FILTER *filter) {
//    float *src = (float *) vector->data;
//    return src[rowId] == *(float *) filter->value;
//}
//
//inline int equalDouble(ColumnVector *vector, long rowId, FILTER *filter) {
//    double *src = (double *) vector->data;
//    return src[rowId] == *(double *) filter->value;
//}

inline int equalBinary(ColumnVector *vector, long rowId, FILTER *filter) {
    int len = vector->childColumns->lengthData[rowId];
    if (len != filter->size) {
        return false;
    }
    int cmpLen = min(len, filter->size);
    int offset = vector->childColumns->offsetData[rowId];

    const char *src = vector->childColumns->data + offset;
    int equal = byte_cmp(src, static_cast<const char *>(filter->value), cmpLen);
    if (equal == 0) {
        equal = len == cmpLen ? true : false;
    }
    return equal;
}