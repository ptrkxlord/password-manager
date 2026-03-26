#ifndef PASSWORDGENERATOR_H
#define PASSWORDGENERATOR_H

#include <QObject>
#include <QString>

class PasswordGenerator : public QObject
{
    Q_OBJECT
public:
    explicit PasswordGenerator(QObject *parent = nullptr);

    Q_INVOKABLE QString generate(int length, bool useUpper, bool useNumbers, bool useSymbols);
};

#endif // PASSWORDGENERATOR_H
