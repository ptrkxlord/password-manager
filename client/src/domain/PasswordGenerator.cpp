#include "PasswordGenerator.h"
#include <QRandomGenerator>

PasswordGenerator::PasswordGenerator(QObject *parent) : QObject(parent) {}

QString PasswordGenerator::generate(int length, bool useUpper, bool useNumbers, bool useSymbols)
{
    QString charset = "abcdefghijklmnopqrstuvwxyz";
    if (useUpper) charset += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (useNumbers) charset += "0123456789";
    if (useSymbols) charset += "!@#$%^&*()_+-=[]{}|;:,.<>?";

    QString password;
    for (int i = 0; i < length; ++i) {
        int index = QRandomGenerator::global()->bounded(charset.length());
        password.append(charset.at(index));
    }
    return password;
}
