#include "renderarea.h"
#include "qevent.h"




RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);

}

void RenderArea::paintEvent(QPaintEvent *)
{
    drawBorder();
    QPainter painter(this);
    painter.drawImage(this->rect(), image,this->rect());
    painter.end();
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(200,200);
}

QSize RenderArea::sizeHint() const
{
    return QSize(400, 200);
}

// nede finde good solution
void RenderArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && (trianglepresset || !paintVertex))
    {
        drawPoint(event->position().toPoint());
        paintVertex ?
        emit addVertexPos(event->position().toPoint()):
        emit addPointPos(event->position().toPoint());
    }
    if(event->button() == Qt::RightButton && trianglepresset)
    {
        trianglepress();
        clearArena();
        emit triagleActivate();
    }
}

void RenderArea::resizeEvent(QResizeEvent *)
{
    if (width() > image.width() || height() > image.height())
    {
        int newWidth = qMax(width(), image.width());
        int newHeight = qMax(height(), image.height());
        resizeImage(QSize(newWidth, newHeight));
        update();
    }
}

void RenderArea::drawPoint(QPoint pos)
{
    QPainter painter(&image);
    painter.setPen(QPen(QBrush(Qt::red,Qt::SolidPattern),6,Qt::SolidLine,Qt::RoundCap));
    painter.drawPoint(pos.x(),pos.y());
    painter.end();
    update();
}

//need join with a slot
void RenderArea::drawLine(QPoint pos1,QPoint pos2)
{
    QPainter painter(&image);
    painter.setPen(QPen(QBrush(Qt::blue,Qt::SolidPattern),2,Qt::SolidLine,Qt::RoundCap));
    painter.drawLine(pos1,pos2);
    painter.end();
    drawPoint(pos1);
    drawPoint(pos2);
    update();
}

void RenderArea::drawBorder()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
    painter.end();
}

void RenderArea::resizeImage( const QSize &newSize)
{
    if (image.size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), image);
    image = newImage;
}

void RenderArea::trianglepress()
{
    trianglepresset = !trianglepresset;
    if(trianglepresset)
        statusTrianglePs();

}
//__________________________
//slots
//__________________________

void RenderArea::statusTrianglePs()
{
    QString str("left button add point|right button of add pointe mode");
    emit changeStatus(str);
}

void RenderArea::fullVertex()
{
    trianglepresset = false;
}

void RenderArea::drowLineWithPoint(QPoint pos1,QPoint pos2)
{
    drawLine(pos1,pos2);
}

void RenderArea::clearArena()
{
    image.fill(qRgb(255, 255, 255));
    emit deletAllPoint();
    emit triagleActivate();
    paintVertex = true;
    update();
}

void RenderArea::paintPoint()
{
    paintVertex = false;
}
