#ifndef MAINWIN_H
#define MAINWIN_H

#include <QMainWindow>
#include<QTextEdit>
#include <QCloseEvent>
#include<QDialog>
#include <QLineEdit>
#include<QVBoxLayout>
#include<QGridLayout>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWin; }

QT_END_NAMESPACE

class MainWin : public QMainWindow
{
    Q_OBJECT

public:
    MainWin(QWidget *parent = nullptr);
    ~MainWin();

    static QString path;
    static bool saveAs;
    void openFile();
    void saveFile();
    void newFile();
    void saveAsFile();
    void openSearch();
    void search();
    void searchBack();
//    void showError(QString message);
    bool m_isTextChanged;
    void initMainEditor();
    void onTextChanged();
    void checkChanged();
    int showQueryMessage(QString message);
    void closeEvent(QCloseEvent *ev);
private:
    Ui::MainWin *ui;
    QTextEdit textEd;
    QDialog *findDlg;
    QLineEdit *findLineEdit;
};
#endif // MAINWIN_H
