#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    this->resize(1024, 600);

    // Show some sample markdown
    QFile markdownSampleText(":/markdown_sample.txt");
    markdownSampleText.open(QIODevice::ReadOnly);

    // Create the source textbox
    m_TextBox = new QTextEdit();
    m_TextBox->setAcceptRichText(false);
    m_TextBox->setText(markdownSampleText.readAll());

    // Create the rendered view
    m_WebView = new QWebView();
    m_WebView->page()->settings()->setUserStyleSheetUrl(QUrl("qrc:///markdown_base.txt"));

    // Place the two widgets in a splitted view
    QSplitter * splitter = new QSplitter(this);
    splitter->addWidget(m_TextBox);
    splitter->addWidget(m_WebView);

    // Initially, assign the same size to each widget
    QList<int> sizes;
    sizes << 512 << 512;
    splitter->setSizes(sizes);

    // Add the splitted view to a layout
    m_MainLayout = new QHBoxLayout();
    m_MainLayout->addWidget(splitter);

    // Set the layout to the widgets
    this->setLayout(m_MainLayout);

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
}

void MainWindow::onTextChanged()
{
    // Save current scroll position
    int previousScrollPosition = m_WebView->page()->mainFrame()->scrollBarValue(Qt::Vertical);

    // Get source markdown text
    QByteArray plainText = m_TextBox->toPlainText().toUtf8();

    // Source markdown size
    int plainTextSize = plainText.size();

    // Build a document
    Document * doc = mkd_string(plainText.constData(), plainTextSize, 0);

    // Compile the document
    mkd_compile(doc, 0);

    // Get the generated HTML
    char * outputText;
    int outputSize = mkd_document(doc, &outputText);

    // Build the output string
    QString outputGood = QString::fromLocal8Bit(outputText, outputSize);

    // Set the HTML to the WebView
    m_WebView->setHtml(outputGood);

    // Restore scroll position
    m_WebView->page()->mainFrame()->setScrollBarValue(Qt::Vertical, previousScrollPosition);

    // Cleanup temporary structures
    mkd_cleanup(doc);

}
