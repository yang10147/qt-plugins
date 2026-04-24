#include "shadowhelper.h"
#include <QEvent>
#include <QWindow>

ShadowHelper::ShadowHelper(QObject* parent) : QObject(parent) {}

bool ShadowHelper::registerWidget(QWidget* widget) 
{ 
    if (!widget) return false;
    widget->installEventFilter(this);
    return true; 
}

void ShadowHelper::unregisterWidget(QWidget* widget) 
{
    if (!widget) return;
    widget->removeEventFilter(this);
}

bool ShadowHelper::eventFilter(QObject* obj, QEvent* ev) 
{
    return QObject::eventFilter(obj, ev);
}
