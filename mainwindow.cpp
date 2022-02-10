#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "node.h"
#include <QMouseEvent>
#include <QPainter>
#include <QFile>
#include <iostream>
#include<QTextStream>
#include <QRadioButton>
#include<QMessageBox>
#include<QPainter>
#include <QDebug>
#include<QtMath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    drawNode = false;
    drawArc = false;
    isOriented = true;
    ui->setupUi(this);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    drawNode = false;
    drawArc = false;
    if(e->button() == Qt::RightButton)
    {
        Node n(e->pos());
        QPointF p = e->localPos();
        std::vector<Node> noduri = g.GetNoduri();
        for(auto& index:noduri)
        {
            if(fabs(index.getPoint().x() - p.x()) < 20 && fabs(index.getPoint().y() - p.y()) < 20)
            {
                return;
            }
        }


        g.AddNod(n);
        drawNode = true;
        update();
        firstNode = Node();
    }
    else
    {
        QPointF p = e->localPos();
        std::vector<Node> noduri = g.GetNoduri();//se pun aici nodurile deja existente
        Node foundNode;
        for (auto& n : noduri)
        {
            if (fabs(n.getPoint().x() - p.x()) < 20 && fabs(n.getPoint().y() - p.y()) < 20)
            {
                foundNode = n;
                break;
            }
        }
        if (foundNode.getNumber() == -1)
            return;
        if (firstNode.getNumber() == -1)
        {
            firstNode = foundNode;
        }
        else
        {
            secondNode = foundNode;
            g.AddArc(Arc(firstNode, secondNode));
            firstNode = Node();
            secondNode = Node();
            drawArc = true;
            update();
        }
    }
}

void MainWindow::DrawLineWithArrow(QPainter& painter, QPoint start, QPoint end) {

  painter.setRenderHint(QPainter::Antialiasing, true);

  qreal arrowSize = 15; // size of head
  std::vector<Arc>arce;
  arce=g.GetArce();
  for(auto &arc:arce)
  { if(arc.getFirstPoint().getPoint()==start && arc.getSecondPoint().getPoint()==end)
      {
          if(arc.GetColour()=="green")
          {
              painter.setPen(Qt::green);
              painter.setBrush(Qt::green);

          }
          else
          {
              painter.setPen(Qt::red);
              painter.setBrush(Qt::red);
          }
      }
  }

  QLineF line(end, start);

  double angle = std::atan2(-line.dy(), line.dx());
  QPointF arrowP1 = line.p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                        cos(angle + M_PI / 3) * arrowSize);
  QPointF arrowP2 = line.p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                        cos(angle + M_PI - M_PI / 3) * arrowSize);

  QPolygonF arrowHead;
  arrowHead.clear();
  arrowHead << line.p1() << arrowP1 << arrowP2;

  painter.drawLine(line);
  painter.drawPolygon(arrowHead);

}

void MainWindow::paintEvent(QPaintEvent *event)
{
    if (g.getNumberofNodes())
    {
        QPainter p(this);
        std::vector<Node> noduri = g.GetNoduri();
        for(auto& nod: noduri)
        {
            QRect r(nod.getPoint().x()-10,nod.getPoint().y()-10, 20,20);

            p.setPen(QPen(Qt::white));
            p.setBrush(QBrush(Qt::magenta));
            p.drawEllipse(r);
            p.drawText(r,Qt::AlignCenter, QString::number(nod.getNumber()));
        }
        std::vector<Arc> arce = g.GetArce();
        for(auto& arc: arce)
        {

            if(isOriented==false)
            {
               p.drawLine(arc.getFirstPoint().getPoint(), arc.getSecondPoint().getPoint());
            }
            else if(isOriented==true)
            {
                float x,y;
                DrawLineWithArrow(p,arc.getFirstPoint().getPoint(), arc.getSecondPoint().getPoint());
                x = (arc.getFirstPoint().getPoint().x() +  arc.getSecondPoint().getPoint().x()) / 2;
                y = (arc.getFirstPoint().getPoint().y() +  arc.getSecondPoint().getPoint().y()) / 2;

                QPoint point(x,y);
                p.drawText(point, QString::number(arc.GetCapacitate()));
            }

        }

        if (drawNode)
        {
            Node n = g.GetLastNode();
            p.setPen(QPen(Qt::red));
            QRect r(n.getPoint().x()-10,n.getPoint().y()-10, 20,20);
            p.drawEllipse(r);
            p.drawText(n.getPoint(), QString::number(n.getNumber()));
        }
        else if (drawArc)
        {

            if(isOriented==false)
            {
                p.setPen(QPen(Qt::red));
                p.drawLine(QLine(arce[arce.size()-1].getFirstPoint().getPoint(), arce[arce.size()-1].getSecondPoint().getPoint()));
            }
            else if(isOriented==true)
            {

                DrawLineWithArrow(p,arce[arce.size()-1].getFirstPoint().getPoint(), arce[arce.size()-1].getSecondPoint().getPoint());

            }
        }
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    int begin,end,rezultat;
    g.GenerareMatriceCosturi();
    begin=ui->lineEdit->text().toInt();
    end=ui->lineEdit_2->text().toInt();
    rezultat=g.fordFulkerson(begin,end);
   qDebug()<<rezultat;
    update();

}

