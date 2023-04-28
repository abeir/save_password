#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "global_defines.h"
#include <QQmlEngine>
#include <QColor>
#include <QFont>
#include <QObject>


namespace PROTECT_NAMESPACE {


typedef struct ConstantData ConstantData;


class Constants : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int width READ width CONSTANT)
    Q_PROPERTY(int height READ height CONSTANT)
    Q_PROPERTY(QFont font READ font CONSTANT)
    Q_PROPERTY(QFont largeFont READ largeFont CONSTANT)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor CONSTANT)
public:
    explicit Constants(QObject *parent = nullptr);
    ~Constants();


    int width();
    int height();

    QFont font();
    QFont largeFont();

    QColor backgroundColor();
private:
    ConstantData *m_data;
};

}
#endif // CONSTANTS_H
