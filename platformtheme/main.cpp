#include <qpa/qplatformtheme_p.h>
#include <qpa/qplatformthemeplugin.h>
#include "platformtheme.h"

#include <qpa/qplatformtheme.h>

QT_BEGIN_NAMESPACE

void updateXdgIconSystemTheme()
{
    // XdgIconLoader 被 Qt6 内部管理
}

class PlatformThemePlugin : public QPlatformThemePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QPlatformThemeFactoryInterface_iid FILE "cutefish-platformtheme.json")

public:
    PlatformThemePlugin(QObject *parent = nullptr)
        : QPlatformThemePlugin(parent) {}

    QPlatformTheme *create(const QString &key, const QStringList &paramList) override
    {
        Q_UNUSED(key)
        Q_UNUSED(paramList)
        return new PlatformTheme;
    }
};

QT_END_NAMESPACE

#include "main.moc"
