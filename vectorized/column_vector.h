//
// Created by wpy on 18-7-15.
//

#ifndef C_OFF_HEAP_COLUMN_VECTOR_H
#define C_OFF_HEAP_COLUMN_VECTOR_H

#include <stdlib.h>

typedef enum _DataType {
    INT_8 = 0,
    INT_16,
    INT_32,
    INT_64,
    FLOAT,
    DOUBLE,
    BINARY
} DataType;

typedef struct _ColumnVector {

    DataType type;////类型

    long capacity;////元素个数

    int elementsAppended;////已存在元素个数

    char *nulls;////为null的元素位置   bit

    int *lengthData;////数组模式使用  记录当前长度

    int *offsetData;////数组模式使用  记录当前数组值

    struct _ColumnVector *childColumns;////下级列

    char *data;////记录当前值  与offsetData冲突
} ColumnVector;

/**
 * 申请对应内存空间
 * @param capacity
 * @param type
 * @return
 */
ColumnVector *allocateColumn(long capacity, DataType type);

/**
 * 更新单个值,不支持Binary类型
 * @param vector
 * @param rowId
 * @param value
 */
void updateValue(ColumnVector *vector, long rowId, void *value);

/**
 * 更新多个值  Binary被当作一组Byte
 * @param vector
 * @param rowId
 * @param value
 * @param nums
 */
void batchUpdate(ColumnVector *vector, long rowId, void *value, int nums);

#endif //C_OFF_HEAP_COLUMN_VECTOR_H
