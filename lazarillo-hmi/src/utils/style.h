#pragma once

#include <QColor>
#include <QObject>
#include <QString>

namespace lzr
{
namespace utils
{
class Style : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Skin type READ getType WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QColor accentColor READ getAccentColor WRITE setAccentColor
                   NOTIFY accentColorChanged)
    Q_PROPERTY(QColor backgroundColor READ getBackgroundColor WRITE
                   setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(QColor overlayColor READ getOverlayColor WRITE setOverlayColor
                   NOTIFY overlayColorChanged)
    Q_PROPERTY(QString iconPath READ getIconPath WRITE setIconPath NOTIFY
                   iconPathChanged)

public:
    enum Skin
    {
        Light,
        Dark
    };
    Q_ENUM(Skin)

    explicit Style(QObject *parent = nullptr);

    Style(Style const &p_style, QObject *parent = nullptr);

    /**
     * Simply change skin between light and dark when it corresponds
     */
    Q_INVOKABLE void changeSkin();

    Skin getType() const;
    void setType(Skin const &p_type) noexcept;

    QColor getAccentColor() const;
    void setAccentColor(QColor const &p_color) noexcept;

    QColor getBackgroundColor() const;
    void setBackgroundColor(QColor const &p_color) noexcept;

    QColor getOverlayColor() const;
    void setOverlayColor(QColor const &p_color) noexcept;

    QString getIconPath() const;
    void setIconPath(QString const &p_path) noexcept;

private:
    // Identifier of the skin
    Skin m_type{Skin::Light};

    // Background color behind the content
    QColor m_accentColor{"#FFBD00"};

    // Background color behind the content
    QColor m_backgroundColor{"white"};

    // Overlay used over icons to make contrast with the background
    QColor m_overlayColor{"black"};

    // Icon used in the change skin button
    QString m_iconPath{"qrc:/img/moon.png"};

signals:
    void typeChanged();
    void accentColorChanged();
    void backgroundColorChanged();
    void overlayColorChanged();
    void iconPathChanged();
};
} // namespace utils
} // namespace lzr
