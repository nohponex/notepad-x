#include "iconpack.h"

iconpack* iconpack::s_instance = 0;

#include <QIcon>
iconpack::iconpack()
{
    theme = ":/default/icons/";
    icon_table[ icon_new ] = "document-text.png";
    icon_table[ icon_open ] = "folder.png";
    icon_table[ icon_recent ] = "folder--arrow.png";
    icon_table[ icon_save ] = "disk.png";
    icon_table[ icon_saveAs ] = "disks.png";
    icon_table[ icon_exit ] = "cross.png";
    icon_table[ icon_close ] = "cross.png";

    icon_table[ icon_print ] = "printer.png";
    icon_table[ icon_pageSetup ] = "printer_empty.png";

    icon_table[ icon_copy ] = "document-copy.png";
    icon_table[ icon_cut ] = "scissors-blue.png";
    icon_table[ icon_paste ] = "clipboard-paste.png";

    icon_table[ icon_next ] = "arrow-000-medium.png";
    icon_table[ icon_previous ] = "arrow-180-medium.png";
    icon_table[ icon_moveToWindow ] = "application-export.png";
    icon_table[ icon_moveToNewWindow ] = "application--plus.png";

    icon_table[ icon_saved ] = "/document-hf-insert.png";
    icon_table[ icon_notsaved ] = "/document-hf-delete.png";

    icon_table[ icon_redo ] = "arrow-return.png";
    icon_table[ icon_undo ] = "arrow-return-180-left.png";

    icon_table[ icon_find ] = "binocular.png";
    icon_table[ icon_replace ] = "edit-replace.png";

    icon_table[ icon_tools ] = "gear.png";
    icon_table[ icon_settings ] = "wrench-screwdriver.png";
    icon_table[ icon_layout ] = "layout-design.png";
    icon_table[ icon_layout_default ] = "layout-hf.png";
    icon_table[ icon_layout_addRow ] = "layout-split-vertical.png";
    icon_table[ icon_layout_addCol ] = "layout-split.png";
    icon_table[ icon_layout_split ] = "application-split.png";
    icon_table[ icon_layout_splitVertical ] = "application-split-vertical.png";
    icon_table[ icon_layout_grid ] = "application-split-tile.png";

    icon_table[ icon_language ] = "highlighter-text.png";
    icon_table[ icon_window ] = "application.png";

    icon_table[ icon_projects ] = "briefcase.png";
    icon_table[ icon_projectsCreate ] = "briefcase--plus.png";
    icon_table[ icon_projectsRecent ] = "briefcase--arrow.png";

    icon_table[ icon_website ] = "home.png";

    icon_table[ icon_bugReport ] = "bug.png";
    icon_table[ icon_featureRequest ] = "light-bulb.png";
    icon_table[ icon_donate ] = "home.png";
    icon_table[ icon_about ] = "information.png";
    icon_table[ icon_help ] = "question.png";

}

QIcon* iconpack::get_icon(icons icon){
    return (QIcon*)( new QIcon( theme + icon_table[ icon ] ));
}
