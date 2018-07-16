//
// Created by wangpengyu6 on 18-7-16.
//

#include "filters.h"

inline int contains(ColumnVector *vector, FILTER *filter) {
    return strstr(vector->data, filter->value) != NULL;
}