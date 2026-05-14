//
// Created by codex on 26-05-14.
//

#ifndef MP2000_MSTATIONITEM_H
#define MP2000_MSTATIONITEM_H

#include <QWidget>
#include <QColor>

class MStationItem : public QWidget
{
Q_OBJECT
public:
    explicit MStationItem(QWidget *parent = nullptr);
    ~MStationItem() override;

    void SetTitle(const QString &title);
    void SetArcSize(int x, int y);
    void SetBorderSize(int size);
    void SetBorderColor(const QColor &color);
    void SetBackgroundColor(const QColor &color);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QString m_title{"工位项"};
    int m_nArcX{10};
    int m_nArcY{10};
    int m_nBdSize{1};
    QColor m_clBorder{QColor(0x3D475C)};
    QColor m_clBackground{QColor(0x292F3D)};
};

#endif //MP2000_MSTATIONITEM_H
