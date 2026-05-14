//
// Created by codex on 26-05-14.
//

#ifndef MP2000_MSTATIONLIST_H
#define MP2000_MSTATIONLIST_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPainter>
#include <QList>

#include "MStationItem.h"

class MStationList : public QWidget
{
Q_OBJECT
public:
    explicit MStationList(QWidget *parent = nullptr);
    ~MStationList() override;

    void InitLayout();
    void SetArcSize(int x, int y);
    void SetBorderSize(int size);
    void SetBorderColor(const QColor &color);
    void SetBackgroundColor(const QColor &color);

    void AddStationItem(MStationItem *item);
    MStationItem *GetStationItem();
    void Clear();

signals:
    void UpdateContent();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void AdjustContent();

    QList<MStationItem *> m_StationItemList{};
    MStationItem *m_selectedStationItem{};
    QVBoxLayout *m_pMainLayout{};

    int m_nArcX{20};
    int m_nArcY{20};
    int m_nBdSize{};
    QColor m_clBorder{};
    QColor m_clBackground{Qt::transparent};
};

#endif //MP2000_MSTATIONLIST_H
