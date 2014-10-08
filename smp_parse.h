#ifndef SMP_PARSE_H
#define SMP_PARSE_H

#include <QString>
#include <QByteArray>
#include <QDebug>

extern "C"
{
    #include <markdown.h>
}

QString parseMarkdown (QString source)
{
    // Get source markdown text
    QByteArray plainText = source.toUtf8();
    int plainTextSize = plainText.size();
    const char * plainTextData = plainText.constData();

    // Build a document
    Document * doc = mkd_string (plainTextData, plainTextSize, 0);

    // Compile the document
    mkd_compile(doc, 0);

    // Get the generated HTML
    char * outputText;
    int outputSize = mkd_document(doc, &outputText);

    // Build the output string
    QString result = QString::fromUtf8(outputText, outputSize);

    // Cleanup temporary structures
    mkd_cleanup(doc);

    return result;
}

#endif // SMP_PARSE_H
