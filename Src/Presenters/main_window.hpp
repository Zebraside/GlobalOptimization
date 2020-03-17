#pragma once

#include "chart.h"
#include "../Optimization/IFunction.h"
#include "../Optimization/Function.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCore/QtMath>
#include <QtCore/QRandomGenerator>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChartView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QComboBox>
#include <memory>
#include <QtCharts/QScatterSeries>

class MainWinow {
    void createSidePanel(QVBoxLayout* layout) {
        QComboBox* box = new QComboBox();
        box->addItem(QString("one"));
        box->addItem(QString("two"));
        box->addItem(QString("three"));
        layout->addWidget(box);
    }

    void fillPlotView(QLayout* layout) {
        m_chart = std::make_unique<QChartView>();
        m_chart->setChart(new Chart());

        auto chart = m_chart->chart();
        chart->setTitle("Zoom in/out example");
        chart->setAnimationOptions(QChart::SeriesAnimations);
        chart->legend()->hide();
        chart->createDefaultAxes();

        m_chart->setRenderHint(QPainter::Antialiasing);

        layout->addWidget(m_chart.get());
    }

    void fillRandomPlot() {
        auto series = new QLineSeries();
        Function* f = new Function(1, 1, 1, 1);
        float step = 1.0 / 500;
        float strat = -1;
        for (int i = 0 ; i < 500; i++) {
            QPointF p(strat + step * i, (*f)(strat + step * i));
            p.ry() += QRandomGenerator::global()->bounded(20);
            *series << p;
        }

        m_chart->chart()->addSeries(series);

        step = 1.0 / 10;
        auto new_series = new QScatterSeries();
        new_series->setMarkerSize(7.0);
        for (int i = 0 ; i < 10; i++) {
            QPointF p(strat + step * i, 5);
            *new_series << p;
        }


        m_chart->chart()->addSeries(new_series);
        m_chart->chart()->createDefaultAxes();
    }

public:
    MainWinow() {
        m_window = std::make_unique<QWidget>();

        auto hLayout = new QHBoxLayout();
        auto vLayout = new QVBoxLayout();

        m_window->setLayout(hLayout);

        fillPlotView(hLayout);

        hLayout->addWidget(m_chart.get());

        hLayout->addLayout(vLayout);
        vLayout->setAlignment(Qt::AlignTop);

        createSidePanel(vLayout);

        fillRandomPlot();
        m_window->show();
    }

    ~MainWinow() {
        int x = 42;
    }

private:
    std::unique_ptr<QWidget> m_window;
    std::unique_ptr<QChartView> m_chart;

};
