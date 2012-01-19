#ifndef COMMON_H
#define COMMON_H

template<typename T, T DefaultValue>
struct ___x3 {
public:
    T x, y, z;

protected:
    ___x3() : x(DefaultValue), y(DefaultValue), z(DefaultValue) {}
    ___x3(const T &x, const T &y, const T &z) : x(x), y(y), z(z) {}
};

// по красоте, надо написать макросы

struct int3 : public ___x3<int, 0> {
    int3() {}
    int3(int x, int y, int z) : ___x3(x, y, z) {}
};

struct dim3 : public ___x3<int, 1> {
    dim3() {}
    dim3(int x, int y, int z) : ___x3(x, y, z) {}
};

#endif // COMMON_H
