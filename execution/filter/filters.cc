//
// Created by wpy on 18-7-16.
//


#include <utils/utils.h>
#include <string>
#include <set>
#include "filters.h"
#include "_SIMILAR.h"

//////////////////////////////////////
////  base type
/////////////////////////////////////

template<typename t>
static inline int lessThan(ColumnVector *vector, long rowId, FILTER *filter) {
    t *src = (t *) vector->data;
    return src[rowId] < *(t *) filter->value;
}

template<typename t>
static inline int lessOrEqual(ColumnVector *vector, long rowId, FILTER *filter) {
    const t *src = (t *) vector->data;
    return src[rowId] <= *(t *) filter->value;
}

template<typename t>
static inline int equals(ColumnVector *vector, long rowId, FILTER *filter) {
    t *src = (t *) vector->data;
    return src[rowId] == *(t *) filter->value;
}

template<typename t>
static inline int greaterOrEqual(ColumnVector *vector, long rowId, FILTER *filter) {
    t *src = (t *) vector->data;
    return src[rowId] >= *(t *) filter->value;
}

template<typename t>
static inline int greaterThan(ColumnVector *vector, long rowId, FILTER *filter) {
    t *src = (t *) vector->data;
    return src[rowId] > *(t *) filter->value;
}

template<typename t>
static inline int inSet(ColumnVector *vector, long rowId, FILTER *filter) {
    t *src = (t *) vector->data;
    auto s = (std::set<t> *) filter->value;
    return s->find(src[rowId]) != s->end();
}

template<typename t>
static inline int startWith(ColumnVector *vector, long rowId, FILTER *filter) {
    return true;
}

template<typename t>
static inline int endsWith(ColumnVector *vector, long rowId, FILTER *filter) {
    return true;
}

template<typename t>
static inline int contains(ColumnVector *vector, long rowId, FILTER *filter) {
    return true;
}

template<typename t>
static inline int similar(ColumnVector *vector, long rowId, FILTER *filter) {
    return true;
}


/////////////////////////////////////
//// binary 特殊处理
/////////////////////////////////////

template<>
int lessThan<char *>(ColumnVector *vector, long rowId, FILTER *filter) {
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

template<>
int lessOrEqual<char *>(ColumnVector *vector, long rowId, FILTER *filter) {
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

template<>
int equals<char *>(ColumnVector *vector, long rowId, FILTER *filter) {
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

template<>
int greaterOrEqual<char *>(ColumnVector *vector, long rowId, FILTER *filter) {
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

template<>
int greaterThan<char *>(ColumnVector *vector, long rowId, FILTER *filter) {
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

template<>
int inSet<char *>(ColumnVector *vector, long rowId, FILTER *filter) {
    int len = vector->childColumns->lengthData[rowId];
    int offset = vector->childColumns->offsetData[rowId];
    const char *src = vector->childColumns->data + offset;
    std::string str(src, len);

    auto *s = (std::set<std::string> *) filter->value;
    return s->find(str) != s->end();
}

template<>
int startWith<char *>(ColumnVector *vector, long rowId, FILTER *filter) {
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

template<>
int endsWith<char *>(ColumnVector *vector, long rowId, FILTER *filter) {
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

template<>
int contains<char *>(ColumnVector *vector, long rowId, FILTER *filter) {
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

////////////////////////model compare////////////////////////
template<>
int similar<char *>(ColumnVector *vector, long rowId, FILTER *filter) {
    const char *src = vector->childColumns->data + rowId * (MODEL_LEN + TAG_LEN);
    const float *dst = static_cast<const float *>(filter->value);
    float minSimilarity = *dst;
    dst += 1;
    float maxSimilarity = *dst;
    dst += 1;
    float sim = compare(src, (const char *) dst);

    return sim >= minSimilarity && sim <= maxSimilarity;
}

////////////////////////////////////////
////  使用连续内存  对应函数
////////////////////////////////////////
#define int8Filter  {lessThan<char>, lessOrEqual<char>, equals<char>, greaterOrEqual<char>, greaterThan<char>, inSet<char>\
        , startWith<char>, endsWith<char>, contains<char>, similar<char>}

#define int16Filter  {lessThan<short>, lessOrEqual<short>, equals<short>, greaterOrEqual<short>,greaterThan<short>,inSet<short>\
        , startWith<short>, endsWith<short>, contains<short>, similar<short>}

#define int32Filter  {lessThan<int>, lessOrEqual<int>, equals<int>, greaterOrEqual<int>,greaterThan<int>,inSet<int>\
        , startWith<int>, endsWith<int>, contains<int>, similar<int>}

#define int64Filter {lessThan<long>, lessOrEqual<long>, equals<long>, greaterOrEqual<long>,greaterThan<long>,inSet<long>\
        , startWith<long>, endsWith<long>, contains<long>, similar<long>}

#define floatFilter  {lessThan<float>, lessOrEqual<float>, equals<float>, greaterOrEqual<float>,greaterThan<float>,inSet<float>\
        , startWith<float>, endsWith<float>, contains<float>, similar<float>}

#define doubleFilter {lessThan<double>, lessOrEqual<double>, equals<double>, greaterOrEqual<double>,greaterThan<double>,inSet<double>\
        , startWith<double>, endsWith<double>, contains<double>, similar<double>}

#define binaryFilters {lessThan<char*>, lessOrEqual<char*>, equals<char*>, greaterOrEqual<char*>, greaterThan<char*>, inSet<char*>\
        , startWith<char*>, endsWith<char*>, contains<char*>, similar<char*>}

constexpr filter baseFilters[][10] = {int8Filter, int16Filter, int32Filter, int64Filter, floatFilter, doubleFilter,
                                      binaryFilters};