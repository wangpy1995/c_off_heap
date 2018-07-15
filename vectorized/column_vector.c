//
// Created by wpy on 18-7-15.
//

#include <string.h>
#include <sys/param.h>
#include "column_vector.h"

#define DEFAULT_ARRAY_LENGTH 4

//////////////////////////////////////////
////  allocate
/////////////////////////////////////////
static ColumnVector *allocateInt8Column(long capacity) {
    ColumnVector *vector = malloc(sizeof(ColumnVector));
    vector->type = INT_8;
    vector->childColumns = NULL;
    vector->elementsAppended = 0;
    vector->nulls = malloc(sizeof(char) * ((capacity >> 3) + 1));
    vector->lengthData = NULL;
    vector->offsetData = NULL;
    vector->data = malloc(sizeof(char) * capacity);
    return vector;
}

static ColumnVector *allocateInt16Column(long capacity) {
    ColumnVector *vector = malloc(sizeof(ColumnVector));
    vector->type = INT_16;
    vector->childColumns = NULL;
    vector->elementsAppended = 0;
    vector->nulls = malloc(sizeof(char) * ((capacity >> 3) + 1));
    vector->lengthData = NULL;
    vector->offsetData = NULL;
    vector->data = malloc(sizeof(short) * capacity);
    return vector;
}

static ColumnVector *allocateInt32Column(long capacity) {
    ColumnVector *vector = malloc(sizeof(ColumnVector));
    vector->type = INT_32;
    vector->childColumns = NULL;
    vector->elementsAppended = 0;
    vector->nulls = malloc(sizeof(char) * ((capacity >> 3) + 1));
    vector->lengthData = NULL;
    vector->offsetData = NULL;
    vector->data = malloc(sizeof(int) * capacity);
    return vector;
}

static ColumnVector *allocateInt64Column(long capacity) {
    ColumnVector *vector = malloc(sizeof(ColumnVector));
    vector->type = INT_64;
    vector->childColumns = NULL;
    vector->elementsAppended = 0;
    vector->nulls = malloc(sizeof(char) * ((capacity >> 3) + 1));
    vector->lengthData = NULL;
    vector->offsetData = NULL;
    vector->data = malloc(sizeof(long) * capacity);
    return vector;
}

static ColumnVector *allocateFloatColumn(long capacity) {
    ColumnVector *vector = malloc(sizeof(ColumnVector));
    vector->type = FLOAT;
    vector->childColumns = NULL;
    vector->elementsAppended = 0;
    vector->nulls = malloc(sizeof(char) * ((capacity >> 3) + 1));
    vector->lengthData = NULL;
    vector->offsetData = NULL;
    vector->data = malloc(sizeof(float) * capacity);
    return vector;
}

static ColumnVector *allocateDoubleColumn(long capacity) {
    ColumnVector *vector = malloc(sizeof(ColumnVector));
    vector->type = DOUBLE;
    vector->childColumns = NULL;
    vector->elementsAppended = 0;
    vector->nulls = malloc(sizeof(char) * ((capacity >> 3) + 1));
    vector->lengthData = NULL;
    vector->offsetData = NULL;
    vector->data = malloc(sizeof(double) * capacity);
    return vector;
}

static ColumnVector *allocateBinaryColumn(long capacity) {
    ColumnVector *vector = malloc(sizeof(ColumnVector));
    vector->type = BINARY;
    vector->childColumns = allocateInt8Column(capacity * DEFAULT_ARRAY_LENGTH);
    vector->childColumns->lengthData = malloc(sizeof(int) * capacity);
    vector->childColumns->offsetData = malloc(sizeof(int) * capacity);
    vector->elementsAppended = 0;
    vector->nulls = NULL;
    vector->data = NULL;
    return vector;
}

////////////////////////////////////////
////  put
////////////////////////////////////////
static inline void putInt8(ColumnVector *vector, long rowId, void *value) {
    vector->data[rowId] = *(char *) value;
    ++(vector->elementsAppended);
}

static inline void putInt16(ColumnVector *vector, long rowId, void *value) {
    short *des = (short *) (vector->data);
    des[rowId] = *(short *) value;
    ++(vector->elementsAppended);
}

static inline void putInt32(ColumnVector *vector, long rowId, void *value) {
    int *des = (int *) (vector->data);
    des[rowId] = *(int *) value;
    ++(vector->elementsAppended);
}

static inline void putInt64(ColumnVector *vector, long rowId, void *value) {
    long *des = (long *) (vector->data);
    des[rowId] = *(long *) value;
    ++(vector->elementsAppended);
}

static inline void putFloat(ColumnVector *vector, long rowId, void *value) {
    float *des = (float *) (vector->data);
    des[rowId] = *(float *) value;
    ++(vector->elementsAppended);
}

static inline void putDouble(ColumnVector *vector, long rowId, void *value) {
    double *des = (double *) (vector->data);
    des[rowId] = *(double *) value;
    ++(vector->elementsAppended);
}


/////////////////////////////////////////////////////////////////////////
static inline void reallocate(void **data, size_t oldCapacity, size_t newCapacity) {
    void *newData = malloc(newCapacity);
    memcpy(newData, data, oldCapacity);
    free(*data);
    *data = newData;
}

static inline void putBinary(ColumnVector *vector, long rowId, void *value, int length) {
    ColumnVector des = vector->childColumns[0];
    long requiredCapacity = des.elementsAppended + length;
    long newCapacity = requiredCapacity * 2;
    long oldCapacity = des.capacity;
    //内存扩容
    if (requiredCapacity > oldCapacity) {
        size_t oldBitLen = ((sizeof(char) * oldCapacity) >> 3) + 1;
        size_t newBitLen = ((sizeof(char) * newCapacity) >> 3) + 1;
        reallocate((void **) &(des.nulls), oldBitLen, newBitLen);
        memset(des.nulls, 0, newBitLen - oldBitLen);
        reallocate((void **) &(des.lengthData), sizeof(int) * oldCapacity, sizeof(int) * newCapacity);
        reallocate((void **) &(des.offsetData), sizeof(int) * oldCapacity, sizeof(int) * newCapacity);
    }
    des.capacity = newCapacity;
    des.lengthData[rowId] = length;
    memcpy(des.offsetData + des.elementsAppended, value, sizeof(char) * length);
    des.elementsAppended += length;
}


/////////////////////////////////////
////  puts
////////////////////////////////////
static inline void putInt8s(ColumnVector *vector, long rowId, void *value, int nums) {
    memcpy(vector->data + rowId, value, sizeof(char) * nums);
    (vector->elementsAppended) += nums;
}

static inline void putInt16s(ColumnVector *vector, long rowId, void *value, int nums) {
    short *des = (short *) (vector->data);
    memcpy(des + rowId, value, sizeof(short) * nums);
    (vector->elementsAppended) += nums;
}

static inline void putInt32s(ColumnVector *vector, long rowId, void *value, int nums) {
    int *des = (int *) (vector->data);
    memcpy(des + rowId, value, sizeof(int) * nums);
    (vector->elementsAppended) += nums;
}

static inline void putInt64s(ColumnVector *vector, long rowId, void *value, int nums) {
    long *des = (long *) (vector->data);
    memcpy(des + rowId, value, sizeof(long) * nums);
    (vector->elementsAppended) += nums;
}

static inline void putFloats(ColumnVector *vector, long rowId, void *value, int nums) {
    float *des = (float *) (vector->data);
    memcpy(des + rowId, value, sizeof(float) * nums);
    (vector->elementsAppended) += nums;
}

static inline void putDoubles(ColumnVector *vector, long rowId, void *value, int nums) {
    double *des = (double *) (vector->data);
    memcpy(des + rowId, value, sizeof(double) * nums);
    (vector->elementsAppended) += nums;
}

typedef ColumnVector *(*ColumnAllocator)(long);

typedef void (*UpdateColumn)(ColumnVector *, long, void *);

typedef void (*BatchUpdateColumn)(ColumnVector *, long, void *, int);

static const ColumnAllocator columnAllocator[7] = {
        allocateInt8Column, allocateInt16Column, allocateInt32Column,
        allocateInt64Column, allocateFloatColumn,
        allocateDoubleColumn, allocateBinaryColumn};

static const UpdateColumn updateColumn[6] = {
        putInt8, putInt16, putInt32, putInt64, putFloat, putDouble
};

static const BatchUpdateColumn batchUpdateColumn[7] = {
        putInt8s, putInt16s, putInt32s, putInt64s, putFloats, putDoubles, putBinary
};

ColumnVector *allocateColumn(long capacity, DataType type) {
    return columnAllocator[type](capacity);
}

void updateValue(ColumnVector *vector, long rowId, void *value) {
    updateColumn[vector->type](vector, rowId, value);
}

void batchUpdate(ColumnVector *vector, long rowId, void *value, int nums) {
    batchUpdateColumn[vector->type](vector, rowId, value, nums);
}