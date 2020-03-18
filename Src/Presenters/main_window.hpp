#pragma once

#include <iostream>
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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QCoreApplication>

template <class Widget>
static Widget* makeNamedLine(QBoxLayout* layout, const std::string& name) {
    auto vl = new QHBoxLayout();
    auto label = new QLabel(QString(name.c_str()));
    vl->addWidget(label);
    auto line = new Widget();
    vl->addWidget(line);
    layout->addLayout(vl);
    return line;
}

struct FunctionParameters {
    QLineEdit* _a;
    QLineEdit* _b;
    QLineEdit* _c;
    QLineEdit* _d;

    QLineEdit* _min;
    QLineEdit* _max;

    QLineEdit* _stop_criteria;
    QLineEdit* _num_of_intervals;
    QLineEdit* _r;

    QComboBox* _method;
};

class MainWinow : public QMainWindow {
Q_OBJECT

    void makeParametersSection(QBoxLayout* layout) {
        auto& params = this->parameters;
        params._a = makeNamedLine<QLineEdit>(layout, "A");
        params._b = makeNamedLine<QLineEdit>(layout, "B");
        params._c = makeNamedLine<QLineEdit>(layout, "C");
        params._d = makeNamedLine<QLineEdit>(layout, "D");

        {
            auto vl = new QHBoxLayout();
            auto label = new QLabel(QString("Interval"));
            vl->addWidget(label);
            params._min = new QLineEdit();
            vl->addWidget(params._min);
            params._max = new QLineEdit();
            vl->addWidget(params._max);
            layout->addLayout(vl);
        }

        params._stop_criteria = makeNamedLine<QLineEdit>(layout, "Stop criteria");
        params._num_of_intervals = makeNamedLine<QLineEdit>(layout, "Num of intervals");
        params._r = makeNamedLine<QLineEdit>(layout, "r");

        params._method = new QComboBox();
        params._method->addItem(QString("one"));
        params._method->addItem(QString("two"));
        params._method->addItem(QString("three"));
        layout->addWidget(params._method);

        auto go_button = new QPushButton("Start");
        layout->addWidget(go_button);

        connect(go_button, SIGNAL (released()), this , SLOT (do_nothing())) ;
    }

    void makeExperimentsSection(QBoxLayout* layout) {
        
    }

    void createSidePanel(QBoxLayout* layout) {
        makeParametersSection(layout);

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
        Function* f = new Function(10, 2, 11, 5);
        float step = 0.1;
        float strat = -1;
        float i = 0;
        while ( i < 10) {
            QPointF p(i, (*f)(i));
            *series << p;
            i += step;

        }

        m_chart->chart()->addSeries(series);

//        step = 1.0 / 10;
//        auto new_series = new QScatterSeries();
//        new_series->setMarkerSize(7.0);
//        for (int i = 0 ; i < 10; i++) {
//            QPointF p(strat + step * i, 5);
//            *new_series << p;
//        }
//        m_chart->chart()->addSeries(new_series);

        m_chart->chart()->createDefaultAxes();
    }

    void createPlot(Function& f) {
        auto series = new QLineSeries();

        float step = 0.1;
        float i = parameters._min->text().toFloat();
        float max = parameters._max->text().toFloat();

        while ( i < max) {
            QPointF p(i, (f)(i));
            *series << p;
            i += step;

        }

        m_chart->chart()->addSeries(series);
        m_chart->chart()->createDefaultAxes();
    }


public:
    MainWinow() {
        m_window = std::make_unique<QWidget>();

        auto hLayout = new QHBoxLayout();
        auto vLayout = new QVBoxLayout();

        QWidget *widget = new QWidget();
        widget->setLayout(hLayout);
        setCentralWidget(widget);
        fillPlotView(hLayout);

        hLayout->addWidget(m_chart.get());

        hLayout->addLayout(vLayout);
        vLayout->setAlignment(Qt::AlignTop);

        createSidePanel(vLayout);

        fillRandomPlot();
        this->show();
    }

    ~MainWinow() {
        int x = 42;
    }

    bool checkInput() const {
        if (parameters._a->text().isEmpty())
            return false;

        if (parameters._b->text().isEmpty())
            return false;

        if (parameters._c->text().isEmpty())
            return false;

        if (parameters._d->text().isEmpty())
            return false;

        if (parameters._max->text().isEmpty())
            return false;

        if (parameters._min->text().isEmpty())
            return false;

//        if (parameters._num_of_intervals->text().isEmpty())
//            return false;
//
//        if (parameters._stop_criteria->text().isEmpty())
//            return false;
//
//        if (parameters._r->text().isEmpty())
//            return false;

        return true;
    }

    int lineToInt(QLineEdit* line) {
        return line->text().toInt();
    }

public slots:
    void do_nothing() {
        if (!checkInput())
            return;

        Function f(lineToInt(parameters._a), lineToInt(parameters._b), lineToInt(parameters._c), lineToInt(parameters._d));
        createPlot(f);


    }

private:
    std::unique_ptr<QWidget> m_window;
    std::unique_ptr<QChartView> m_chart;

    std::map<std::string, QLineSeries> m_series_cache;
    FunctionParameters parameters;
};
