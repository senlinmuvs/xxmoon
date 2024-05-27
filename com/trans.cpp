#include "trans.h"

#include "com/global.h"

Trans::Trans() {
    //菜单
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
    trans_zh_map.insert("Minimize", "最小化");
    trans_zh_map.insert("Zoom", "缩放");
    trans_zh_map.insert("How to use ...", "如何使用 ...");
    //关于
    trans_zh_map.insert("Data Path", "数据目录");
    trans_zh_map.insert("Please restart the app!", "请重启软件");
    trans_zh_map.insert("And copy the old data to the new directory.", "然后复制数据到新的目录");
    trans_zh_map.insert("Editor", "编辑器");
    trans_zh_map.insert("Pick Hotkey", "摘录快捷键");
    trans_zh_map.insert("xxmoon", "摘月");
    trans_zh_map.insert("Words", "字数");
    trans_zh_map.insert("Picture", "图片");
    trans_zh_map.insert("Search...", "搜索...");
    trans_zh_map.insert("Delete", "删除");
    trans_zh_map.insert("Generate PDF", "导出单个PDF");
    trans_zh_map.insert("Generate HTML", "导出单个HTML");
    trans_zh_map.insert("Generate XM", "导出单个XM");
    trans_zh_map.insert("Export Site", "导出站点");
    trans_zh_map.insert("Delete from Site", "从站点删除");
    trans_zh_map.insert("Detail", "详情");
    trans_zh_map.insert("Picture Model", "图片模式");
    trans_zh_map.insert("Copy content", "复制内容");
    trans_zh_map.insert("Out Edit", "外部编辑");
    trans_zh_map.insert("Exists Already", "已存在");
    trans_zh_map.insert("Can not delete, it not empty.", "不能删除，其下有内容！");
    trans_zh_map.insert("Book Name", "书籍名称");
    trans_zh_map.insert("Author Name", "作者名称");
    trans_zh_map.insert("Tag(separated by commas)", "标签(逗号分隔)");
    trans_zh_map.insert("Extra", "额外信息");
    trans_zh_map.insert("OK", "确定");
    trans_zh_map.insert("Sorting...", "待排序...");
    trans_zh_map.insert("solved ", "解决");
    trans_zh_map.insert("up ", "更新");
    trans_zh_map.insert("created ", "创建");
    trans_zh_map.insert("Import", "导入");
    trans_zh_map.insert("Close", "关闭");
    trans_zh_map.insert("Ensure delete?", "确定删除？");
    trans_zh_map.insert("Cancel", "取消");
    trans_zh_map.insert("Copy Link", "复制链接");
    trans_zh_map.insert("Reveal in File Manager", "在文件管理器中显示");
    trans_zh_map.insert("Quit", "退出");
    trans_zh_map.insert("Password", "密码");
    trans_zh_map.insert("Imported", "导入完成");
    trans_zh_map.insert("generated success.", "生成成功");
    trans_zh_map.insert("generated failure.", "生成失败");
    trans_zh_map.insert("More", "更多");
    trans_zh_map.insert("Done", "完成");
    trans_zh_map.insert("If you want to constantly switch between editing and preview, please enter the details first and then enter the editing, then C+W -> C+Enter -> C+W ...", "如果要在编辑与预览不断切换，请先进入详情再进入编辑，然后 C+W -> C+Enter -> C+W ...");
    trans_zh_map.insert("Input agian", "再次输入");
    trans_zh_map.insert("Two inputs are not equal!", "两次输入不相等");
    trans_zh_map.insert("Last imported path:", "上次导入路径：");
    trans_zh_map.insert("Failed to register %1. Error: %2", "");
    trans_zh_map.insert("Failed to unregister %1. Error: %2", "");
    trans_zh_map.insert("Failure.Not found the doc!", "失败，未找到此文档！");
    trans_zh_map.insert("Text", "文本");
    trans_zh_map.insert("Add Success!", "添加成功！");
    trans_zh_map.insert("Delete Success!", "删除成功！");
    trans_zh_map.insert("cert gen fail", "");
    trans_zh_map.insert("cert gen suc", "");
    trans_zh_map.insert("Zoom", "缩放");
    trans_zh_map.insert("How to use ...", "如何使用 ...");
    trans_zh_map.insert("Contact ...", "联系 ...");
    trans_zh_map.insert("Server", "服务器");
    trans_zh_map.insert("Disable Server", "关闭服务");
    trans_zh_map.insert("Enable Server", "开启服务");
    trans_zh_map.insert("Gen QR Code", "生成二维码");
    trans_zh_map.insert("Device", "设备");
    trans_zh_map.insert("Time", "时间");
    trans_zh_map.insert("Del", "删除");
    trans_zh_map.insert("input tag", "输入标签");
    trans_zh_map.insert("too long", "太长了");
    trans_zh_map.insert("Can not delete the default folder.", "不能删除默认文件夹！");
    trans_zh_map.insert("Can not edit encrypted content.", "不能修改已加密内容！");
    trans_zh_map.insert("decrypting...", "解密中...");
    trans_zh_map.insert("Finished", "完成");
    trans_zh_map.insert("encrypting...", "加密中...");
    trans_zh_map.insert("Sticky", "置顶");
    trans_zh_map.insert("Copy main image", "复制主图");
    trans_zh_map.insert("Copy main image link", "复制主图链接");
    trans_zh_map.insert("Encrypt | Decrypt", "加密 | 解密");
    trans_zh_map.insert("Export", "导出");
    trans_zh_map.insert("Export PDF", "导出PDF");
    trans_zh_map.insert("Export HTML", "导出HTML");
    trans_zh_map.insert("Export XM", "导出XM");
    trans_zh_map.insert("Clear Solved Time", "清除解决时间");
    trans_zh_map.insert("Success", "成功");
    trans_zh_map.insert("Cancel Sticky", "取消置顶");
    trans_zh_map.insert("Category Name", "分类名称");
    trans_zh_map.insert("Can not delete! found", "不能删除，有");
    trans_zh_map.insert("```referenced.", "引用！");
    trans_zh_map.insert("Failure", "失败");
    trans_zh_map.insert("Cant more than", "不能超过");
    trans_zh_map.insert("tags", "个标签");
    trans_zh_map.insert("yes", "是");
    trans_zh_map.insert("no", "否");
    trans_zh_map.insert("done", "完成");
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
