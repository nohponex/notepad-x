#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QtWidgets/QWidget>
class QTabWidget;
class QTabBar;
class QScrollArea;
class QFormLayout;
class QDialogButtonBox;
class QAbstractButton;
class QTableWidget;
class QGroupBox;
class QCheckBox;
class QComboBox;
class QTableWidgetItem;
class QLabel;
class QPushButton;
class SettingsDialog : public QWidget
{
    Q_OBJECT
public:
    SettingsDialog( QWidget *parent = 0 );
private:
protected:
    QDialogButtonBox *buttons;
    QTabWidget *tab_control;
    //QTabBar *tab_general;
    QScrollArea *gereral_scroll;
    QFormLayout *general_form;

    QTableWidget * general_extensions_table;
    int general_extensions_table_index;
    QScrollArea *shortcuts_scroll;
    QFormLayout *shortcuts_form;
    QTableWidget *shortcuts_table;
    QGroupBox *shortcuts_edit_group;
    QCheckBox *shortcuts_edit_control;
    QCheckBox *shortcuts_edit_shift;
    QCheckBox *shortcuts_edit_alt;
    QComboBox *shortcuts_edit_key;

    QDialogButtonBox *shortcuts_edit_buttons;

    /*QScrollArea *toolbars_scroll;
    QFormLayout *toolbars_form;*/
    QWidget *toolbars_control;
    QTableWidget *toolbars_table;
    QGroupBox *toolbars_details_group;
    QLabel *toolbars_name;
    QLabel *toolbars_author;
    QLabel *toolbars_version;
    QLabel *toolbars_description;
    QDialogButtonBox *toolbar_buttons;
    QPushButton *toolbar_buttons_add;
    QPushButton *toolbar_buttons_delete;
    QPushButton *toolbar_buttons_browse;
    QPushButton *toolbar_buttons_download;
    QPushButton *toolbar_buttons_up;
    QPushButton *toolbar_buttons_down;

    QScrollArea *icons_scroll;
    QFormLayout *icons_form;


protected slots:
    void shortcuts_table_selection_changed(int,int,int,int);
    void shortcuts_edit_buttons_apply( );
    void shortcuts_edit_buttons_cancel();
    void shortcuts_edit_buttons_restore_defaults();
    void cellChanged(int,int);
private slots:

};

#endif // SETTINGSDIALOG_H
