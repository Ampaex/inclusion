#include "qnchatmessage.h"
#include <QPaintEvent>
#include <QDateTime>
#include <QPainter>
#include <QMovie>
#include <QLabel>
#include <QDebug>

QNChatMessage::QNChatMessage(QWidget *parent) : QWidget(parent)
{
    m_leftPixmap = QPixmap("../../media/images/User1.png");
    m_rightPixmap = QPixmap("../../media/images/User2.png");

    m_loadingMovie = new QMovie(this);
    m_loadingMovie->setFileName("../../media/images/loading4.gif");
    m_loading = new QLabel(this);
    m_loading->setMovie(m_loadingMovie);
    m_loading->resize(16,16);
    m_loading->setAttribute(Qt::WA_TranslucentBackground , true);
    m_loading->setAutoFillBackground(false);
}

void QNChatMessage::setTextSuccess()
{
    m_loading->hide();
    m_loadingMovie->stop();
    m_isSending = true;
}

void QNChatMessage::setText(QString text, QString time, QSize allSize, QNChatMessage::User_Type userType)
{
    m_msg = text;
    m_userType = userType;
    m_time = time;
    m_curTime = QDateTime::fromTime_t(time.toInt()).toString("hh:mm");
    m_allSize = allSize;
    if(userType == User_Me) {
        if(!m_isSending) {
            m_loading->move(m_cuadroRightRect.x() - m_loading->width() - 10, m_cuadroRightRect.y()+
                            m_cuadroRightRect.height()/2 - m_loading->height()/2);
            m_loading->show();
            m_loadingMovie->start();
        }
    } else {
        m_loading->hide();
    }

    this->update();
}


QSize QNChatMessage::fontRect(QString str)
{
    m_msg = str;
    int minHei = 30;
    int iconWH = 40;
    int iconSpaceW = 20;
    int iconRectW = 5;
    int iconTMPH = 10;
    int trianguloW = 6;
    int cuadroTMP = 20;
    int textSpaceRect = 12;
    m_cuadroWidth = this->width() - cuadroTMP - 2*(iconWH+iconSpaceW+iconRectW);
    m_textWidth = m_cuadroWidth - 2*textSpaceRect;
    m_spaceWid = this->width() - m_textWidth;
    m_iconLeftRect = QRect(iconSpaceW, iconTMPH, iconWH, iconWH);
    m_iconRightRect = QRect(this->width() - iconSpaceW - iconWH, iconTMPH, iconWH, iconWH);

    QSize size = getRealString(m_msg); // size of all

    qDebug() << "fontRect Size:" << size;
    int hei = size.height() < minHei ? minHei : size.height();

    m_trianguloLeftRect = QRect(iconWH+iconSpaceW+iconRectW, m_lineHeight/2, trianguloW, hei - m_lineHeight);
    m_trianguloRightRect = QRect(this->width() - iconRectW - iconWH - iconSpaceW - trianguloW, m_lineHeight/2, trianguloW, hei - m_lineHeight);

    if(size.width() < (m_textWidth+m_spaceWid)) {
        m_cuadroLeftRect.setRect(m_trianguloLeftRect.x()+m_trianguloLeftRect.width(), m_lineHeight/4*3, size.width()-m_spaceWid+2*textSpaceRect, hei-m_lineHeight);
        m_cuadroRightRect.setRect(this->width() - size.width() + m_spaceWid - 2*textSpaceRect - iconWH - iconSpaceW - iconRectW - trianguloW,
                                 m_lineHeight/4*3, size.width()-m_spaceWid+2*textSpaceRect, hei-m_lineHeight);
    } else {
        m_cuadroLeftRect.setRect(m_trianguloLeftRect.x()+m_trianguloLeftRect.width(), m_lineHeight/4*3, m_cuadroWidth, hei-m_lineHeight);
        m_cuadroRightRect.setRect(iconWH + cuadroTMP + iconSpaceW + iconRectW - trianguloW, m_lineHeight/4*3, m_cuadroWidth, hei-m_lineHeight);
    }
    m_textLeftRect.setRect(m_cuadroLeftRect.x()+textSpaceRect,m_cuadroLeftRect.y()+iconTMPH,
                           m_cuadroLeftRect.width()-2*textSpaceRect,m_cuadroLeftRect.height()-2*iconTMPH);
    m_textRightRect.setRect(m_cuadroRightRect.x()+textSpaceRect,m_cuadroRightRect.y()+iconTMPH,
                            m_cuadroRightRect.width()-2*textSpaceRect,m_cuadroRightRect.height()-2*iconTMPH);

    return QSize(size.width(), hei);
}

QSize QNChatMessage::getRealString(QString src)
{
    QFontMetricsF fm(this->font());
    m_lineHeight = fm.lineSpacing();
    int nCount = src.count("\n");
    int nMaxWidth = 0;
    if(nCount == 0) {
        nMaxWidth = fm.width(src);
        QString value = src;
        if(nMaxWidth > m_textWidth) {
            nMaxWidth = m_textWidth;
            int size = m_textWidth / fm.width(" ");
            int num = fm.width(value) / m_textWidth;
            //int ttmp = num*fm.width(" ");
            num = ( fm.width(value) ) / m_textWidth;
            nCount += num;
            QString temp = "";
            for(int i = 0; i < num; i++) {
                temp += value.mid(i*size, (i+1)*size) + "\n";
            }
            src.replace(value, temp);
        }
    } else {
        for(int i = 0; i < (nCount + 1); i++) {
            QString value = src.split("\n").at(i);
            nMaxWidth = fm.width(value) > nMaxWidth ? fm.width(value) : nMaxWidth;
            if(fm.width(value) > m_textWidth) {
                nMaxWidth = m_textWidth;
                int size = m_textWidth / fm.width(" ");
                int num = fm.width(value) / m_textWidth;
                num = ((i+num)*fm.width(" ") + fm.width(value)) / m_textWidth;
                nCount += num;
                QString temp = "";
                for(int i = 0; i < num; i++) {
                    temp += value.mid(i*size, (i+1)*size) + "\n";
                }
                src.replace(value, temp);
            }
        }
    }
    return QSize(nMaxWidth+m_spaceWid, (nCount + 1) * m_lineHeight+2*m_lineHeight);
}

void QNChatMessage::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);//Anti-aliasing
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::gray));

    if(m_userType == User_Type::User_Other) { // Other Usuario
        //perfil
        painter.drawPixmap(m_iconLeftRect, m_leftPixmap);

        //cuadro + marco
        QColor col_cuadroB(234, 234, 234);
        painter.setBrush(QBrush(col_cuadroB));
        painter.drawRoundedRect(m_cuadroLeftRect.x()-1,m_cuadroLeftRect.y()-1,m_cuadroLeftRect.width()+2,m_cuadroLeftRect.height()+2,4,4);
        //cuadro
        QColor col_cuadro(255,255,255);
        painter.setBrush(QBrush(col_cuadro));
        painter.drawRoundedRect(m_cuadroLeftRect,4,4);

        //triangulo
        QPointF points[3] = {
            QPointF(m_trianguloLeftRect.x(), 30),
            QPointF(m_trianguloLeftRect.x()+m_trianguloLeftRect.width(), 25),
            QPointF(m_trianguloLeftRect.x()+m_trianguloLeftRect.width(), 35),
        };
        QPen pen;
        pen.setColor(col_cuadro);
        painter.setPen(pen);
        painter.drawPolygon(points, 3);

        //triangulo + marco
        QPen pentrianguloBian;
        pentrianguloBian.setColor(col_cuadroB);
        painter.setPen(pentrianguloBian);
        painter.drawLine(QPointF(m_trianguloLeftRect.x() - 1, 30), QPointF(m_trianguloLeftRect.x()+m_trianguloLeftRect.width(), 24));
        painter.drawLine(QPointF(m_trianguloLeftRect.x() - 1, 30), QPointF(m_trianguloLeftRect.x()+m_trianguloLeftRect.width(), 36));

        //contenido
        QPen penText;
        penText.setColor(QColor(51,51,51));
        painter.setPen(penText);
        QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
        option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
        painter.setFont(this->font());
        painter.drawText(m_textLeftRect, m_msg,option);
    }  else if(m_userType == User_Type::User_Me) { // usuario
        //perfil
        painter.drawPixmap(m_iconRightRect, m_rightPixmap);

        //cuadro + marco
        QColor col_cuadro(75,164,242);
        painter.setBrush(QBrush(col_cuadro));
        painter.drawRoundedRect(m_cuadroRightRect,4,4);

        //triangulo
        QPointF points[3] = {
            QPointF(m_trianguloRightRect.x()+m_trianguloRightRect.width(), 30),
            QPointF(m_trianguloRightRect.x(), 25),
            QPointF(m_trianguloRightRect.x(), 35),
        };
        QPen pen;
        pen.setColor(col_cuadro);
        painter.setPen(pen);
        painter.drawPolygon(points, 3);

        //contenido
        QPen penText;
        penText.setColor(Qt::white);
        painter.setPen(penText);
        QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
        option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
        painter.setFont(this->font());
        painter.drawText(m_textRightRect,m_msg,option);
    }  else if(m_userType == User_Type::User_Time) { // tiempo
        QPen penText;
        penText.setColor(QColor(153,153,153));
        painter.setPen(penText);
        QTextOption option(Qt::AlignCenter);
        option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
        painter.drawText(this->rect(),m_curTime,option);
    }
}
