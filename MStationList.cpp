//
// Created by codex on 26-05-14.
//

#include "MStationList.h"

#include <QTimer>

MStationList::MStationList(QWidget *parent)
    : QWidget(parent)
{
    InitLayout();
}

MStationList::~MStationList()
{
}

void MStationList::InitLayout()
{
    m_pMainLayout = new QVBoxLayout(this);
    m_pMainLayout->setContentsMargins(0, 0, 0, 0);
    m_pMainLayout->setSpacing(15);
    m_pMainLayout->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
}

void MStationList::SetArcSize(int x, int y)
{
    m_nArcX = x;
    m_nArcY = y;
}

void MStationList::SetBorderSize(int size)
{
    m_nBdSize = size;
}

void MStationList::SetBorderColor(const QColor &color)
{
    m_clBorder = color;
}

void MStationList::SetBackgroundColor(const QColor &color)
{
    m_clBackground = color;
}

void MStationList::AddStationItem(MStationItem *item)
{
    if (item == nullptr)
    {
        return;
    }

    m_pMainLayout->addWidget(item);
    m_StationItemList.append(item);
    m_selectedStationItem = item;

    QTimer::singleShot(0, this, &MStationList::AdjustContent);
}

MStationItem *MStationList::GetStationItem()
{
    return m_selectedStationItem;
}

void MStationList::Clear()
{
    while (!m_StationItemList.isEmpty())
    {
        auto *item = m_StationItemList.takeLast();
        m_pMainLayout->removeWidget(item);
        item->deleteLater();
    }
    m_selectedStationItem = nullptr;
    AdjustContent();
}

void MStationList::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(m_clBackground);

    if (m_nBdSize == 0)
    {
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(rect(), m_nArcX, m_nArcY);
    }
    else
    {
        painter.setPen(QPen(m_clBorder, m_nBdSize));
        painter.drawRoundedRect(rect().adjusted(m_nBdSize, m_nBdSize, -m_nBdSize, -m_nBdSize), m_nArcX, m_nArcY);
    }
}

void MStationList::AdjustContent()
{
    setFixedHeight(m_pMainLayout->sizeHint().height());
    emit UpdateContent();
}
