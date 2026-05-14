//
// Created by mojia on 25-10-31.
//

#ifndef MP2000_MWELDITEM_H
#define MP2000_MWELDITEM_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include "MMultiStyleButton.h"
#include "MInputBox.h"
#include "MComboBox.h"
#include "src/define/MWeldDataDefine.h"
#include "src/res/Resource.h"
#include "MList.h"
#include "MScrollArea.h"
#include "MIconCheckBox.h"
#include "src/frame/RobotPage/MCraftSettings.h"
#include <iomanip>
#include "src/core/MSerialize.h"
#include "src/utils/MWeldDataManager.h"

class MWeldItem : public QWidget
{
Q_OBJECT
public:

    /**
    ***********************************************************************
    * @brief 构造函数
    * @param [IN] *_pParent > 父窗口指针
    * @return 无返回值
    * @others 无
    * @author 秦李旸
    ***********************************************************************
    */
    explicit MWeldItem(QWidget *_pParent = nullptr);

    /**
    ***********************************************************************
    * @brief  析构函数
    * @return 无返回值
    * @others 无
    * @author 秦李旸
    ***********************************************************************
    */
    ~MWeldItem() override;

    /**
    ***********************************************************************
    * @brief 设置背景颜色
    * @param [IN] Color > 背景颜色
    * @return 无返回值
    * @others 无
    * @author 秦李旸
    ***********************************************************************
    */
    void SetBkColor(const QColor &_BkInColor, const QColor &_BkOutColor,
                    const QColor &_BkPickedColor, const QColor &_BkExpandedColor);

    /**
    *****************************************************************************
    *	@brief	设置圆角的xy分量
    *	@param	[IN] _nX > x分量
    *   @param	[IN] _nY > y分量
    *	@return	无返回值
    *	@others 无
    *	@author 秦李旸
    *****************************************************************************
    */
    void SetArcSize(int _nX, int _nY);

    /**
    *****************************************************************************
    *	@brief	设置组件的尺寸
    *	@param	[IN] _nWidth > 宽度
    *	@param	[IN] _nHeight > 高度
    *	@param	[IN] _nExpandedHeight > 展开后高度
    *	@return	无返回值
    *	@others 无
    *	@author 秦李旸
    *****************************************************************************
    */
    void SetItemSize(int _nWidth, int _nHeight, int _nExpandedHeight);

    /**
    *****************************************************************************
    *	@brief	设置是否展开
    *	@param	[IN] _bExpanded > 是否展开
    *	@return	无返回值
    *	@others 无
    *	@author 秦李旸
    *****************************************************************************
    */
    void SetIsExpanded(bool _bExpanded);

    /**
    *****************************************************************************
    *	@brief	设置是否选中
    *	@param	[IN] _bPicked > 是否选中
    *	@return	无返回值
    *	@others 无
    *	@author 秦李旸
    *****************************************************************************
    */
    void SetIsPicked(bool _bPicked);

    /**
    *****************************************************************************
    *	@brief	设置焊接参数结构体
    *	@param	[IN] _stData > 焊接参数结构体
    *	@return	无返回值
    *	@others 无
    *	@author 秦李旸
    *****************************************************************************
    */
    void SetWeldParaData(WELD_PARAMETER _stData);

    /**
    *****************************************************************************
    *	@brief	设置焊接工艺结构体
    *	@param	[IN] _stData > 焊接工艺结构体
    *	@return	无返回值
    *	@others 无
    *	@author 秦李旸
    *****************************************************************************
    */
    void SetWeldProcessData(WELD_PROCESS &_stData);

    /**
    *****************************************************************************
    *	@brief	设置焊缝下标
    *	@param	[IN] _nWeldIndex > 焊缝下标
    *	@return	无返回值
    *	@others 无
    *	@author 秦李旸
    *****************************************************************************
    */
    void SetWeldIndex(int _nWeldIndex);

    /**
    *****************************************************************************
    *	@brief	设置工程名
    *	@param	[IN] _strName > 工程名
    *	@return	无返回值
    *	@others 无
    *	@author 秦李旸
    *****************************************************************************
    */
    void SetProjectName(std::string &_strName);

    /**
    *****************************************************************************
    *	@brief	设置点列
    *	@param	[IN] _vPts > 点列
    *	@return	无返回值
    *	@others 无
    *	@author 秦李旸
    *****************************************************************************
    */
    void SetWeldPointData(std::vector<ROBOT_POINT_DATA> &_vPts);

    /**
    *****************************************************************************
    *	@brief	设置示教状态
    *	@param	[IN] _vPts > 点列
    *	@return	无返回值
    *	@others 无
    *	@author 秦李旸
    *****************************************************************************
    */
    void SetTeachingFlag(bool _bTeachingFlag);

    /**
    *****************************************************************************
    *	@brief	获取焊接参数结构体
    *	@param	[ot] _vPts > 点列
    *	@return	无返回值
    *	@others 无
    *	@author 秦李旸
    *****************************************************************************
    */
    void GetWeldParaData(WELD_PARAMETER &_stData);

    /**
    *****************************************************************************
    *	@brief	获取焊缝下标
    *	@param	[out] _nWeldIndex > 焊缝下标
    *	@return	无返回值
    *	@others 无
    *	@author 秦李旸
    *****************************************************************************
    */
    void GetWeldIndex(int &_nWeldIndex);

    void UpdateTemples();

    /**
    *****************************************************************************
    *	@brief	获取点数量
    *	@return	点数量
    *	@others 无
    *	@author Wang YangYuKun
    *****************************************************************************
    */
    int GetPointSize();

signals:

    /**
    *****************************************************************************
    *	@brief	尺寸变化信号
    *	@return	无返回值
    *	@others 无
    *	@author 秦李旸
    *****************************************************************************
    */
    void SizeChanged();

    /**
    *****************************************************************************
    *	@brief	选中信号
    *	@return	无返回值
    *	@others 无
    *	@author 秦李旸
    *****************************************************************************
    */
    void PickItem();

    /**
    *****************************************************************************
    *	@brief	打开设置工艺窗口
    *	@return	无返回值
    *	@others 无
    *	@author 秦李旸
    *****************************************************************************
    */
    void CraftBtnClicked(WELD_PROCESS _stData);

    /**
    *****************************************************************************
    *	@brief	示教状态下保存
    *	@return	无返回值
    *	@others 无
    *	@author 秦李旸
    *****************************************************************************
    */
    void TeachingSave();

    /**
    *****************************************************************************
    *	@brief	另存为模板
    *	@return	无返回值
    *	@others 无
    *	@author 秦李旸
    *****************************************************************************
    */
    void SaveAsNewTemple(MWeldItem *_pWeldItem);

    void TempleSaved(int _nId);

    /**
    *****************************************************************************
    *	@brief	点列项选中信号
    *	@return	无返回值
    *	@others 无
    *	@author Wang YangYuKun
    *****************************************************************************
    */
    void PointListItemSelected(int index);

protected:
    /**
    ***********************************************************************
    * @brief 重写窗口绘图事件，用于自定义控件绘制
    * @param [IN] event > 绘图事件对象，包含需要绘制的区域信息
    *        - event->rect(): 获取需要重绘的矩形区域
    *        - event->region(): 获取需要重绘的区域（复杂形状时使用）
    * @return 无返回值
    * @others
    *        - 使用QPainter进行所有绘制操作
    *        - 默认实现会先调用基类的paintEvent
    *        - 必须确保所有绘制操作限制在event指定的区域内
    * @author 王阳煜坤
    ***********************************************************************
    */
    void paintEvent(QPaintEvent *event) override;

    /**
    ***********************************************************************
    * @brief 重写窗口大小调整事件
    * @param [IN] event > 大小改变事件对象，包含新旧尺寸信息
    *        - event->oldSize(): 调整前的窗口尺寸
    *        - event->size(): 调整后的新窗口尺寸
    * @return 无返回值
    * @others
    *        - 通常用于调整内部子控件布局
    *        - 必须调用基类实现以保证正确的事件传递
    * @author 王阳煜坤
    ***********************************************************************
    */
    void resizeEvent(QResizeEvent *event) override;

    /**
    ***********************************************************************
    * @brief 重写鼠标进入事件
    * @param [IN] event > 鼠标事件对象，包含进入信息
    * @return 无返回值
    * @others 无
    * @author 王阳煜坤
    ***********************************************************************
    */
    void enterEvent(QEvent *event) override;

    /**
    ***********************************************************************
    * @brief 重写鼠标离开事件
    * @param [IN] event > 鼠标事件对象，包含离开信息
    * @return 无返回值
    * @others 无
    * @author 王阳煜坤
    ***********************************************************************
    */
    void leaveEvent(QEvent *event) override;

    /**
    ***********************************************************************
    * @brief 重写鼠标按下事件
    * @param [IN] event > 鼠标事件对象，包含按下信息
    *        - event->button(): 获取按下的鼠标按钮(Qt::LeftButton等)
    *        - event->pos(): 获取鼠标位置(相对控件坐标)
    *        - event->globalPos(): 获取屏幕绝对坐标
    * @return 无返回值
    * @others
    *        - 可用于实现拖动开始、按钮点击等交互
    *        - 需要调用event->accept()标记事件已处理
    * @author 王阳煜坤
    ***********************************************************************
    */
    void mousePressEvent(QMouseEvent *event) override;

    /**
    ***********************************************************************
    * @brief 重写鼠标释放事件
    * @param [IN] event > 鼠标事件对象，包含释放信息
    *        - event->button(): 获取释放的鼠标按钮
    *        - event->pos(): 获取释放时的位置
    *        - event->globalPos(): 获取屏幕绝对坐标
    * @return 无返回值
    * @others
    *        - 通常用于结束拖动操作或触发点击动作
    *        - 需要检查与press事件的坐标差以避免误触
    * @author 王阳煜坤
    ***********************************************************************
    */
    void mouseReleaseEvent(QMouseEvent *event) override;

private:

    /**
    ***********************************************************************
    * @brief 更新视图
    * @param 无
    * @return 无返回值
    * @others 无
    * @author 秦李旸
    ***********************************************************************
    */
    void UpdateView();

    /**
    ***********************************************************************
    * @brief 设置展开区域
    * @param 无
    * @return 无返回值
    * @others 无
    * @author 秦李旸
    ***********************************************************************
    */
    void SetExpanded();

    /**
    ***********************************************************************
    * @brief 更新数值
    * @param 无
    * @return 无返回值
    * @others 无
    * @author 秦李旸
    ***********************************************************************
    */
    void UpdateValue();

    /**
    ***********************************************************************
    * @brief 更新外部数值
    * @param 无
    * @return 无返回值
    * @others 无
    * @author 秦李旸
    ***********************************************************************
    */
    void UpdateOutsideValue();

    /* 状态信号 */
    bool m_bExpanded;                ///< 是否为展开状态
    bool m_bPicked;                  ///< 是否为选中状态
    bool m_bMouseIn;                 ///< 鼠标是否在组件内
    bool m_bMouseDown;               ///< 鼠标是否按下
    bool m_bShowParas;               ///< 展开栏显示参数还是点列
    bool m_bTeachingFlag;            ///< 是否是示教模式

    /* 样式属性 */
    QColor m_BkInColor;          ///< 鼠标在内背景颜色
    QColor m_BkOutColor;         ///< 鼠标在外背景颜色
    QColor m_BkPickedColor;      ///< 选中背景颜色
    QColor m_BkExpandedColor;    ///< 展开背景颜色
    int m_nArcX;                 ///< 圆角x分量
    int m_nArcY;                 ///< 圆角y分量
    int m_nWidth;                ///< 宽度
    int m_nHeight;               ///< 高度
    int m_nExpandedHeight;       ///< 展开高度

    /* 未展开状态组件 */
    // 标签
    MLabel *m_plbTitle;          ///< 标题标签
//    MLabel *m_plbSize;           ///< 点数量标签
    MLabel *m_plbTemple;         ///< 参数模板标签
    MLabel *m_plbCurrent;        ///< 电流标签
    MLabel *m_plbVoltage;        ///< 电压标签
    MLabel *m_plbVelocity;          ///< 速度标签
    MLabel *m_plbCraft;          ///< 工艺标签

    // 按钮
    MMultiStyleButton *m_pbtPoints;     ///< 展开点
    MMultiStyleButton *m_pbtParas;      ///< 展开参数

    /* 展开参数状态组件 */
    QWidget *m_pParaContainer;     ///< 参数容器
    MScrollArea *m_pParaScrollArea;      ///< 轨迹列表滑动容器
    MScrollBar *m_pParaScrollBar;  ///< 滚动条

    // 标签
    MLabel *m_plbTempleEX;         ///< 展开栏模板标签
    MLabel *m_plbCurrentEX;        ///< 展开栏电流标签
    MLabel *m_plbVoltageEX;        ///< 展开栏电压标签
    MLabel *m_p_label_ArcOnWaitTime;  ///< 起弧停留时间标签
    MLabel *m_p_label_ArcOffWaitTime; ///< 收弧停留时间标签
    MLabel *m_plbVelocityEX;          ///< 展开栏速度标签
    MLabel *m_plbCraftEX;          ///< 展开栏工艺标签
    MLabel *m_plbWeldType;       ///< 展开栏焊接类型标签
    MLabel *m_plbWorkType;       ///< 展开栏工件类型标签
    MLabel *m_plbWeldFilling;       ///< 是否需要补全焊缝
    MLabel *m_p_label_ReferTeach{}; ///< 参考示教数据描述标签
    MLabel *m_plbWeldOffsetY;    ///< 焊缝X偏移
    MLabel *m_plbWeldOffsetZ;    ///< 焊缝Y偏移
    MLabel *m_plbWeldLiftDist;         ///< 抬起高度

    MLabel *m_plbCurrentUnit;    ///< 展开栏电流单位标签
    MLabel *m_plbVoltageUnit;    ///< 展开栏电压单位标签
    MLabel *m_p_label_ArcOnWaitTimeUnit;  ///< 起弧停留单位标签
    MLabel *m_p_label_ArcOffWaitTimeUnit; ///< 收弧停留单位标签
    MLabel *m_plbVelocityUnit;      ///< 展开栏速度单位标签
    MLabel *m_plbOffsetYUnit;      ///< 焊缝X偏移单位标签
    MLabel *m_plbOffsetZUnit;      ///< 焊缝Y偏移单位标签
    MLabel *m_plbLiftDistUnit;         ///< 抬起高度单位标签
//    MLabel *m_plbWeldProcess;      ///< 焊接工艺

    //    bool bIsWeldFilling;
//    double dWeldOffset_X;
//    double dWeldOffset_Y;
//    WELD_PROCESS stWeldProcess;

    // 输入框
    MInputBox *m_pibCurrent;
    MInputBox *m_pibVoltage;
    MInputBox *m_p_input_ArcOnWaitTime;    ///< 起弧停留时间输入框
    MInputBox *m_p_input_ArcOffWaitTime;   ///< 收弧停留时间输入框
    MInputBox *m_pibVelocity;
    MInputBox *m_pibOffsetY;
    MInputBox *m_pibOffsetZ;
    MInputBox *m_pibLiftDist;

    // 下拉框
    MComboBox *m_pcbTemple;
//    MComboBox *m_pcbCraft;
    MComboBox *m_pcbWeldType;
    MComboBox *m_pcbWorkType;

    // 按钮
    MMultiStyleButton *m_pbtCancel;      ///< 取消按钮
    MMultiStyleButton *m_pbtSaveAs;      ///< 另存为按钮
    MMultiStyleButton *m_pbtApply;       ///< 应用按钮
    MMultiStyleButton *m_pbtCraft;       ///< 工艺界面按钮
    MIconCheckBox *m_pbtFilling;         ///< 补全焊缝按钮
    MIconCheckBox *m_checkBox_ReferTeach;///< 参考示教数据开关

    // 工艺界面

    /* 展开点列表状态组件 */
    MPointList *m_pplPointList;
    MLabel *m_plbSize;           ///< 点数量标签
    MLabel *m_plbNum;          ///< 点号标签
    MLabel *m_plbType;           ///< 点类型标签
    MLabel *m_plbAct;          ///< 操作标签

    /* 数据定义 */
    WELD_PARAMETER m_stData = {};              ///< 焊接参数
    WELD_PARAMETER m_stDataBackUp = {};        ///< 焊接参数备份
    int m_nIndex = 0;                          ///< 工程文件中的焊缝下标
    std::string m_strProjectName = "";         ///< 工程文件名
    std::vector<PointData<Point3D> *> m_vptPointData = {};
    std::vector<WELD_DATA> m_vecWeldDataList;     ///< 焊接参数模板列表
};


#endif //MP2000_MWELDITEM_H
