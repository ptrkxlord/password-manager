#include <QtTest>
#include "../domain/PasswordGenerator.h"

class TestPasswordGenerator : public QObject
{
    Q_OBJECT
private slots:
    void testLength() {
        PasswordGenerator gen;
        QString pwd = gen.generate(12, true, true, true);
        QCOMPARE(pwd.length(), 12);
    }
    
    void testNoNumbers() {
        PasswordGenerator gen;
        QString pwd = gen.generate(10, true, false, false);
        for (QChar c : pwd) {
            QVERIFY(!c.isDigit());
        }
    }
};

QTEST_MAIN(TestPasswordGenerator)
#include "test_pwdgen.moc"
