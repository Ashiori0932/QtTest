//
// Created by mojia on 25-10-31.
//

#include <QToolTip>
#include "MWeldItem.h"

#include "src/utils/MSingletonIPCLog.h"


MWeldItem::MWeldItem(QWidget *parent)
        : QWidget(parent)

        //组件初始化
        //未展开状态组件
        , m_plbTitle(new MLabel(this))                 // 标题标签
        , m_plbTemple(new MLabel(this))                // 参数模板标签
        , m_plbCurrent(new MLabel(this))               // 电流标签
        , m_plbVoltage(new MLabel(this))               // 电压标签
        , m_plbVelocity(new MLabel(this))                 // 速度标签
        , m_plbCraft(new MLabel(this))                 // 工艺标签
        , m_pbtPoints(new MMultiStyleButton(this))     // 展开点按钮
        , m_pbtParas(new MMultiStyleButton(this))      // 展开参数按钮

        // 展开参数状态组件
        , m_pParaScrollArea(new MScrollArea(this))              // 滑动区域
        , m_pParaScrollBar(new MScrollBar(m_pParaScrollArea))   // 滑动条
        , m_pParaContainer(new QWidget())          // 参数容器
        , m_plbTempleEX(new MLabel(m_pParaContainer)),
          m_plbCurrentEX(new MLabel(m_pParaContainer))             // 展开栏电流标签
        , m_plbVoltageEX(new MLabel(m_pParaContainer))             // 展开栏电压标签
        , m_p_label_ArcOnWaitTime(new MLabel(m_pParaContainer))    // 起弧停留时间标签
        , m_p_label_ArcOffWaitTime(new MLabel(m_pParaContainer))   // 收弧停留时间标签
        , m_plbVelocityEX(new MLabel(m_pParaContainer))               // 展开栏速度标签
        , m_plbCraftEX(new MLabel(m_pParaContainer))               // 展开栏工艺标签
        , m_plbWeldType(new MLabel(m_pParaContainer))            // 展开栏焊接类型标签
        , m_plbWorkType(new MLabel(m_pParaContainer))            // 展开栏工件类型标签
//        , m_plbWeldFilling(new MLabel(m_pParaContainer))       // 是否需要补全焊缝
        , m_p_label_ReferTeach(new MLabel(m_pParaContainer))   // 参考示教数据描述标签
        , m_plbWeldOffsetY(new MLabel(m_pParaContainer))       // 焊缝Y偏移
        , m_plbWeldOffsetZ(new MLabel(m_pParaContainer))       // 焊缝Z偏移
//        , m_plbWeldLiftDist(new MLabel(m_pParaContainer))       // 抬起高度

        , m_plbCurrentUnit(new MLabel(m_pParaContainer))         // 展开栏电流单位标签
        , m_plbVoltageUnit(new MLabel(m_pParaContainer))         // 展开栏电压单位标签
        , m_p_label_ArcOnWaitTimeUnit(new MLabel(m_pParaContainer))   // 起弧停留时间单位标签
        , m_p_label_ArcOffWaitTimeUnit(new MLabel(m_pParaContainer))  // 收弧停留时间单位标签
        , m_plbVelocityUnit(new MLabel(m_pParaContainer))           // 展开栏速度单位标签
        , m_plbOffsetYUnit(new MLabel(m_pParaContainer))         // 焊缝Y偏移单位标签
        , m_plbOffsetZUnit(new MLabel(m_pParaContainer))           // 焊缝Z偏移单位标签
//        , m_plbLiftDistUnit(new MLabel(m_pParaContainer))           // 抬起高度单位标签

        , m_pibCurrent(new MInputBox(m_pParaContainer))            // 展开栏电流输入框
        , m_pibVoltage(new MInputBox(m_pParaContainer))            // 展开栏电压输入框
        , m_p_input_ArcOnWaitTime(new MInputBox(m_pParaContainer))    // 起弧停留时间输入框
        , m_p_input_ArcOffWaitTime(new MInputBox(m_pParaContainer))   // 收弧停留时间输入框
        , m_pibVelocity(new MInputBox(m_pParaContainer))              // 展开栏速度输入框
        , m_pibOffsetY(new MInputBox(m_pParaContainer))            // 展开栏Y偏移输入框
        , m_pibOffsetZ(new MInputBox(m_pParaContainer))              // 展开栏Z偏移输入框
//        , m_pibLiftDist(new MInputBox(m_pParaContainer))              // 抬起高度输入框


        , m_pcbTemple(new MComboBox(m_pParaContainer))
//        , m_pcbCraft(new MComboBox(m_pParaContainer))                 // 展开栏工艺下拉框
        , m_pcbWeldType(new MComboBox(m_pParaContainer))              // 展开栏焊接类型下拉框
        , m_pcbWorkType(new MComboBox(m_pParaContainer))              // 展开栏工件类型下拉框

        , m_pbtCancel(new MMultiStyleButton(this))     // 取消按钮
        , m_pbtSaveAs(new MMultiStyleButton(this))     // 另存为按钮
        , m_pbtApply(new MMultiStyleButton(this))      // 应用按钮
        , m_pbtCraft(new MMultiStyleButton(m_pParaContainer))     // 工艺界面按钮
//        , m_pbtFilling(new MIconCheckBox(m_pParaContainer))      // 补全焊缝按钮
        , m_checkBox_ReferTeach(new MIconCheckBox(m_pParaContainer))      // 参考示教数据开关

//        , m_pCraftSettings(new MCraftSettings(m_pDialog))  // 工艺界面

        // 展开轨迹状态组件
        , m_pplPointList(new MPointList(this, 126, 20))  // 点列
        , m_plbSize(new MLabel(this))                  // 点数量标签
        , m_plbNum(new MLabel(this))                   // 点号标签
        , m_plbType(new MLabel(this))                  // 点类型标签
        , m_plbAct(new MLabel(this))                   // 操作标签

        // 状态变量初始化
        , m_bExpanded(false)                           // 是否为展开状态
        , m_bPicked(false)                             // 是否为选中状态
        , m_bMouseIn(false)                            // 鼠标是否在组件内
        , m_bMouseDown(false)                          // 鼠标是否按下
        , m_bShowParas(true)                           // 展开部分是否显示参数
        , m_bTeachingFlag(false)

        // 样式属性初始化
        , m_BkInColor(QColor(0x3D475C))                       // 鼠标在内背景颜色
        , m_BkOutColor(QColor(0x292F3D))               // 鼠标在外背景颜色
        , m_BkPickedColor(QColor(0x15C79B))                    // 选中背景颜色
        , m_BkExpandedColor(QColor(0x3D475C))                  // 展开部分背景颜色
        , m_nArcX(10)                                  // 圆角x分量
        , m_nArcY(10)                                  // 圆角y分量
        , m_nWidth(428)                                // 宽度
        , m_nHeight(95)                               // 高度
        , m_nExpandedHeight(367)                       // 展开高度
{
    // 未展开状态组件

    // 标签

    m_plbTitle->setGeometry(QRect(22, 8, 184, 30));
    m_plbTitle->SetBkColor(Qt::transparent);
    m_plbTitle->SetTextStyle(Qt::white, 14, Qt::AlignBottom | Qt::AlignLeft, true);
    m_plbTitle->SetShowText("焊缝轨迹1");

//    m_plbSize->setGeometry(QRect(126, 8, 184, 30));
//    m_plbSize->SetBkColor(Qt::transparent);
//    m_plbSize->SetTextStyle(QColor(255,255,255,153), 12, Qt::AlignBottom | Qt::AlignLeft, false);
//    m_plbSize->SetShowText("点位数量：15");

    m_plbTemple->setGeometry(QRect(126, 8, 184, 28));
    m_plbTemple->SetBkColor(Qt::transparent);
    m_plbTemple->SetTextStyle(QColor(255, 255, 255, 153), 10, Qt::AlignBottom | Qt::AlignLeft, false);
    m_plbTemple->SetShowText("参数模板：");

    m_plbCurrent->setGeometry(QRect(22, 42, 100, 21));
    m_plbCurrent->SetBkColor(Qt::transparent);
    m_plbCurrent->SetTextStyle(QColor(255, 255, 255, 153), 10, Qt::AlignBottom | Qt::AlignLeft, false);
    m_plbCurrent->SetShowText("电流：");

    m_plbVoltage->setGeometry(QRect(22, 66, 100, 21));
    m_plbVoltage->SetBkColor(Qt::transparent);
    m_plbVoltage->SetTextStyle(QColor(255, 255, 255, 153), 10, Qt::AlignBottom | Qt::AlignLeft, false);
    m_plbVoltage->SetShowText("电压：");

    m_plbVelocity->setGeometry(QRect(126, 42, 144, 21));
    m_plbVelocity->SetBkColor(Qt::transparent);
    m_plbVelocity->SetTextStyle(QColor(255, 255, 255, 153), 10, Qt::AlignBottom | Qt::AlignLeft, false);
    m_plbVelocity->SetShowText("速度：");

    m_plbCraft->setGeometry(QRect(126, 66, 144, 21));
    m_plbCraft->SetBkColor(Qt::transparent);
    m_plbCraft->SetTextStyle(QColor(255, 255, 255, 153), 10, Qt::AlignBottom | Qt::AlignLeft, false);
    m_plbCraft->SetShowText("工艺：");

    // 按钮
    m_pbtParas->SwitchIconEnableState(true);
    m_pbtParas->SetIconPixmap(QPixmap(MJROBOT_MAIN_RESOUCE_ITEM_WELD_PARAS),
                              QPixmap(MJROBOT_MAIN_RESOUCE_ITEM_WELD_PARAS),
                              QPixmap(MJROBOT_MAIN_RESOUCE_ITEM_WELD_PARAS));
    m_pbtParas->SetBkColor(Qt::transparent, Qt::transparent, Qt::transparent);
    m_pbtParas->setGeometry(QRect(320, 39, 96, 21));

    connect(m_pbtParas, &MMultiStyleButton::clicked, this, [this]()
    {
        if (!m_bPicked)
        {
            emit PickItem();
        }
        if (!m_bExpanded)
        {
            m_bExpanded = true;
            m_bShowParas = true;
        } else if (m_bShowParas)
        {
            m_bExpanded = false;
        } else
        {
            m_bShowParas = true;
        }
        m_bPicked = true;
        UpdateView();
        m_stData = m_stDataBackUp;
        UpdateValue();
    });

    m_pbtPoints->SwitchIconEnableState(true);
    m_pbtPoints->SetIconPixmap(QPixmap(MJROBOT_MAIN_RESOUCE_ITEM_WELD_POINTS),
                               QPixmap(MJROBOT_MAIN_RESOUCE_ITEM_WELD_POINTS),
                               QPixmap(MJROBOT_MAIN_RESOUCE_ITEM_WELD_POINTS));
    m_pbtPoints->SetBkColor(Qt::transparent, Qt::transparent, Qt::transparent);
    m_pbtPoints->setGeometry(QRect(320, 65, 96, 21));

    connect(m_pbtPoints, &MMultiStyleButton::clicked, this, [this]()
    {
        if (!m_bPicked)
        {
            emit PickItem();
        }
        if (!m_bExpanded)
        {
            m_bExpanded = true;
            m_bShowParas = false;
        } else if (m_bShowParas)
        {
            m_bShowParas = false;
        } else
        {
            m_bExpanded = false;
        }
        m_bPicked = true;
        // 显示点列展示组件
        UpdateView();
        m_stData = m_stDataBackUp;
        UpdateValue();
    });

    m_pParaScrollArea->setGeometry(QRect(22, 107, 406, 204));
    m_pParaScrollArea->setScrollSpeed(60);
    m_pParaScrollArea->SetContent(m_pParaContainer);

    m_pParaContainer->setFixedSize(406, 371);
    m_pParaContainer->setStyleSheet("background: transparent");

    m_pParaScrollBar->raise();

    // 滚动区域主动更新滚动条
    connect(m_pParaScrollArea, &MScrollArea::Scrolled, [this]()
    {
        QSize size{8, m_pParaScrollArea->height()};
        if (size != m_pParaScrollBar->size())
        {
            m_pParaScrollBar->setGeometry(m_pParaScrollArea->width() - 8, 0, size.width(), size.height());
        }

        if (m_pParaScrollArea->GetMaxYOffset() > 0)
        {
            m_pParaScrollBar->show();
        } else
        {
            m_pParaScrollBar->hide();
        }
        m_pParaScrollBar->SetPageStep(m_pParaScrollArea->height());
        m_pParaScrollBar->SetMaximum(m_pParaScrollArea->GetMaxYOffset());
        m_pParaScrollBar->SetValue(m_pParaScrollArea->yOffset());
    });
    // 滚动条主动更新滚动条滚动区域
    connect(m_pParaScrollBar, &MScrollBar::valueChanged, [this](int _nValue)
    {
        m_pParaScrollArea->setYOffset(_nValue);
    });

    // 标签
    m_plbTempleEX->setGeometry(QRect(0, 3, 100, 23));
    m_plbTempleEX->SetBkColor(Qt::transparent);
    m_plbTempleEX->SetTextStyle(Qt::white, 12, Qt::AlignBottom | Qt::AlignLeft, false);
    m_plbTempleEX->SetShowText("参数模板：");

    m_plbCurrentEX->setGeometry(QRect(0, 35, 100, 21));
    m_plbCurrentEX->SetBkColor(Qt::transparent);
    m_plbCurrentEX->SetTextStyle(Qt::white, 10, Qt::AlignBottom | Qt::AlignLeft, false);
    m_plbCurrentEX->SetShowText("电流：");

    m_plbVoltageEX->setGeometry(QRect(0, 92, 100, 21));
    m_plbVoltageEX->SetBkColor(Qt::transparent);
    m_plbVoltageEX->SetTextStyle(Qt::white, 10, Qt::AlignBottom | Qt::AlignLeft, false);
    m_plbVoltageEX->SetShowText("电压：");

    m_plbVelocityEX->setGeometry(QRect(0, 149, 144, 21));
    m_plbVelocityEX->SetBkColor(Qt::transparent);
    m_plbVelocityEX->SetTextStyle(Qt::white, 10, Qt::AlignBottom | Qt::AlignLeft, false);
    m_plbVelocityEX->SetShowText("速度：");

    m_plbCraftEX->setGeometry(QRect(144, 35, 144, 21));
    m_plbCraftEX->SetBkColor(Qt::transparent);
    m_plbCraftEX->SetTextStyle(Qt::white, 10, Qt::AlignBottom | Qt::AlignLeft, false);
    m_plbCraftEX->SetShowText("焊接工艺：");

    m_plbWorkType->setGeometry(QRect(144, 92, 144, 21));
    m_plbWorkType->SetBkColor(Qt::transparent);
    m_plbWorkType->SetTextStyle(Qt::white, 10, Qt::AlignBottom | Qt::AlignLeft, false);
    m_plbWorkType->SetShowText("焊接类型：");

    m_plbWeldType->setGeometry(QRect(144, 149, 144, 21));
    m_plbWeldType->SetBkColor(Qt::transparent);
    m_plbWeldType->SetTextStyle(Qt::white, 10, Qt::AlignBottom | Qt::AlignLeft, false);
    m_plbWeldType->SetShowText("工件类型：");

    m_plbWeldOffsetY->setGeometry(QRect(0, 206, 144, 21));
    m_plbWeldOffsetY->SetBkColor(Qt::transparent);
    m_plbWeldOffsetY->SetTextStyle(Qt::white, 10, Qt::AlignBottom | Qt::AlignLeft, false);
    m_plbWeldOffsetY->SetShowText("焊缝Y偏移：");

//    m_plbWeldOffsetZ->setGeometry(QRect(0, 263, 144, 21));
    m_plbWeldOffsetZ->setGeometry(QRect(144, 206, 144, 21));
    m_plbWeldOffsetZ->SetBkColor(Qt::transparent);
    m_plbWeldOffsetZ->SetTextStyle(Qt::white, 10, Qt::AlignBottom | Qt::AlignLeft, false);
    m_plbWeldOffsetZ->SetShowText("焊缝Z偏移：");

    m_p_label_ArcOnWaitTime->setGeometry(QRect(0, 263, 144, 21));
    m_p_label_ArcOnWaitTime->SetBkColor(Qt::transparent);
    m_p_label_ArcOnWaitTime->SetTextStyle(Qt::white, 10, Qt::AlignBottom | Qt::AlignLeft, false);
    m_p_label_ArcOnWaitTime->SetShowText("起弧停留时间：");

//    m_plbWeldOffsetZ->setGeometry(QRect(0, 263, 144, 21));
    m_p_label_ArcOffWaitTime->setGeometry(QRect(144, 263, 144, 21));
    m_p_label_ArcOffWaitTime->SetBkColor(Qt::transparent);
    m_p_label_ArcOffWaitTime->SetTextStyle(Qt::white, 10, Qt::AlignBottom | Qt::AlignLeft, false);
    m_p_label_ArcOffWaitTime->SetShowText("收弧停留时间：");

//    m_plbWeldLiftDist->setGeometry(QRect(144, 206, 144, 21));
//    m_plbWeldLiftDist->SetBkColor(Qt::transparent);
//    m_plbWeldLiftDist->SetTextStyle(Qt::white, 10, Qt::AlignBottom | Qt::AlignLeft, false);
//    m_plbWeldLiftDist->SetShowText("抬起距离");

//    m_plbWeldFilling->setGeometry(QRect(144, 263, 144, 21));
//    m_plbWeldFilling->SetBkColor(Qt::transparent);
//    m_plbWeldFilling->SetTextStyle(Qt::white, 10, Qt::AlignBottom | Qt::AlignLeft, false);
//    m_plbWeldFilling->SetShowText("补全焊缝：");

    m_p_label_ReferTeach->setGeometry(0, 320, 144, 21);
//    m_p_label_ReferTeach->setGeometry(244, 263, 144, 21);
    m_p_label_ReferTeach->SetBkColor(Qt::transparent);
    m_p_label_ReferTeach->SetTextStyle(Qt::white, 10, Qt::AlignBottom | Qt::AlignLeft, false);
    m_p_label_ReferTeach->SetShowText("参考示教数据：");

//    m_plbWeldProcess->setGeometry(QRect(144, 263, 144, 21));
//    m_plbWeldProcess->SetBkColor(Qt::transparent);
//    m_plbWeldProcess->SetTextStyle(Qt::white, 10, Qt::AlignBottom | Qt::AlignLeft, false);
//    m_plbWeldProcess->SetShowText("焊接工艺：");

    m_plbCurrentUnit->setGeometry(QRect(85, 61, 100, 21));
    m_plbCurrentUnit->SetBkColor(Qt::transparent);
    m_plbCurrentUnit->SetTextStyle(Qt::white, 12, Qt::AlignBottom | Qt::AlignLeft, false);
    m_plbCurrentUnit->SetShowText("A");

    m_plbVoltageUnit->setGeometry(QRect(85, 118, 100, 21));
    m_plbVoltageUnit->SetBkColor(Qt::transparent);
    m_plbVoltageUnit->SetTextStyle(Qt::white, 12, Qt::AlignBottom | Qt::AlignLeft, false);
    m_plbVoltageUnit->SetShowText("V");

    m_plbVelocityUnit->setGeometry(QRect(85, 175, 144, 21));
    m_plbVelocityUnit->SetBkColor(Qt::transparent);
    m_plbVelocityUnit->SetTextStyle(Qt::white, 12, Qt::AlignBottom | Qt::AlignLeft, false);
    m_plbVelocityUnit->SetShowText("mm/s");

    m_plbOffsetYUnit->setGeometry(QRect(85, 232, 100, 21));
    m_plbOffsetYUnit->SetBkColor(Qt::transparent);
    m_plbOffsetYUnit->SetTextStyle(Qt::white, 12, Qt::AlignBottom | Qt::AlignLeft, false);
    m_plbOffsetYUnit->SetShowText("mm");

//    m_plbOffsetZUnit->setGeometry(QRect(85, 289, 100, 21));
    m_plbOffsetZUnit->setGeometry(QRect(229, 232, 100, 21));
    m_plbOffsetZUnit->SetBkColor(Qt::transparent);
    m_plbOffsetZUnit->SetTextStyle(Qt::white, 12, Qt::AlignBottom | Qt::AlignLeft, false);
    m_plbOffsetZUnit->SetShowText("mm");

    m_p_label_ArcOnWaitTimeUnit->setGeometry(QRect(85, 289, 100, 21));
    m_p_label_ArcOnWaitTimeUnit->SetBkColor(Qt::transparent);
    m_p_label_ArcOnWaitTimeUnit->SetTextStyle(Qt::white, 12, Qt::AlignBottom | Qt::AlignLeft, false);
    m_p_label_ArcOnWaitTimeUnit->SetShowText("ms");

//    m_plbOffsetZUnit->setGeometry(QRect(85, 289, 100, 21));
    m_p_label_ArcOffWaitTimeUnit->setGeometry(QRect(229, 289, 100, 21));
    m_p_label_ArcOffWaitTimeUnit->SetBkColor(Qt::transparent);
    m_p_label_ArcOffWaitTimeUnit->SetTextStyle(Qt::white, 12, Qt::AlignBottom | Qt::AlignLeft, false);
    m_p_label_ArcOffWaitTimeUnit->SetShowText("ms");

//    m_plbLiftDistUnit->setGeometry(QRect(229, 232, 100, 21));
//    m_plbLiftDistUnit->SetBkColor(Qt::transparent);
//    m_plbLiftDistUnit->SetTextStyle(Qt::white, 12, Qt::AlignBottom | Qt::AlignLeft, false);
//    m_plbLiftDistUnit->SetShowText("mm");

    // 输入框
    m_pibCurrent->SetTitleMode();
    m_pibCurrent->setGeometry(QRect(0, 54, 80, 32));
    m_pibCurrent->SetClearButtonIcon(QPixmap(MJROBOT_MAIN_RESOUCE_PARADATA_INPUT_BOX_CLEAR_1_PNG),
                                     QPixmap(MJROBOT_MAIN_RESOUCE_PARADATA_INPUT_BOX_CLEAR_2_PNG),
                                     QPixmap(MJROBOT_MAIN_RESOUCE_PARADATA_INPUT_BOX_CLEAR_3_PNG));
    m_pibCurrent->SetClearButtonBkColor(QColor(0, 0, 0, 0), QColor(0, 0, 0, 0), QColor(0, 0, 0, 0));
//    QDoubleValidator *pCurrentValidator = new QDoubleValidator(0, 400, 1);  // 最小值, 最大值, 小数位数
//    pCurrentValidator->setNotation(QDoubleValidator::StandardNotation);  // 标准表示法
//    pCurrentValidator->setLocale(QLocale::C);  // 使用C语言区域设置，避免千分位分隔符
//    m_pibCurrent->SetValidator(pCurrentValidator);
    m_pibCurrent->SetBkColor(Qt::transparent, Qt::transparent, Qt::transparent);
    m_pibCurrent->SetBdColor(Qt::white, Qt::white, Qt::white);
    m_pibCurrent->SetArcSize(4, 4);
    m_pibCurrent->SetBdSize(1);
    m_pibCurrent->SetContentsMargins(2, 0, 2, 0);
    m_pibCurrent->SetPixelFontSize(20);

    connect(m_pibCurrent, &MInputBox::editingFinished, this, [this]()
    {
        double dValue = std::floor(m_pibCurrent->Text().toDouble() * 10) / 10;
        // qDebug() << dValue;
        if(dValue > 500)
        {
            dValue = 500;
        }
        if(dValue < 0)
        {
            dValue = 0;
        }
        m_stData.dWeldCurrent = dValue;
        m_pibCurrent->ClearFocus();
        UpdateValue();
    });

    m_pibVoltage->SetTitleMode();
    m_pibVoltage->setGeometry(QRect(0, 111, 80, 32));
    m_pibVoltage->SetClearButtonIcon(QPixmap(MJROBOT_MAIN_RESOUCE_PARADATA_INPUT_BOX_CLEAR_1_PNG),
                                     QPixmap(MJROBOT_MAIN_RESOUCE_PARADATA_INPUT_BOX_CLEAR_2_PNG),
                                     QPixmap(MJROBOT_MAIN_RESOUCE_PARADATA_INPUT_BOX_CLEAR_3_PNG));
    m_pibVoltage->SetClearButtonBkColor(QColor(0, 0, 0, 0), QColor(0, 0, 0, 0), QColor(0, 0, 0, 0));
//    QDoubleValidator *pVoltageValidator = new QDoubleValidator(0, 50, 1);  // 最小值, 最大值, 小数位数
//    m_pibVoltage->SetValidator(pVoltageValidator);
    m_pibVoltage->SetBkColor(Qt::transparent, Qt::transparent, Qt::transparent);
    m_pibVoltage->SetBdColor(Qt::white, Qt::white, Qt::white);
    m_pibVoltage->SetArcSize(4, 4);
    m_pibVoltage->SetBdSize(1);
    m_pibVoltage->SetContentsMargins(2, 0, 2, 0);
    m_pibVoltage->SetPixelFontSize(20);

    connect(m_pibVoltage, &MInputBox::editingFinished, this, [this]()
    {
        double dValue = std::floor(m_pibVoltage->Text().toDouble() * 10) / 10;
        // qDebug() << dValue;
        if(dValue > 500)
        {
            dValue = 500;
        }
        if(dValue < 0)
        {
            dValue = 0;
        }
        m_stData.dWeldVoltage = dValue;
        m_pibVoltage->ClearFocus();
        UpdateValue();
    });

    m_pibVelocity->SetTitleMode();
    m_pibVelocity->setGeometry(QRect(0, 168, 80, 32));
    m_pibVelocity->SetClearButtonIcon(QPixmap(MJROBOT_MAIN_RESOUCE_PARADATA_INPUT_BOX_CLEAR_1_PNG),
                                      QPixmap(MJROBOT_MAIN_RESOUCE_PARADATA_INPUT_BOX_CLEAR_2_PNG),
                                      QPixmap(MJROBOT_MAIN_RESOUCE_PARADATA_INPUT_BOX_CLEAR_3_PNG));
    m_pibVelocity->SetClearButtonBkColor(QColor(0, 0, 0, 0), QColor(0, 0, 0, 0), QColor(0, 0, 0, 0));
//    QDoubleValidator *pVelocityValidator = new QDoubleValidator(0, 50, 1);  // 最小值, 最大值, 小数位数
//    m_pibVelocity->SetValidator(pVelocityValidator);
    m_pibVelocity->SetBkColor(Qt::transparent, Qt::transparent, Qt::transparent);
    m_pibVelocity->SetBdColor(Qt::white, Qt::white, Qt::white);
    m_pibVelocity->SetArcSize(4, 4);
    m_pibVelocity->SetBdSize(1);
    m_pibVelocity->SetContentsMargins(2, 0, 2, 0);
    m_pibVelocity->SetPixelFontSize(20);

    connect(m_pibVelocity, &MInputBox::editingFinished, this, [this]()
    {
        double dValue = std::floor(m_pibVelocity->Text().toDouble() * 10) / 10;
        // qDebug() << dValue;
        if(dValue > 100)
        {
            dValue = 100;
        }
        if(dValue < 0)
        {
            dValue = 0;
        }
        m_stData.dWeldVelocity = dValue;
        m_pibVelocity->ClearFocus();
        UpdateValue();
    });

    m_pibOffsetY->SetTitleMode();
    m_pibOffsetY->setGeometry(QRect(0, 225, 80, 32));
    m_pibOffsetY->SetClearButtonIcon(QPixmap(MJROBOT_MAIN_RESOUCE_PARADATA_INPUT_BOX_CLEAR_1_PNG),
                                     QPixmap(MJROBOT_MAIN_RESOUCE_PARADATA_INPUT_BOX_CLEAR_2_PNG),
                                     QPixmap(MJROBOT_MAIN_RESOUCE_PARADATA_INPUT_BOX_CLEAR_3_PNG));
    m_pibOffsetY->SetClearButtonBkColor(QColor(0, 0, 0, 0), QColor(0, 0, 0, 0), QColor(0, 0, 0, 0));
//    QDoubleValidator *pOffsetYValidator = new QDoubleValidator(0, 50, 1);  // 最小值, 最大值, 小数位数
//    m_pibOffsetY->SetValidator(pOffsetYValidator);
    m_pibOffsetY->SetBkColor(Qt::transparent, Qt::transparent, Qt::transparent);
    m_pibOffsetY->SetBdColor(Qt::white, Qt::white, Qt::white);
    m_pibOffsetY->SetArcSize(4, 4);
    m_pibOffsetY->SetBdSize(1);
    m_pibOffsetY->SetContentsMargins(2, 0, 2, 0);
    m_pibOffsetY->SetPixelFontSize(20);

    connect(m_pibOffsetY, &MInputBox::editingFinished, this, [this]()
    {
        double dValue = std::floor(m_pibOffsetY->Text().toDouble() * 10) / 10;
        // qDebug() << dValue;
        if(dValue > 100)
        {
            dValue = 100;
        }
        if(dValue < -100)
        {
            dValue = -100;
        }
        m_stData.dWeldOffset_Y = dValue;
        m_pibOffsetY->ClearFocus();
        UpdateValue();
    });

    m_pibOffsetZ->SetTitleMode();
//    m_pibOffsetZ->setGeometry(QRect(0, 282, 80, 32));
    m_pibOffsetZ->setGeometry(QRect(144, 225, 80, 32));
    m_pibOffsetZ->SetClearButtonIcon(QPixmap(MJROBOT_MAIN_RESOUCE_PARADATA_INPUT_BOX_CLEAR_1_PNG),
                                     QPixmap(MJROBOT_MAIN_RESOUCE_PARADATA_INPUT_BOX_CLEAR_2_PNG),
                                     QPixmap(MJROBOT_MAIN_RESOUCE_PARADATA_INPUT_BOX_CLEAR_3_PNG));
    m_pibOffsetZ->SetClearButtonBkColor(QColor(0, 0, 0, 0), QColor(0, 0, 0, 0), QColor(0, 0, 0, 0));
//    QDoubleValidator *pOffsetZValidator = new QDoubleValidator(0, 50, 1);  // 最小值, 最大值, 小数位数
//    m_pibOffsetZ->SetValidator(pOffsetZValidator);
    m_pibOffsetZ->SetBkColor(Qt::transparent, Qt::transparent, Qt::transparent);
    m_pibOffsetZ->SetBdColor(Qt::white, Qt::white, Qt::white);
    m_pibOffsetZ->SetArcSize(4, 4);
    m_pibOffsetZ->SetBdSize(1);
    m_pibOffsetZ->SetContentsMargins(2, 0, 2, 0);
    m_pibOffsetZ->SetPixelFontSize(20);
    connect(m_pibOffsetZ, &MInputBox::editingFinished, this, [this]()
    {
        double dValue = std::floor(m_pibOffsetZ->Text().toDouble() * 10) / 10;
        // qDebug() << dValue;
        if(dValue > 100)
        {
            dValue = 100;
        }
        if(dValue < -100)
        {
            dValue = -100;
        }
        m_stData.dWeldOffset_Z = dValue;
        m_pibOffsetZ->ClearFocus();
        UpdateValue();
    });

    // 起弧停留时间输入框
    m_p_input_ArcOnWaitTime->SetTitleMode();
    m_p_input_ArcOnWaitTime->setGeometry(QRect(0, 282, 80, 32));
    m_p_input_ArcOnWaitTime->SetClearButtonIcon(QPixmap(MJROBOT_MAIN_RESOUCE_PARADATA_INPUT_BOX_CLEAR_1_PNG),
                                     QPixmap(MJROBOT_MAIN_RESOUCE_PARADATA_INPUT_BOX_CLEAR_2_PNG),
                                     QPixmap(MJROBOT_MAIN_RESOUCE_PARADATA_INPUT_BOX_CLEAR_3_PNG));
    m_p_input_ArcOnWaitTime->SetClearButtonBkColor(QColor(0, 0, 0, 0), QColor(0, 0, 0, 0), QColor(0, 0, 0, 0));
    m_p_input_ArcOnWaitTime->SetBkColor(Qt::transparent, Qt::transparent, Qt::transparent);
    m_p_input_ArcOnWaitTime->SetBdColor(Qt::white, Qt::white, Qt::white);
    m_p_input_ArcOnWaitTime->SetArcSize(4, 4);
    m_p_input_ArcOnWaitTime->SetBdSize(1);
    m_p_input_ArcOnWaitTime->SetContentsMargins(2, 0, 2, 0);
    m_p_input_ArcOnWaitTime->SetPixelFontSize(20);

    connect(m_p_input_ArcOnWaitTime, &MInputBox::editingFinished, this, [this]()
    {
        double dValue = m_p_input_ArcOnWaitTime->Text().toInt();
        // qDebug() << dValue;
        if(dValue > 10000)
        {
            dValue = 10000;
        }
        if(dValue < 0)
        {
            dValue = 0;
        }
        m_stData.nArcOnWaitTime = dValue;
        m_p_input_ArcOnWaitTime->ClearFocus();
        UpdateValue();
    });

    // 起弧停留时间输入框
    m_p_input_ArcOffWaitTime->SetTitleMode();
    m_p_input_ArcOffWaitTime->setGeometry(QRect(144, 282, 80, 32));
    m_p_input_ArcOffWaitTime->SetClearButtonIcon(QPixmap(MJROBOT_MAIN_RESOUCE_PARADATA_INPUT_BOX_CLEAR_1_PNG),
                                     QPixmap(MJROBOT_MAIN_RESOUCE_PARADATA_INPUT_BOX_CLEAR_2_PNG),
                                     QPixmap(MJROBOT_MAIN_RESOUCE_PARADATA_INPUT_BOX_CLEAR_3_PNG));
    m_p_input_ArcOffWaitTime->SetClearButtonBkColor(QColor(0, 0, 0, 0), QColor(0, 0, 0, 0), QColor(0, 0, 0, 0));
    m_p_input_ArcOffWaitTime->SetBkColor(Qt::transparent, Qt::transparent, Qt::transparent);
    m_p_input_ArcOffWaitTime->SetBdColor(Qt::white, Qt::white, Qt::white);
    m_p_input_ArcOffWaitTime->SetArcSize(4, 4);
    m_p_input_ArcOffWaitTime->SetBdSize(1);
    m_p_input_ArcOffWaitTime->SetContentsMargins(2, 0, 2, 0);
    m_p_input_ArcOffWaitTime->SetPixelFontSize(20);
    connect(m_p_input_ArcOffWaitTime, &MInputBox::editingFinished, this, [this]()
    {
        double dValue = m_p_input_ArcOffWaitTime->Text().toInt();
        // qDebug() << dValue;
        if(dValue > 10000)
        {
            dValue = 10000;
        }
        if(dValue < 0)
        {
            dValue = 0;
        }
        m_stData.nArcOffWaitTime = dValue;
        m_p_input_ArcOffWaitTime->ClearFocus();
        UpdateValue();
    });

//    m_pibLiftDist->SetTitleMode();
//    m_pibLiftDist->setGeometry(QRect(144, 225, 80, 32));
//    m_pibLiftDist->SetClearButtonIcon(QPixmap(MJROBOT_MAIN_RESOUCE_PARADATA_INPUT_BOX_CLEAR_1_PNG),
//                                     QPixmap(MJROBOT_MAIN_RESOUCE_PARADATA_INPUT_BOX_CLEAR_2_PNG),
//                                     QPixmap(MJROBOT_MAIN_RESOUCE_PARADATA_INPUT_BOX_CLEAR_3_PNG));
//    m_pibLiftDist->SetClearButtonBkColor(QColor(0, 0, 0, 0), QColor(0, 0, 0, 0), QColor(0, 0, 0, 0));
////    QDoubleValidator *pLiftDistValidator = new QDoubleValidator(0, 50, 1);  // 最小值, 最大值, 小数位数
////    m_pibLiftDist->SetValidator(pLiftDistValidator);
//    m_pibLiftDist->SetBkColor(Qt::transparent, Qt::transparent, Qt::transparent);
//    m_pibLiftDist->SetBdColor(Qt::white, Qt::white, Qt::white);
//    m_pibLiftDist->SetArcSize(4, 4);
//    m_pibLiftDist->SetBdSize(1);
//    m_pibLiftDist->SetContentsMargins(2, 0, 2, 0);
//    m_pibLiftDist->SetPixelFontSize(20);
//    connect(m_pibLiftDist, &MInputBox::editingFinished, this, [this]()
//    {
//        double dValue = std::floor(m_pibLiftDist->Text().toDouble() * 10) / 10;
//        // qDebug() << dValue;
//        if(dValue > 100)
//        {
//            dValue = 100;
//        }
//        if(dValue < 0)
//        {
//            dValue = 0;
//        }
//        m_stData.dWeldLiftDist = dValue;
//        m_pibLiftDist->ClearFocus();
//        UpdateValue();
//    });

    // 下拉框
    m_pcbTemple->setFixedWidth(202);
    m_pcbTemple->setFixedHeight(28);
    m_pcbTemple->move(85, 0);
    m_pcbTemple->setAppearance(QColor(0, 0, 0, 0), QColor(255, 255, 255, 255));
    m_pcbTemple->setListPanelAppearance(QColor(0x3D475C), QColor(255, 255, 255, 255));
    m_pcbTemple->setDisplayTextSize(14, Qt::white, false);
//    m_pcbTemple->s
    m_pcbTemple->setCornerRadius(4);
    m_pcbTemple->setItemAppearance(QColor(0, 0, 0, 0), QColor(255, 255, 255, 255),
                                   QColor(0x7584A3), QColor(255, 255, 255, 255),
                                   QColor(0x15C79B), QColor(255, 255, 255, 255),
                                   2);
    m_pcbTemple->setDragButtonIcons(QPixmap(MJROBOT_MAIN_RESOUCE_PARADATA_COMBO_BOX_DRAG_1_PNG),
                                    QPixmap(MJROBOT_MAIN_RESOUCE_PARADATA_COMBO_BOX_DRAG_2_PNG),
                                    QPixmap(MJROBOT_MAIN_RESOUCE_PARADATA_COMBO_BOX_DRAG_3_PNG), 20, 12);
    m_pcbTemple->setItemReserveSpaceWhenHidden(false);
    m_pcbTemple->SetItemFontSize(14);
    m_pcbTemple->SetItemHeight(28);
    m_pcbTemple->SetBdSize(1);
    m_pcbTemple->SetListBdSize(1);
    m_pcbTemple->setListMaxHeight(130);

    // 焊接类型选择框
    connect(m_pcbTemple, &MComboBox::OnSelectionChanged, [this]()
    {
        // 获取当前选择文本
        std::string text(m_pcbTemple->GetHlText().toStdString());
        // 遍历工件枚举类型以匹配枚举量
        for (int i = 0; i < m_vecWeldDataList.size(); ++i)
        {
            // 匹配文本
            if (m_vecWeldDataList[i].strTitle == text)
            {
                // 更改当前数据中对应值
                m_stData = m_vecWeldDataList[i].weld_para;
                UpdateValue();
                break;
            }
        }
    });



//    connect(m_pcbTemple, &MComboBox::Click, [this]()
//    {
//        UpdateTemples();
//        m_pcbTemple->Clear();
//        // 焊接类型选择框
//        for (int i = 0; i < m_vecWeldDataList.size(); ++i)
//        {
//            m_pcbTemple->AddItem(m_vecWeldDataList[i].strTitle);
//            m_pcbTemple->setItemIcons(i, false, false);
//        }
//    });

//    UpdateTemples();
//    qDebug() << "bFound?";
    /*    m_pcbCraft->setFixedWidth(142);
    m_pcbCraft->setFixedHeight(32);
    m_pcbCraft->move(144, 54);
    m_pcbCraft->setAppearance(QColor(0, 0, 0, 0), QColor(255, 255, 255, 255));
    m_pcbCraft->setListPanelAppearance(QColor(0x3D475C), QColor(255, 255, 255, 255));
    m_pcbCraft->setDisplayTextSize(14, Qt::white, false);
    m_pcbCraft->setCornerRadius(4);
    m_pcbCraft->setItemAppearance(QColor(0, 0, 0, 0), QColor(255, 255, 255, 255),
                                  QColor(0x7584A3), QColor(255, 255, 255, 255),
                                  QColor(0x15C79B), QColor(255, 255, 255, 255),
                                  2);
    m_pcbCraft->setDragButtonIcons(QPixmap(MJROBOT_MAIN_RESOUCE_PARADATA_COMBO_BOX_DRAG_1_PNG),
                                   QPixmap(MJROBOT_MAIN_RESOUCE_PARADATA_COMBO_BOX_DRAG_2_PNG),
                                   QPixmap(MJROBOT_MAIN_RESOUCE_PARADATA_COMBO_BOX_DRAG_3_PNG), 20, 12);
    m_pcbCraft->setItemReserveSpaceWhenHidden(false);
    m_pcbCraft->SetItemFontSize(14);
    m_pcbCraft->SetItemHeight(32);
    m_pcbCraft->SetBdSize(1);
    m_pcbCraft->SetListBdSize(1);
    m_pcbCraft->setListMaxHeight(150);

    // 焊接工艺选择框
    connect(m_pcbCraft, &MComboBox::OnSelectionChanged, [this]()
    {
        // 获取当前选择文本
        std::string text(m_pcbCraft->GetHlText().toStdString());
        // 遍历工件枚举类型以匹配枚举量
        for (int i = 0; i < static_cast<int>(MWELD_CRAFT::COUNT); ++i)
        {
            // 重新转换回枚举量
            auto enumValue = static_cast<MWELD_CRAFT>(i);
            // 匹配文本
            if (MWeldDataDefine::TranslateMWELD_CRAFT(enumValue) == text)
            {
                // 更改当前数据中对应值
                m_stData.stWeldProcess.nType = i;
                break;
            }
        }
        UpdateValue();
    });

    // 焊接工艺选择框
    for (int i = 0; i < static_cast<int>(MWELD_CRAFT::COUNT); ++i)
    {
        // 重新转换回枚举量
        auto enumValue = static_cast<MWELD_CRAFT>(i);
        m_pcbCraft->AddItem(MWeldDataDefine::TranslateMWELD_CRAFT(enumValue));
        m_pcbCraft->setItemIcons(i, false, false);
    }*/

    m_pcbWeldType->setFixedWidth(142);
    m_pcbWeldType->setFixedHeight(32);
    m_pcbWeldType->move(144, 111);
    m_pcbWeldType->setAppearance(QColor(0, 0, 0, 0), QColor(255, 255, 255, 255));
    m_pcbWeldType->setListPanelAppearance(QColor(0x3D475C), QColor(255, 255, 255, 255));
    m_pcbWeldType->setDisplayTextSize(14, Qt::white, false);
    m_pcbWeldType->setCornerRadius(4);
    m_pcbWeldType->setItemAppearance(QColor(0, 0, 0, 0), QColor(255, 255, 255, 255),
                                     QColor(0x7584A3), QColor(255, 255, 255, 255),
                                     QColor(0x15C79B), QColor(255, 255, 255, 255),
                                     2);
    m_pcbWeldType->setDragButtonIcons(QPixmap(MJROBOT_MAIN_RESOUCE_PARADATA_COMBO_BOX_DRAG_1_PNG),
                                      QPixmap(MJROBOT_MAIN_RESOUCE_PARADATA_COMBO_BOX_DRAG_2_PNG),
                                      QPixmap(MJROBOT_MAIN_RESOUCE_PARADATA_COMBO_BOX_DRAG_3_PNG), 20, 12);
    m_pcbWeldType->setItemReserveSpaceWhenHidden(false);
    m_pcbWeldType->SetItemFontSize(14);
    m_pcbWeldType->SetItemHeight(32);
    m_pcbWeldType->SetBdSize(1);
    m_pcbWeldType->SetListBdSize(1);
    m_pcbWeldType->setListMaxHeight(150);

    // 焊接类型选择框
    connect(m_pcbWeldType, &MComboBox::OnSelectionChanged, [this]()
    {
        // 获取当前选择文本
        std::string text(m_pcbWeldType->GetHlText().toStdString());
        // 遍历工件枚举类型以匹配枚举量
        for (int i = 0; i < static_cast<int>(MWELD_TYPE::COUNT); ++i)
        {
            // 重新转换回枚举量
            auto enumValue = static_cast<MWELD_TYPE>(i);
            // 匹配文本
            if (MWeldDataDefine::TranslateMWELD_TYPE(enumValue) == text)
            {
                // 更改当前数据中对应值
                m_stData.nWeldingType = i;
                break;
            }
        }
    });

    // 焊接类型选择框
    for (int i = 0; i < static_cast<int>(MWELD_TYPE::COUNT); ++i)
    {
        // 重新转换回枚举量
        auto enumValue = static_cast<MWELD_TYPE>(i);
        m_pcbWeldType->AddItem(MWeldDataDefine::TranslateMWELD_TYPE(enumValue));
        m_pcbWeldType->setItemIcons(i, false, false);
    }


    m_pcbWorkType->setFixedWidth(142);
    m_pcbWorkType->setFixedHeight(32);
    m_pcbWorkType->move(144, 168);
    m_pcbWorkType->setAppearance(QColor(0, 0, 0, 0), QColor(255, 255, 255, 255));
    m_pcbWorkType->setListPanelAppearance(QColor(0x3D475C), QColor(255, 255, 255, 255));
    m_pcbWorkType->setDisplayTextSize(14, Qt::white, false);
    m_pcbWorkType->setCornerRadius(4);
    m_pcbWorkType->setItemAppearance(QColor(0, 0, 0, 0), QColor(255, 255, 255, 255),
                                     QColor(0x7584A3), QColor(255, 255, 255, 255),
                                     QColor(0x15C79B), QColor(255, 255, 255, 255),
                                     2);
    m_pcbWorkType->setDragButtonIcons(QPixmap(MJROBOT_MAIN_RESOUCE_PARADATA_COMBO_BOX_DRAG_1_PNG),
                                      QPixmap(MJROBOT_MAIN_RESOUCE_PARADATA_COMBO_BOX_DRAG_2_PNG),
                                      QPixmap(MJROBOT_MAIN_RESOUCE_PARADATA_COMBO_BOX_DRAG_3_PNG), 20, 12);
    m_pcbWorkType->setItemReserveSpaceWhenHidden(false);
    m_pcbWorkType->SetItemFontSize(14);
    m_pcbWorkType->SetItemHeight(32);
    m_pcbWorkType->SetBdSize(1);
    m_pcbWorkType->SetListBdSize(1);
    m_pcbWorkType->setListMaxHeight(150);

    // 工件类型选择框
    connect(m_pcbWorkType, &MComboBox::OnSelectionChanged, [this]()
    {
        // 获取当前选择文本
        std::string text(m_pcbWorkType->GetHlText().toStdString());
        // 遍历工件枚举类型以匹配枚举量
        for (int i = 0; i < static_cast<int>(MWORKPIECE_TYPE::COUNT); ++i)
        {
            // 重新转换回枚举量
            auto enumValue = static_cast<MWORKPIECE_TYPE>(i);
            // 匹配文本
            if (MWeldDataDefine::TranslateMWORKPIECE_TYPE(enumValue) == text)
            {
                // 更改当前数据中对应值
                m_stData.nWorkpieceType = i;
                break;
            }
        }
    });

    // 工件类型选择框
    for (int i = 0; i < static_cast<int>(MWORKPIECE_TYPE::COUNT); ++i)
    {
        // 重新转换回枚举量
        auto enumValue = static_cast<MWORKPIECE_TYPE>(i);
        std::string strTypeName = MWeldDataDefine::TranslateMWORKPIECE_TYPE(enumValue);
        // 空间有限，去除“工件”两字，共占六个字节
        m_pcbWorkType->AddItem(strTypeName.substr(0, strTypeName.size() - 6));
        m_pcbWorkType->setItemIcons(i, false, false);
    }

    // 按钮

    m_pbtCraft->setGeometry(144, 54, 142, 32);
    m_pbtCraft->SetText("平焊");
    m_pbtCraft->SetTextSize(14);
    m_pbtCraft->SetTextColor(Qt::white, Qt::white, Qt::white);
    m_pbtCraft->SetBkColor(QColor(0x15C79B), QColor(0x15C79B), QColor(0x15C79B));
    m_pbtCraft->SetArcSize(5, 5);
    m_pbtCraft->SetTextFlags(Qt::AlignLeft|Qt::AlignVCenter);
    m_pbtCraft->SetTextContentsMargins(13,0,6,0);

    m_pbtCraft->SwitchIconEnableState(true);
    m_pbtCraft->PutIconToRightSide(true);
    m_pbtCraft->SetIconPixmap(QPixmap(MJROBOT_MAIN_RESOUCE_SET_CRAFT_PNG),
                                       QPixmap(MJROBOT_MAIN_RESOUCE_SET_CRAFT_PNG),
                                       QPixmap(MJROBOT_MAIN_RESOUCE_SET_CRAFT_PNG));
    m_pbtCraft->SetFixedIconSize(24,24);

    connect(m_pbtCraft, &MMultiStyleButton::clicked, this, [this]()
    {
        emit CraftBtnClicked(m_stData.stWeldProcess);
    });

//    ///< 补全焊缝开关
//    m_pbtFilling->setGeometry(144, 282 + 4, 56, 24);
//    // 设置开状态图片
//    m_pbtFilling->SetCheckTruePicture(MJROBOT_MAIN_RESOUCE_SWITCH_OPEN_1_PNG,
//                                      MJROBOT_MAIN_RESOUCE_SWITCH_OPEN_2_PNG,
//                                      MJROBOT_MAIN_RESOUCE_SWITCH_OPEN_3_PNG);
//    // 设置关状态图片
//    m_pbtFilling->SetCheckFalsePicture(MJROBOT_MAIN_RESOUCE_SWITCH_CLOSE_1_PNG,
//                                       MJROBOT_MAIN_RESOUCE_SWITCH_CLOSE_2_PNG,
//                                       MJROBOT_MAIN_RESOUCE_SWITCH_CLOSE_3_PNG);
//
//    m_pbtFilling->SetState(m_stData.bIsWeldFilling);
//    connect(m_pbtFilling, &MIconCheckBox::stateChanged, this, [this]()
//    {
//        m_stData.bIsWeldFilling = m_pbtFilling->GetState();
//        UpdateValue();
//    });

    ///< 参考示教数据开关
    m_checkBox_ReferTeach->setGeometry(0, 339, 75, 32);
//    m_checkBox_ReferTeach->setGeometry(244, 282 + 4, 56, 24);
    // 设置开状态图片
    m_checkBox_ReferTeach->SetCheckTruePicture(MJROBOT_MAIN_RESOUCE_SWITCH_OPEN_1_PNG,
                                      MJROBOT_MAIN_RESOUCE_SWITCH_OPEN_2_PNG,
                                      MJROBOT_MAIN_RESOUCE_SWITCH_OPEN_3_PNG);
    // 设置关状态图片
    m_checkBox_ReferTeach->SetCheckFalsePicture(MJROBOT_MAIN_RESOUCE_SWITCH_CLOSE_1_PNG,
                                       MJROBOT_MAIN_RESOUCE_SWITCH_CLOSE_2_PNG,
                                       MJROBOT_MAIN_RESOUCE_SWITCH_CLOSE_3_PNG);

    m_checkBox_ReferTeach->SetState(m_stData.bIsReferTeachData);
    connect(m_checkBox_ReferTeach, &MIconCheckBox::stateChanged, this, [this]()
    {
        m_stData.bIsReferTeachData = m_checkBox_ReferTeach->GetState();
        UpdateValue();
    });


    m_pbtCancel->SwitchTextEnableState(true);
    m_pbtCancel->SetText("重置");
    m_pbtCancel->SetTextSize(10);
    m_pbtCancel->SetTextColor(Qt::white, Qt::white, Qt::white);
    m_pbtCancel->SetBkColor(QColor(0x667699), QColor(0x667699), QColor(0x667699));
    m_pbtCancel->setGeometry(QRect(191, 331, 48, 24));
    m_pbtCancel->SetArcSize(5, 5);

    connect(m_pbtCancel, &MMultiStyleButton::clicked, this, [this]()
    {
//        std::string text(m_pcbTemple->GetHlText().toStdString());
//        // 遍历工件枚举类型以匹配枚举量
//        for (int i = 0; i < m_vecWeldDataList.size(); ++i)
//        {
//            // 匹配文本
//            if (m_vecWeldDataList[i].strTitle == text)
//            {
//                // 更改当前数据中对应值
//                m_stData = m_vecWeldDataList[i].weld_para;
//                UpdateValue();
//                break;
//            }
//        }
        WELD_DATA stWeldData;
        int nRtn = MWeldDataManager::GetInstance().GetWeldData(m_stDataBackUp.nID, stWeldData);
//        qDebug() << nRtn;
        if(!nRtn)
        {
            MWeldDataManager::GetInstance().GetCheckedWeldData(m_stData);
        }
        else
        {
            m_stData = stWeldData.weld_para;
        }
        m_stDataBackUp =  m_stData;
        UpdateTemples();
        UpdateValue();
    });

    m_pbtSaveAs->SwitchTextEnableState(true);
    m_pbtSaveAs->SetText("另存为模板");
    m_pbtSaveAs->SetTextSize(10);
    m_pbtSaveAs->SetTextColor(Qt::white, Qt::white, Qt::white);
    m_pbtSaveAs->SetBkColor(QColor(0x667699), QColor(0x667699), QColor(0x667699));
    m_pbtSaveAs->setGeometry(QRect(77, 331, 87, 24));
    m_pbtSaveAs->SetArcSize(5, 5);

    connect(m_pbtSaveAs, &MMultiStyleButton::clicked, this, [this]()
    {
        // 另存为
//        WELD_DATA stWeldData = {};
//        stWeldData.weld_para = m_stData;
//        stWeldData.weld_para.nID = -1;
//        MWeldDataManager::GetInstance().InsertWeldData(stWeldData, nNewId);
//        stWeldData.strTitle += std::to_string(nNewId);
//        stWeldData.weld_para.nID = nNewId;
//        MWeldDataManager::GetInstance().UpdateWeldData(stWeldData);

        emit SaveAsNewTemple(this);

//        UpdateTemples();
//        m_pcbTemple->Clear();
//        // 焊接类型选择框
//        for (int i = 0; i < m_vecWeldDataList.size(); ++i)
//        {
//            m_pcbTemple->AddItem(m_vecWeldDataList[i].strTitle);
//            m_pcbTemple->setItemIcons(i, false, false);
//        }
    });

    connect(this, &MWeldItem::TempleSaved,[this](int _nId)
    {
        m_stData.nID = _nId;
        m_stDataBackUp = m_stData;
        UpdateTemples();
    });

    m_pbtApply->SwitchTextEnableState(true);
    m_pbtApply->SetText("应用");
    m_pbtApply->SetTextSize(10);
    m_pbtApply->SetTextColor(Qt::white, Qt::white, Qt::white);
    m_pbtApply->SetBkColor(QColor(0x15C79B), QColor(0x15C79B), QColor(0x15C79B));
    m_pbtApply->setGeometry(QRect(260, 331, 48, 24));
    m_pbtApply->SetArcSize(5, 5);

    connect(m_pbtApply, &MMultiStyleButton::clicked, this, [this]()
    {
        // 准备日志信息
        std::stringstream ss;
        ss << "用户点击应用第" << m_nIndex << "条焊缝轨迹的焊接工艺";
        MSingletonIPCLog::GetInstance().WriteLog(MLOG_TYPE_INFO, MLOG_DIR_USER,
                                                 ss.str(), __FILENAME__, __LINE__);

        if(m_strProjectName.empty())
        {
            qDebug() << "工程名为空!";
        }
        if(m_bTeachingFlag)
        {
            qDebug() << "示教状态保存";
            emit TeachingSave();
        }
        else
        {
            MSerialize::SetWeldData(m_strProjectName, m_nIndex, m_stData);
        }
        if(m_stDataBackUp != m_stData)
        {
            UpdateOutsideValue();
            // 应用
            m_pbtApply->SetText("已应用");
            m_stDataBackUp = m_stData;
        }
    });


    // 展开点列状态组件
    m_pplPointList->setGeometry(0, 144, 428, 126); //126

//    m_vptPointData.push_back(new PointData<Point3D>(Point3D(1.0, 2.0, 3.0), 1, 100));
//    m_vptPointData.push_back(new PointData<Point3D>(Point3D(4.5, 6.7, 8.9), 2, 100));
//    m_vptPointData.push_back(new PointData<Point3D>(Point3D(10.1, 11.2, 12.3), 1, 100));
//    m_vptPointData.push_back(new PointData<Point3D>(Point3D(10.1, 11.5, 12.3), 1, 100));
//    m_vptPointData.push_back(new PointData<Point3D>(Point3D(1.0, 2.0, 3.0), 1, 100));
//    m_vptPointData.push_back(new PointData<Point3D>(Point3D(4.5, 6.7, 8.9), 2, 100));
//    m_vptPointData.push_back(new PointData<Point3D>(Point3D(10.1, 11.2, 12.3), 1, 100));
//    m_vptPointData.push_back(new PointData<Point3D>(Point3D(10.1, 11.5, 12.3), 1, 100));
//    m_vptPointData.push_back(new PointData<Point3D>(Point3D(1.0, 2.0, 3.0), 1, 100));
//    m_vptPointData.push_back(new PointData<Point3D>(Point3D(4.5, 6.7, 8.9), 2, 100));
//    m_vptPointData.push_back(new PointData<Point3D>(Point3D(10.1, 11.2, 12.3), 1, 100));
//    m_vptPointData.push_back(new PointData<Point3D>(Point3D(10.1, 11.5, 12.3), 1, 100));
    m_pplPointList->SetItemFontSize(10);
    m_pplPointList->ResetPointData(m_vptPointData, true);
    // 绑定跟踪点列表的选中事件
    connect(m_pplPointList, &MPointList::itemSelectionChanged, [this]()
    {
        // 获取当前选中项
        MPointItem *pPointItem = m_pplPointList->GetCurrentItem();
        // 如果不为空指针
        if (pPointItem != nullptr)
        {
            // 输出当前点的ID
            emit PointListItemSelected(pPointItem->GetId() - 1);
        }
    });

//    // 绑定跟踪点列表的删除事件
//    connect(&*m_pplPointList, &MPointList::DeleteItemIndex, [&](int _nRow)
//    {
//        auto &PointData = m_umTrack[m_pcbComboBox->GetCurrentItem()];
//
//        // 在数据库中删除当前选中工程文件对应的点数据表的特定点
//        bool bDeleteRet = MDataBase::GetInstance().DeleteTrajectoryData(
//                m_strProjectName,
//                std::vector<int>{PointData[nDeleteIndex]->nIndex});
//
//        // 数据库删除成功后再删除管理器数据
//        if (bDeleteRet)
//        {
//            // 删除管理器中对应的数据
//            PointData.erase(PointData.begin() + nDeleteIndex);
//
//            // 重新设置点数据
//            m_pplPointList->ResetPointData(PointData, false);
//            // 删除可视化界面的点
//            m_pglWidget->DeleteTrackPoint(nDeleteIndex);
//        }
//
//        // 输出删除的点的ID
//        qDebug() << "toDeleteItem ID：" << nDeleteIndex;
//
//    });

    m_plbSize->setGeometry(QRect(22, 100, 100, 22));
    m_plbSize->SetBkColor(Qt::transparent);
    m_plbSize->SetTextStyle(QColor(255, 255, 255, 179), 10, Qt::AlignVCenter | Qt::AlignLeft, false);
    m_plbSize->SetShowText("点位总数：15");

    m_plbNum->setGeometry(QRect(39, 118, 20, 26));
    m_plbNum->SetBkColor(Qt::transparent);
    m_plbNum->SetTextStyle(QColor(255, 255, 255, 179), 12, Qt::AlignVCenter | Qt::AlignLeft, false);
    m_plbNum->SetShowText("#");

    m_plbType->setGeometry(QRect(157, 118, 100, 26));
    m_plbType->SetBkColor(Qt::transparent);
    m_plbType->SetTextStyle(QColor(255, 255, 255, 179), 12, Qt::AlignVCenter | Qt::AlignLeft, false);
    m_plbType->SetShowText("轨迹属性");

    m_plbAct->setGeometry(QRect(327, 118, 50, 26));
    m_plbAct->SetBkColor(Qt::transparent);
    m_plbAct->SetTextStyle(QColor(255, 255, 255, 179), 12, Qt::AlignVCenter | Qt::AlignLeft, false);
    m_plbAct->SetShowText("操作");

    UpdateView();
    UpdateValue();
}

MWeldItem::~MWeldItem()
{

}

void MWeldItem::SetBkColor(const QColor &_BkInColor, const QColor &_BkOutColor,
                           const QColor &_BkPickedColor, const QColor &_BkExpandedColor)
{
    m_BkInColor = _BkInColor;
    m_BkOutColor = _BkOutColor;
    m_BkPickedColor = _BkPickedColor;
    m_BkExpandedColor = _BkExpandedColor;
    update();
}

void MWeldItem::SetArcSize(int _nX, int _nY)
{
    m_nArcX = _nX;
    m_nArcY = _nY;
    update();
}

void MWeldItem::SetItemSize(int _nWidth, int _nHeight, int _nExpandedHeight)
{
    m_nWidth = _nWidth;
    m_nHeight = _nHeight;
    m_nExpandedHeight = _nExpandedHeight;
    UpdateView();
}

void MWeldItem::SetIsExpanded(bool _bExpanded)
{
    m_bExpanded = _bExpanded;
    if (_bExpanded)
    {
        m_bPicked = true;
    }
    UpdateView();
}

void MWeldItem::SetIsPicked(bool _bPicked)
{
    m_bPicked = _bPicked;
    if (!_bPicked)
    {
        m_bExpanded = false;
    }
    UpdateView();
}

void MWeldItem::SetWeldParaData(WELD_PARAMETER _stData)
{
    m_stData = _stData;
    m_stDataBackUp = _stData;
    UpdateTemples();
    UpdateOutsideValue();
    UpdateValue();
}


void MWeldItem::paintEvent(QPaintEvent *event)
{
//    qDebug() << "update";

    QPainter painter(this);
    // 开启抗锯齿
    painter.setRenderHint(QPainter::Antialiasing, true);

    QColor qcBkColor;
    if (m_bPicked)
    {
        qcBkColor = m_BkPickedColor;
    } else if (m_bMouseIn)
    {
        qcBkColor = m_BkInColor;
    } else
    {
        qcBkColor = m_BkOutColor;
    }

    if (m_bPicked)
    {
        m_plbTemple->SetTextStyle(QColor(255, 255, 255, 255), 10, Qt::AlignBottom | Qt::AlignLeft, false);
        m_plbCurrent->SetTextStyle(QColor(255, 255, 255, 255), 10, Qt::AlignBottom | Qt::AlignLeft, false);
        m_plbVoltage->SetTextStyle(QColor(255, 255, 255, 255), 10, Qt::AlignBottom | Qt::AlignLeft, false);
        m_plbVelocity->SetTextStyle(QColor(255, 255, 255, 255), 10, Qt::AlignBottom | Qt::AlignLeft, false);
        m_plbCraft->SetTextStyle(QColor(255, 255, 255, 255), 10, Qt::AlignBottom | Qt::AlignLeft, false);
    } else
    {
        m_plbTemple->SetTextStyle(QColor(255, 255, 255, 153), 10, Qt::AlignBottom | Qt::AlignLeft, false);
        m_plbCurrent->SetTextStyle(QColor(255, 255, 255, 153), 10, Qt::AlignBottom | Qt::AlignLeft, false);
        m_plbVoltage->SetTextStyle(QColor(255, 255, 255, 153), 10, Qt::AlignBottom | Qt::AlignLeft, false);
        m_plbVelocity->SetTextStyle(QColor(255, 255, 255, 153), 10, Qt::AlignBottom | Qt::AlignLeft, false);
        m_plbCraft->SetTextStyle(QColor(255, 255, 255, 153), 10, Qt::AlignBottom | Qt::AlignLeft, false);
    }


    if (m_bExpanded)
    {
        // 先绘制大圆角背景
        painter.setBrush(m_BkExpandedColor);
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(rect(), m_nArcX, m_nArcY);

        // 再用小圆角矩形覆盖上半部分
        painter.setBrush(qcBkColor);
        painter.setPen(Qt::NoPen);

        QRect qrTopArea = rect();
        qrTopArea.setHeight(m_nHeight);

        // 绘制上半部分的圆角矩形
        painter.drawRoundedRect(qrTopArea, m_nArcX, m_nArcY);
    } else
    {
        // 绘制圆角背景
        painter.setBrush(qcBkColor);
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(rect(), m_nArcX, m_nArcY);
    }

}

void MWeldItem::resizeEvent(QResizeEvent *event)
{
    event->accept();
}

void MWeldItem::enterEvent(QEvent *event)
{
    m_bMouseIn = true;          ///< 使能控件状态
    update();
}

void MWeldItem::leaveEvent(QEvent *event)
{
    m_bMouseIn = false;         ///< 复位控件状态
    update();
}

void MWeldItem::mousePressEvent(QMouseEvent *event)
{
    // 检测是否为左键按下
    if (event->button() == Qt::LeftButton)
    {
        m_bMouseDown = true;            ///< 使能控件状态
        update();
    }
}

void MWeldItem::mouseReleaseEvent(QMouseEvent *event)
{
    // 检测是否为左键松开
    if (event->button() == Qt::LeftButton)
    {
        // 如果鼠标释放时仍在按钮区域内，则切换激活状态并发射信号
        if (rect().contains(event->pos()))
        {
            if (!m_bPicked)
            {
                emit PickItem();
            }
            m_bPicked = true;
            if (m_bExpanded)
            {
                m_bPicked = true;
            }
        }
        m_bMouseDown = false;          ///< 复位控件状态
        update();
    }
}

void MWeldItem::UpdateView()
{
    SetExpanded();
    if (m_bExpanded)
    {
        if (m_vptPointData.size() >= 6 || m_bShowParas)
        {
            setFixedSize(m_nWidth, m_nExpandedHeight);
        } else
        {
            setFixedSize(m_nWidth, m_nExpandedHeight - (6 - m_vptPointData.size()) * 20);
        }
    } else
    {
        setFixedSize(m_nWidth, m_nHeight);
    }
    m_pplPointList->ResetPointData(m_vptPointData, true);
    update();
    emit SizeChanged();
}

void MWeldItem::SetExpanded()
{
    if (m_bShowParas)
    {
        m_pplPointList->hide();
        m_plbSize->hide();
        m_plbNum->hide();
        m_plbType->hide();
        m_plbAct->hide();
        m_pParaScrollArea->show();
        m_pbtCancel->show();
        m_pbtApply->show();
        m_pbtSaveAs->show();
        m_nExpandedHeight = 367;
        if (m_bExpanded)
        {
            m_pbtParas->SetIconPixmap(QPixmap(MJROBOT_MAIN_RESOUCE_ITEM_WELD_PARAS_PICKED),
                                      QPixmap(MJROBOT_MAIN_RESOUCE_ITEM_WELD_PARAS_PICKED),
                                      QPixmap(MJROBOT_MAIN_RESOUCE_ITEM_WELD_PARAS_PICKED));
            m_pbtPoints->SetIconPixmap(QPixmap(MJROBOT_MAIN_RESOUCE_ITEM_WELD_POINTS),
                                       QPixmap(MJROBOT_MAIN_RESOUCE_ITEM_WELD_POINTS),
                                       QPixmap(MJROBOT_MAIN_RESOUCE_ITEM_WELD_POINTS));
        } else
        {
            m_pbtParas->SetIconPixmap(QPixmap(MJROBOT_MAIN_RESOUCE_ITEM_WELD_PARAS),
                                      QPixmap(MJROBOT_MAIN_RESOUCE_ITEM_WELD_PARAS),
                                      QPixmap(MJROBOT_MAIN_RESOUCE_ITEM_WELD_PARAS));
            m_pbtPoints->SetIconPixmap(QPixmap(MJROBOT_MAIN_RESOUCE_ITEM_WELD_POINTS),
                                       QPixmap(MJROBOT_MAIN_RESOUCE_ITEM_WELD_POINTS),
                                       QPixmap(MJROBOT_MAIN_RESOUCE_ITEM_WELD_POINTS));
        }
    } else
    {
        m_pParaScrollArea->hide();
        m_pbtCancel->hide();
        m_pbtApply->hide();
        m_pbtSaveAs->hide();
        m_pplPointList->show();
        m_plbSize->show();
        m_plbNum->show();
        m_plbType->show();
        m_plbAct->show();
        m_nExpandedHeight = 275;
        if (m_bExpanded)
        {
            m_pbtParas->SetIconPixmap(QPixmap(MJROBOT_MAIN_RESOUCE_ITEM_WELD_PARAS),
                                      QPixmap(MJROBOT_MAIN_RESOUCE_ITEM_WELD_PARAS),
                                      QPixmap(MJROBOT_MAIN_RESOUCE_ITEM_WELD_PARAS));
            m_pbtPoints->SetIconPixmap(QPixmap(MJROBOT_MAIN_RESOUCE_ITEM_WELD_POINTS_PICKED),
                                       QPixmap(MJROBOT_MAIN_RESOUCE_ITEM_WELD_POINTS_PICKED),
                                       QPixmap(MJROBOT_MAIN_RESOUCE_ITEM_WELD_POINTS_PICKED));
        } else
        {
            m_pbtParas->SetIconPixmap(QPixmap(MJROBOT_MAIN_RESOUCE_ITEM_WELD_PARAS),
                                      QPixmap(MJROBOT_MAIN_RESOUCE_ITEM_WELD_PARAS),
                                      QPixmap(MJROBOT_MAIN_RESOUCE_ITEM_WELD_PARAS));
            m_pbtPoints->SetIconPixmap(QPixmap(MJROBOT_MAIN_RESOUCE_ITEM_WELD_POINTS),
                                       QPixmap(MJROBOT_MAIN_RESOUCE_ITEM_WELD_POINTS),
                                       QPixmap(MJROBOT_MAIN_RESOUCE_ITEM_WELD_POINTS));
        }
    }
}

void MWeldItem::UpdateValue()
{
    if(m_stData != m_stDataBackUp)
    {
        m_pbtApply->SetText("应用");
    }

    std::string strCraft = MWeldDataDefine::TranslateMWELD_CRAFT(static_cast<MWELD_CRAFT>(m_stData.stWeldProcess.nType));
    m_pbtCraft->SetText(QString::fromStdString(strCraft));

    std::string strWeldType = MWeldDataDefine::TranslateMWELD_TYPE(static_cast<MWELD_TYPE>(m_stData.nWeldingType));
    m_pcbWeldType->SetHlText(QString::fromStdString(strWeldType));
    m_pcbWeldType->setActivatedItem(nullptr);

    std::string strWorkPieceType = MWeldDataDefine::TranslateMWORKPIECE_TYPE(static_cast<MWORKPIECE_TYPE>(m_stData.nWorkpieceType));
    m_pcbWorkType->SetHlText(QString::fromStdString(strWorkPieceType.substr(0, strWorkPieceType.size() - 6)));
    m_pcbWorkType->setActivatedItem(nullptr);

//    m_pbtFilling->SetState(m_stData.bIsWeldFilling);
    m_checkBox_ReferTeach->SetState(m_stData.bIsReferTeachData);

    // 使用WELD_PARAMETER结构体中的实际数值，保留1位小数
    m_pibCurrent->SetText(QString::number(m_stData.dWeldCurrent, 'f', 1));
    m_pibVoltage->SetText(QString::number(m_stData.dWeldVoltage, 'f', 1));
    m_p_input_ArcOnWaitTime->SetText(QString::number(m_stData.nArcOnWaitTime));
    m_p_input_ArcOffWaitTime->SetText(QString::number(m_stData.nArcOffWaitTime));
    m_pibVelocity->SetText(QString::number(m_stData.dWeldVelocity, 'f', 1));
    m_pibOffsetY->SetText(QString::number(m_stData.dWeldOffset_Y, 'f', 1));
    m_pibOffsetZ->SetText(QString::number(m_stData.dWeldOffset_Z, 'f', 1));
//    m_pibLiftDist->SetText(QString::number(m_stData.dWeldLiftDist, 'f', 1));
}

void MWeldItem::UpdateOutsideValue()
{
    bool bFound = false;
    for(auto & stWeldData : m_vecWeldDataList)
    {
        if(stWeldData.weld_para.nID == m_stData.nID)
        {
            m_pcbTemple->SetHlText(QString::fromStdString(stWeldData.strTitle));
            m_plbTemple->SetShowText(QString::fromStdString("参数模板：" + stWeldData.strTitle));
            bFound = true;
            break;
        }
    }

    if(!bFound)
    {
        m_pcbTemple->SetHlText("");
        m_plbTemple->SetShowText("参数模板：无");
    }

    m_plbTitle->SetShowText(QString("焊缝轨迹%1").arg(m_nIndex));

    // 使用WELD_PARAMETER结构体中的实际数值，保留1位小数
    m_plbCurrent->SetShowText(QString("电流：%1A").arg(m_stData.dWeldCurrent, 0, 'f', 1));
    m_plbVoltage->SetShowText(QString("电压：%1V").arg(m_stData.dWeldVoltage, 0, 'f', 1));
    m_plbVelocity->SetShowText(QString("速度：%1mm/s").arg(m_stData.dWeldVelocity, 0, 'f', 1));


    std::string strCraft = MWeldDataDefine::TranslateMWELD_CRAFT(static_cast<MWELD_CRAFT>(m_stData.stWeldProcess.nType));
    m_plbCraft->SetShowText(QString("工艺：%1").arg(QString::fromStdString(strCraft)));;
}

void MWeldItem::UpdateTemples()
{
    std::vector<WELD_DATA> vecDataListMismatched;
    MWeldDataManager::GetInstance().SearchWeldData(m_vecWeldDataList, vecDataListMismatched, "");
    m_pcbTemple->Clear();

    bool bFound = false;
    for (int i = 0; i < m_vecWeldDataList.size(); ++i)
    {
        const auto& stWeldData = m_vecWeldDataList[i];

        // 添加项到选择框
        auto item = m_pcbTemple->AddItem(stWeldData.strTitle);
        m_pcbTemple->setItemIcons(i, false, false);

        // 检查是否匹配当前ID
        if (!bFound && stWeldData.weld_para.nID == m_stData.nID)
        {
            m_pcbTemple->SetHlText(QString::fromStdString(stWeldData.strTitle));
            m_plbTemple->SetShowText(QString::fromStdString("参数模板：" + stWeldData.strTitle));
            m_pcbTemple->setActivatedItem(item);
            bFound = true;
        }
    }

//    qDebug() << "bFound" << bFound;
//    qDebug() << "m_stData.nID" << m_stData.nID;
    if(!bFound)
    {
        m_pcbTemple->SetHlText("");
        m_plbTemple->SetShowText("参数模板：");
        m_pcbTemple->setActivatedItem(nullptr);
    }
//    UpdateValue();
}

void MWeldItem::SetWeldIndex(int _nWeldIndex)
{
    m_nIndex = _nWeldIndex;
    UpdateOutsideValue();
}

void MWeldItem::SetProjectName(std::string &_strName)
{
    m_strProjectName = _strName;
}

void MWeldItem::SetWeldPointData(std::vector<ROBOT_POINT_DATA> &_vPts)
{
    // 清空原有数据
    for (auto* ptr : m_vptPointData) {
        delete ptr;
    }
    m_vptPointData.clear();

    // 转换数据
    for (const auto& robotPoint : _vPts) {
        // 创建 Point3D 对象，只使用坐标信息 (dX, dY, dZ)
        Point3D point3D(robotPoint.dX, robotPoint.dY, robotPoint.dZ);

        // 创建 PointData<Point3D> 对象，使用机器人点的类型
        PointData<Point3D>* pointData = new PointData<Point3D>(
                point3D,
                robotPoint.nType,
                -1  // 数据库索引默认为-1，可根据需要调整
        );

        // 添加到向量中
        m_vptPointData.push_back(pointData);
    }
    m_plbSize->SetShowText(QString("点位数量：%1").arg(m_vptPointData.size()));
    UpdateView();
}

void MWeldItem::SetWeldProcessData(WELD_PROCESS &_stData)
{
    m_stData.stWeldProcess = _stData;
    UpdateOutsideValue();
    UpdateValue();
}

void MWeldItem::GetWeldParaData(WELD_PARAMETER &_stData)
{
    _stData = m_stData;
}

void MWeldItem::GetWeldIndex(int &_nWeldIndex)
{
    _nWeldIndex = m_nIndex;
}

void MWeldItem::SetTeachingFlag(bool _bTeachingFlag)
{
    m_bTeachingFlag = _bTeachingFlag;
}

int MWeldItem::GetPointSize()
{
    return m_vptPointData.size();
}




