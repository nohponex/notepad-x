#ifndef ICONPACK_H
#define ICONPACK_H

#include <QIcon>
class QIcon;

class iconpack
{
    public:
        static iconpack *instance()
        {
            if (!s_instance)
              s_instance = new iconpack;
            return s_instance;
        }
        enum icons{ icon_new = 0 , icon_open,icon_recent, icon_save, icon_saveAs, icon_close, icon_closeAll, icon_closeOthers, icon_print, icon_printPreview, icon_pageSetup, icon_exit,
                    icon_cut, icon_copy, icon_paste, icon_find, icon_replace, icon_selectAll, icon_undo, icon_redo,
                    icon_next, icon_previous,icon_moveToNewWindow, icon_moveToWindow, icon_saved, icon_notsaved,
                    icon_settings, icon_layout, icon_layout_addRow, icon_layout_addCol, icon_layout_default,icon_console,
                    icon_layout_split,icon_layout_splitVertical,icon_layout_grid,
                    icon_tools,icon_language, icon_window,icon_projects,icon_projectsCreate,
                    icon_projectsRemove, icon_projectsRecent,
                    icon_help, icon_bugReport, icon_featureRequest, icon_donate, icon_website, icon_about };

        QIcon *get_icon( icons icon);
    private:
        QString theme;
        QString icon_table[ icon_about +1 ];
        static iconpack *s_instance;
        iconpack();

};

#endif // ICONPACK_H
