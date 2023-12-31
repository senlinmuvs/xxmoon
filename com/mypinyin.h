/*
0. 功能包括：自动分离姓名中的[姓,名]；姓名转拼音（一对一，首字母+全拼音）；姓名转拼音（一对多，首字母+全拼音）
1. 版本：V1.0   日期：2019年06月06日
2. 详情：
    https://blog.csdn.net/weixin_38887369/article/details/91047524   // 本开源项目介绍
    https://blog.csdn.net/weixin_38887369                            //
3. 版权所有 qq:2271590144,新月
4. 使用语言:c++,使用库：qt
5. qt库只使用了 qstring qstringlist qvector，如果你不想使用qt,直接使用标准的c++也可，只需要做很少的改动
   如果使用标准的c++库,改动如下：
   qstring     -> string
   qstringlist -> vector<string>
   qvector     -> vector
   a. cpp文件中的代码就300行左右,所以改动不多
   b. [vector,qvector],[string,qstring] 的相似度极高，很多函数都是一样的，所以改起来也容易
   c. 使用标准的string效率会更高
6. 实际运用测试：
    a. 已经商用，没什么问题
    b. 速度测试，环境：win10系统 + i5-8265U + 单线程下 + 每人3个字 ，很粗糙的速度测试结果如下
       getComPingyinForStr() => 50 人/ms
       getNamePingyin()      => 100人/ms
7. 使用方法：可以直接看本文件（.h文件）的注释 或 进入详情页面开，见第二条的网址

更新：
    V2.0 2020年04月10日：
    1. 更新c++版本，主要使用wstring
    2. 删除字库中的: ','
    3. 更改汉字判断规则，详情看isHanziChar(wchar_t wch);
*/
#pragma once

#include <string>
#include <vector>
using namespace std;


// ----- 外部使用 ----- //
/*
0. 获取组合拼音(一可能对多),用于搜索
1. eg:
    getComPingyinForStr("解红",fristPy,fullPy);    // fristPy =  "jg xg jh xh"  , fullPy =  "jiegong xiegong jiehong xiehong"
    getComPingyinForStr("查查",fristPy,fullPy);    // fristPy =  "cc zc cz zz"  , fullPy =  "chacha zhacha chazha zhazha"
    getComPingyinForStr("尉迟萌",fristPy,fullPy);  // fristPy =  "wcm ycm"  , fullPy =  "weichimeng yuchimeng"
    getComPingyinForStr("李石",fristPy,fullPy);    // fristPy =  "ld ls"  , fullPy =  "lidan lishi"
    getComPingyinForStr("小明",fristPy,fullPy);    // fristPy =  "xm"  , fullPy =  "xiaoming"
*/
int getComPingyinForStr(const wstring& inStr, wstring& outFrist_py, wstring& outFull_py);//ok
/*
0. 【姓、名】分别转拼音（严格的一一对应），用于汉字强转拼音
1. 使用了：姓氏特殊读音字库 + 多音字常用读音字库 + 全字库
2. eg:
    str = getNamePingyin("春",true);   // str => "chun"
    str = getNamePingyin("春",false);  // str => "chun"

    str = getNamePingyin("解",true);   // str => "xie"
    str = getNamePingyin("解",false);  // str => "jie"

    str = getNamePingyin("翟",true);   // str => "zhai"
    str = getNamePingyin("翟",false);  // str => "di"

    str = getNamePingyin("参",true);   // str => "can"
    str = getNamePingyin("参",false);  // str => "can"

    str = getNamePingyin("单于",true);   // str => "chanyu"
    str = getNamePingyin("单于",false);  // str => "danyu"
*/
wstring getNamePingyin(const wstring& inStr, bool isLastName);//ok
/*
0. 自动切分 姓、名
1. 基本只能应对普通的复姓（两个字），如果在复姓表中没有找到，则: 姓氏 = （fullName.size() == 4） ? fullName的前两个个字符 ： fullName的第一个字符
2. 备注：百度的姓氏基本就70多个，这里有90个，但是忽略的少数民族的姓氏，也不要认为复姓就是两个字，(《中国少数民族姓氏》汇总大概有1万多)
   例如：乌拉乌拉氏、爱新觉罗、钮钴禄、色氏、尼玛（我见过很多姓这个的）
3. eg:
    wcout << L"姓名拆分测试：" << endl;
    wstring names[13] = { L"东皇太一", L"尉迟小白", L"解波", L"卜艾", L"颜碧玉", L"句帅", L"杨红给", L"吕布", L"亚里士多缺德", L"覃黄埔", L"菊花拉姆", L"上官万", L"mack" };
    for (size_t i = 0; i < 13; i++)
    {
        wstring full, fist, last;
        full = names[i];
        myNameSplit(full, last, fist);
        wcout << full <<  L" => 姓:" << last  <<L" ,名:" << fist << endl;
    }

    // 结果
    姓名拆分测试：
    东皇太一	 => 姓:东皇 ,名:太一
    尉迟小白	 => 姓:尉迟 ,名:小白
    解波		 => 姓:解   ,名:波
    卜艾		 => 姓:卜   ,名:艾
    颜碧玉		 => 姓:颜   ,名:碧玉
    句帅		 => 姓:句   ,名:帅
    杨红给		 => 姓:杨   ,名:红给
    吕布         => 姓:吕   ,名:布
    亚里士多缺德 => 姓:亚   ,名:里士多缺德
    覃黄埔		 => 姓:覃   ,名:黄埔
    菊花拉姆     => 姓:菊花 ,名:拉姆
    上官万       => 姓:上官 ,名:万
    mack         => 姓:     ,名:mack
*/
void myNameSplit(const wstring& inFullName, wstring& outLastName, wstring& outFirstName);//ok


// ----- 内部部使用 ----- //
/*
0. 获取一个汉字的【所有】拼音(首字母、全拼)
1. 使用字库 ： hanziTables[]
2. 输出不会为空，除非输入就等于空
3. 如果输入为非中文字符，则返回和输入一样
4. inWord 只能输入一个汉字，否则返回-1
5. eg:
   getAllPingyinForWord("句",fristPy,fullPy); // fristPy => {"g","j"} , fullPy => {"gou","ju"}
   getAllPingyinForWord("龙",fristPy,fullPy); // fristPy => {"l"}     , fullPy => {"long"}
*/
int getAllPingyinForWord(const wstring& inWord, vector<wstring>& outFrist_py, vector<wstring>& outFull_py);
/*
0. 获取一个字的拼音,如果是多音字返回常用读音
1. 偏向于名的发音偏好,而不是姓氏的发音偏好
2. 输出不会为空，除非输入就等于空
3. 使用字库：multiToneWordTable[]（多音字库）+ hanziTables[]（全字库）
4. 如果输入为非中文字符，则返回和输入一样
5. 多音字的取舍规则见：multiToneWordTable[]
6. inWord 只能输入一个汉字，否则直接放回输入内容
7. eg:
   str = getNoRepeatPingyinForWord("大"); // str => "da"
   str = getNoRepeatPingyinForWord("解"); // str => "jie"
   str = getNoRepeatPingyinForWord("石"); // str => "shi"
*/
wstring getNoRepeatPingyinForWord(const wstring& inWord);
/*
0. 检查是否是汉字
1. 不同的编码方式、IDE，可能需要不同的设置值
*/
bool isHanziChar(wchar_t wch);
/*
0. 测试本字库在本环境下运行时的汉字的编码值
*/
void testHanziRang();
