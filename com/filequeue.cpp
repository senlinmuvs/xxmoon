#include "filequeue.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>

FileQueue::FileQueue(const QString& file):file(file) {}

void FileQueue::enqueue(const QString& msg) {
    QMutexLocker locker(&mtx);
    QFile f(file);
    if (f.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&f);
        out << msg << "\n";
        f.close();
    }
    locker.unlock();
}
bool writeNumberToFile(const QString& filename, int number) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "write number failure" << filename << number;
        return false;
    }
    QTextStream out(&file);
    out << number;
    file.close();
    return true;
}
int readNumberFromFile(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return 0;
    }

    int number;
    QTextStream in(&file);
    in >> number;
    file.close();
    return number;
}
void FileQueue::dequeue(CB_BL_STR cb) {
    QString filex = file+POSTFIX_DOLOGX;
    {
        QMutexLocker locker(&mtx);
        QFile f(filex);
        if (!f.exists()) {
            QFile::rename(file, filex);
            QString filexn = file+POSTFIX_DOLOGXN;
            QFile::remove(filexn);
        }
    }

    QFile f(filex);
    if(f.exists()) {
        if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QString filexn = file+POSTFIX_DOLOGXN;
            uint startLine = readNumberFromFile(filexn);
            uint n = 0;
            QTextStream in(&f);
            while (!in.atEnd()) {
                QString msg = in.readLine();
                if(n < startLine) {
                    continue;
                }
                bool ok = cb(msg);
                if(ok) {
                    if(!writeNumberToFile(filexn, n)) {
                        return;
                    }
                } else {
                    qDebug() << "filequeue dequeue cb error stop";
                    return;
                }
                n++;
            }
            f.close();
            QFile::remove(filex);
            QFile::remove(filexn);
        }
    }
}
