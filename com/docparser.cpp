#include "docparser.h"
#include "com/global.h"
#include "libxxmoon.h"
#include <QWindow>
#include <QRegularExpression>

DocParser::DocParser() {
    tags << DocParser::DocTag::create(DocParser::TY_QUOTE);
    tags << DocParser::DocTag::create(DocParser::TY_CODE);
    tags << DocParser::DocTag::create(DocParser::TY_IMG);
}

QString DocParser::parseHtml(QString s, uint maxWidth) {
    QStringList l = parse0(false, s, maxWidth);
    QString html = "";
    for(QString& s:l) {
        html += s;
    }
    return html;
}

QStringList DocParser::parseQML(QString s, uint maxWidth) {
    return parse0(true, s, maxWidth);
}

void DocParser::addQmlList(QStringList& l, Doc& doc, uint maxWidth) {
//    qDebug() << "addQmlList" << doc.cont << doc.ty;
    if(maxWidth <= 0) {
        QWindow *w = qobject_cast<QWindow *>(engine->rootObjects().at(0));
        maxWidth = w->width() - 20;
    } else {
        maxWidth -= 20;
    }
    doc.cont = doc.cont.replace("\\", "\\\\");
    QString css = "<style>*{margin:0;padding:0;}h1,h2,h3{color:black;}b{color:#303030;}</style>";
    if(doc.ty == DocParser::TY_TEXT) {
        doc.cont = txtKeepPre(doc.cont.toHtmlEscaped());
        QString html = parseTxtHtml(doc.cont, maxWidth);
        html = doESC(html);
        html = css+filterQml(html).trimmed();
        QString s = QString("Txt{text:\"%1\";width:parent?parent.width:0}")
                .arg(html);
        l << s;
    } else if(doc.ty == DocParser::TY_IMG) {
        QVariantList vl = calWinHeight(doc.cont, maxWidth);
        QString s = QString("Img{src:\"%1/%2\";width:Math.min(parent?parent.width:0, %3);height:%4}")
                .arg(getFilePre() + cfg->imgDir,
                     doc.cont.trimmed(),
                     vl.at(1).toString(),
                     vl.at(2).toString());
        l << s;
    } else if(doc.ty == DocParser::TY_QUOTE) {
        doc.cont = txtKeepPre(doc.cont.toHtmlEscaped());
        QString html = parseTxtHtml(doc.cont.trimmed(), maxWidth);
        html = doESC(html);
        html = (css+filterQml(html)).trimmed();
        QString s = QString("Quote{text:\"%1\";width:parent?parent.width:0;color:'%2';textColor:'%3';}")
                        .arg(html, cfg->uiQuoteBgColor, cfg->uiQuoteTextColor);
        l << s;
    } else if(doc.ty == DocParser::TY_CODE) {
        QString cont = doc.cont.trimmed();
        cont = cont.replace("\t", "   ");
        int i = cont.indexOf("\n");
        QString code = cont.mid(0, i);
        QString src = cont.mid(i+1);
        QString html = Highlight(src.toUtf8().data(), code.toUtf8().data());
        //fix bug:3018
        if(!src.endsWith("\n")) {
            html = html.replace("\n</span></pre>", "</span></pre>");
        }
        //
        QString s = QString("Code{text:'%1';width:parent?parent.width:0;color:'%2';}").arg(html, "#ECECEC");
        l << s;
    } else {
        l << doc.cont.trimmed();
    }
//    qDebug() << l.at(l.size()-1).toUtf8().data();
}
void DocParser::addHtmlList(QStringList& l, Doc& doc, uint maxWidth) {
    if(maxWidth <= 0) {
        QWindow *w = qobject_cast<QWindow *>(engine->rootObjects().at(0));
        maxWidth = w->width() - 20;
    } else {
        maxWidth -= 20;
    }
    doc.cont = doc.cont.replace("\\", "\\\\");
    if(doc.ty == TY_TEXT) {
        doc.cont = txtKeepPre(doc.cont.toHtmlEscaped());
        QString html = parseTxtHtml(doc.cont, maxWidth);
        html = doESC(html);
        html = filterHtml(html).trimmed();
        l << html;
    } else if(doc.ty == DocParser::TY_IMG) {
        QString x = "!("+doc.cont+")\n";
        QString html = filterHtml(parseImgHtml(x, maxWidth)).trimmed();
        l << html;
    } else if(doc.ty == DocParser::TY_QUOTE) {
        doc.cont = doc.cont.toHtmlEscaped();
        QString x = "```\n"+doc.cont.trimmed()+"```\n";
        QString html = parseQuoteHtml(x, maxWidth);
        html = doESC(html);
        html = filterHtml(html);
        l << html;
    } else if(doc.ty == DocParser::TY_CODE) {
        QString cont = doc.cont.trimmed();
        int i = cont.indexOf("\n");
        QString code = cont.mid(0, i);
        QString src = cont.mid(i+1);
        QString html = Highlight(src.toUtf8().data(), code.toUtf8().data());
//        html = html.replace("\"", "\\\"");
        QString x = "```"+code+"\n"+html+"```\n";
        html = parseCodeHtml(x, maxWidth);
        l << html;
    } else {
        l << doc.cont.trimmed();
    }
}

//```\na\n```\n\n# b
QStringList DocParser::parse0(bool qml, QString s, uint maxWidth) {
    s += "\n";//先在尾部加个\n，以好匹配那些以\n结尾的标签但又出现在了尾部，解析完如果还在的话再在最后一个元素中去掉
    QList<Doc> list;
    int start = 0;
    while(true) {
        int i0 = -1;//头标签开始
        int i1 = -1;//尾标签开始
        int tagsIndex = 0;
        for(int i = 0; i < tags.size(); i++) {
            DocTag dt = tags.at(i);
            int i0_ = s.indexOf(dt.tag0, start);
            if(i0_ >= 0) {
                int i1_ = s.indexOf(dt.tag1, i0_+dt.tag0.size());
                if(i1_ >= 0) {
                    if((i0 < 0 || i0_ < i0) && (i1 < 0 || i1_ < i1)) {
                        i0 = i0_;
                        i1 = i1_;
                        tagsIndex = i;
                        // break; //这个break不能加上，不是找到一个就结束了，而是所有标签都检查一遍再用最前面的
                    }
                }
            }
        }

        if(i0 >= 0 && i1 >= 0) {
            QString text = "";
            if(i0 > start) {
                text = s.mid(start, i0-start);
            }
            //
            DocTag dt = tags.at(tagsIndex);
            int tag0Len = dt.tag0.length();
            int tag1Len = dt.tag1.length();
            if(i1 > i0+tag0Len) {
                int ty = dt.ty;
                QString cont = s.mid(i0+tag0Len, i1-i0-tag0Len);
                if(i0 > 0) {
                    if(s.at(i0-1) == '`') {
                        ty = TY_TEXT;
                        cont = text + s.mid(i0,i1+tag1Len-i0);
                    }
                }
                if(ty != TY_TEXT && text != "") {
                    Doc doc(TY_TEXT, text);
                    list << doc;
                }
                Doc doc(ty, cont);
                list << doc;
            }
            //
            int start_ = i1 + tag1Len;
            if(start_ > start) {
                start = start_;
            }
        } else {
            if(s.size() > start) {
                Doc doc(TY_TEXT,s.right(s.size() - start));
                list << doc;
            }
            break;
        }
    }

    QList<Doc> newList;
    //合并Txt类型的
    for(int i = 0; i < list.size(); i++) {
        Doc doc = list.at(i);
        Doc lastDoc;
        int lastNewListIndex = newList.size()-1;
        if(newList.size() > 0) {
            lastDoc = newList.at(lastNewListIndex);
        }
        if(lastDoc.ty > 0 && doc.ty == lastDoc.ty && doc.ty == TY_TEXT) {
            lastDoc.cont += doc.cont;
            newList[lastNewListIndex] = lastDoc;
        } else {
            newList << doc;
        }
    }

    //处理Quote/Code/Img块前面的Txt紧接着的非块级元素后面的\n去掉一个
    for(int i = 0; i < newList.size(); i++) {
        Doc doc = newList.at(i);
        if(doc.ty == TY_TEXT) {
            //如果下一个元素是引用块或代码块或图片
            if(i+1 < newList.size()) {
                Doc nextDoc = newList.at(i+1);
                if(nextDoc.ty == TY_QUOTE || nextDoc.ty == TY_CODE || nextDoc.ty == TY_IMG) {
                    //如果前面不是tag+\n作为标签1的话就去掉，否则不去掉因为本来匹配标签后就会去掉
                    static QRegularExpression re("(#{1,3}[-)]*\\s[^\n]+\n\n|(http|https|ftp|file)://[^\n]+\n\n|:\\[[^\n]+\\]\n\n|---\n\n)$");
                    QRegularExpressionMatch match = re.match(doc.cont);
                    if(!match.hasMatch()) {
                        doc.cont = doc.cont.mid(0, doc.cont.length()-1);
                        newList[i] = doc;
                    }
                }
            }
            //如果前一个元素是引用块或代码块或图片
            if(i-1 >= 0) {
                Doc preDoc = newList[i-1];
                if(preDoc.ty == TY_QUOTE || preDoc.ty == TY_CODE || preDoc.ty == TY_IMG) {
                    //如果开头是\n就直接去掉
                    if(doc.cont.startsWith("\n")) {
                        doc.cont = doc.cont.mid(1);
                        newList[i] = doc;
                    }
                }
            }
        }
    }

    for(int i = newList.size()-1; i >= 0; i--) {
        if(newList[i].ty == TY_TEXT && newList[i].cont.isEmpty()) {
            newList.remove(i);
        }
    }

    //解析完后去掉开始加的\n如果还在的话
    if(newList.size() > 0) {
        if(newList[newList.size()-1].cont.isEmpty()) {
            newList.remove(newList.size()-1);
        } else if(newList[newList.size()-1].cont.endsWith("\n")) {
            newList[newList.size()-1].cont = newList[newList.size()-1].cont.mid(0, newList[newList.size()-1].cont.length()-1);
            if(newList[newList.size()-1].cont.isEmpty()) {
                newList.remove(newList.size()-1);
            }
        }
    }

    QStringList l;
    for(Doc doc:newList) {
        if(qml) {
            addQmlList(l, doc, maxWidth);
        } else {
            addHtmlList(l, doc, maxWidth);
        }
    }
    return l;
}
QString fixUrl4Escaped(QString& url) {
    return url.replace("&amp;", "&");
}
QVariantList eachTag(const QString& srcTag1, const QString& srcTag2, const QString& dstTag1, const QString& dstTag2, QString k, const QString& param) {
    if(srcTag1 == "![") {
        int i = k.lastIndexOf(":");
        int n = 0;
        if(k.startsWith(HTTP_PRE)){
            n = 4;
        } else if(k.startsWith(HTTPS_PRE)){
            n = 5;
        } else if(Reg_Win_Path.match(k).hasMatch()){
            n = 1;
        }
        if(i > n) {
            QString url = k.mid(0, i);
            k = k.mid(i+1);
            return {k, fixUrl4Escaped(url)};
        } else {
            return {k, fixUrl4Escaped(k)};
        }
    } else if(srcTag1 == HTTP_PRE || srcTag1 == HTTPS_PRE || srcTag1 == "file://" || srcTag1 == "ftp://") {
        return {fixUrl4Escaped(k)};
    } else if(srcTag1 == "!(") {
        uint maxWidth = param.toUInt();
        return calWinHeight(k, maxWidth);
    } else if(srcTag1 == "```" && srcTag2=="```\n") {
        int i = k.indexOf("\n");
        QString code = k.mid(0, i);
        QString src = k.mid(i+1);
//        src = src.replace("", "");
        return {src, code};
    } else if(srcTag1 == "@#" && srcTag2 == "@") {
//        qDebug() << "eachTag :::::::::: " << k;
        int i = k.indexOf("&nbsp;");
        QString color = "red";
        if(i >= 0) {
            color = k.mid(0, i);
            k = k.mid(i+6);
        }
        return {k, color};
    } else if(srcTag1 == "---\n" && srcTag2 == "---\n") {
        QStringList lines = k.split("\n");
        QString html = "";
        for(QString& line: lines) {
            if(!line.isEmpty() && line != "<br/>") {
                QString tr = "";
                QStringList tds = line.split("|");
                for(QString& td:tds) {
                    tr += "<td>"+td+"</td>";
                }
                html += "<tr>"+tr+"</tr>";
            }
        }
        return {html};
    }
    return {};
}
QString DocParser::txtKeepPre(QString s) {
    return s.replace(" ","&nbsp;")
            .replace("\t","&nbsp;&nbsp;&nbsp;&nbsp;");
}

/*
1. b下面会多一个br
-------------------------------------------------------
# a

b

http://c
-------------------------------------------------------
# a\n\nb\n\nhttp://c
<h1>a</h1><br>b<br><br><div><a href='http://c'>http://c</a></div>

这个b下面也会多一个br
-------------------------------------------------------
# a

b

# c
-------------------------------------------------------
# a\n\nb\n\n# c
<h1>a</h1><br>b<br><br><h1>c</h1>
-------------------------------------------------------

结论：块元素本来就有换行功能，块元素前面的\n本来是用来换行用的，此时就变成换了两次行，
非块元素与块元素之间的\n，如果块元素前面有\n应该处理为减少一个\n
而当标签最后一个字符本来就是\n时，此元素与块元素之间的\n不用减少，因为那个\n本来就会换成html标签后消失
注：引用块与代码块也属于这个情况，相当于块元素带自动换行，但不在同一个qml元素中，得在其它地方再处理

2. 最后一个空行比前两个空行短，都是一个br
-------------------------------------------------------
# a

# b

http://c

a
-------------------------------------------------------
<h1>a</h1><br><h1>b</h1><br><div><a href='http://c'>http://c</a></div><br>a
-------------------------------------------------------

结论：块元素间的br比非块元素间的br要高，这个没法调，设计如此。

3. 空行不见了
-------------------------------------------------------
# a

# b
-------------------------------------------------------
# a\n\n# b
<h1>a</h1><h1>b</h1>
-------------------------------------------------------

-------------------------------------------------------
# a

http://b
-------------------------------------------------------
# a\n\nhttp://b
<h1>a</h1><div><a href='http://b'>http://b</a></div>
-------------------------------------------------------

结论：两个相临块元素之间的\n不能全去掉，至少留一个
*/
QString DocParser::filterQml(QString s) {
    //用来先解决上面注释中第三种情况，先把这种情况的这样替换成空行，以免后面被全干掉了
    QString emptyLine = "<p style='line-height:20px'>&nbsp;</p>";
    QStringList arr = {"h1", "h2", "h3", "div", "p"};
    for(QString& tag : arr) {
        for(QString& tagx : arr) {
            s = s.replace("</"+tagx+">\n<"+tag,"</"+tagx+">"+emptyLine+"<"+tag);
        }
    }

    //解决上面注释中第一种情况
    //1. 先处理\n开头的情况，fix bug: 3088
    if(s.startsWith("\n")) {
        s = "<br>" + s.mid(1);
    }
    //2. 再处理不以\n开头的：xxxx\n<h1>b</h1>，不然光像下面这样替换会把上面\n开头的给替掉
    QString pattern = "(.*)(\n*)<%1";
    for(const QString& tag : arr) {
        QRegularExpression re(pattern.arg(tag));
        QRegularExpressionMatch match = re.match(s);
        while (match.hasMatch()) {
            QString captured1 = match.captured(1); // 第一个捕获组的内容（闭合标签）
            QString captured2 = match.captured(2); // 第二个捕获组的内容（换行符）

            //当第一个捕获组是以这些结尾时就不替换
            if(captured1.endsWith("</h1>") || captured1.endsWith("</h2>") || captured1.endsWith("</h3>")
                || captured1.endsWith("</div>") || captured1.endsWith("</p>") || captured1.endsWith("</table>")) {
                // 获取下一个匹配项的起始位置
                int matchStartNext = match.capturedEnd(0);
                // 继续寻找下一个匹配
                match = re.match(s, matchStartNext);
                continue;
            }

            // 如果有多个换行符，去掉一个，其余的保留
            if (captured2.length() > 1) {
                captured2.remove(0, 1); // 去掉第一个换行符
            } else {
                captured2.clear(); // 如果只有一个换行符，或者没有，则清空
            }

            // 构建替换字符串
            QString replacement = captured1 + captured2 + "<" + tag;

            // 执行替换
            int matchStart = match.capturedStart(0);
            int matchLength = match.capturedLength(0);
            s.replace(matchStart, matchLength, replacement);

            // 继续寻找下一个匹配
            match = re.match(s, matchStart + replacement.length());
        }
    }
    s = s.replace("\n<hr>", "<hr>");
    s = s.replace("<hr>\n", "<hr>");
    s = s.replace("\n","<br>");//不用br还不行，只有br才会在块元素后是空一行，在行内元素后是换行，而这个p元素都是空一行。
    // qDebug() << "filterQml" << s;
//    qDebug() << QString("-------------------------------------------------------").toUtf8().data();
    return s;
}
/*
软件中qt的html渲染与浏览器中的渲染效果不一致，分开处理
源文本：
a
http://b

qt有空行，浏览器没有。
---------------------------------------------------------------
浏览器中块元素后的一个<br>就会有空行，行内元素则要两个<br>才会有空行了。而qt中的textarea中试了下像没有块级元素的概念。
# h1                  - <h1>  块元素
## h2                 - <h2>  块元素
### h3                - <h3>  块元素
**blod**              - <b>   行内元素
```                   - <pre> 块元素
quote
```
!(img.jpg)            - <img> 行内元素
![http://x.cn:link]   - <a>   行内元素
![http://x.cn:link]   - <div> 块元素
:[annotation]         - <p>   块元素

这个函数要达到的效果：不管行内元素还是块元素，要与源文本中的一致，即之后的一个\n就是换行，再有多的\n就是空行。
如果统一把所有\n换成<br/>，那块元素后的一个空行（即两个\n）就会变成两个空行，而行内元素则表现一致，两个\n对应两个<br>，都是换行并空一行。
所以要针对块元素专门处理：即块元素后的\n与<br>对应的数，<br>要少一个。（h1,h2,h3这几个本来在之前就把这行末尾的\n给去掉了，所以这里不用处理了）
*/
QString DocParser::filterHtml(QString s) {
///   qDebug() << "------------------------------";
    // qDebug() << "filterHtml" << s;
//    qDebug() << "------------------------------";
//    s = s.replace("</h1>\n","</h1>");
//    s = s.replace("</h2>\n","</h2>");
//    s = s.replace("</h3>\n","</h3>");
    // if(s.endsWith("\n")) {
    //     s = s.mid(0, s.length()-1);
    // }
    s = s.replace("</pre>\n","</pre>");
    s = s.replace("</p>\n","</p>");
//    s = s.replace("\n","<p class='br'></p>");
    s = s.replace("\n<hr>\n", "<hr>");
    s = s.replace("\n","<br>");//不用br还不行，只有br才会在块元素后是空一行，在行内元素后是换行，而这个p元素都是空一行。
    // qDebug() << "filterHtml" << s;
    return s;
}

//`xxx -> xxx
//``xxx -> `xxx
//```xxx -> ``xxx
QString DocParser::doESC(QString s) {
//    qDebug() << "doESC" << s;
    QString x = "";
    QString tag = "";
    for(int i = 0; i < s.length(); i++) {
        if(s[i] == '`') {
            tag += s[i];
        } else {
            if(tag != "") {
                x += tag.mid(1);
            }
            x += s[i];
            tag = "";
        }
    }
    return x;
}
QString DocParser::parseTxtHtml(QString s, uint maxWidth) {
    // qDebug() << ":" << s;
    QString blank = "&nbsp;";
    QString param = QString::number(maxWidth);
//    qDebug() << "parseTxtHtml-------------->>>" << s;
    s += "\n";//在末尾加个换行，以匹配# x这种，最后再去掉这个换行，如果还在的话，还在说明没有匹配到，不在说明被替换了。
    s = ut::str::replaceAllTag(s, "#"+blank,"\n", "<h1>", "</h1>");
    s = ut::str::replaceAllTag(s, "#-"+blank,"\n", "<h1 style='text-align: center;'>", "</h1>");
    s = ut::str::replaceAllTag(s, "#)"+blank,"\n", "<h1 style='text-align: right;'>", "</h1>");
//    qDebug() << "parseTxtHtml-------------->>>" << s;
    s = ut::str::replaceAllTag(s, "##"+blank,"\n", "<h2>", "</h2>");
    s = ut::str::replaceAllTag(s, "##-"+blank,"\n", "<h2 style='text-align: center;'>", "</h2>");
    s = ut::str::replaceAllTag(s, "##)"+blank,"\n", "<h2 style='text-align: right;'>", "</h2>");
    s = ut::str::replaceAllTag(s, "###"+blank,"\n", "<h3>", "</h3>");
    s = ut::str::replaceAllTag(s, "###-"+blank,"\n", "<h3 style='text-align: center;'>", "</h3>");
    s = ut::str::replaceAllTag(s, "###)"+blank,"\n", "<h3 style='text-align: right;'>", "</h3>");
    //用<div>是为了html导出时方便控制，<br/>不受控制
    s = ut::str::replaceAllTag(s, "http://","\n", "<div><a href='http://{0}'>http://", "</a></div>", 0, param, "", eachTag);
    s = ut::str::replaceAllTag(s, "https://","\n", "<div><a href='https://{0}'>https://", "</a></div>", 0, param, "", eachTag);
    s = ut::str::replaceAllTag(s, "ftp://","\n", "<div><a href='ftp://{0}'>ftp://", "</a></div>", 0, param, "", eachTag);
    s = ut::str::replaceAllTag(s, "file://","\n", "<div><a href='file://{0}'>file://", "</a></div>", 0, param, "", eachTag);
    s = ut::str::replaceAllTag(s, "![","]", "<a href='{1}'>", "</a>", 1, param, "", eachTag);
    s = ut::str::replaceAllTag(s, "**","**", "<b>", "</b>", 1, param, "\n", eachTag);//匹配的串中间不能有\n
    s = ut::str::replaceAllTag(s, "@#","@", "<font color='{1}'>", "</font>", 1, param, "\n", eachTag);//匹配的串中间不能有\n
    s = ut::str::replaceAllTag(s, "---\n","---\n", "<table border='0' cellpadding='5' cellspacing='5' style='border-collapse:collapse;'>", "</table>", 0, param, "", eachTag);
    s = ut::str::replaceAllTag(s, "----","\n", "<hr>", "");
    s = ut::str::replaceAllTag(s, ":[","]\n", "<p style='color:gray;text-align: right;font-style: italic;'>", "</p>", 0, param, "", eachTag);
    s = ut::str::replaceAllTag(s, "~~","~~", "<s>", "</s>", 1, param, "\n", eachTag);//匹配的串中间不能有\n
    if(s.endsWith("\n")) {//最后再去掉这个换行，如果还在的话，还在说明没有匹配到，不在说明被替换了。
        s = s.mid(0, s.length()-1);
    }
    // qDebug() << ":" << s;
    return s;
}
QString DocParser::parseQuoteHtml(QString s, uint maxWidth) {
    QString param = QString::number(maxWidth);
    s = ut::str::replaceAllTag(s, "```\n","```\n", "<pre class='quote' style='background:"+cfg->uiQuoteBgColor
                               +";color:"+cfg->uiQuoteTextColor+";'>", "</pre>", 0, param, "", eachTag);
    return s;
}
QString DocParser::parseImgHtml(QString s, uint maxWidth) {
    QString param = QString::number(maxWidth);
//    s = ut::str::replaceAllTag(s, "!(",")\n", "<p><img src='file:///"+cfg->imgDir+"/", "' width='{1}' height='{2}'/><p/>", 0, param, "", eachTag);
    s = ut::str::replaceAllTag(s, "!(",")\n", "<p><img src='file:///"+cfg->imgDir+"/", "' width='{1}'/><p/>", 0, param, "", eachTag);
    return s;
}
QString DocParser::parseCodeHtml(QString s, uint maxWidth) {
    QString param = QString::number(maxWidth);
    s = ut::str::replaceAllTag(s, "```","```\n", "<div class='code'>", "</div>", 0, param, "", eachTag);
    return s;
}
