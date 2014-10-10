#include <QFile>
#include <QApplication>
#include <QTextStream>
#include <QSplitter>
#include <QWebFrame>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

#include "mainwindow.h"
#include "smp_parse.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow (parent)
{
    this->resize(1024, 600);

    // Show some sample markdown
    QFile markdownSampleText(":/markdown_sample.txt");
    markdownSampleText.open(QIODevice::ReadOnly);

    // Build the general layout
    m_MainLayout = new QVBoxLayout;

    // Build actions
    m_ActionNew = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
    m_ActionNew->setShortcuts(QKeySequence::New);
    m_ActionNew->setStatusTip(tr("Create a new file"));
    connect(m_ActionNew, SIGNAL(triggered()), this, SLOT(onActionNew()));

    m_ActionOpen = new QAction(QIcon(":/images/open.png"), tr("&Open Markdown file"), this);
    m_ActionOpen->setShortcuts(QKeySequence::Open);
    m_ActionOpen->setStatusTip(tr("Open Markdown file"));
    connect(m_ActionOpen, SIGNAL(triggered()), this, SLOT(onActionOpen()));

    m_ActionSave = new QAction(QIcon(":/images/save.png"), tr("&Save Markdown to file"), this);
    m_ActionSave->setShortcuts(QKeySequence::Save);
    m_ActionSave->setStatusTip(tr("Save Markdown to file"));
    connect(m_ActionSave, SIGNAL(triggered()), this, SLOT(onActionSave()));

    m_ActionExport = new QAction(QIcon(":/images/export.png"), tr("&Export HTML"), this);
    // m_ActionExport->setShortcuts(QKeySequence::New);
    m_ActionExport->setStatusTip(tr("Export HTML"));
    connect(m_ActionExport, SIGNAL(triggered()), this, SLOT(onActionExport()));

    m_ActionExit = new QAction(QIcon(":/images/exit.png"), tr("&Exit"), this);
    m_ActionExit->setShortcuts(QKeySequence::Quit);
    m_ActionExit->setStatusTip(tr("Exit"));
    connect(m_ActionExit, SIGNAL(triggered()), this, SLOT(onActionExit()));

    // Create the toolbar
    m_ToolBar = addToolBar(tr("File"));
    m_ToolBar->setMovable(false);

    m_ToolBar->addAction(m_ActionNew);
    m_ToolBar->addAction(m_ActionOpen);
    m_ToolBar->addAction(m_ActionSave);
    m_ToolBar->addSeparator();
    m_ToolBar->addAction(m_ActionExport);
    m_ToolBar->addSeparator();
    m_ToolBar->addAction(m_ActionExit);

    // Create the menu bar
    m_MenuBar = menuBar();
    QMenu * fileMenu = m_MenuBar->addMenu(tr("&File"));

    fileMenu->addAction(m_ActionNew);
    fileMenu->addAction(m_ActionOpen);
    fileMenu->addAction(m_ActionSave);
    fileMenu->addSeparator();
    fileMenu->addAction(m_ActionExport);
    fileMenu->addSeparator();
    fileMenu->addAction(m_ActionExit);

    // Create the source textbox
    m_TextBox = new QTextEdit();
    m_TextBox->setAcceptRichText(false);
    m_TextBox->setText(markdownSampleText.readAll());

    // Manually open the base CSS file and convert the contents to Base64
    QFile sourceCss(":/markdown_base.txt");
    sourceCss.open(QIODevice::ReadOnly);
    QByteArray sourceCssBase64 = sourceCss.readAll().toBase64();

    // Create the rendered view
    m_WebView = new QWebView();
    m_WebView->page()->settings()
        ->setUserStyleSheetUrl(QString("data:text/css;charset=utf-8;base64,") + QString::fromUtf8(sourceCssBase64));

    // Place the two widgets in a splitted view
    QSplitter * splitter = new QSplitter(this);
    splitter->addWidget(m_TextBox);
    splitter->addWidget(m_WebView);

    // Initially, assign the same size to each widget
    QList<int> sizes;
    sizes << 512 << 512;
    splitter->setSizes(sizes);

    // Add the splitted view to a layout
    m_PanelsLayout = new QHBoxLayout();
    m_PanelsLayout->addWidget(splitter);

    // Set the layout to the widgets
    // m_MainLayout->addWidget(m_ToolBar);
    m_MainLayout->addLayout(m_PanelsLayout);

    QWidget * wdg = new QWidget;
    wdg->setLayout(m_MainLayout);
    this->setCentralWidget(wdg);

    // Make sure markdown parsing is triggered when source text changes
    connect(m_TextBox, SIGNAL(textChanged()), this, SLOT(onTextChanged()));

    // Trigger the markdown parsing
    onTextChanged();
}

MainWindow::~MainWindow()
{
    delete m_MainLayout;
    delete m_TextBox;
    delete m_WebView;
    delete m_ToolBar;
}

void MainWindow::onActionExit ()
{
    QApplication::quit();
}

void MainWindow::onActionNew ()
{
    m_TextBox->clear();
}

void MainWindow::onActionOpen ()
{
    QFileDialog dialog (this, tr("Load Markdown"));
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setDefaultSuffix("md");
    dialog.setNameFilter(tr("Markdown (*.markdown *.mdown *.mkdn *.mkd *.md)"));

    if (!dialog.exec()) {
        return;
    }

    QStringList fileNames;
    fileNames = dialog.selectedFiles();

    QFile inputFile (fileNames[0]);

    if (!inputFile.open(QIODevice::ReadOnly)) {
        QMessageBox messageBox;
        messageBox.critical(0,"Error", QString("Can't read from file ")
            + fileNames[0]);
    }

    m_TextBox->setText(inputFile.readAll());

    // QTextStream inputStream (&inputFile);
    // inputStream << m_TextBox->toPlainText();
    // // outputStream << m_GeneratedMarkdown;
}

void MainWindow::onActionSave ()
{
    QFileDialog dialog (this, tr("Save Markdown"));
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setAcceptMode (QFileDialog::AcceptSave);
    dialog.setDefaultSuffix("md");
    dialog.setNameFilter(tr("Markdown (*.markdown *.mdown *.mkdn *.mkd *.md)"));

    if (!dialog.exec()) {
        return;
    }

    QStringList fileNames;
    fileNames = dialog.selectedFiles();

    QFile outputFile (fileNames[0]);

    if (!outputFile.open(QIODevice::WriteOnly)) {
        QMessageBox messageBox;
        messageBox.critical(0,"Error", QString("Can't write to file ")
            + fileNames[0]);
    }

    QTextStream outputStream (&outputFile);
    outputStream << m_TextBox->toPlainText();
    // outputStream << m_GeneratedMarkdown;
}

void MainWindow::onActionExport ()
{
    QFileDialog dialog (this, tr("Export HTML"));
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setAcceptMode (QFileDialog::AcceptSave);
    dialog.setDefaultSuffix("html");
    dialog.setNameFilter(tr("HTML (*.html *.htm)"));

    if (!dialog.exec()) {
        return;
    }

    QStringList fileNames;
    fileNames = dialog.selectedFiles();

    QFile outputFile (fileNames[0]);

    if (!outputFile.open(QIODevice::WriteOnly)) {
        QMessageBox messageBox;
        messageBox.critical(0,"Error", QString("Can't write to file ")
            + fileNames[0]);
    }

    QTextStream outputStream (&outputFile);
    // outputStream << m_TextBox->toPlainText();
    outputStream << m_GeneratedMarkdown;
}
void MainWindow::onTextChanged()
{
    // Save current scroll position
    int previousScrollPosition = m_WebView->page()->mainFrame()
        ->scrollBarValue(Qt::Vertical);

    // Parse the markdown
    m_GeneratedMarkdown = parseMarkdown(m_TextBox->toPlainText());

    // Set the HTML to the WebView
    m_WebView->setHtml(m_GeneratedMarkdown);

    // Restore scroll position
    m_WebView->page()->mainFrame()
        ->setScrollBarValue(Qt::Vertical, previousScrollPosition);
}
