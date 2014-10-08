#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QHBoxLayout>
#include <QTextEdit>
#include <QWebView>

#if QT_VERSION >= 0x050000
// #include <QtWidgets/QDockWidget>
#include <QtWebKitWidgets>
#else
#include <QtGui/QDockWidget>
#endif

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
};

#endif // MAINWINDOW_H
