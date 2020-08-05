#include "mainwin.h"
#include "ui_mainwin.h"
#include<QMenuBar>
#include<QMenu>
#include<QAction>
#include<QDebug>
#include<QToolBar>
#include<QPushButton>
#include<QStatusBar>
#include<QLabel>
//#include<QTextEdit>
#include<QDialog>
#include<QMessageBox>
#include<QFileDialog>
#include<QBuffer>
#include <QTextCodec>

QString MainWin::path = "";

MainWin::MainWin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWin)
{
    ui->setupUi(this);
    //编辑控件
//    QTextCodec *codec = QTextCodec::codecForName("GBK");
//    QTextCodec::setCodecForLocale(codec);
//    QTextCodec::setCodecForCStrings(codec);
//    QTextCodec::setCodecForTr(codec);
    setWindowTitle("NotePad 2020");
    textEd = new QTextEdit(this);
    setCentralWidget(textEd);
    //菜单
    QMenuBar *mBar = menuBar();
    QMenu *pFile = mBar->addMenu("文件");

    QAction *pNew = pFile->addAction("新建");
    connect(pNew,&QAction::triggered,this,&MainWin::newFile);

    //文件dialog
    QAction *open = pFile->addAction("打开");
    connect(open,&QAction::triggered,this,&MainWin::openFile);

    //save
    QAction *save = pFile->addAction("保存");
    connect(save,&QAction::triggered,this,&MainWin::saveFile);

    pFile->addSeparator();

    //tuichu
    QAction *pQuit = pFile->addAction("quit");
    connect(pQuit,&QAction::triggered,this,&MainWin::close);


    //模态
    QMenu *pDuihuak = mBar->addMenu("dialog");
    QAction *pdialog1 = pDuihuak->addAction("dialog1");
    connect(pdialog1,&QAction::triggered,
            [](){
        QDialog dia;
        dia.exec();
        qDebug()<<"dialog1";
    });

    //非模态
    QAction *pdialog2 = pDuihuak->addAction("dialog2");
    connect(pdialog2,&QAction::triggered,
            [=](){
        QDialog *dia = new QDialog();
        dia->setAttribute(Qt::WA_DeleteOnClose);
        dia->show();
        qDebug()<<"dialog2";
    });

    //guanyu
    QAction *pdialog3 = pDuihuak->addAction("dialog3");
    connect(pdialog3,&QAction::triggered,
            [=](){
                QMessageBox::about(this,"----1-----","xxxxxxxx");
                qDebug()<<"dialog3";
            }
    );

    //wenti
    QAction *pdialog4 = pDuihuak->addAction("dialog4");
    connect(pdialog4,&QAction::triggered,
            [=](){
                int ret = QMessageBox::question(this,"----2----","xxxxxxxx",QMessageBox::Ok,QMessageBox::Close,QMessageBox::Cancel);
                qDebug()<<"dialog4-"<<ret;
                qDebug()<<"QMessageBox::yes-"<<(ret==QMessageBox::Ok);
            }
    );

    //工具
    QToolBar *toolBar = addToolBar("toolBar1");
    toolBar->addAction(pNew);
    toolBar->addAction(open);
    toolBar->addAction(save);
    QPushButton *b = new QPushButton(this);
    b->setText("quit");
    toolBar->addWidget(b);
    connect(b,&QPushButton::pressed,this,&MainWin::close);

    //状态
    QStatusBar *stu = statusBar();
    QLabel *lab = new QLabel(this);
    lab->setText("text");
    stu->addWidget(lab);

}

void MainWin::openFile(){
    //打开文件
    QString tmpPath = QFileDialog::getOpenFileName(
                this,"打开","../","all(*.*);;test(*.qml);;source(*.cpp *.h)");
    if( tmpPath != "" )
        {
            QFile file(tmpPath);

            if( file.open(QIODevice::ReadOnly | QIODevice::Text) )
            {
                QTextStream textStream(&file);

                while(!textStream.atEnd()){
                    QTextCodec *codec = QTextCodec::codecForName("GBK");//读取中文防止乱码
                    QString str = codec->toUnicode(file.readAll());
                    textEd->setPlainText(str);//读取文件的所有数据并导入到编辑组件
                }
                file.close();
                setWindowTitle("NotePad 2020 - [ " + tmpPath + " ]");
            }
            path = tmpPath;
        }
    qDebug()<<"path="<<path;
    qDebug()<<"openFile success";
}

void MainWin::saveFile(){
    qDebug()<<"save path"<<path;
    if(path==""){
        //path为空时，新建文件，创建文件对话框
        QFileDialog *fileDialog = new QFileDialog(this);
        fileDialog->setWindowTitle(tr("Save As"));
        fileDialog->setAcceptMode(QFileDialog::AcceptSave);
        fileDialog->setFileMode(QFileDialog::AnyFile);//设置文件对话框弹出的时候显示任何文件，不论是文件夹还是文件
        fileDialog->setViewMode(QFileDialog::Detail);//文件以详细的形式显示，显示文件名，大小，创建日期等信息；
//        fileDialog->setGeometry(0,0,100,200);//设置文件对话框的显示位置
        fileDialog->setDirectory(".");//设置文件对话框打开时初始打开的位置
//        fileDialog->setFilter(tr("Image Files(*.jpg *.png)"));//设置文件类型过滤器
        if(fileDialog->exec() == QDialog::Accepted) {//注意使用的是QFileDialog::Accepted或者QDialog::Accepted,不是QFileDialog::Accept
            path = fileDialog->selectedFiles()[0];//得到用户选择的文件名
            qDebug()<<"得到用户选择的文件名"<<path;
            QFile file(path);//创建一个文件对象，存储用户选择的文件
            if( file.open(QIODevice::WriteOnly | QIODevice::Text) )
            {
                qDebug()<<"if(true)";
                QTextStream out(&file);
//                out.setCodec("unicode");
                out << textEd->toPlainText();
                file.close();
                setWindowTitle("NotePad 2020 - [ " + path + " ]");
            }
        }
        qDebug()<<"new save path"<<path;
    }else if(path!=""){
        //path不为空时保存到当前文件
        QFile file(path);
        if( file.open(QIODevice::WriteOnly | QIODevice::Text) )
        {
            qDebug()<<"if(true)";
            QTextStream out(&file);
            out << textEd->toPlainText();
            file.close();
            setWindowTitle("NotePad 2020 - [ " + path + " ]");
        }
    }
    qDebug()<<"saveFile success";
}

void MainWin::newFile(){
    textEd->clear();
    qDebug()<<"newFile success";
}
MainWin::~MainWin()
{
    delete ui;
}

