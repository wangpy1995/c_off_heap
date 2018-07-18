//
// Created by wangpengyu6 on 18-7-18.
//

#include <vectorized/column_vector.h>
#include "git_wpy_format_vector_OffHeapUtils.h"

/*
 * Class:     git_wpy_format_vector_OffHeapUtils
 * Method:    allocateColumn
 * Signature: (IJ)J
 */
JNIEXPORT jlong JNICALL Java_git_wpy_format_vector_OffHeapUtils_allocateColumn
        (JNIEnv *env, jclass ignore, jint dataType, jlong capacity) {
    ColumnVector *vector = allocateColumn(capacity, dataType);
    return (jlong) vector;
}

/*
 * Class:     git_wpy_format_vector_OffHeapUtils
 * Method:    setNullAt
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_git_wpy_format_vector_OffHeapUtils_setNullAt
        (JNIEnv *env, jclass ignore, jlong ptr, jlong rowId) {
    ColumnVector *vector = (ColumnVector *) ptr;
}

/*
 * Class:     git_wpy_format_vector_OffHeapUtils
 * Method:    setByte
 * Signature: (JJB)V
 */
JNIEXPORT void JNICALL Java_git_wpy_format_vector_OffHeapUtils_setByte
        (JNIEnv *env, jclass ignore, jlong ptr, jlong rowId, jbyte value) {
    ColumnVector *vector = (ColumnVector *) ptr;
    put(vector, rowId, &value);
}

/*
 * Class:     git_wpy_format_vector_OffHeapUtils
 * Method:    setShort
 * Signature: (JJS)V
 */
JNIEXPORT void JNICALL Java_git_wpy_format_vector_OffHeapUtils_setShort
        (JNIEnv *env, jclass ignore, jlong ptr, jlong rowId, jshort value) {
    ColumnVector *vector = (ColumnVector *) ptr;
    put(vector, rowId, &value);
}

/*
 * Class:     git_wpy_format_vector_OffHeapUtils
 * Method:    setInt
 * Signature: (JJI)V
 */
JNIEXPORT void JNICALL Java_git_wpy_format_vector_OffHeapUtils_setInt
        (JNIEnv *env, jclass ignore, jlong ptr, jlong rowId, jint value) {
    ColumnVector *vector = (ColumnVector *) ptr;
    put(vector, rowId, &value);
}

/*
 * Class:     git_wpy_format_vector_OffHeapUtils
 * Method:    setLong
 * Signature: (JJJ)V
 */
JNIEXPORT void JNICALL Java_git_wpy_format_vector_OffHeapUtils_setLong
        (JNIEnv *env, jclass ignore, jlong ptr, jlong rowId, jlong value) {
    ColumnVector *vector = (ColumnVector *) ptr;
    put(vector, rowId, &value);
}

/*
 * Class:     git_wpy_format_vector_OffHeapUtils
 * Method:    setFloat
 * Signature: (JJF)V
 */
JNIEXPORT void JNICALL Java_git_wpy_format_vector_OffHeapUtils_setFloat
        (JNIEnv *env, jclass ignore, jlong ptr, jlong rowId, jfloat value) {
    ColumnVector *vector = (ColumnVector *) ptr;
    put(vector, rowId, &value);
}

/*
 * Class:     git_wpy_format_vector_OffHeapUtils
 * Method:    setDouble
 * Signature: (JJD)V
 */
JNIEXPORT void JNICALL Java_git_wpy_format_vector_OffHeapUtils_setDouble
        (JNIEnv *env, jclass ignore, jlong ptr, jlong rowId, jdouble value) {
    ColumnVector *vector = (ColumnVector *) ptr;
    put(vector, rowId, &value);
}

/*
 * Class:     git_wpy_format_vector_OffHeapUtils
 * Method:    setByteArray
 * Signature: (JJ[B)V
 */
JNIEXPORT void JNICALL Java_git_wpy_format_vector_OffHeapUtils_setByteArray__JJ_3B
        (JNIEnv *env, jclass ignore, jlong ptr, jlong rowId, jbyteArray bytes) {
    ColumnVector *vector = (ColumnVector *) ptr;
    jint len = (*env)->GetArrayLength(env, bytes);
    jbyte *value = malloc(sizeof(char) * len);
    (*env)->GetByteArrayRegion(env, bytes, 0, len, value);
    put(vector, rowId, &value);
}

/*
 * Class:     git_wpy_format_vector_OffHeapUtils
 * Method:    setByteArray
 * Signature: (JJLjava/nio/ByteBuffer;)V
 */
JNIEXPORT void JNICALL Java_git_wpy_format_vector_OffHeapUtils_setByteArray__JJLjava_nio_ByteBuffer_2
        (JNIEnv *env, jclass ignore, jlong ptr, jlong rowId, jobject buff) {
    void *value = (*env)->GetDirectBufferAddress(env, buff);
    ColumnVector *vector = (ColumnVector *) ptr;
    put(vector, rowId, value);
}

/*
 * Class:     git_wpy_format_vector_OffHeapUtils
 * Method:    bulkPut
 * Signature: (JJ[BI)V
 */
JNIEXPORT void JNICALL Java_git_wpy_format_vector_OffHeapUtils_bulkPut__JJ_3BI
        (JNIEnv *env, jclass ignore, jlong ptr, jlong rowId, jbyteArray bytes, jint count) {
    ColumnVector *vector = (ColumnVector *) ptr;
    jint len = (*env)->GetArrayLength(env, bytes);
    jbyte *value = malloc(sizeof(char) * len);
    (*env)->GetByteArrayRegion(env, bytes, 0, len, value);
    bulkPut(vector, rowId, &value, count);
}

/*
 * Class:     git_wpy_format_vector_OffHeapUtils
 * Method:    bulkPut
 * Signature: (JJ[SI)V
 */
JNIEXPORT void JNICALL Java_git_wpy_format_vector_OffHeapUtils_bulkPut__JJ_3SI
        (JNIEnv *env, jclass ignore, jlong ptr, jlong rowId, jshortArray shortBytes, jint count) {
    ColumnVector *vector = (ColumnVector *) ptr;
    jint len = (*env)->GetArrayLength(env, shortBytes);
    jbyte *value = malloc(sizeof(char) * len);
    (*env)->GetByteArrayRegion(env, shortBytes, 0, len, value);
    bulkPut(vector, rowId, &value, count);
}

/*
 * Class:     git_wpy_format_vector_OffHeapUtils
 * Method:    bulkPut
 * Signature: (JJ[CI)V
 */
JNIEXPORT void JNICALL Java_git_wpy_format_vector_OffHeapUtils_bulkPut__JJ_3CI
        (JNIEnv *env, jclass ignore, jlong ptr, jlong rowId, jcharArray charBytes, jint count) {
    ColumnVector *vector = (ColumnVector *) ptr;
    jint len = (*env)->GetArrayLength(env, charBytes);
    jbyte *value = malloc(sizeof(char) * len);
    (*env)->GetByteArrayRegion(env, charBytes, 0, len, value);
    bulkPut(vector, rowId, &value, count);
}

/*
 * Class:     git_wpy_format_vector_OffHeapUtils
 * Method:    bulkPut
 * Signature: (JJ[II)V
 */
JNIEXPORT void JNICALL Java_git_wpy_format_vector_OffHeapUtils_bulkPut__JJ_3II
        (JNIEnv *env, jclass ignore, jlong ptr, jlong rowId, jintArray intBytes, jint count) {
    ColumnVector *vector = (ColumnVector *) ptr;
    jint len = (*env)->GetArrayLength(env, intBytes);
    jbyte *value = malloc(sizeof(char) * len);
    (*env)->GetByteArrayRegion(env, intBytes, 0, len, value);
    bulkPut(vector, rowId, &value, count);
}

/*
 * Class:     git_wpy_format_vector_OffHeapUtils
 * Method:    bulkPut
 * Signature: (JJ[JI)V
 */
JNIEXPORT void JNICALL Java_git_wpy_format_vector_OffHeapUtils_bulkPut__JJ_3JI
        (JNIEnv *env, jclass ignore, jlong ptr, jlong rowId, jlongArray longBytes, jint count) {
    ColumnVector *vector = (ColumnVector *) ptr;
    jint len = (*env)->GetArrayLength(env, longBytes);
    jbyte *value = malloc(sizeof(char) * len);
    (*env)->GetByteArrayRegion(env, longBytes, 0, len, value);
    bulkPut(vector, rowId, &value, count);
}

/*
 * Class:     git_wpy_format_vector_OffHeapUtils
 * Method:    bulkPut
 * Signature: (JJ[FI)V
 */
JNIEXPORT void JNICALL Java_git_wpy_format_vector_OffHeapUtils_bulkPut__JJ_3FI
        (JNIEnv *env, jclass ignore, jlong ptr, jlong rowId, jfloatArray floatBytes, jint count) {
    ColumnVector *vector = (ColumnVector *) ptr;
    jint len = (*env)->GetArrayLength(env, floatBytes);
    jbyte *value = malloc(sizeof(char) * len);
    (*env)->GetByteArrayRegion(env, floatBytes, 0, len, value);
    bulkPut(vector, rowId, &value, count);
}

/*
 * Class:     git_wpy_format_vector_OffHeapUtils
 * Method:    bulkPut
 * Signature: (JJ[DI)V
 */
JNIEXPORT void JNICALL Java_git_wpy_format_vector_OffHeapUtils_bulkPut__JJ_3DI
        (JNIEnv *env, jclass ignore, jlong ptr, jlong rowId, jdoubleArray doubleBytes, jint count) {
    ColumnVector *vector = (ColumnVector *) ptr;
    jint len = (*env)->GetArrayLength(env, doubleBytes);
    jbyte *value = malloc(sizeof(char) * len);
    (*env)->GetByteArrayRegion(env, doubleBytes, 0, len, value);
    bulkPut(vector, rowId, &value, count);
}

/*
 * Class:     git_wpy_format_vector_OffHeapUtils
 * Method:    freeColumn
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_git_wpy_format_vector_OffHeapUtils_freeColumn
        (JNIEnv *env, jclass ignore, jlong ptr) {
    ColumnVector *vector = (ColumnVector *) ptr;
    freeColumnVector(vector);
}