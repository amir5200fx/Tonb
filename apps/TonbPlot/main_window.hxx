//
// Created by amir on 9/1/25.
//
#pragma once
#include <QMainWindow>

#include <memory>

class Tri2dView;
class DataPanel;
class AppearancePanel;

class TonbPlotMainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit TonbPlotMainWindow(QWidget *parent = nullptr);

private slots:
    void open_dataset();
    void load_dataset(const QString& prefix);
    void export_png();
    void reset_view();

private:

    void create_menu();
    void create_toolbar();
    void create_docks();
    void connect_signals();
    void update_status_counts();

    Tri2dView* triView_ = nullptr;
    DataPanel* dataPanel_ = nullptr;
    AppearancePanel* appearancePanel_ = nullptr;

    QAction* actOpen_ = nullptr;
    QAction* actExport_ = nullptr;
    QAction* actResetView_ = nullptr;

};