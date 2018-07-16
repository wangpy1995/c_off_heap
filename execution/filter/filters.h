//
// Created by wangpengyu6 on 18-7-16.
//

#ifndef C_OFF_HEAP_FILTERS_H
#define C_OFF_HEAP_FILTERS_H

#include "inline_avx_sum.h"
#include "string.h"
#include "column_vector.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct _FILTER {
    const int size;
    const void *value;
} FILTER;

enum _FILTER_TYPE {
    LT = 0,
    LE,
    EQ,
    GE,
    GT,
    IN_SET,
    START_WITH,
    ENDS_WITH,
    CONTAINS,
    SIMILAR
};

typedef int (*filter)(ColumnVector *, long, FILTER *);

extern const filter binaryFilters[];
extern const filter baseFilters[][6];

#ifdef __cplusplus
}
#endif

#endif //C_OFF_HEAP_FILTERS_H
