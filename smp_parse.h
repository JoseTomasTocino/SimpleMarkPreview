#ifndef SMP_PARSE_H
#define SMP_PARSE_H

#include <markdown.h>

QString parseMarkdown(QString & source)
{
    // Get source markdown text
    QByteArray plainText = source.toUtf8();

    // Source markdown size
    int plainTextSize = plainText.size();

    // Build a document
    Document * doc = mkd_string(plainText.constData(), plainTextSize, 0);

    // Compile the document
    mkd_compile(doc, 0);

    // Get the generated HTML
    char * outputText;
    int outputSize = mkd_document(doc, &outputText);

    // Return the output string
    return QString::fromLocal8Bit(outputText, outputSize);
}

#endif // SMP_PARSE_H
