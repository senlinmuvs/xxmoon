#include "trans.h"

#include "com/global.h"

Trans::Trans() {
    trans_zh_map.insert("File", "文件");
    trans_zh_map.insert("Edit", "编辑");
    trans_zh_map.insert("Window", "窗口");
    trans_zh_map.insert("Help", "帮助");
    trans_zh_map.insert("Open", "打开");
    trans_zh_map.insert("Undo", "撤销");
    trans_zh_map.insert("Redo", "重做");
    trans_zh_map.insert("Copy", "复制");
    trans_zh_map.insert("Paste", "粘贴");
    trans_zh_map.insert("Cut", "剪切");
    trans_zh_map.insert("Select All", "全选");
    trans_zh_map.insert("Minizime", "最小化");
    trans_zh_map.insert("Zoom", "最大化");
    trans_zh_map.insert("How to use ...", "如何使用 ...");
}

QString Trans::tr(QString k) {
    if(cfg->lang == "zh_CN") {
        QString v = trans_zh_map.value(k);
        if(v.length() > 0) {
            return v;
        }
        return k;
    }
    return k;
}
