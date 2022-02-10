#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graph.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    virtual void mouseReleaseEvent(QMouseEvent *e);
    virtual void paintEvent(QPaintEvent *event);
    virtual void DrawLineWithArrow(QPainter& painter, QPoint start, QPoint end);
    ~MainWindow();

private slots:


    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Graph g;
    Node firstNode, secondNode;
    bool drawNode, drawArc, isOriented;

};
#endif // MAINWINDOW_H
