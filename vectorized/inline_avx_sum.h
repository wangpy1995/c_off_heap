//
// Created by wpy on 18-4-13.
//
#include <immintrin.h>
#include <stdbool.h>

#ifndef C_OFF_HEAP_INLINE_AVX_SUM_H
#define C_OFF_HEAP_INLINE_AVX_SUM_H
#ifdef __cplusplus
extern "C" {
#endif

#define init_sum __m256i za, zb, za0, za1

#define sum256(a, b, i, sum) za = _mm256_load_si256((const __m256i *) ((a) + (i)));\
zb = _mm256_cvtepi8_epi16(*(__m128i *) ((b) + (i)));\
za0 = _mm256_cvtepi8_epi16(_mm256_extracti128_si256(za, 0x0));\
za0 = _mm256_madd_epi16(za0, zb);\
zb = _mm256_cvtepi8_epi16(*(__m128i *) ((b) + (i) + 16));\
za1 = _mm256_cvtepi8_epi16(_mm256_extracti128_si256(za, 0x1));\
za1 = _mm256_madd_epi16(za1, zb);\
za = _mm256_add_epi32(za1, za0);\
(sum) = _mm256_add_epi32((sum), za)

inline int byte_cmp(const char *src, const char *des, int len) {
    int i;
    for (i = 0; i < len; ++i) {
        if (src[i] != des[i]) {
            return src[i] > des[i] ? 1 : -1;
        }
    }
    return 0;
}

inline int avx256_cmpeq(const char *src, const char *des, int cmpLen) {
    int i;
    //TODO 内存对齐
    int tail = cmpLen & 0x1F;
    int head = cmpLen - tail;

    __m256i src_m = *(const __m256i *) src;
    __m256i des_m = *(const __m256i *) des;
    __m256i res;
    long *r = (long *) &res;
    for (i = 0; i < head; i += 32) {
        res = _mm256_cmpeq_epi64(src_m, des_m);
        if (r[0] + r[1] + r[2] + r[3] != 4) {
            return false;
        }
    }
    return byte_cmp(src + head, des + head, tail);
}

inline int avx128_cmpeq(const char *src, const char *des, int cmpLen) {
    int i;
    //TODO 内存对齐
    int tail = cmpLen & 0x0F;
    int head = cmpLen - tail;
    __m128i src_m = *(const __m128i *) src;
    __m128i des_m = *(const __m128i *) des;
    __m128i res;
    long *r = (long *) &res;
    for (i = 0; i < head; i += 16) {
        res = _mm_cmpeq_epi64(src_m, des_m);
        if (r[0] + r[1] != 2) {
            return false;
        }
    }
    return byte_cmp(src + head, des + head, tail);
}

#ifdef __cplusplus
"}"
#endif

#endif //JNI_TEST_INLINE_AVX_SUM_H