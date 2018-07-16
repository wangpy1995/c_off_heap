//
// Created by wpy on 18-7-16.
//

#ifndef C_OFF_HEAP_UTILS_H
#define C_OFF_HEAP_UTILS_H

template<typename t>
inline t min(const t &lhs, const t &rhs) {
    return lhs < rhs ? lhs : rhs;
}
#endif //C_OFF_HEAP_UTILS_H
