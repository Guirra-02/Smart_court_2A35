#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
            ui->setupUi(this);
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));
    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                       QCoreApplication::organizationName(), QCoreApplication::applicationName());


int ret=A.connect_arduino(); // lancer la connexion à arduino
 switch(ret){
case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
    break;
case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
   break;
case(-1):qDebug() << "arduino is not available";
}
 QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(getCardUid())); // permet de lancer


}
void MainWindow::statfn()
{
    QPieSeries *series=new QPieSeries();

    series->append("Audiance reussi",80);
    series->append("Nombres des avocats",30);
    series->append("Nombre d'audiance faite",80);

    series->setName("Avocats");
    QPieSlice *slice=series->slices().at(1);
    slice->setExploded(true);
    slice->setLabelVisible(true);
    slice->setPen(QPen(Qt::darkRed));
    slice->setBrush(Qt::yellow);
    QChart *chart=new QChart();
    chart->addSeries(series);
    chart->setTitle("Les avocats selon audiances reussies");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    QChartView *chartview= new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);
    chartview->setParent(ui->horizontalFrame);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_username_editingFinished()
{
ui->username->setStyleSheet("background:transparent;border-radius:14px;border:none;color:#b89d64;border-bottom:1px solid #b89d64;");
}

void MainWindow::on_username_textChanged( )
{
    ui->username->setStyleSheet("border-bottom: 2px solid #b89d64 ;color:#b89d64;font-weight:600;border-radius:0px;");

}


void MainWindow::on_password_textChanged( )
{
ui->password->setStyleSheet("border-bottom: 2px solid #b89d64 ;color:#b89d64;font-weight:600;border-radius:0px;");
}

void MainWindow::on_password_editingFinished()
{
    ui->password->setStyleSheet("background:transparent;border-radius:14px;border:none;color:#b89d64;border-bottom:1px solid #b89d64;");


}

void MainWindow::getCardUid()
{QByteArray x=A.read_from_arduino();QMessageBox msgBox;

    qDebug()<<x<<endl;
    if(x=="163 232 226 145\r\n")
               {
         ui->stackedWidget->setCurrentIndex(1);
      }
        }

void MainWindow::on_signup_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}

void MainWindow::on_signup_2_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWindow::on_signin_clicked()
{QMessageBox msgBox;
    QByteArray x=A.read_from_arduino();
    msgBox.setWindowTitle("Something Went Worng");
msgBox.setStyleSheet("background :#b89d64;border-bottom: 2px solid #b89d64 ; font-weight:600;");
    if(ui->username->text()=="admin" && ui->password->text()=="admin")
    {ui->stackedWidget->setCurrentIndex(1);
    }
    else {msgBox.setText("user or password is wrong");
    msgBox.exec();}


}

void MainWindow::on_pushButton_ajouter_clicked()
{QMessageBox msgBox;
QString id=ui->identifiant->text();
QString nom=ui->nom->text();
QString prenom=ui->prenom->text();
Avocat a(id,nom,prenom);
    a.ajouter();
    QMessageBox::information(nullptr,"ajout","ajout faiiit");
    ui->Tabetu->setModel(a.afficher());
    QMessageBox msg;
}

void MainWindow::on_pushButton_2_clicked()
{
    Avocat a;
    ui->Tabetu->setModel(a.afficher());
    ui->Tabetu->setStyleSheet("background :#b89d64; font-weight:600;");
    ui->label_id->setText(a.getid());
    a.afficher();
}

void MainWindow::on_eliminer_clicked()
{
    Avocat a;
a.setid(ui->identifiant->text());
a.supprimer(a.getid());
ui->Tabetu->setModel(a.afficher());

}

void MainWindow::on_pushButton_modifier_clicked()
{
    {QMessageBox msgBox; bool test;
        QString id=ui->identifiant->text();
        QString nom=ui->nom->text();
        QString prenom=ui->prenom->text();
    Avocat a(id,nom,prenom);
    test=a.modifier(id);
    if(test==false)
    {

        QMessageBox::information(nullptr,"ajout","non effectue");
    }
    else {
        QMessageBox::information(nullptr,"modification","mdification faiiiteee");
    }
    ui->Tabetu->setModel(a.afficher());
    QMessageBox msg;

    }
}
void MainWindow::on_pushButton_12_clicked()
{
    Avocat a;
   QString id=ui->identifiant->text();
    ui->tableView->setModel(a.search_Avocat(id));
    a.search_Avocat(id);
}

void MainWindow::on_pushButton_8_clicked()
{
    QPrinter print;
    print.setPrinterName("Printer name ");
    QPrintDialog printdialog(&print,this);
    if (printdialog.exec()==QDialog::Rejected)
     return;
    QString id,prenom,nom;
id=ui->identifiant->text();
prenom=ui->prenom->text();
nom=ui->nom->text();

      QFile file("C:/Users/admin/Documents/qtprojet/22-10-2022/22-10-2022/""Avocats """".pdf");
      QPdfWriter pdf("C:/Users/admin/Documents/qtprojet/22-10-2022/22-10-2022/""Avocats"""".pdf");
      QPainter painter(&pdf);
      painter.setPen(Qt::black);
      painter.drawText(2000,1000,"ID_AVOCAT N°= "+id+"" );
      painter.drawText(2000,1700,"PRENOM Avocat = "+nom+"");
      painter.drawText(2000,2500,"Nom Avocat = "+prenom+"");
      //painter.drawText(3500,2100,"Numero telephone :  "+numtel+"" );
     // painter.drawText(3500,2500,"Nombre d'audiance: :  "+audiance+"" );
      painter.end();
}

void MainWindow::on_pushButton_9_clicked()
{
    Avocat a;
    ui->Tabetu->setModel(a.affichageASC());
    ui->Tabetu->setStyleSheet("background :#b89d64; font-weight:600;");
    ui->label_id->setText(a.getid());
    a.affichageASC();

}

void MainWindow::on_pushButton_10_clicked()
{
    Avocat a;
    ui->Tabetu->setModel(a.affichageDSC());
    ui->Tabetu->setStyleSheet("background :#b89d64; font-weight:600;");
    ui->label_id->setText(a.getid());
    a.affichageDSC();
}

void MainWindow::on_pushButton_11_clicked()
{
    c=new camera();
     c->show();
}


void  MainWindow::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );

}




void   MainWindow::sendMail()
{
    Smtp* smtp = new Smtp("melek.guirat@esprit.tn",ui->mail_pass->text(), "211JMT3324");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("melek.guirat@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail("melek.guirat@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}
void   MainWindow::mailSent(QString status)
{

    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    ui->rcpt->clear();
    ui->subject->clear();
    ui->file->clear();
    ui->msg->clear();
    ui->mail_pass->clear();
}


void MainWindow::on_browseBtn_clicked()
{
    browse();

}

