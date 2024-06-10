#include <QtTest>
#include "../client_interface/SHA512.h"
// add necessary includes here

class test1 : public QObject
{
    Q_OBJECT

public:
    test1();
    ~test1();

private slots:
    void test_case1();
};

test1::test1() {}

test1::~test1() {}

void test1::test_case1() {
    SHA512 sha512;
    QVERIFY("fa585d89c851dd338a70dcf535aa2a92fee7836dd6aff1226583e88e0996293f16bc009c652826e0fc5c706695a03cddce372f139eff4d13959da6f1f5d3eabe" == sha512.hash("12345678"));
    QVERIFY("73941847d9611927275d93139981ee78316de50bc51bf398f8ccdd778c7723f370cb252c5293c085ec3c6a3d185246837ed71d651a679cb680793581ad77ac24" == sha512.hash("qwer"));

}

QTEST_APPLESS_MAIN(test1)

#include "tst_test1.moc"
