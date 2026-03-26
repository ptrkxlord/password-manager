#ifndef CLIPBOARDMANAGER_H
#define CLIPBOARDMANAGER_H

#include <QObject>
#include <QClipboard>
#include <QTimer>
#include <QGuiApplication>

class ClipboardManager : public QObject
{
    Q_OBJECT
public:
    explicit ClipboardManager(QObject *parent = nullptr);

    Q_INVOKABLE void setClipboardText(const QString &text, int timeoutMs = 30000);

private slots:
    void clearClipboard();

private:
    QTimer *m_timer;
};

#endif // CLIPBOARDMANAGER_H
