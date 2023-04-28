#include "constants.h"
#include <QGuiApplication>

namespace PROTECT_NAMESPACE {


struct ConstantData
{
    int width;
    int height;
    QFont largeFont;
    QColor color;
};


Constants::Constants(QObject *parent)
    : QObject{parent}
    , m_data(new ConstantData)
{
    m_data->width = 460;
    m_data->height = 600;
    QFont defaultFont = QGuiApplication::font();
    m_data->largeFont = QFont(defaultFont.family(), defaultFont.pixelSize() * 1.6);
    m_data->color = QColor("#c2c2c2");
}

Constants::~Constants()
{
    delete m_data;
}

int Constants::width()
{
    return m_data->width;
}

int Constants::height()
{
    return m_data->height;
}

QFont Constants::font()
{
    return QGuiApplication::font();
}

QFont Constants::largeFont()
{
    return m_data->largeFont;
}

QColor Constants::backgroundColor()
{
    return m_data->color;
}

}
