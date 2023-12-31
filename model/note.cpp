#include "model/note.h"
#include "com/global.h"

Note::Note() {
};

QString Note::toString() {
    return ut::str::mapToStr(toVMap());
}

QVariantMap Note::toVMap(bool parse, uint maxWidth) {
    QVariantMap m;
    m.insert("id", id);
    m.insert("book", book);
    m.insert("author", author);
    m.insert("wid", wid);
    m.insert("time", time);
    m.insert("pos0", pos0);
    m.insert("pos1", pos1);
    cont = cont.replace("\r", "\n");
    m.insert("cont", cont);
    if(parse) {
//        m.insert("html", doc_parser->parseHtml(cont));
        m.insert("qmls", doc_parser->parseQML(cont, maxWidth));
    }
    m.insert("imgs", extractImgs(cont));
    m.insert("tags", tags);
    m.insert("bj", bj);
    m.insert("refids", refids);
    m.insert("refimgids", refimgids);
    return m;
}
