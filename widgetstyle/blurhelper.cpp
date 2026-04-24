#include "blurhelper.h"
#include <QWindow>
#include <QWidget>

BlurHelper::BlurHelper(QObject* parent) : QObject(parent) {}
void BlurHelper::registerWidget(QWidget* w) { if(w) w->installEventFilter(this); }
void BlurHelper::unregisterWidget(QWidget* w) { if(w) w->removeEventFilter(this); }
bool BlurHelper::eventFilter(QObject* o, QEvent* e) { return QObject::eventFilter(o, e); }
void BlurHelper::installBlur(QWindow*) {}
void BlurHelper::uninstallBlur(QWindow*) {}
