#ifndef TABWIDGETX_H
#define TABWIDGETX_H

#include <QtWidgets/QTabWidget>
class TabWidgetX : public QTabWidget
{
    Q_OBJECT
private:
    //bool root;
    public:
        TabWidgetX( QWidget* parent=0);
        /*QTabBar* tabBar()
        {
          return QTabWidget::tabBar();
        }*/
        void tabInserted(int index);
    private slots:
        void closing( int index );
        void selection_change( int index );
public slots:
        void document_changed();
        void document_saved( bool saved );
};

#endif // TABWIDGETX_H
