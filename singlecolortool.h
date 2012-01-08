#ifndef SINGLEBRUSH_H
#define SINGLEBRUSH_H

#include <map>
#include <QtGui>

template<class QColorTool>
class SingleColorTool
{
public:
    static QColorTool* instance(Qt::GlobalColor color)  {
        if (_instances.find(color) == _instances.end()) {
            _instances[color] = QColorTool(color);
        }
        return &_instances[color];
    }

protected:
    SingleColorTool();

private:
    SingleColorTool(SingleColorTool const&);
    SingleColorTool& operator=(SingleColorTool const&);


    static std::map<Qt::GlobalColor, QColorTool> _instances;
};

template<class QColorTool>
std::map<Qt::GlobalColor, QColorTool> SingleColorTool<QColorTool>::_instances = std::map<Qt::GlobalColor, QColorTool>();

#endif // SINGLEBRUSH_H
