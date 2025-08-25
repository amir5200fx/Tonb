//
// Created by amir on 8/22/25.
//
#pragma once
template<class T>
void tonb::base::Range<T>::check(T lower, T upper) {
    if (lower > upper) {
        throw std::invalid_argument("interval lower is greater than upper");
    }
}

template<class T>
bool tonb::base::Range<T>::empty() const noexcept {
    return data_.first == data_.second;
}

template<class T>
bool tonb::base::Range<T>::inside(T x) const noexcept{
    return data_.first <= x && x <= data_.second;
}

template<class T>
void tonb::base::Range<T>::set(T lower, T upper) {
    data_.first = lower;
    data_.second = upper;
    check(data_.first, data_.second);
}
