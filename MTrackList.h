//
// Created by wyyk on 25-10-31.
//

#ifndef MP2000_MTRACKLIST_H
#define MP2000_MTRACKLIST_H

#include <QWidget>
#include <QPainter>
#include <QVBoxLayout>
#include <QDebug>
#include <QApplication>

#include "MWeldItem.h"
#include "src/frame/RobotPage/MDragItem.h"

class MTrackList : public QWidget
{
Q_OBJECT
public:
    /**
    ***********************************************************************
    * @brief 构造函数
    * @param [IN] parent > 父窗口指针
    * @return 无返回值
    * @others 无
    * @author 王阳煜坤
    ***********************************************************************
    */
    explicit MTrackList(QWidget *parent = nullptr);

    /**
    ***********************************************************************
    * @brief  析构函数
    * @return 无返回值
    * @others 无
    * @author 王阳煜坤
    ***********************************************************************
    */
    ~MTrackList() override;

    /**
    ***********************************************************************
    * @brief  初始化布局
    * @return 无返回值
    * @others 无
    * @author 王阳煜坤
    ***********************************************************************
    */
    void InitLayout();

    /**
    *****************************************************************************
    *	@brief	设置圆角的左右宽
    *	@param	[IN] x > 左宽
    *   @param	[IN] y > 右宽
    *	@return	无返回值
    *	@others 无
    *	@author 王阳煜坤
    *****************************************************************************
    */
    void SetArcSize(int x, int y);

    /**
    *****************************************************************************
    *	@brief	设置边框尺寸
    *	@param	[IN] size > 尺寸（像素）
    *	@return	无返回值
    *	@others 无
    *	@author 王阳煜坤
    *****************************************************************************
    */
    void SetBorderSize(int size);

    /**
    *****************************************************************************
    *	@brief	设置边框颜色
    *	@param	[IN] color > 颜色
    *	@return	无返回值
    *	@others 无
    *	@author 王阳煜坤
    *****************************************************************************
    */
    void SetBorderColor(const QColor &color);

    /**
    *****************************************************************************
    *	@brief	设置背景颜色
    *	@param	[IN] color > 颜色
    *	@return	无返回值
    *	@others 无
    *	@author 王阳煜坤
    *****************************************************************************
    */
    void SetBackgroundColor(const QColor &color);

    /**
    *****************************************************************************
    *	@brief	添加焊缝轨迹控件
    *	@param	[IN] item > 控件指针
    *	@return	无返回值
    *	@others 无
    *	@author 王阳煜坤
    *****************************************************************************
    */
    void AddWeldItem(MWeldItem *item);

    /**
    *****************************************************************************
    *	@brief	添加拖拽轨迹控件
    *	@param	[IN] item > 控件指针
    *	@return	无返回值
    *	@others 无
    *	@author 王阳煜坤
    *****************************************************************************
    */
    void AddDragItem(MDragItem *item);

    /**
    *****************************************************************************
    *	@brief	获取焊缝轨迹控件指针
    *	@param	[IN] index > 要获取的焊缝轨迹在列表中的索引
    *	@return	无返回值
    *	@others 无
    *	@author 王阳煜坤
    *****************************************************************************
    */
    MWeldItem *GetWeldItem();

    /**
    *****************************************************************************
    *	@brief	设置dialog指针
    *	@param	[IN] _pDialog > 指针
    *	@return	无返回值
    *	@others 无
    *	@author 秦李旸
    *****************************************************************************
    */
    static void SetDialog(QWidget *_pDialog);

    /**
    *****************************************************************************
    *	@brief	清空列表
    *	@return	无返回值
    *	@others 无
    *	@author 王阳煜坤
    *****************************************************************************
    */
    void Clear();

    void UpdateAllWeldItem();

signals:
    void SaveAsNewTemple(MWeldItem *_pWeldItem);

    void TempleSaved(int _nId);

    /**
    *****************************************************************************
    *	@brief	布局更新信号
    *	@return	无返回值
    *	@others 无
    *	@author 王阳煜坤
    *****************************************************************************
    */
    void UpdateContent();

    /**
    *****************************************************************************
    *	@brief	推送选中项点索引信号
    *	@return	无返回值
    *	@others 无
    *	@author 王阳煜坤
    *****************************************************************************
    */
    void PushSelectItemPointIdx(std::vector<int> _vec_idx);

    /**
    *****************************************************************************
    *	@brief	推送点列选中项索引信号
    *	@return	无返回值
    *	@others 无
    *	@author 王阳煜坤
    *****************************************************************************
    */
    void PushPointListSelectItemIdx(int index);

protected:
    /**
    ***********************************************************************
    * @brief 重写窗口绘图事件，用于自定义控件绘制
    * @param [IN] event > 绘图事件对象，包含需要绘制的区域信息
    * @return 无返回值
    * @others 无
    * @author 王阳煜坤
    ***********************************************************************
    */
    void paintEvent(QPaintEvent *event) override;

private:

    /**
    ***********************************************************************
    * @brief 调整内容区域
    * @return 无返回值
    * @others 无
    * @author 王阳煜坤
    ***********************************************************************
    */
    void AdjustContent();

    /**
    ***********************************************************************
    * @brief 获取拖拽轨迹项点索引
    * @param [IN] item > 拖拽轨迹项
    * @param [IN] _vec_idx > 轨迹项点索引
    * @return 无返回值
    * @others 无
    * @author 王阳煜坤
    ***********************************************************************
    */
    void GetDragItemPointIndex(MDragItem *item, std::vector<int> &_vec_idx);

    /**
    ***********************************************************************
    * @brief 获取焊缝轨迹项点索引
    * @param [IN] item > 焊缝轨迹项
    * @param [IN] _vec_idx > 轨迹项点索引
    * @return 无返回值
    * @others 无
    * @author 王阳煜坤
    ***********************************************************************
    */
    void GetWeldItemPointIndex(MWeldItem *item, std::vector<int> &_vec_idx);


    ///< 数据管理
    QList<int> m_ItemTypeList{};                     ///< 焊缝轨迹控件种类列表 0:drag 1:weld
    QList<MDragItem *> m_DragItemList{};             ///< 拖拽轨迹控件列表
    QList<MWeldItem *> m_WeldItemList{};             ///< 焊缝轨迹控件列表
    MWeldItem *m_selectedWeldItem{};                   ///< 当前选中的焊缝轨迹控件
    MDragItem *m_selectedDragItem{};                   ///< 当前选中的拖拽轨迹控件
    ///< 布局管理
    QVBoxLayout *m_pMainLayout{};                    ///< 主布局
    ///< 样式属性
    int m_nArcX{20};                                 ///< 圆角x分量
    int m_nArcY{20};                                 ///< 圆角y分量
    int m_nBdSize{};                                 ///< 边框尺寸
    QColor m_clBorder{};                             ///< 边框颜色
    QColor m_clBackground{Qt::transparent};    ///< 背景颜色

    MCraftSettings *m_pCraftSettings;

    static QWidget *m_pDialog;
};


#endif //MP2000_MTRACKLIST_H
