//
// Created by wangpengyu6 on 18-7-17.
//

#ifndef C_OFF_HEAP_ROW_H
#define C_OFF_HEAP_ROW_H

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
    explicit Row(Object seq[]) : columns(seq) {}
    Row &operator=(const Row &that) {
        if (this == &that) {
            return *this;
        } else {
            this->columns = that.columns;
        }
    }

    template<typename t>
    inline t *getAs(int idx) {
        return (t *) (this->columns[idx].ptr);
    }

    template<typename t>
    inline void put(int idx, t &value) {
        this->columns[idx].ptr = &value;
    }

protected:
    Object *columns;
private:
    explicit Row() : columns(nullptr) {}
};


#endif //C_OFF_HEAP_ROW_H
