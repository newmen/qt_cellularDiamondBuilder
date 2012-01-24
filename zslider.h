#ifndef ZSLIDER_H
#define ZSLIDER_H

#include <QSlider>

class ZSlider : public QSlider
{
//    Q_OBJECT
public:
    explicit ZSlider(QWidget *parent, int max_value);
    
//signals:
//public slots:

private:
    ZSlider(const ZSlider &);
    ZSlider &operator= (const ZSlider &);
};

#endif // ZSLIDER_H
