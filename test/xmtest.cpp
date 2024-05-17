#include "xmtest.h"

void XMTest::test_case1() {
    QVERIFY(true); // 确保条件为真
}

void XMTest::test_case2() {
    QCOMPARE(1 + 1, 2); // 比较两个值是否相等
}
