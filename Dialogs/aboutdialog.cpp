#include "aboutdialog.h"
#include <QtWidgets/QWidget>
#include <QtWidgets/QAction>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>

#include <QtWidgets/QFormLayout>
#include <QFont>

#include <QtWidgets/QDialogButtonBox>
//#include <QPushButton>
#include <QtWidgets/QToolButton>

#include <QRect>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>

#include <QDesktopServices>
#include <QUrl>

#include <QDebug>
#include "mainwindow.h"
#include <Classes/iconpack.h>
AboutDialog::AboutDialog( QWidget *parent ): QWidget(parent)
{
    QVBoxLayout *lay = new QVBoxLayout();
    resize(200,300);

    //QRect scr = QApplication::desktop()->screenGeometry();
    //move( scr.center() - rect().center() );
    move( MainWindow::instance()->geometry().center() - rect().center() );



    setWindowTitle("About");
    this->setLayout( lay );
    QLabel *title = new QLabel("Notepad X");
    QFont font = title->font();
    font.setPointSize( 36 );
    font.setWeight(60);
    title->setFont(font);
    QLabel *website = new QLabel("<a href='#'>http://notepad-x.sourceforge.net</a>");
    connect(website,SIGNAL(linkActivated(QString)),MainWindow::instance(),SLOT(help_website()));
    website->setCursor( Qt::PointingHandCursor  );
    //connect(website,SIGNAL())
    QLabel *version = new QLabel("Version 0.1 Alpha");

    QWidget *Details = new QWidget();
    QFormLayout *form = new QFormLayout();
    Details->setLayout( form );
    form->addRow( QString("Developer"), new QLabel("NohponeX") );
    form->addRow( QString("Translator"), new QLabel("NohponeX") );


    QLabel *license = new QLabel("CONDITIONS OF ANY KIND, either express or implied.\n   See the License for the specific language governing permissions and\n   limitations under the License.");
    font = license->font();
    font.setPointSize( 12 );
    font.setWeight(40);
    license->setFont(font);
    QWidget *buttons = new QWidget();

    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttons->setLayout( buttonsLayout );

    QToolButton *close = new QToolButton();
    close->setIcon( *iconpack::instance()->get_icon( iconpack::icon_close ) );
    close->setToolButtonStyle( Qt::ToolButtonTextBesideIcon );
    close->setText("Close");
    close->setMinimumHeight(25);


    connect( close, SIGNAL( clicked() ), this, SLOT( close() ) );

    QToolButton *donate = new QToolButton();
    donate->setIcon( *iconpack::instance()->get_icon( iconpack::icon_donate ) );
    donate->setText("Donate");
    donate->setToolButtonStyle( Qt::ToolButtonTextBesideIcon );
    donate->setMinimumHeight(25);
    connect( donate, SIGNAL( clicked() ), MainWindow::instance(), SLOT( help_donate() ) );
    buttonsLayout->addWidget( close );
    buttonsLayout->addWidget( donate );



    lay->addWidget( title );
    lay->addWidget( website );
    lay->addWidget( version );
    lay->addWidget( Details );
    lay->addWidget( license );
    lay->addWidget( buttons );
    this->setWindowIcon( *iconpack::instance()->get_icon( iconpack::icon_about ) );
}
