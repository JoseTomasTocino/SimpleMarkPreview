#ifndef SMP_PARSE_H
#define SMP_PARSE_H

#include <iostream>
#include <sstream>

#include <QString>
#include <QByteArray>
#include <QDebug>

#include <markdown.h>

QString parseMarkdown (QString source)
{
    // Build the source string
    std::string stdSource = source.toStdString();

    // Build the document
    markdown::Document d;

    // Feed the source string to the doc
    d.read(stdSource);

    // Build the target stream
    std::stringstream ostr_stream;

    d.writeTokens(std::cout);

    // Populate the target stream with the generated HTML
    d.write(ostr_stream);

    // Get the resulting string
    std::string stdResult = ostr_stream.str();

    return QString::fromStdString(stdResult);
}

#endif // SMP_PARSE_H
