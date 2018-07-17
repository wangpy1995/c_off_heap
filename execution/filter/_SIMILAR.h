//
// Created by wangpengyu6 on 18-7-17.
//

#ifndef C_OFF_HEAP_SIMILAR_H
#define C_OFF_HEAP_SIMILAR_H

#ifdef __cplusplus
extern "C" {
#endif
#define TAG_LEN         16
#define MODEL_LEN 512

float compare(const char *src, const char *dst);

#ifdef __cplusplus
}
#endif

#endif //C_OFF_HEAP_SIMILAR_H
