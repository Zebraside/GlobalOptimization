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
#include "../Optimization/SolverFactory.hpp"
#include <QtWidgets/QSlider>
#include "../Optimization/FunctionFactory.h"

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
    std::map<std::string, QLineEdit*> parameters;
    QLineEdit* _min;
    QLineEdit* _max;

    QLineEdit* _stop_criteria;
    QLineEdit* _num_of_intervals;
    QLineEdit* _r;

    QComboBox* _method;
    QComboBox* _function;
};

class MainWinow : public QMainWindow {
Q_OBJECT

    void makeParametersSection(QBoxLayout* layout) {
        auto& params = this->parameters;

        assert(function);
        auto parameter_names = function->getParameterNames();
        for (const auto& name : parameter_names) {
            params.parameters[name] = makeNamedLine<QLineEdit>(layout, name);
        }

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
        for (auto& method : SolverFactory::getMethods()) {
            params._method->addItem(QString(method.c_str()));
        }

//        params._function = new QComboBox();
//        for (auto& function : FunctionFactory::getFunctions()) {
//            params._function->addItem(QString(function.c_str()));
//        }

        layout->addWidget(params._method);
//        layout->addWidget(params._function);

        auto go_button = new QPushButton("Solve");
        layout->addWidget(go_button);

        connect(go_button, SIGNAL (released()), this , SLOT (do_nothing())) ;
    }

    void update_slider(const std::vector<Test>& test_history) {
        _slider->setRange(0, test_history.size());
    }

    void makeExperimentsSection(QBoxLayout* layout) {
        _result = makeNamedLine<QLineEdit>(layout, "Result");
        layout->addWidget(_result);
        _op_count = makeNamedLine<QLineEdit>(layout, "Iterations Count");
        layout->addWidget(_op_count);

        _slider = new QSlider(Qt::Orientation::Horizontal);
        _slider->setTickPosition(QSlider::TicksBothSides);
        _slider->setTickInterval(1);
        connect(_slider, SIGNAL(sliderReleased()), this, SLOT(updatePlot()));
        layout->addWidget(_slider);
    }

    void createSidePanel(QBoxLayout* layout) {
        makeParametersSection(layout);
        makeExperimentsSection(layout);
    }

    void fillPlotView(QLayout* layout) {
        m_chart = std::make_unique<QChartView>();
        m_chart->setChart(new Chart());

        auto chart = m_chart->chart();
        chart->setTitle("Global Optimization");
        chart->setAnimationOptions(QChart::SeriesAnimations);
        chart->legend()->hide();
        chart->createDefaultAxes();

        m_chart->setRenderHint(QPainter::Antialiasing);

        layout->addWidget(m_chart.get());
    }

    void fillRandomPlot() {
        auto series = new QLineSeries();
        Function* f = new Function();
        float step = 0.05;
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

    void createPlot(IFunction& f) {
        m_chart->chart()->removeAllSeries();
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
        function = new Function();

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
    }

    bool checkInput() const {
        for (auto& [name, line] : parameters.parameters) {
            if (line->text().isEmpty())
                return false;
        }

        if (parameters._max->text().isEmpty())
            return false;

        if (parameters._min->text().isEmpty())
            return false;

        if (parameters._num_of_intervals->text().isEmpty())
            return false;

        if (parameters._stop_criteria->text().isEmpty())
            return false;

        if (parameters._r->text().isEmpty())
            return false;

        return true;
    }

    int lineToInt(QLineEdit* line) {
        return line->text().toInt();
    }

    float lineToFloat(QLineEdit* line) {
        return line->text().toFloat();
    }

public slots:
    void do_nothing() {
        if (!checkInput())
            return;


        std::map<std::string, double> params;
        for (auto& [key, value] : parameters.parameters) {
            params[key] = lineToInt(value);
        }

        // auto function = FunctionFactory::getFunctions()[parameters._function->currentIndex()];
        std::shared_ptr<IFunction> f = FunctionFactory::create("ExampleFunction", params);
        createPlot(*f);


        auto method = SolverFactory::getMethods()[parameters._method->currentIndex()];
        auto solving_method = SolverFactory::create(method, lineToFloat(parameters._r));
        std::vector<Test> history;
        int operationCount;
        auto result = solving_method->solve(*f,
                lineToFloat(parameters._min),
                lineToFloat(parameters._max),
                lineToFloat(parameters._stop_criteria),
                lineToInt(parameters._num_of_intervals),
                history,
                operationCount);

        _result->setText(QString::number(result));
        _op_count->setText(QString::number(operationCount));

        experiment = {f, history};

        update_slider(history);
    }


    void updatePlot() {
        if (!experiment.function)
            return;

        createPlot(*experiment.function);

        int current_idx = _slider->value();


        auto old_series = new QScatterSeries();
        old_series->setMarkerSize(7.0);

        auto& history = experiment.history;
        for (int i = 0; i < current_idx - 1; ++i) {
            QPointF p(history[i].point, history[i].functionValue);
            *old_series << p;
        }

        m_chart->chart()->addSeries(old_series);

        auto new_series = new QScatterSeries();
        new_series->setMarkerSize(7.0);
        *new_series <<  QPointF(history[current_idx].point, history[current_idx].functionValue);

        m_chart->chart()->addSeries(new_series);

        m_chart->chart()->createDefaultAxes();
    }

private:
    struct Experiment {
        std::shared_ptr<IFunction> function;
        std::vector<Test> history;
    };

    Experiment experiment;
//    std::unique_ptr<QWidget> m_window;
    std::unique_ptr<QChartView> m_chart;

    std::map<std::string, QLineSeries> m_series_cache;
    FunctionParameters parameters;
    QLineEdit* _result;
    QLineEdit* _op_count;
    QSlider* _slider;
    IFunction* function;
};
