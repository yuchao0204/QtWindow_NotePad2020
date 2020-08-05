#ifndef MAINWIN_H
#define MAINWIN_H

#include <QMainWindow>
#include<QTextEdit>

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
    void openFile();
    void saveFile();
    void newFile();
private:
    Ui::MainWin *ui;
    QTextEdit *textEd;
};
#endif // MAINWIN_H
