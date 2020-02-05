#pragma once

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <QtGui/QPainter>
#include <QtGui/QScreen>

#include "surfacegraph.h"

class MainWinow {
    void createModelGroup(QWidget* widget, QLayout* layout, SurfaceGraph* modifier) {
        QGroupBox *modelGroupBox = new QGroupBox(QStringLiteral("Model"));

        QRadioButton *sqrtSinModelRB = new QRadioButton(widget);
        sqrtSinModelRB->setText(QStringLiteral("Sqrt && Sin"));
        sqrtSinModelRB->setChecked(false);

        QRadioButton *heightMapModelRB = new QRadioButton(widget);
        heightMapModelRB->setText(QStringLiteral("Height Map"));
        heightMapModelRB->setChecked(false);

        QVBoxLayout *modelVBox = new QVBoxLayout;
        modelVBox->addWidget(sqrtSinModelRB);
        modelVBox->addWidget(heightMapModelRB);
        modelGroupBox->setLayout(modelVBox);

        layout->addWidget(modelGroupBox);

        QObject::connect(heightMapModelRB, &QRadioButton::toggled,
                         modifier, &SurfaceGraph::enableHeightMapModel);
        QObject::connect(sqrtSinModelRB, &QRadioButton::toggled,
                         modifier, &SurfaceGraph::enableSqrtSinModel);
    }

    void createSelectionMode(QWidget* widget, QLayout* layout, SurfaceGraph* modifier) {
        QGroupBox *selectionGroupBox = new QGroupBox(QStringLiteral("Selection Mode"));

        QRadioButton *modeNoneRB = new QRadioButton(widget);
        modeNoneRB->setText(QStringLiteral("No selection"));
        modeNoneRB->setChecked(false);

        QRadioButton *modeItemRB = new QRadioButton(widget);
        modeItemRB->setText(QStringLiteral("Item"));
        modeItemRB->setChecked(false);

        QRadioButton *modeSliceRowRB = new QRadioButton(widget);
        modeSliceRowRB->setText(QStringLiteral("Row Slice"));
        modeSliceRowRB->setChecked(false);

        QRadioButton *modeSliceColumnRB = new QRadioButton(widget);
        modeSliceColumnRB->setText(QStringLiteral("Column Slice"));
        modeSliceColumnRB->setChecked(false);

        QVBoxLayout *selectionVBox = new QVBoxLayout;
        selectionVBox->addWidget(modeNoneRB);
        selectionVBox->addWidget(modeItemRB);
        selectionVBox->addWidget(modeSliceRowRB);
        selectionVBox->addWidget(modeSliceColumnRB);
        selectionGroupBox->setLayout(selectionVBox);

        layout->addWidget(selectionGroupBox);

        QObject::connect(modeNoneRB, &QRadioButton::toggled,
                         modifier, &SurfaceGraph::toggleModeNone);
        QObject::connect(modeItemRB,  &QRadioButton::toggled,
                         modifier, &SurfaceGraph::toggleModeItem);
        QObject::connect(modeSliceRowRB,  &QRadioButton::toggled,
                         modifier, &SurfaceGraph::toggleModeSliceRow);
        QObject::connect(modeSliceColumnRB,  &QRadioButton::toggled,
                         modifier, &SurfaceGraph::toggleModeSliceColumn);

        modeItemRB->setChecked(true);
    }

    void createRangeSliders(QWidget* widget, QLayout* layout, SurfaceGraph* modifier) {
        QSlider *axisMinSliderX = new QSlider(Qt::Horizontal, widget);
        axisMinSliderX->setMinimum(0);
        axisMinSliderX->setTickInterval(1);
        axisMinSliderX->setEnabled(true);
        QSlider *axisMaxSliderX = new QSlider(Qt::Horizontal, widget);
        axisMaxSliderX->setMinimum(1);
        axisMaxSliderX->setTickInterval(1);
        axisMaxSliderX->setEnabled(true);
        QSlider *axisMinSliderZ = new QSlider(Qt::Horizontal, widget);
        axisMinSliderZ->setMinimum(0);
        axisMinSliderZ->setTickInterval(1);
        axisMinSliderZ->setEnabled(true);
        QSlider *axisMaxSliderZ = new QSlider(Qt::Horizontal, widget);
        axisMaxSliderZ->setMinimum(1);
        axisMaxSliderZ->setTickInterval(1);
        axisMaxSliderZ->setEnabled(true);

        layout->addWidget(new QLabel(QStringLiteral("Column range")));
        layout->addWidget(axisMinSliderX);
        layout->addWidget(axisMaxSliderX);
        layout->addWidget(new QLabel(QStringLiteral("Row range")));
        layout->addWidget(axisMinSliderZ);
        layout->addWidget(axisMaxSliderZ);

        modifier->setAxisMinSliderX(axisMinSliderX);
        modifier->setAxisMaxSliderX(axisMaxSliderX);
        modifier->setAxisMinSliderZ(axisMinSliderZ);
        modifier->setAxisMaxSliderZ(axisMaxSliderZ);

        QObject::connect(axisMinSliderX, &QSlider::valueChanged,
                         modifier, &SurfaceGraph::adjustXMin);
        QObject::connect(axisMaxSliderX, &QSlider::valueChanged,
                         modifier, &SurfaceGraph::adjustXMax);
        QObject::connect(axisMinSliderZ, &QSlider::valueChanged,
                         modifier, &SurfaceGraph::adjustZMin);
        QObject::connect(axisMaxSliderZ, &QSlider::valueChanged,
                         modifier, &SurfaceGraph::adjustZMax);


    }

    void createThemeSelector(QWidget* widget, QLayout* layout, SurfaceGraph* modifier) {
        QComboBox *themeList = new QComboBox(widget);
        themeList->addItem(QStringLiteral("Qt"));
        themeList->addItem(QStringLiteral("Primary Colors"));
        themeList->addItem(QStringLiteral("Digia"));
        themeList->addItem(QStringLiteral("Stone Moss"));
        themeList->addItem(QStringLiteral("Army Blue"));
        themeList->addItem(QStringLiteral("Retro"));
        themeList->addItem(QStringLiteral("Ebony"));
        themeList->addItem(QStringLiteral("Isabelle"));

        QGroupBox *colorGroupBox = new QGroupBox(QStringLiteral("Custom gradient"));

        QLinearGradient grBtoY(0, 0, 1, 100);
        grBtoY.setColorAt(1.0, Qt::black);
        grBtoY.setColorAt(0.67, Qt::blue);
        grBtoY.setColorAt(0.33, Qt::red);
        grBtoY.setColorAt(0.0, Qt::yellow);
        QPixmap pm(24, 100);
        QPainter pmp(&pm);
        pmp.setBrush(QBrush(grBtoY));
        pmp.setPen(Qt::NoPen);
        pmp.drawRect(0, 0, 24, 100);
        QPushButton *gradientBtoYPB = new QPushButton(widget);
        gradientBtoYPB->setIcon(QIcon(pm));
        gradientBtoYPB->setIconSize(QSize(24, 100));

        QLinearGradient grGtoR(0, 0, 1, 100);
        grGtoR.setColorAt(1.0, Qt::darkGreen);
        grGtoR.setColorAt(0.5, Qt::yellow);
        grGtoR.setColorAt(0.2, Qt::red);
        grGtoR.setColorAt(0.0, Qt::darkRed);
        pmp.setBrush(QBrush(grGtoR));
        pmp.drawRect(0, 0, 24, 100);
        QPushButton *gradientGtoRPB = new QPushButton(widget);
        gradientGtoRPB->setIcon(QIcon(pm));
        gradientGtoRPB->setIconSize(QSize(24, 100));

        QHBoxLayout *colorHBox = new QHBoxLayout;
        colorHBox->addWidget(gradientBtoYPB);
        colorHBox->addWidget(gradientGtoRPB);
        colorGroupBox->setLayout(colorHBox);


        layout->addWidget(new QLabel(QStringLiteral("Theme")));
        layout->addWidget(themeList);
        layout->addWidget(colorGroupBox);


        QObject::connect(themeList, SIGNAL(currentIndexChanged(int)),
                         modifier, SLOT(changeTheme(int)));
        QObject::connect(gradientBtoYPB, &QPushButton::pressed,
                         modifier, &SurfaceGraph::setBlackToYellowGradient);
        QObject::connect(gradientGtoRPB, &QPushButton::pressed,
                         modifier, &SurfaceGraph::setGreenToRedGradient);

        themeList->setCurrentIndex(2);
    }

public:
    MainWinow() {
        Q3DSurface *graph = new Q3DSurface();
        QWidget *container = QWidget::createWindowContainer(graph);
        SurfaceGraph *modifier = new SurfaceGraph(graph);

        if (!graph->hasContext()) {
            QMessageBox msgBox;
            msgBox.setText("Couldn't initialize the OpenGL context.");
            msgBox.exec();
            throw std::logic_error("Can't init");
        }

        QSize screenSize = graph->screen()->size();
        container->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 1.6));
        container->setMaximumSize(screenSize);
        container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        container->setFocusPolicy(Qt::StrongFocus);

        QWidget *widget = new QWidget;
        QHBoxLayout *hLayout = new QHBoxLayout(widget);
        QVBoxLayout *vLayout = new QVBoxLayout();
        hLayout->addWidget(container, 1);
        hLayout->addLayout(vLayout);
        vLayout->setAlignment(Qt::AlignTop);

        widget->setWindowTitle(QStringLiteral("Global Optimization"));

        createModelGroup(widget, vLayout, modifier);
        createSelectionMode(widget, vLayout, modifier);
        createRangeSliders(widget, vLayout, modifier);
        createThemeSelector(widget, vLayout, modifier);

        widget->show();
    }
};
