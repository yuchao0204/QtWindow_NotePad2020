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
#include<QMessageBox>
#include<QFileDialog>
#include<QBuffer>
#include <QTextCodec>

QString MainWin::path = "";
bool MainWin::saveAs = false;
MainWin::MainWin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWin)
{
    ui->setupUi(this);
    //编辑控件
    resize( 1000, 800 );
    initMainEditor();
    //菜单
    QMenuBar *mBar = menuBar();
    QMenu *pFile = mBar->addMenu("文件");
    QMenu *pDuihuak = mBar->addMenu("窗口");
    QMenu *pEdit = mBar->addMenu("编辑");

    QAction *pNew = pFile->addAction("新建");
    connect(pNew,&QAction::triggered,this,&MainWin::newFile);

    //文件dialog
    QAction *open = pFile->addAction("打开");
    connect(open,&QAction::triggered,this,&MainWin::openFile);

    //save
    QAction *save = pFile->addAction("保存");
    connect(save,&QAction::triggered,this,&MainWin::saveFile);

    //另存为
    QAction *saveAs = pFile->addAction(("另存为"));
    connect(saveAs,&QAction::triggered,this,&MainWin::saveAsFile);

    pFile->addSeparator();

    //tuichu
    QAction *pQuit = pFile->addAction("退出");
    connect(pQuit,&QAction::triggered,this,&MainWin::close);


    //模态
    QAction *pdialog1 = pDuihuak->addAction("窗口1");
    connect(pdialog1,&QAction::triggered,
            [](){
        QDialog dia;
        dia.exec();
        qDebug()<<"dialog1";
    });

    //非模态
    QAction *pdialog2 = pDuihuak->addAction("窗口2");
    connect(pdialog2,&QAction::triggered,
            [=](){
        QDialog *dia = new QDialog();
        dia->setAttribute(Qt::WA_DeleteOnClose);
        dia->show();
        qDebug()<<"dialog2";
    });

    //guanyu
    QAction *pdialog3 = pDuihuak->addAction("窗口3");
    connect(pdialog3,&QAction::triggered,
            [=](){
                QMessageBox::about(this,"----1-----","xxxxxxxx");
                qDebug()<<"dialog3";
            }
    );

    //wenti
    QAction *pdialog4 = pDuihuak->addAction("窗口4");
    connect(pdialog4,&QAction::triggered,
            [=](){
                int ret = QMessageBox::question(this,"----2----","xxxxxxxx",QMessageBox::Ok,QMessageBox::Close,QMessageBox::Cancel);
                qDebug()<<"dialog4-"<<ret;
                qDebug()<<"QMessageBox::yes-"<<(ret==QMessageBox::Ok);
            }
    );

    //编辑
    QAction *search = pEdit->addAction("查找");
    connect(search,&QAction::triggered,this,&MainWin::openSearch);
    //工具
    QToolBar *toolBar = addToolBar("toolBar1");
    toolBar->addAction(pNew);
    toolBar->addAction(open);
    toolBar->addAction(save);

    //状态
    QStatusBar *stu = statusBar();
    QLabel *lab = new QLabel(this);
    lab->setText("text");
    stu->addWidget(lab);

}

//打开文件
void MainWin::openFile(){
    checkChanged();
    if(!m_isTextChanged){
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
                    textEd.setPlainText(str);//读取文件的所有数据并导入到编辑组件
                }
                file.close();
                setWindowTitle("NotePad 2020 - [ " + tmpPath + " ]");
                m_isTextChanged=false;
            }
            path = tmpPath;
        }
        qDebug()<<"path="<<path;
        qDebug()<<"openFile success";
    }
}

//保存文件
void MainWin::saveFile(){
    qDebug()<<"save path"<<path;
    if(path==""||saveAs){//saveAs：另存为标识
        saveAs=false;
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
                out << textEd.toPlainText();
                file.close();
                setWindowTitle("NotePad 2020 - [ " + path + " ]");
                m_isTextChanged=false;
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
            out << textEd.toPlainText();
            file.close();
            setWindowTitle("NotePad 2020 - [ " + path + " ]");
            m_isTextChanged=false;
        }
    }
    qDebug()<<"saveFile success";
}

//另存为
void MainWin::saveAsFile(){
    saveAs = true;
    saveFile();
}

//新建文件
void MainWin::newFile(){
    checkChanged();
    if(!m_isTextChanged){
        textEd.clear();
        setWindowTitle("NotePad 2020 - [ New ]");
        path = "";
        m_isTextChanged = false;
    }

    qDebug()<<"newFile success";
//    showError("newFile success");
}

//初始化编辑区
void MainWin::initMainEditor(){
    setWindowTitle("NotePad 2020 - [New]");
    m_isTextChanged=false;
    textEd.setParent(this);
    setCentralWidget(&textEd);
    connect(&textEd,&QTextEdit::textChanged,this,&MainWin::onTextChanged);
}

void MainWin::onTextChanged(){
    if( !m_isTextChanged )
    {
        setWindowTitle("*" + windowTitle());
    }

    m_isTextChanged = true;
}

void MainWin::checkChanged(){
    qDebug()<<"checkChanged"<<m_isTextChanged;
    if(m_isTextChanged)
    {
        int r = showQueryMessage("Do you want to save the changes to file?");
        switch(r)
        {
        case QMessageBox::Yes:
            saveFile();
            break;
        case QMessageBox::No:
            m_isTextChanged = false;
            break;
        }
    }
}

void MainWin::openSearch(){
    qDebug()<<"openSearch"<<endl;
    findDlg = new QDialog(this);
    findDlg->setWindowTitle(tr("查找"));
//    findDlg->setBaseSize(200,50);
    QGridLayout *GridLayout = new QGridLayout(findDlg);//网格布局

    findDlg->sizeHint();
    findLineEdit = new QLineEdit(findDlg);
    QPushButton *btnFind= new QPushButton(tr("查找下一个"), findDlg);
    QPushButton *btnCancole= new QPushButton(tr("取消"), findDlg);
//    QVBoxLayout *layout= new QVBoxLayout(findDlg);
    QLabel *findText = new QLabel(this);
    findText->setText("查找内容");
    GridLayout->addWidget(findText,0,0);
    GridLayout->addWidget(findLineEdit,0,1);
    GridLayout->addWidget(btnFind,1,1);
    GridLayout->addWidget(btnCancole,2,1);
    findDlg->show();
}
int MainWin::showQueryMessage(QString message){
    QMessageBox msg(this);

    msg.setWindowTitle("Query");
    msg.setText(message);
    msg.setIcon(QMessageBox::Question);
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

    return msg.exec();
}
//弹出错误信息提示
//void MainWin::showError(QString message){
//    QMessageBox msg(this);

//    msg.setWindowTitle("Error");
//    msg.setText(message);
//    msg.setIcon(QMessageBox::Critical);
//    msg.setStandardButtons(QMessageBox::Ok);

//    msg.exec();
//}

void MainWin::closeEvent(QCloseEvent *event){

//    checkChanged();
    if(m_isTextChanged)
    {
        int r = showQueryMessage("Do you want to save the changes to file?");
        switch(r)
        {
        case QMessageBox::Yes:
            saveFile();
            qDebug()<<"QCloseEvent Yes"<<m_isTextChanged<<endl;
            if(!m_isTextChanged){
                event->accept();
            }else{
                event->ignore();
            }
            break;
        case QMessageBox::No:
            qDebug()<<"QCloseEvent No"<<endl;
            m_isTextChanged = false;
            event->accept();
            break;
        }
    }
}

MainWin::~MainWin()
{
    delete ui;
}

