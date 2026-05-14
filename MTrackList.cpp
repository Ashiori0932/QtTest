//
// Created by wyyk on 25-10-31.
//

#include "MTrackList.h"

#include "src/utils/MSingletonIPCLog.h"

QWidget* MTrackList::m_pDialog = nullptr;

MTrackList::MTrackList(QWidget *parent) : QWidget(parent)
{
    ///< 初始化布局
    InitLayout();
}

MTrackList::~MTrackList()
{

}

void MTrackList::InitLayout()
{
    // 实例化
    m_pMainLayout = new QVBoxLayout(this);
    // 设置边距
    m_pMainLayout->setContentsMargins(0, 0, 0, 0);
    // 设置间距
    m_pMainLayout->setSpacing(15);
    // 设置主布局对齐方式
    m_pMainLayout->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

    m_pCraftSettings = new MCraftSettings(m_pDialog);

    m_pCraftSettings->move(260, 138);
    // 显示角度调整组件
    m_pCraftSettings->raise();
    m_pCraftSettings->activateWindow();
    m_pCraftSettings->show();
    // 测试用
    m_pCraftSettings->SetTravelAngle(30);
    m_pCraftSettings->SetWorkAngle(60);

    WELD_PROCESS stData = {};
    m_pCraftSettings->SetWeldProcessData(stData);
    m_pCraftSettings->Hide();

    // 事件响应：
    // 关闭键和取消键 均为直接关闭窗口
    connect(m_pCraftSettings, &MCraftSettings::CloseBtnClicked, this, [this]()
    {
        m_pCraftSettings->hide();
    });

    connect(m_pCraftSettings, &MCraftSettings::ResetBtnClicked, this, [this]()
    {
        // 重置逻辑写在类内部
    });

    // 确认键 删除参数后关闭弹窗
    connect(m_pCraftSettings, &MCraftSettings::ConfirmBtnClicked, this, [this](WELD_PROCESS _stData)
    {
        m_pCraftSettings->hide();
        GetWeldItem()->SetWeldProcessData(_stData);
    });


}

void MTrackList::SetArcSize(int x, int y)
{
    m_nArcX = x;    ///< 圆角左宽
    m_nArcY = y;    ///< 圆角右宽
}

void MTrackList::SetBorderSize(int size)
{
    m_nBdSize = size;
}

void MTrackList::SetBorderColor(const QColor &color)
{
    m_clBorder = color;
}

void MTrackList::SetBackgroundColor(const QColor &color)
{
    m_clBackground = color;
}

void MTrackList::paintEvent(QPaintEvent *event)
{
//    qDebug() << "update";
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    // 绘制圆角背景
    painter.setBrush(m_clBackground);
    if (m_nBdSize == 0)
    {
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(rect(), m_nArcX, m_nArcY);
    } else
    {
        painter.setPen(QPen(m_clBorder, m_nBdSize));
        painter.drawRoundedRect(rect().adjusted(m_nBdSize, m_nBdSize, -m_nBdSize, -m_nBdSize),
                                m_nArcX, m_nArcY);
    }
}

void MTrackList::AdjustContent()
{
    // 强制布局立即更新
//    m_pMainLayout->update();
//    m_pMainLayout->activate();

    // 给Qt一点时间处理布局更新
//    QApplication::processEvents();
    auto height = m_pMainLayout->sizeHint().height();
//    qDebug() << height;

//    int height = 0;
//    // 遍历容器列表，计算总高度
//    for (auto &widget: m_WeldItemList)
//    {
//        qDebug() << widget->height();
//        height += widget->height();
//    }
//    qDebug() << "total:" << height;
    setFixedHeight(height);
    emit UpdateContent();
}

void MTrackList::AddWeldItem(MWeldItem *item)
{
    if (item == nullptr)
    {
        return;
    }
    m_pMainLayout->addWidget(item);
    m_WeldItemList.append(item);
    m_ItemTypeList.append(1);
    item->SetWeldIndex(m_WeldItemList.size());
    // 绑定尺寸变化信号
    connect(item, &MWeldItem::SizeChanged, this, [this]()
    {
        QTimer::singleShot(0, this, &MTrackList::AdjustContent);
//        AdjustContent();
    });
    // 绑定选中信号
    connect(item, &MWeldItem::PickItem, this, [this, item]()
    {
        // 准备日志信息
        std::stringstream ss;
        int index{};
        item->GetWeldIndex(index);
        ss << "用户选中第" << index << "条焊缝轨迹";
        MSingletonIPCLog::GetInstance().WriteLog(MLOG_TYPE_INFO, MLOG_DIR_USER,
                                                 ss.str(), __FILENAME__, __LINE__);

        // 替换选中项指针所指向的控件
        if (m_selectedWeldItem != nullptr)  // 如果原焊缝项所指不为空
        {
            m_selectedWeldItem->SetIsPicked(false);
        }
        if (m_selectedDragItem != nullptr)  // 如果原拖拽项所指不为空
        {
            m_selectedDragItem->SetIsPicked(false);
        }
        m_selectedWeldItem = item;
        m_selectedDragItem = nullptr;
        // 获取点索引
        std::vector<int> vec_idx{};
        GetWeldItemPointIndex(item, vec_idx);
        emit PushSelectItemPointIdx(vec_idx);
    });
    // 绑定点列项选中信号
    connect(item, &MWeldItem::PointListItemSelected, this, [this, item](int index)
    {
        // 获取点索引
        std::vector<int> vec_idx{};
        GetWeldItemPointIndex(item, vec_idx);
        emit PushPointListSelectItemIdx(vec_idx[index]);
    });
    // 绑定点击工艺设置信号
    connect(item, &MWeldItem::CraftBtnClicked, this, [this](WELD_PROCESS _stData)
    {
        m_pCraftSettings->SetWeldProcessData(_stData);
        m_pCraftSettings->Show();
    });

    // 延迟调用确保布局更新完成
    QTimer::singleShot(0, this, &MTrackList::AdjustContent);

//    AdjustContent();

    connect(item, &MWeldItem::SaveAsNewTemple,
            this, &MTrackList::SaveAsNewTemple);

    connect(this, &MTrackList::TempleSaved, item, &MWeldItem::TempleSaved);
}

void MTrackList::AddDragItem(MDragItem *item)
{
    if (item == nullptr)
    {
        return;
    }
    m_pMainLayout->addWidget(item);
    m_DragItemList.append(item);
    m_ItemTypeList.append(0);
    item->SetDragIndex(m_DragItemList.size());
    // 绑定尺寸变化信号
    connect(item, &MDragItem::SizeChanged, this, [this]()
    {
//        AdjustContent();
        QTimer::singleShot(0, this, &MTrackList::AdjustContent);
    });
    // 绑定选中信号
    connect(item, &MDragItem::PickItem, this, [this, item]()
    {
        // 准备日志信息
        std::stringstream ss;
        int index{};
        item->GetDragIndex(index);
        ss << "用户选中第" << index << "条拖拽轨迹";
        MSingletonIPCLog::GetInstance().WriteLog(MLOG_TYPE_INFO, MLOG_DIR_USER,
                                                 ss.str(), __FILENAME__, __LINE__);
        // 替换选中项指针所指向的控件
        if (m_selectedWeldItem != nullptr)  // 如果原焊缝项所指不为空
        {
            m_selectedWeldItem->SetIsPicked(false);
        }
        if (m_selectedDragItem != nullptr)  // 如果原拖拽项所指不为空
        {
            m_selectedDragItem->SetIsPicked(false);
        }
        m_selectedWeldItem = nullptr;
        m_selectedDragItem = item;
        // 获取点索引
        std::vector<int> vec_idx{};
        GetDragItemPointIndex(item, vec_idx);
        emit PushSelectItemPointIdx(vec_idx);
    });
    // 绑定点列项选中信号
    connect(item, &MDragItem::PointListItemSelected, this, [this, item](int index)
    {
        // 获取点索引
        std::vector<int> vec_idx{};
        GetDragItemPointIndex(item, vec_idx);
        emit PushPointListSelectItemIdx(vec_idx[index]);
    });
    // 绑定删除信号
    connect(item, &MDragItem::DeleteItem, this, [this, item]()
    {
        if (m_selectedDragItem == item)
        {
            m_selectedDragItem = nullptr;
        }
        m_DragItemList.removeOne(item);
//        m_ItemTypeList.removeOne(item);
        item->deleteLater();
//        AdjustContent();
        QTimer::singleShot(0, this, &MTrackList::AdjustContent);
    });

    // 延迟调用确保布局更新完成
    QTimer::singleShot(0, this, &MTrackList::AdjustContent);

//    // 立即更新一次内容
//    AdjustContent();
}

void MTrackList::SetDialog(QWidget *_pDialog)
{
    m_pDialog = _pDialog;
}

void MTrackList::Clear()
{
    for (auto item: m_DragItemList)
    {
        item->deleteLater();
    }
    for (auto item: m_WeldItemList)
    {
        item->deleteLater();
    }
    m_DragItemList.clear();
    m_WeldItemList.clear();
    m_ItemTypeList.clear();
    m_selectedWeldItem = nullptr;
    m_selectedDragItem = nullptr;
//    AdjustContent();
    QTimer::singleShot(0, this, &MTrackList::AdjustContent);
}

MWeldItem *MTrackList::GetWeldItem()
{
    return m_selectedWeldItem;
}

void MTrackList::UpdateAllWeldItem()
{
    for(auto Item:m_WeldItemList)
    {
        Item->UpdateTemples();
    }
}

void MTrackList::GetDragItemPointIndex(MDragItem *item, std::vector<int> &_vec_idx)
{
    // 准备变量
    _vec_idx.clear();
    int index{};
    item->GetDragIndex(index);
    int dragCount{};
    int weldCount{};
    int pointNum{};
    // 获取点数量
    for (auto i: m_ItemTypeList)
    {
        if (i == 0)
        {
            if (dragCount >= index - 1)
            {
                break;
            }
            pointNum += m_DragItemList[dragCount]->GetPointSize();
            dragCount++;
        } else
        {
            pointNum += m_WeldItemList[weldCount]->GetPointSize();
            weldCount++;
        }
    }
    // 获取索引
    int curSize = item->GetPointSize();
    for (int i = pointNum; i < pointNum + curSize;i++)
    {
        _vec_idx.emplace_back(i);
    }
}

void MTrackList::GetWeldItemPointIndex(MWeldItem *item, std::vector<int> &_vec_idx)
{
    // 准备变量
    _vec_idx.clear();
    int index{};
    item->GetWeldIndex(index);
    int dragCount{};
    int weldCount{};
    int pointNum{};
    // 获取点数量
    for (auto i: m_ItemTypeList)
    {
        if (i == 0)
        {
            pointNum += m_DragItemList[dragCount]->GetPointSize();
            dragCount++;
        } else
        {
            if (weldCount >= index - 1)
            {
                break;
            }
            pointNum += m_WeldItemList[weldCount]->GetPointSize();
            weldCount++;
        }
    }
    // 获取索引
    int curSize = item->GetPointSize();
    for (int i = pointNum; i < pointNum + curSize;i++)
    {
        _vec_idx.emplace_back(i);
    }
}
