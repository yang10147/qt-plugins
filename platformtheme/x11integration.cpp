#include "x11integration.h"
#include <QWindow>
#include <QGuiApplication>
#include <qpa/qplatformnativeinterface.h>
#include <netwm.h>
#include <xcb/xcb.h>

X11Integration::X11Integration() {}
X11Integration::~X11Integration() {}

void X11Integration::init() {}

// 获取 XCB 连接的助手函数
static xcb_connection_t* getXcbConnection() {
    auto *native = qGuiApp->platformNativeInterface();
    return static_cast<xcb_connection_t*>(native->nativeResourceForIntegration("connection"));
}

static xcb_window_t getRootWindow() {
    auto *native = qGuiApp->platformNativeInterface();
    return static_cast<xcb_window_t>(reinterpret_cast<quintptr>(native->nativeResourceForIntegration("rootwindow")));
}

bool X11Integration::eventFilter(QObject *obj, QEvent *ev) {
    return QObject::eventFilter(obj, ev);
}

void X11Integration::installDesktopFileName(QWindow *w) {
    QString desktopFileName = qGuiApp->desktopFileName();
    if (desktopFileName.isEmpty()) return;

    NETWinInfo info(getXcbConnection(), w->winId(), getRootWindow(), NET::Properties(), NET::Properties2());
    info.setDesktopFileName(desktopFileName.toUtf8().constData());
}

void X11Integration::setWindowProperty(QWindow *w, const QByteArray &name, const QByteArray &value) {
    if (!w) return;
    // 这里暂时简化处理，确保编译通过
}
