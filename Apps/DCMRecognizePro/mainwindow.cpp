#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mModel  = new QDirModel;

    QStringList filters;
    filters << "*.dcm";

    mModel->setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);
    mModel->setNameFilters(filters);

    ui->treeView->setModel(mModel);
    ui->treeView->setRootIndex(mModel->index("G:/"));


    mRecognizeWdg  = nullptr;
    mReCheckWdg = nullptr;

    connect(ui->pushButton_recognize, SIGNAL(clicked(bool)), this, SLOT(slotBtnClick(bool)));
    connect(ui->pushButton_recheck, SIGNAL(clicked(bool)), this, SLOT(slotBtnClick(bool)));
    connect(ui->pushButton_search, SIGNAL(clicked(bool)), this, SLOT(slotBtnClick(bool)));
    connect(ui->lineEdit_search, SIGNAL(textChanged(QString)), this, SLOT(textChanged(QString)));

    connect(ui->treeView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(doubleClicked(QModelIndex)));
}

void MainWindow::doubleClicked(QModelIndex index)
{
    QString filePath = mModel->filePath(index);

    QFileInfo info;
    info.setFile(filePath);

    if (info.isDir())
        return ;


    QString dateTimeStr = QDateTime::currentDateTime().toString("MM-dd hh-mm-ss-zzz");
    QString outFileName = QString(QStringLiteral("%1.jpg")).arg(dateTimeStr);


    std::thread([&] {
        //1.5秒循环
        std::string errorStr;
        ReadDCMFile::readDCMFile(filePath.toLocal8Bit().toStdString(), outFileName.toLocal8Bit().toStdString(), errorStr);

//        ReadDCMFile file;
//        bool isSuc = file.readDCMFile(filePath.toLocal8Bit().toStdString(), outFileName.toLocal8Bit().toStdString(), errorStr);

//        qDebug() << errorStr.c_str() << isSuc;
        std::cout << errorStr << std::endl;

    }).detach();


//    qDebug() <<  filePath << info.baseName() << info.filePath();


}

void MainWindow::textChanged(QString text)
{
//    qDebug() << __FUNCTION__ << text;

    ui->treeView->reset();

    QModelIndex index = mModel->index(text);
    ui->treeView->setRootIndex(index);
}

void MainWindow::slotBtnClick(bool bClick)
{
    if (QObject::sender() == ui->pushButton_recognize)
    {
        if (nullptr == mRecognizeWdg)
        {
            mRecognizeWdg = new RecognizeWdg;
        }

        mRecognizeWdg->show();
    }
    else if (QObject::sender() == ui->pushButton_recheck)
    {
        if (nullptr == mReCheckWdg)
        {
            mReCheckWdg = new ReCheckWdg;
        }
        mReCheckWdg->show();
    }
    else if (QObject::sender() == ui->pushButton_search)
    {
        QString s = QFileDialog::getExistingDirectory(
            this, "open file dialog",
                "./");

        if (!s.isEmpty())
        {
            ui->lineEdit_search->setText(s);
        }
        else {
            ui->lineEdit_search->setText("./");
        }

    }
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    return QMainWindow::resizeEvent(e);
}

MainWindow::~MainWindow()
{
    if (nullptr != mModel)
    {
        delete mModel;
        mModel = nullptr;
    }

    delete ui;
}
