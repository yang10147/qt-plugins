#ifndef SHADOWHELPER_H
#define SHADOWHELPER_H

#include <QObject>
#include <QWidget>
#include <QMap>
#include <QPointer>
#include <QWindow>

class ShadowHelper : public QObject
{
    Q_OBJECT
public:
    explicit ShadowHelper(QObject* parent = nullptr);
    bool registerWidget(QWidget*);
    void unregisterWidget(QWidget*);
    void installShadows(QWidget*, qreal) {}
    void uninstallShadows(QWidget*) {}

protected:
    bool eventFilter(QObject*, QEvent*) override;

private:
    QMap<QWindow*, QPointer<QWidget>> m_widgets;
};

#endif
