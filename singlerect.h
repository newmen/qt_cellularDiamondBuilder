#ifndef SINGLERECT_H
#define SINGLERECT_H

#include <map>
#include <QRect>

typedef std::map<unsigned int, QRect> QRectHash;

class SingleRect
{
public:
    static QRect* instance(int left, int top, int width, int height);

protected:
    SingleRect();

private:
    SingleRect(SingleRect const&);
    SingleRect& operator=(SingleRect const&);

    static unsigned int uniqueHash(int left, int top, int width, int height);

    static QRectHash _instances;
};

#endif // SINGLERECT_H
