#include "singlerect.h"

QRectHash SingleRect::_instances = QRectHash();

QRect* SingleRect::instance(int left, int top, int width, int height) {
    unsigned int hash = uniqueHash(left, top, width, height);

    if (_instances.find(hash) == _instances.end()) {
        _instances[hash] = QRect(left, top, width, height);
    }

    return &_instances[hash];
}

unsigned int SingleRect::uniqueHash(int left, int top, int width, int height) {
    unsigned int hash = 17;
    hash = hash * 37 + left;
    hash = hash * 37 + top;
    hash = hash * 37 + width;
    hash = hash * 37 + height;
    return hash;
}
