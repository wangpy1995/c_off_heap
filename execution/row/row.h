//
// Created by wangpengyu6 on 18-7-17.
//

#ifndef C_OFF_HEAP_ROW_H
#define C_OFF_HEAP_ROW_H

#include <column_vector.h>

#ifdef __cplusplus
extern "C" {
#endif

//object 内部存放一个元素的指针
typedef struct _OBJECT {
    void *ptr;
} Object;

#ifdef __cplusplus
}
#endif

//column 存放数据的地址
class Row {
public:
    template<typename T>
    explicit Row(T &seq, int size) : columns(seq), size(size) {}

    template<typename T>
    explicit Row(T &seq) : columns(seq), size(sizeof(seq) / sizeof(seq[0])) {}

    virtual ~Row() = default;

    template<typename data_type>
    inline data_type *getAs(const int idx) const {
        if (idx >= size) return nullptr;
        return (data_type *) (this->columns[idx].ptr);
    }

    template<typename data_type>
    inline void put(const int idx, const data_type &value) {
        if (idx >= size)return;
        this->columns[idx].ptr = &value;
    }

protected:
    explicit Row() : columns(nullptr), size(0) {}

    Row(const Row &r) = default;

    Object *columns;
    int size;
private:
    Row &operator=(const Row &that) { return *this; };
};

#endif //C_OFF_HEAP_ROW_H
