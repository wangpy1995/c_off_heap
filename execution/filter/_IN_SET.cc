//
// Created by wangpengyu6 on 18-7-16.
//

#include "filters.h"

template<typename t>
inline int inSet(ColumnVector *vector, long rowId, FILTER *filter) {
    const t *src = (t *) vector->data;
    std::set<t> values = filter->value;
}

inline int inSetBinary(ColumnVector *vector, long rowId, FILTER *filter) {

}