//
// Created by wangpengyu6 on 18-7-17.
//

#ifndef C_OFF_HEAP_ROW_H
#define C_OFF_HEAP_ROW_H

#ifdef __cplusplus
extern "C" {
#endif


//column 存放数据的地址
struct _ROW {
    void *columns[];
} Row;

//row中存放一行数据  每一行只包含数据的地址
struct _TABLE {
    _ROW *row[];
} Table;

#ifdef __cplusplus
}
#endif
#endif //C_OFF_HEAP_ROW_H
