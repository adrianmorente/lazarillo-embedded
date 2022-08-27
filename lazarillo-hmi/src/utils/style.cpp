#include "lazarillo-hmi/utils/style.h"

#include <QColor>
#include <QDebug>
#include <iostream>

using lzr::utils::Style;

Style::Style(QObject *parent)
    : QObject(parent)
{
}

Style::Style(Style const &p_style, QObject *parent)
    : QObject(parent)
{
    m_type            = p_style.m_type;
    m_accentColor     = p_style.m_accentColor;
    m_backgroundColor = p_style.m_backgroundColor;
    m_overlayColor    = p_style.m_overlayColor;
    m_iconPath        = p_style.m_iconPath;
}

void Style::changeSkin()
{
    if (m_type == Style::Skin::Light)
    {
        setType(Style::Skin::Dark);
        setAccentColor("#FFBD00");
        setBackgroundColor(QColor("#303030"));
        setOverlayColor("white");
        setIconPath("qrc:/img/sun.png");
    }
    else
    {
        setType(Style::Skin::Light);
        setAccentColor("#75B8C8");
        setBackgroundColor("white");
        setOverlayColor("black");
        setIconPath("qrc:/img/moon.png");
    }
}

Style::Skin Style::getType() const
{
    return m_type;
}

void Style::setType(Style::Skin const &p_type) noexcept
{
    m_type = p_type;
    emit typeChanged();
}

QColor Style::getAccentColor() const
{
    return m_accentColor;
}

void Style::setAccentColor(QColor const &p_color) noexcept
{
    m_accentColor = p_color;
    emit accentColorChanged();
}

QColor Style::getBackgroundColor() const
{
    return m_backgroundColor;
}

void Style::setBackgroundColor(QColor const &p_color) noexcept
{
    m_backgroundColor = p_color;
    emit backgroundColorChanged();
}

QColor Style::getOverlayColor() const
{
    return m_overlayColor;
}

void Style::setOverlayColor(QColor const &p_color) noexcept
{
    m_overlayColor = p_color;
    emit overlayColorChanged();
}

QString Style::getIconPath() const
{
    return m_iconPath;
}

void Style::setIconPath(QString const &p_path) noexcept
{
    m_iconPath = p_path;
    emit iconPathChanged();
}
