#include "ClipboardManager.h"

ClipboardManager::ClipboardManager(QObject *parent) : QObject(parent)
{
    m_timer = new QTimer(this);
    m_timer->setSingleShot(true);
    connect(m_timer, &QTimer::timeout, this, &ClipboardManager::clearClipboard);
}

void ClipboardManager::setClipboardText(const QString &text, int timeoutMs)
{
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(text);
    
    m_timer->start(timeoutMs);
}

void ClipboardManager::clearClipboard()
{
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->clear();
}
