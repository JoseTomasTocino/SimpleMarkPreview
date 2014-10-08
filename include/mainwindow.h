#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QHBoxLayout>
#include <QMainWindow>
#include <QTextEdit>
#include <QToolBar>
#include <QMenuBar>
#include <QWebView>
#include <QAction>

#if QT_VERSION >= 0x050000
// #include <QtWidgets/QDockWidget>
#include <QtWebKitWidgets>
#else
#include <QtGui/QDockWidget>
#endif

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow (QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onTextChanged();

    void onActionNew ();
    void onActionOpen ();
    void onActionSave ();
    void onActionExport ();
    void onActionExit ();

private:
    QVBoxLayout * m_MainLayout;
    QHBoxLayout * m_PanelsLayout;
    QTextEdit * m_TextBox;
    QWebView * m_WebView;

    QToolBar * m_ToolBar;
    QMenuBar * m_MenuBar;

    QAction * m_ActionNew;
    QAction * m_ActionOpen;
    QAction * m_ActionSave;
    QAction * m_ActionExport;
    QAction * m_ActionExit;

    QString m_GeneratedMarkdown;
};

#endif // MAINWINDOW_H
