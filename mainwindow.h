#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWebKitWidgets>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QWebView>

#include <markdown.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onTextChanged();

private:
    QHBoxLayout * m_MainLayout;
    QTextEdit * m_TextBox;
    QWebView * m_WebView;

    QByteArray m_MarkdownBase;
};

#endif // MAINWINDOW_H
