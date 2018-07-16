//
// Created by wpy on 18-7-16.
//

#include <set>
#include <iostream>
#include "filters.h"

template<typename t>
inline int lessThan(ColumnVector *vector, long rowId, FILTER *filter) {
    t *src = (t *) vector->data;
    return src[rowId] < *(t *) filter->value;
}

template<typename t>
inline int lessOrEqual(ColumnVector *vector, long rowId, FILTER *filter) {
    const t *src = (t *) vector->data;
    return src[rowId] <= *(t *) filter->value;
}

template<typename t>
inline int equals(ColumnVector *vector, long rowId, FILTER *filter) {
    t *src = (t *) vector->data;
    return src[rowId] == *(t *) filter->value;
}

template<typename t>
inline int greaterOrEqual(ColumnVector *vector, long rowId, FILTER *filter) {
    t *src = (t *) vector->data;
    return src[rowId] >= *(t *) filter->value;
}

template<typename t>
inline int greaterThan(ColumnVector *vector, long rowId, FILTER *filter) {
    t *src = (t *) vector->data;
    return src[rowId] > *(t *) filter->value;
}

template<typename t>
inline int inSet(ColumnVector *vector, long rowId, FILTER *filter) {
    t *src = (t *) vector->data;
    auto s = (std::set<t> *) filter->value;
    return s->find(src[rowId]) != s->end();
}

#define int8Filter  {lessThan<char>, lessOrEqual<char>, equals<char>, greaterOrEqual<char>, greaterThan<char>, inSet<char>}
#define int16Filter  {lessThan<short>, lessOrEqual<short>, equals<short>, greaterOrEqual<short>,greaterThan<short>,inSet<short>}
#define int32Filter  {lessThan<int>, lessOrEqual<int>, equals<int>, greaterOrEqual<int>,greaterThan<int>,inSet<int>}
#define int64Filter {lessThan<long>, lessOrEqual<long>, equals<long>, greaterOrEqual<long>,greaterThan<long>,inSet<long>}
#define floatFilter  {lessThan<float>, lessOrEqual<float>, equals<float>, greaterOrEqual<float>,greaterThan<float>,inSet<float>}
#define doubleFilter {lessThan<double>, lessOrEqual<double>, equals<double>, greaterOrEqual<double>,greaterThan<double>,inSet<double>}


constexpr filter baseFilters[][6] = {int8Filter, int16Filter, int32Filter, int64Filter, floatFilter, doubleFilter};