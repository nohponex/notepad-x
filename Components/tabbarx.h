#ifndef TABBARX_H
#define TABBARX_H

#include <QtWidgets/QTabBar>
#include <QtWidgets/QWidget>
#include <QDropEvent>
#include <QMouseEvent>
class TabBarX : public QTabBar
{
    Q_OBJECT
public:
        TabBarX();
        void dropEvent(QDropEvent* event);
        void dragEnterEvent(QDragEnterEvent* event);

        /**
         *  this event is called when the mouse moves inside the widgets area during a drag/drop operation
         */
        void dragMoveEvent(QDragMoveEvent* event);

        /**
         *  this event is called when the mouse leaves the widgets area during a drag/drop operation
         */
        void dragLeaveEvent(QDragLeaveEvent* event);

        void mousePressEvent( QMouseEvent* event );
public slots:
    void makeDrag();
};

#endif // TABBARX_H
