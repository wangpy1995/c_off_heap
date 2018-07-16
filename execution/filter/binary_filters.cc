//
// Created by wpy on 18-7-16.
//


#include <utils/utils.h>
#include <string>
#include <set>
#include "filters.h"

int lessThanBinary(ColumnVector *vector, long rowId, FILTER *filter) {
    int len = vector->childColumns->lengthData[rowId];
    int cmpLen = min(len, filter->size);
    int offset = vector->childColumns->offsetData[rowId];

    const char *src = vector->childColumns->data + offset;
    int less = byte_cmp(src, static_cast<const char *>(filter->value), cmpLen);
    if (less == 0) {
        less = len < cmpLen;
    }
    return less;
}

int lessOrEqualBinary(ColumnVector *vector, long rowId, FILTER *filter) {
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

int equalBinary(ColumnVector *vector, long rowId, FILTER *filter) {
    int len = vector->childColumns->lengthData[rowId];
    if (len != filter->size) {
        return false;
    }
    int cmpLen = min(len, filter->size);
    int offset = vector->childColumns->offsetData[rowId];

    const char *src = vector->childColumns->data + offset;
    int equal = byte_cmp(src, static_cast<const char *>(filter->value), cmpLen);
    if (equal == 0) {
        equal = len == cmpLen;
    }
    return equal;
}

int greaterOrEqualBinary(ColumnVector *vector, long rowId, FILTER *filter) {
    int len = vector->childColumns->lengthData[rowId];
    int cmpLen = min(len, filter->size);
    int offset = vector->childColumns->offsetData[rowId];

    const char *src = vector->childColumns->data + offset;
    int greaterOrEqual = byte_cmp(src, static_cast<const char *>(filter->value), cmpLen);
    if (greaterOrEqual == 0) {
        greaterOrEqual = len >= cmpLen;
    }
    return greaterOrEqual;
}

int greaterThanBinary(ColumnVector *vector, long rowId, FILTER *filter) {
    int len = vector->childColumns->lengthData[rowId];
    int cmpLen = min(len, filter->size);
    int offset = vector->childColumns->offsetData[rowId];

    const char *src = vector->childColumns->data + offset;
    int greaterThan = byte_cmp(src, static_cast<const char *>(filter->value), cmpLen);
    if (greaterThan == 0) {
        greaterThan = len > cmpLen;
    }
    return greaterThan;
}

int inSetBinary(ColumnVector *vector, long rowId, FILTER *filter) {
    int len = vector->childColumns->lengthData[rowId];
    int offset = vector->childColumns->offsetData[rowId];
    const char *src = vector->childColumns->data + offset;
    std::string str(src);

    auto *s = (std::set<std::string> *) filter->value;
    return s->find(str) != s->end();
}

int startWith(ColumnVector *vector, long rowId, FILTER *filter) {
    const int len = vector->childColumns->lengthData[rowId];
    int cmpLen = filter->size;
    if (cmpLen > len) {
        return false;
    }

    const long offset = vector->childColumns->offsetData[rowId];
    const char *src = vector->childColumns->data + offset;
    const char *des = static_cast<const char *>(filter->value);
    if (cmpLen > 32) {
        return avx256_cmpeq(src, des, cmpLen);
    } else if (cmpLen > 16) {
        return avx128_cmpeq(src, des, cmpLen);
    } else {
        return byte_cmp(src, des, cmpLen);
    }
}

int endsWith(ColumnVector *vector, long rowId, FILTER *filter) {
    const int len = vector->childColumns->lengthData[rowId];
    int cmpLen = filter->size;
    if (cmpLen > len) {
        return false;
    }

    const long offset = vector->childColumns->offsetData[rowId];
    const char *des = static_cast<const char *>(filter->value);
    const char *src = vector->childColumns->data + offset + len;
    if (cmpLen > 32) {
        return avx256_cmpeq(src - cmpLen, des, cmpLen);
    } else if (cmpLen > 16) {
        return avx128_cmpeq(src - cmpLen, des, cmpLen);
    } else {
        return byte_cmp(src - cmpLen, des, cmpLen);
    }
}

int contains(ColumnVector *vector, long rowId, FILTER *filter) {
    const int len = vector->childColumns->lengthData[rowId];
    int cmpLen = filter->size;
    if (cmpLen > len) {
        return false;
    }
    const long offset = vector->childColumns->offsetData[rowId];
    const char *des = static_cast<const char *>(filter->value);
    const char *src = vector->childColumns->data + offset + len;

    return strstr(src, des) != nullptr;
}

const filter binaryFilters[] = {lessThanBinary, lessOrEqualBinary, equalBinary, greaterOrEqualBinary,
                                greaterThanBinary, inSetBinary, startWith, endsWith, contains};