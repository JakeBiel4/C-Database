#pragma once
//must be overwritten by a subclass
template<class T> class Comparator {
public:
    virtual int compare(T& a, T& b) = 0;
    virtual ~Comparator() = default;
};
