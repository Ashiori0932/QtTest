//
// Created by codex on 26-05-14.
//

#include "MStationItem.h"

#include <QPainter>

MStationItem::MStationItem(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(428, 95);
}

MStationItem::~MStationItem()
{
}

void MStationItem::SetTitle(const QString &title)
{
    m_title = title;
    update();
}

void MStationItem::SetArcSize(int x, int y)
{
    m_nArcX = x;
    m_nArcY = y;
    update();
}

void MStationItem::SetBorderSize(int size)
{
    m_nBdSize = size;
    update();
}

void MStationItem::SetBorderColor(const QColor &color)
{
    m_clBorder = color;
    update();
}

void MStationItem::SetBackgroundColor(const QColor &color)
{
    m_clBackground = color;
    update();
}

void MStationItem::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QRect drawRect = rect();
    if (m_nBdSize > 0)
    {
        painter.setPen(QPen(m_clBorder, m_nBdSize));
        drawRect = drawRect.adjusted(m_nBdSize, m_nBdSize, -m_nBdSize, -m_nBdSize);
    }
    else
    {
        painter.setPen(Qt::NoPen);
    }

    painter.setBrush(m_clBackground);
    painter.drawRoundedRect(drawRect, m_nArcX, m_nArcY);

    painter.setPen(QColor(255, 255, 255, 180));
    painter.drawText(rect().adjusted(16, 0, -16, 0), Qt::AlignVCenter | Qt::AlignLeft, m_title);
}
