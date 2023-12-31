#include "l.h"
#include "com/global.h"

L::L() : QObject(){

}

bool L::isDebug() {
    return lg->isDebug();
}
bool L::isTrace() {
    return lg->isTrace();
}
void L::trace(QString msg) {
    lg->trace(msg);
}
void L::debug(QString msg) {
    lg->debug(msg);
}
void L::info(QString msg) {
    lg->info(msg);
}
void L::warn(QString msg) {
    lg->warn(msg);
}
void L::error(QString msg) {
    lg->error(msg);
}
