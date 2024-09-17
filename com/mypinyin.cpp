#include "mypinyin.h"

#define g_length_lastNameTable 554
#define g_length_multiToneWordTable 708
#define g_length_hanziTables 411

// 汉字-拼音
struct hanziTableS
{
    // 拼音
    wstring first_py;  // 首字母
    wstring full_py;   // 全拼

    // 汉字
    wstring hanzis;
};

// 特殊姓氏发音
struct lastNameTableS
{
    wstring hanzi;
    wstring pinyi;
};

// 常用多音字
struct multiToneWordTableS
{
    wstring hanzi;
    wstring pinyi;
};


/*
0. 姓氏特殊读音(包括：特殊、非特殊、复姓读音)
1. 可以自己添加
3. 来源于各种网络数据的整合
*/
lastNameTableS lastNameTable[g_length_lastNameTable] =
{
{ L"赵" , L"zhao" },
{ L"钱" , L"qian" },
{ L"孙" , L"sun" },
{ L"李" , L"li" },
{ L"周" , L"zhou" },
{ L"吴" , L"wu" },
{ L"郑" , L"zheng" },
{ L"王" , L"wang" },
{ L"冯" , L"feng" },
{ L"陈" , L"chen" },
{ L"褚" , L"chu" },
{ L"卫" , L"wei" },
{ L"蒋" , L"jiang" },
{ L"沈" , L"shen" },
{ L"韩" , L"han" },
{ L"杨" , L"yang" },
{ L"朱" , L"zhu" },
{ L"秦" , L"qin" },
{ L"尤" , L"you" },
{ L"许" , L"xu" },
{ L"何" , L"he" },
{ L"吕" , L"lv" },
{ L"施" , L"shi" },
{ L"张" , L"zhang" },
{ L"孔" , L"kong" },
{ L"曹" , L"cao" },
{ L"严" , L"yan" },
{ L"华" , L"hua" },
{ L"金" , L"jin" },
{ L"魏" , L"wei" },
{ L"陶" , L"tao" },
{ L"姜" , L"jiang" },
{ L"戚" , L"qi" },
{ L"谢" , L"xie" },
{ L"邹" , L"zou" },
{ L"喻" , L"yu" },
{ L"柏" , L"bai" },
{ L"水" , L"shui" },
{ L"窦" , L"dou" },
{ L"章" , L"zhang" },
{ L"云" , L"yun" },
{ L"苏" , L"su" },
{ L"潘" , L"pan" },
{ L"葛" , L"ge" },
{ L"奚" , L"xi" },
{ L"范" , L"fan" },
{ L"彭" , L"peng" },
{ L"郎" , L"lang" },
{ L"鲁" , L"lu" },
{ L"韦" , L"wei" },
{ L"昌" , L"chang" },
{ L"马" , L"ma" },
{ L"苗" , L"miao" },
{ L"凤" , L"feng" },
{ L"花" , L"hua" },
{ L"方" , L"fang" },
{ L"俞" , L"yu" },
{ L"任" , L"ren" },
{ L"袁" , L"yuan" },
{ L"柳" , L"liu" },
{ L"酆" , L"feng" },
{ L"鲍" , L"bao" },
{ L"史" , L"shi" },
{ L"唐" , L"tang" },
{ L"费" , L"fei" },
{ L"廉" , L"lian" },
{ L"岑" , L"cen" },
{ L"薛" , L"xue" },
{ L"雷" , L"lei" },
{ L"贺" , L"he" },
{ L"倪" , L"ni" },
{ L"汤" , L"tang" },
{ L"滕" , L"teng" },
{ L"殷" , L"yin" },
{ L"罗" , L"luo" },
{ L"毕" , L"bi" },
{ L"郝" , L"hao" },
{ L"邬" , L"wu" },
{ L"安" , L"an" },
{ L"常" , L"chang" },
{ L"乐" , L"yue" },
{ L"于" , L"yu" },
{ L"时" , L"shi" },
{ L"傅" , L"fu" },
{ L"皮" , L"pi" },
{ L"卞" , L"bian" },
{ L"齐" , L"qi" },
{ L"康" , L"kang" },
{ L"伍" , L"wu" },
{ L"余" , L"yu" },
{ L"元" , L"yuan" },
{ L"卜" , L"bu" },
{ L"顾" , L"gu" },
{ L"孟" , L"meng" },
{ L"平" , L"ping" },
{ L"黄" , L"huang" },
{ L"和" , L"he" },
{ L"穆" , L"mu" },
{ L"萧" , L"xiao" },
{ L"尹" , L"yin" },
{ L"姚" , L"yao" },
{ L"邵" , L"shao" },
{ L"湛" , L"zhan" },
{ L"汪" , L"wang" },
{ L"祁" , L"qi" },
{ L"毛" , L"mao" },
{ L"禹" , L"yu" },
{ L"狄" , L"di" },
{ L"米" , L"mi" },
{ L"贝" , L"bei" },
{ L"明" , L"ming" },
{ L"臧" , L"zang" },
{ L"计" , L"ji" },
{ L"伏" , L"fu" },
{ L"成" , L"cheng" },
{ L"戴" , L"dai" },
{ L"谈" , L"tan" },
{ L"宋" , L"song" },
{ L"茅" , L"mao" },
{ L"庞" , L"pang" },
{ L"熊" , L"xiong" },
{ L"纪" , L"ji" },
{ L"舒" , L"shu" },
{ L"屈" , L"qu" },
{ L"项" , L"xiang" },
{ L"祝" , L"zhu" },
{ L"董" , L"dong" },
{ L"梁" , L"liang" },
{ L"杜" , L"du" },
{ L"阮" , L"ruan" },
{ L"蓝" , L"lan" },
{ L"闵" , L"min" },
{ L"席" , L"xi" },
{ L"季" , L"ji" },
{ L"麻" , L"ma" },
{ L"强" , L"qiang" },
{ L"贾" , L"jia" },
{ L"路" , L"lu" },
{ L"娄" , L"lou" },
{ L"危" , L"wei" },
{ L"江" , L"jiang" },
{ L"童" , L"tong" },
{ L"颜" , L"yan" },
{ L"郭" , L"guo" },
{ L"梅" , L"mei" },
{ L"盛" , L"sheng" },
{ L"林" , L"lin" },
{ L"刁" , L"diao" },
{ L"钟" , L"zhong" },
{ L"徐" , L"xu" },
{ L"邱" , L"qiu" },
{ L"骆" , L"luo" },
{ L"高" , L"gao" },
{ L"夏" , L"xia" },
{ L"蔡" , L"cai" },
{ L"田" , L"tian" },
{ L"樊" , L"fan" },
{ L"胡" , L"hu" },
{ L"凌" , L"ling" },
{ L"霍" , L"huo" },
{ L"虞" , L"yu" },
{ L"万" , L"wan" },
{ L"支" , L"zhi" },
{ L"柯" , L"ke" },
{ L"昝" , L"zan" },
{ L"管" , L"guan" },
{ L"卢" , L"lu" },
{ L"莫" , L"mo" },
{ L"经" , L"jing" },
{ L"房" , L"fang" },
{ L"裘" , L"qiu" },
{ L"缪" , L"miao" },
{ L"干" , L"gan" },
{ L"解" , L"xie" },
{ L"应" , L"ying" },
{ L"宗" , L"zong" },
{ L"丁" , L"ding" },
{ L"宣" , L"xuan" },
{ L"贲" , L"ben" },
{ L"邓" , L"deng" },
{ L"郁" , L"yu" },
{ L"单" , L"shan" },
{ L"杭" , L"hang" },
{ L"洪" , L"hong" },
{ L"包" , L"bao" },
{ L"诸" , L"zhu" },
{ L"左" , L"zuo" },
{ L"石" , L"shi" },
{ L"崔" , L"cui" },
{ L"吉" , L"ji" },
{ L"钮" , L"niu" },
{ L"龚" , L"gong" },
{ L"程" , L"cheng" },
{ L"嵇" , L"ji" },
{ L"邢" , L"xing" },
{ L"滑" , L"hua" },
{ L"裴" , L"pei" },
{ L"陆" , L"lu" },
{ L"荣" , L"rong" },
{ L"翁" , L"weng" },
{ L"荀" , L"xun" },
{ L"羊" , L"yang" },
{ L"於" , L"yu" },
{ L"惠" , L"hui" },
{ L"甄" , L"zhen" },
{ L"曲" , L"qu" },
{ L"家" , L"jia" },
{ L"封" , L"feng" },
{ L"芮" , L"rui" },
{ L"羿" , L"yi" },
{ L"储" , L"chu" },
{ L"靳" , L"jin" },
{ L"汲" , L"ji" },
{ L"邴" , L"bing" },
{ L"糜" , L"mi" },
{ L"松" , L"song" },
{ L"井" , L"jing" },
{ L"段" , L"duan" },
{ L"富" , L"fu" },
{ L"巫" , L"wu" },
{ L"乌" , L"wu" },
{ L"焦" , L"jiao" },
{ L"巴" , L"ba" },
{ L"弓" , L"gong" },
{ L"牧" , L"mu" },
{ L"隗" , L"kui" },
{ L"山" , L"shan" },
{ L"谷" , L"gu" },
{ L"车" , L"che" },
{ L"侯" , L"hou" },
{ L"宓" , L"mi" },
{ L"蓬" , L"peng" },
{ L"全" , L"quan" },
{ L"郗" , L"xi" },
{ L"班" , L"ban" },
{ L"仰" , L"yang" },
{ L"秋" , L"qiu" },
{ L"仲" , L"zhong" },
{ L"伊" , L"yi" },
{ L"宫" , L"gong" },
{ L"宁" , L"ning" },
{ L"仇" , L"qiu" },
{ L"栾" , L"luan" },
{ L"暴" , L"bao" },
{ L"甘" , L"gan" },
{ L"钭" , L"tou" },
{ L"厉" , L"li" },
{ L"戎" , L"rong" },
{ L"祖" , L"zu" },
{ L"武" , L"wu" },
{ L"符" , L"fu" },
{ L"刘" , L"liu" },
{ L"景" , L"jing" },
{ L"詹" , L"zhan" },
{ L"束" , L"shu" },
{ L"龙" , L"long" },
{ L"叶" , L"ye" },
{ L"幸" , L"xing" },
{ L"司" , L"si" },
{ L"韶" , L"shao" },
{ L"郜" , L"gao" },
{ L"黎" , L"li" },
{ L"蓟" , L"ji" },
{ L"薄" , L"bo" },
{ L"印" , L"yin" },
{ L"宿" , L"su" },
{ L"白" , L"bai" },
{ L"怀" , L"huai" },
{ L"蒲" , L"pu" },
{ L"邰" , L"tai" },
{ L"从" , L"cong" },
{ L"鄂" , L"e" },
{ L"索" , L"suo" },
{ L"咸" , L"xian" },
{ L"籍" , L"ji" },
{ L"赖" , L"lai" },
{ L"卓" , L"zhuo" },
{ L"蔺" , L"lin" },
{ L"屠" , L"tu" },
{ L"蒙" , L"meng" },
{ L"池" , L"chi" },
{ L"乔" , L"qiao" },
{ L"阴" , L"yin" },
{ L"郁" , L"yu" },
{ L"胥" , L"xu" },
{ L"能" , L"nai" },
{ L"苍" , L"cang" },
{ L"双" , L"shuang" },
{ L"闻" , L"wen" },
{ L"莘" , L"shen" },
{ L"党" , L"dang" },
{ L"翟" , L"zhai" },
{ L"谭" , L"tan" },
{ L"贡" , L"gong" },
{ L"劳" , L"lao" },
{ L"逄" , L"pang" },
{ L"姬" , L"ji" },
{ L"申" , L"shen" },
{ L"扶" , L"fu" },
{ L"堵" , L"du" },
{ L"冉" , L"ran" },
{ L"宰" , L"zai" },
{ L"郦" , L"li" },
{ L"雍" , L"yong" },
{ L"郤" , L"xi" },
{ L"璩" , L"qu" },
{ L"桑" , L"sang" },
{ L"桂" , L"gui" },
{ L"濮" , L"pu" },
{ L"牛" , L"niu" },
{ L"寿" , L"shou" },
{ L"通" , L"tong" },
{ L"边" , L"bian" },
{ L"扈" , L"hu" },
{ L"燕" , L"yan" },
{ L"冀" , L"ji" },
{ L"郏" , L"jia" },
{ L"浦" , L"pu" },
{ L"尚" , L"shang" },
{ L"农" , L"nong" },
{ L"温" , L"wen" },
{ L"别" , L"bie" },
{ L"庄" , L"zhuang" },
{ L"晏" , L"yan" },
{ L"柴" , L"chai" },
{ L"瞿" , L"qu" },
{ L"阎" , L"yan" },
{ L"充" , L"chong" },
{ L"慕" , L"mu" },
{ L"连" , L"lian" },
{ L"茹" , L"ru" },
{ L"习" , L"xi" },
{ L"宦" , L"huan" },
{ L"艾" , L"ai" },
{ L"鱼" , L"yu" },
{ L"容" , L"rong" },
{ L"向" , L"xiang" },
{ L"古" , L"gu" },
{ L"易" , L"yi" },
{ L"慎" , L"shen" },
{ L"戈" , L"ge" },
{ L"廖" , L"liao" },
{ L"庾" , L"yu" },
{ L"终" , L"zhong" },
{ L"暨" , L"ji" },
{ L"居" , L"ju" },
{ L"衡" , L"heng" },
{ L"步" , L"bu" },
{ L"都" , L"du" },
{ L"耿" , L"geng" },
{ L"满" , L"man" },
{ L"弘" , L"hong" },
{ L"匡" , L"kuang" },
{ L"国" , L"guo" },
{ L"文" , L"wen" },
{ L"寇" , L"kou" },
{ L"广" , L"guang" },
{ L"禄" , L"lu" },
{ L"阙" , L"que" },
{ L"东" , L"dong" },
{ L"欧" , L"ou" },
{ L"殳" , L"shu" },
{ L"沃" , L"wo" },
{ L"利" , L"li" },
{ L"蔚" , L"wei" },
{ L"越" , L"yue" },
{ L"夔" , L"kui" },
{ L"隆" , L"long" },
{ L"师" , L"shi" },
{ L"巩" , L"gong" },
{ L"厍" , L"she" },
{ L"聂" , L"nie" },
{ L"晁" , L"chao" },
{ L"勾" , L"gou" },
{ L"句" , L"gou" },
{ L"敖" , L"ao" },
{ L"融" , L"rong" },
{ L"冷" , L"leng" },
{ L"訾" , L"zi" },
{ L"辛" , L"xin" },
{ L"阚" , L"kan" },
{ L"那" , L"na" },
{ L"简" , L"jian" },
{ L"饶" , L"rao" },
{ L"空" , L"kong" },
{ L"曾" , L"zeng" },
{ L"母" , L"mu" },
{ L"沙" , L"sha" },
{ L"乜" , L"nie" },
{ L"养" , L"yang" },
{ L"鞠" , L"ju" },
{ L"须" , L"xu" },
{ L"丰" , L"feng" },
{ L"巢" , L"chao" },
{ L"关" , L"guan" },
{ L"蒯" , L"kuai" },
{ L"相" , L"xiang" },
{ L"查" , L"zha" },
{ L"后" , L"hou" },
{ L"荆" , L"jing" },
{ L"红" , L"hong" },
{ L"游" , L"you" },
{ L"竺" , L"zhu" },
{ L"权" , L"quan" },
{ L"逯" , L"lu" },
{ L"盖" , L"gai" },
{ L"益" , L"yi" },
{ L"桓" , L"huan" },
{ L"公" , L"gong" },
{ L"万俟" , L"moqi" },
{ L"司马" , L"sima" },
{ L"上官" , L"shangguan" },
{ L"欧阳" , L"ouyang" },
{ L"夏侯" , L"xiahou" },
{ L"诸葛" , L"zhuge" },
{ L"闻人" , L"wenren" },
{ L"东方" , L"dongfang" },
{ L"赫连" , L"helian" },
{ L"皇甫" , L"huangpu" },
{ L"尉迟" , L"yuchi" },
{ L"公羊" , L"gongyang" },
{ L"澹台" , L"tantai" },
{ L"公冶" , L"gongye" },
{ L"宗政" , L"zongzheng" },
{ L"濮阳" , L"puyang" },
{ L"淳于" , L"chunyu" },
{ L"单于" , L"chanyu" },
{ L"太叔" , L"taishu" },
{ L"申屠" , L"shentu" },
{ L"公孙" , L"gongsun" },
{ L"仲孙" , L"zhongsun" },
{ L"轩辕" , L"xuanyuan" },
{ L"令狐" , L"linghu" },
{ L"钟离" , L"zhongli" },
{ L"宇文" , L"yuwen" },
{ L"长孙" , L"zhangsun" },
{ L"慕容" , L"murong" },
{ L"鲜于" , L"xianyu" },
{ L"闾丘" , L"luqiu" },
{ L"司徒" , L"situ" },
{ L"司空" , L"sikong" },
{ L"亓官" , L"qiguan" },
{ L"司寇" , L"sikou" },
{ L"仉督" , L"zhangdu" },
{ L"子车" , L"ziju" },
{ L"颛孙" , L"zhuansun" },
{ L"端木" , L"duanmu" },
{ L"巫马" , L"wuma" },
{ L"公西" , L"gongxi" },
{ L"漆雕" , L"qidiao" },
{ L"乐正" , L"yuezheng" },
{ L"壤驷" , L"rangsi" },
{ L"公良" , L"gongliang" },
{ L"拓跋" , L"tuoba" },
{ L"夹谷" , L"jiagu" },
{ L"宰父" , L"zaifu" },
{ L"榖梁" , L"guliang" },
{ L"晋" , L"jin" },
{ L"楚" , L"chu" },
{ L"闫" , L"yan" },
{ L"法" , L"fa" },
{ L"汝" , L"ru" },
{ L"鄢" , L"yan" },
{ L"涂" , L"tu" },
{ L"钦" , L"qin" },
{ L"段干" , L"duangan" },
{ L"百里" , L"baili" },
{ L"东郭" , L"dongguo" },
{ L"南门" , L"nanmen" },
{ L"呼延" , L"huyan" },
{ L"归" , L"gui" },
{ L"海" , L"hai" },
{ L"羊舌" , L"yangshe" },
{ L"微" , L"wei" },
{ L"生" , L"sheng" },
{ L"岳" , L"yue" },
{ L"帅" , L"shuai" },
{ L"缑" , L"gou" },
{ L"亢" , L"kang" },
{ L"况" , L"kuang" },
{ L"后" , L"hou" },
{ L"有" , L"you" },
{ L"琴" , L"qin" },
{ L"梁丘" , L"liangqiu" },
{ L"左丘" , L"zuoqiu" },
{ L"东门" , L"dongmen" },
{ L"西门" , L"ximen" },
{ L"商" , L"shang" },
{ L"牟" , L"mou" },
{ L"佘" , L"she" },
{ L"佴" , L"nai" },
{ L"伯" , L"bo" },
{ L"赏" , L"shang" },
{ L"南宫" , L"nangong" },
{ L"墨" , L"mo" },
{ L"哈" , L"ha" },
{ L"谯" , L"qiao" },
{ L"笪" , L"da" },
{ L"年" , L"nian" },
{ L"爱" , L"ai" },
{ L"阳" , L"yang" },
{ L"佟" , L"tong" },
{ L"第五" , L"diwu" },
{ L"言" , L"yan" },
{ L"福" , L"fu" },
{ L"黑" , L"he" },
{ L"区" , L"ou" },
{ L"朴" , L"piao" },
{ L"繁" , L"po" },
{ L"员" , L"yun" },
{ L"蕃" , L"pi" },
{ L"种" , L"chong" },
{ L"秘" , L"bi" },
{ L"谌" , L"chen" },
{ L"啜" , L"chuai" },
{ L"邸" , L"di" },
{ L"苻" , L"fu" },
{ L"甫" , L"fu" },
{ L"杲" , L"gao" },
{ L"艮" , L"gen" },
{ L"冠" , L"guan" },
{ L"妫" , L"gui" },
{ L"过" , L"guo" },
{ L"晟" , L"cheng" },
{ L"隽" , L"juan" },
{ L"逢" , L"pang" },
{ L"邳" , L"pi" },
{ L"莆" , L"pu" },
{ L"溥" , L"pu" },
{ L"亓" , L"qi" },
{ L"少" , L"shao" },
{ L"召" , L"shao" },
{ L"折" , L"she" },
{ L"彤" , L"tong" },
{ L"庹" , L"tuo" },
{ L"宛" , L"wan" },
{ L"尉" , L"wei" },
{ L"冼" , L"xian" },
{ L"洗" , L"xian" },
{ L"郇" , L"xun" },
{ L"幺" , L"yao" },
{ L"郧" , L"yun" },
{ L"恽" , L"yun" },
{ L"郓" , L"yun" },
{ L"羊角" , L"yangjue" },
{ L"妘" , L"yun" },
{ L"祭" , L"zhai" },
{ L"砦" , L"zhai" },
{ L"占" , L"zhan" },
{ L"仉" , L"zhang" },
{ L"中行" , L"zhonghang" },
{ L"禚" , L"zhuo" },
{ L"迮" , L"ze" },
{ L"覃" , L"qin" },
};

/*
0. 多音字表
1. 后面的注释表示的是：这个字剩余的其他读音 （日、韩分别表示汉字是日语或韩语）
2. 来源于 hanziTables[]，（遍历的所有，没有遗漏）
3. 多音字选中读音规则：
   a. 选择常用读音 ：
        { "红" , "hong" },      // gong
        { "薄" , "bo" },        // bao
        { "拆" , "chai" },      // ca
   b. 选择根据拼音可以猜出汉字的读音。这种字大家知道是多音字，如果我输出'ju'你基本可以猜到汉字'句'，但是我输出'gou'你还能猜到汉字是'句'就...
        { "句" , "ju" },        // gou
        { "旁" , "pang" },      // bang
        { "给" , "gei" },       // ji
        { "艾" , "ai" },        // yi
        { "大" , "da" },        // dai
        { "炮" , "pao" },       // bao
   c. 选中非姓氏读音
        { "仇" , "chou" },      // qiu ，仇：作姓氏时读qiú
        { "解" , "jie" },       // xie ，解：作姓氏时读xiè
        { "曾" , "ceng" },      // zeng，曾：作姓氏时读zēng
   d. 选中姓名中比较可能出现的字,下面的例子可能恰好符合其他的规则，但是在我手动筛选多音字时确实考虑到这方面的情况，因为有些多音字的其中一些读音代表的意义明显不可能被当名字来使用，因为筛选时没记录，下面的例子可能不贴切
        { "盛" , "sheng" },     // cheng ， 茂盛（maoSheng），盛饭(chengFan)
        { "石" , "shi" },       // dan    ， 潘石屹
        { "矜" , "jin" },       // qin guan
        { "强" , "qiang" },     // jiang , 坚强（qiang），倔强（jiang）
   e. 需要上下文联系的，这种字没法了，只能查表，这里的输出原则遵循（abcd）
        { "屏" , "ping" },      // bing ， 屏幕、屏弃
        { "卜" , "bu" },        // bo ，   占卜、萝卜
*/
multiToneWordTableS multiToneWordTable[g_length_multiToneWordTable] =
{
{ L"厑" , L"e" },         // si a
{ L"吖" , L"ya" },        // a
{ L"阿" , L"a" },         // e
{ L"呵" , L"he" },        // ha ke a
{ L"腌" , L"yan" },       // a
{ L"嗄" , L"sha" },       // a
{ L"閊" , L"ci" },        // ka lu ai
{ L"魞" , L"li" },        // ai
{ L"鱛" , L"ai" },        // suo
{ L"娭" , L"xi" },        // ai
{ L"佁" , L"yi" },        // ai
{ L"欸" , L"ei" },        // ai
{ L"艾" , L"ai" },        // yi
{ L"嗌" , L"yi" },        // ai
{ L"噫" , L"yi" },        // ai
{ L"餲" , L"ai" },        // he
{ L"厂" , L"chang" },     // an
{ L"广" , L"guang" },     // an
{ L"晻" , L"yan" },       // an
{ L"犴" , L"han" },       // an
{ L"胺" , L"an" },        // e
{ L"肮" , L"ang" },       // hang
{ L"卬" , L"yang" },      // ang
{ L"仰" , L"yang" },      // ang
{ L"凹" , L"ao" },        // wa
{ L"嚣" , L"xiao" },      // ao
{ L"夭" , L"ao" },        // yao
{ L"拗" , L"ao" },        // niu
{ L"鎺" , L"ha" },        // ba
{ L"鯐" , L"li" },        // si xi ba
{ L"叭" , L"ba" },        // pa
{ L"鎺" , L"ba" },        // pa
{ L"伯" , L"bo" },        // bai  ba
{ L"杷" , L"pa" },        // ba
{ L"叭" , L"ba" },        // pa
{ L"耙" , L"pa" },        // ba
{ L"瓸" , L"bai" },       // wa
{ L"兡" , L"bai" },       // ke
{ L"陌" , L"mo" },        // bai
{ L"柏" , L"bai" },       // bo
{ L"伴" , L"ban" },       // pan
{ L"拌" , L"ban" },       // pan
{ L"坢" , L"pan" },       // ban
{ L"柈" , L"pan" },       // ban
{ L"膀" , L"bang" },      // pang
{ L"旁" , L"pang" },      // bang
{ L"蚌" , L"bang" },      // beng
{ L"棓" , L"bang" },      // bei
{ L"搒" , L"bang" },      // peng
{ L"磅" , L"bang" },      // pang
{ L"炮" , L"pao" },       // bao
{ L"枹" , L"bao" },       // fu
{ L"薄" , L"bo" },        // bao
{ L"堡" , L"bao" },       // bu pu
{ L"刨" , L"pao" },       // bao
{ L"袌" , L"pao" },       // bao
{ L"暴" , L"bao" },       // pu
{ L"瀑" , L"pu" },        // bao
{ L"曝" , L"bao" },       // pu
{ L"陂" , L"bei" },       // pi po
{ L"椑" , L"bei" },       // pi
{ L"孛" , L"bei" },       // bo
{ L"被" , L"bei" },       // pi
{ L"贲" , L"ben" },       // bi
{ L"夯" , L"hang" },      // ben
{ L"萙" , L"ta" },        // ku lai bi
{ L"蛯" , L"bi" },        // e
{ L"鎞" , L"bi" },        // pi
{ L"吡" , L"pi" },        // bi
{ L"箄" , L"pai" },       // bi
{ L"芘" , L"bi" },        // pi
{ L"泌" , L"mi" },        // bi
{ L"秘" , L"mi" },        // bi
{ L"裨" , L"bi" },        // pi
{ L"辟" , L"pi" },        // bi
{ L"睥" , L"pi" },        // bi
{ L"扁" , L"bian" },      // pian
{ L"褊" , L"bian" },      // pian
{ L"便" , L"bian" },      // pian
{ L"缏" , L"bian" },      // pian
{ L"杓" , L"shao" },      // biao
{ L"骠" , L"biao" },      // piao
{ L"麃" , L"pao" },       // biao
{ L"玢" , L"fen" },       // bin
{ L"槟" , L"bing" },      // bin
{ L"屏" , L"ping" },      // bing
{ L"绠" , L"geng" },      // bing
{ L"卜" , L"bu" },        // bo
{ L"畓" , L"da" },        // bo
{ L"泊" , L"po" },        // bo
{ L"魄" , L"po" },        // tuo bo
{ L"埔" , L"pu" },        // bu
{ L"拆" , L"chai" },      // ca
{ L"嚓" , L"ca" },        // cha
{ L"偲" , L"si" },        // cai
{ L"参" , L"can" },       // cen san shen
{ L"篸" , L"can" },       // zan
{ L"掺" , L"chan" },      // shan can
{ L"孱" , L"chan" },      // can
{ L"臧" , L"zang" },      // cang
{ L"藏" , L"cang" },      // zang
{ L"猠" , L"o" },         // ce
{ L"硛" , L"ce" },        // ke o
{ L"侧" , L"ce" },        // ze zhai
{ L"筴" , L"ce" },        // jia
{ L"噌" , L"cheng" },     // ceng
{ L"曾" , L"ceng" },      // zeng
{ L"差" , L"cha" },       // chai ci
{ L"喳" , L"zha" },       // cha
{ L"查" , L"cha" },       // zha
{ L"猹" , L"cha" },       // zha
{ L"楂" , L"zha" },       // cha
{ L"槎" , L"cha" },       // zha
{ L"刹" , L"sha" },       // cha
{ L"咤" , L"zha" },       // cha
{ L"柴" , L"chai" },      // zhai
{ L"茝" , L"chai" },      // zhi
{ L"瘥" , L"cuo" },       // chai
{ L"单" , L"dan" },       // shan chan
{ L"禅" , L"chan" },      // shan
{ L"长" , L"chang" },     // zhang
{ L"倘" , L"tang" },      // chang
{ L"惝" , L"chang" },     // tang
{ L"绰" , L"chuo" },      // chao
{ L"焯" , L"chao" },      // zhuo
{ L"剿" , L"chao" },      // jiao
{ L"朝" , L"chao" },      // zhao
{ L"鼌" , L"zhao" },      // chao
{ L"嘲" , L"chao" },      // zhao
{ L"车" , L"che" },       // ju
{ L"尺" , L"chi" },       // che
{ L"嗔" , L"chen" },      // tian
{ L"称" , L"cheng" },     // chen
{ L"铛" , L"dang" },      // cheng
{ L"樘" , L"tang" },      // cheng
{ L"乘" , L"cheng" },     // sheng
{ L"盛" , L"sheng" },     // cheng
{ L"澄" , L"cheng" },     // deng
{ L"坻" , L"di" },        // chi
{ L"瘈" , L"zhi" },       // chi
{ L"涌" , L"yong" },      // chong
{ L"虫" , L"chong" },     // hui
{ L"种" , L"zhong" },     // chong
{ L"重" , L"zhong" },     // chong
{ L"仇" , L"chou" },      // qiu
{ L"帱" , L"chou" },      // dao
{ L"杻" , L"niu" },       // chou
{ L"臭" , L"chou" },      // xiu
{ L"助" , L"zhu" },       // chu
{ L"褚" , L"zhu" },       // chuzhe
{ L"畜" , L"chu" },       // xu
{ L"俶" , L"chu" },       // ti
{ L"滀" , L"chu" },       // xu
{ L"欻" , L"xu" },        // chua
{ L"啜" , L"chuo" },      // chuai
{ L"传" , L"chuan" },     // zhuan
{ L"串" , L"chuan" },     // guan
{ L"幢" , L"zhuang" },    // chuang
{ L"椎" , L"zhui" },      // chui
{ L"錞" , L"dchun" },     // ui
{ L"婼" , L"ruo" },       // chuo
{ L"茈" , L"zi" },        // ci
{ L"兹" , L"zi" },        // ci
{ L"伺" , L"si" },        // ci
{ L"枞" , L"cong" },      // zong
{ L"楤" , L"song" },      // cong
{ L"卒" , L"zu" },        // cu
{ L"趣" , L"qu" },        // cu
{ L"菆" , L"zou" },       // cuan
{ L"攒" , L"zan" },       // cuan
{ L"粹" , L"cui" },       // sui
{ L"蹲" , L"dun" },       // cun
{ L"酂" , L"zan" },       // cuo
{ L"鶎" , L"ku" },        // ta yi da
{ L"嗒" , L"da" },        // ta
{ L"沓" , L"ta" },        // da
{ L"惮" , L"dan" },       // da
{ L"大" , L"da" },        // dai
{ L"汏" , L"tai" },       // da
{ L"呔" , L"dai" },       // tai
{ L"骀" , L"dai" },       // tai
{ L"掸" , L"dan" },       // shan
{ L"黵" , L"dan" },       // zhan
{ L"石" , L"shi" },       // dan
{ L"弹" , L"tan" },       // dan
{ L"澹" , L"dan" },       // tan
{ L"乭" , L"dao" },       // ri
{ L"叨" , L"dao" },       // tao
{ L"焘" , L"dao" },       // tao
{ L"的" , L"de" },        // di
{ L"地" , L"di" },        // de
{ L"底" , L"di" },        // de
{ L"得" , L"de" },        // dei
{ L"嘚" , L"de" },        // dei
{ L"嚸" , L"di" },        // mi
{ L"提" , L"ti" },        // di
{ L"翟" , L"di" },        // zhai
{ L"蹢" , L"di" },        // zhi
{ L"杕" , L"di" },        // duo
{ L"揥" , L"ti" },        // di
{ L"阽" , L"dian" },      // yan
{ L"佃" , L"dian" },      // tian
{ L"钿" , L"dian" },      // tian
{ L"鸟" , L"niao" },      // diao
{ L"调" , L"tiao" },      // zhou diao
{ L"铫" , L"diao" },      // yao
{ L"咥" , L"die" },       // xi
{ L"昳" , L"die" },       // yi
{ L"喋" , L"die" },       // zha
{ L"揲" , L"die" },       // she
{ L"螲" , L"zhi" },       // die
{ L"丁" , L"ding" },      // zheng
{ L"町" , L"ding" },      // ting
{ L"铤" , L"ting" },      // ding
{ L"侗" , L"tong" },      // dong
{ L"垌" , L"dong" },      // tong
{ L"恫" , L"dong" },      // tong
{ L"峒" , L"tong" },      // dong
{ L"都" , L"dou" },       // du
{ L"读" , L"du" },        // dou
{ L"渎" , L"du" },        // dou
{ L"叾" , L"du" },        // ge
{ L"阇" , L"du" },        // she
{ L"度" , L"duo" },       // du
{ L"斁" , L"yi" },        // du
{ L"敦" , L"dun" },       // dui
{ L"镦" , L"dui" },       // dun
{ L"沌" , L"dun" },       // zhuan
{ L"囤" , L"tun" },       // dun
{ L"楯" , L"dun" },       // shun
{ L"鯲" , L"wu" },        // ya duo ji
{ L"驮" , L"tuo" },       // duo
{ L"堕" , L"duo" },       // hui
{ L"仒" , L"o" },         // e
{ L"旕" , L"o" },         // si e
{ L"襨" , L"e" },         // ta
{ L"欕" , L"mi" },        // e
{ L"恶" , L"e" },         // wu
{ L"哦" , L"o" },         // e
{ L"蛾" , L"e" },         // yi
{ L"阏" , L"e" },         // yan
{ L"椧" , L"mi" },        // eng
{ L"臑" , L"nao" },       // er
{ L"佴" , L"er" },        // nai
{ L"发" , L"fa" },        // fei
{ L"酦" , L"fa" },        // po
{ L"番" , L"fan" },       // pan
{ L"袢" , L"pan" },       // fan
{ L"繁" , L"fan" },       // po
{ L"仿" , L"fang" },      // pang
{ L"彷" , L"pang" },      // fang
{ L"芾" , L"fu" },        // fei
{ L"怫" , L"fu" },        // fei
{ L"濆" , L"fen" },       // pen
{ L"冯" , L"feng" },      // ping
{ L"佛" , L"fo" },        // fu
{ L"否" , L"fou" },       // pi
{ L"莩" , L"fu" },        // piao
{ L"俛" , L"mian" },      // fu
{ L"脯" , L"pu" },        // fu
{ L"乫" , L"ga" },        // ri
{ L"凩" , L"xi" },        // la  ga
{ L"軈" , L"ya" },        // ga
{ L"夹" , L"jia" },       // ga
{ L"伽" , L"ga" },        // jia qie
{ L"呷" , L"xia" },       // ga
{ L"咖" , L"ka" },        // ga
{ L"轧" , L"zha" },       // ya  ga
{ L"芥" , L"jie" },       // gai
{ L"盖" , L"gai" },       // ge
{ L"奸" , L"jian" },      // gan
{ L"感" , L"gan" },       // han
{ L"赣" , L"gan" },       // gong
{ L"扛" , L"kang" },      // gang
{ L"戆" , L"gang" },      // zhuang
{ L"皋" , L"gao" },       // hao
{ L"羙" , L"mei" },       // gao
{ L"镐" , L"gao" },       // hao
{ L"乬" , L"ge" },        // ri
{ L"巪" , L"xi" },        // ge
{ L"唟" , L"ge" },        // xi
{ L"仡" , L"yi" },        // ge
{ L"纥" , L"ge" },        // he
{ L"咯" , L"ge" },        // ka luo
{ L"革" , L"ge" },        // ji
{ L"鬲" , L"ge" },        // li
{ L"蛤" , L"ge" },        // ha
{ L"合" , L"he" },        // ge
{ L"硌" , L"luo" },       // ge
{ L"给" , L"gei" },       // ji
{ L"哏" , L"gen" },       // hen
{ L"红" , L"hong" },      // gong
{ L"唝" , L"gong" },      // hong
{ L"句" , L"ju" },        // gou
{ L"枸" , L"gou" },       // ju
{ L"呱" , L"gua" },       // gu
{ L"家" , L"jia" },       // gu
{ L"鹘" , L"gu" },        // hu
{ L"汩" , L"gu" },        // yu
{ L"谷" , L"gu" },        // yu
{ L"苦" , L"ku" },        // gu
{ L"贾" , L"jia" },       // gu
{ L"鹄" , L"gu" },        // he hu
{ L"嘏" , L"gu" },        // jia
{ L"雇" , L"gu" },        // hu
{ L"栝" , L"gua" },       // kuo
{ L"纶" , L"lun" },       // guan
{ L"矜" , L"jin" },       // qin guan
{ L"莞" , L"guan" },      // wan
{ L"归" , L"gui" },       // kui
{ L"龟" , L"gui" },       // jun qiu
{ L"廆" , L"gui" },       // hui wei
{ L"鲑" , L"gui" },       // hua xie
{ L"氿" , L"jiu" },       // gui
{ L"炅" , L"jiong" },     // gui
{ L"炔" , L"que" },       // gui
{ L"柜" , L"gui" },       // ju
{ L"桧" , L"hui" },       // gui
{ L"鳜" , L"gui" },       // jue
{ L"涡" , L"wo" },        // guo
{ L"乤" , L"ha" },        // ri
{ L"扖" , L"ru" },        // me  ha
{ L"溌" , L"tu" },        // ha
{ L"噺" , L"xi" },        // ha na
{ L"鱩" , L"ta" },        // ha
{ L"虾" , L"xia" },       // ha
{ L"咳" , L"ke" },        // hai
{ L"嗨" , L"hai" },       // hei
{ L"还" , L"huan" },      // hai
{ L"害" , L"hai" },       // he
{ L"炕" , L"kang" },      // hang
{ L"行" , L"xing" },      // hang heng
{ L"吭" , L"keng" },      // hang
{ L"巷" , L"xiang" },     // hang
{ L"貉" , L"he" },        // hao
{ L"遤" , L"he" },        // wo
{ L"和" , L"he" },        // hu huo
{ L"核" , L"he" },        // hu
{ L"吓" , L"xia" },       // he
{ L"猲" , L"xie" },       // he
{ L"熇" , L"he" },        // kao
{ L"嘿" , L"hei" },       // mo
{ L"戏" , L"xi" },        // hu hui
{ L"芴" , L"wu" },        // hu
{ L"浒" , L"hu" },        // xu
{ L"唬" , L"hu" },        // xia
{ L"楛" , L"ku" },        // hu
{ L"砉" , L"xu" },        // hua
{ L"郇" , L"xun" },       // huan
{ L"圜" , L"yuan" },      // huan
{ L"嬛" , L"huan" },      // qiong xuan
{ L"眩" , L"xuan" },      // huan
{ L"炜" , L"wei" },       // hui
{ L"珲" , L"hun" },       // hui
{ L"睢" , L"hui" },       // sui
{ L"会" , L"hui" },       // kuai
{ L"浍" , L"hui" },       // kuai
{ L"哕" , L"yue" },       // hui
{ L"荤" , L"hun" },       // xun
{ L"奇" , L"qi" },        // ji
{ L"其" , L"qi" },        // ji
{ L"缉" , L"ji" },        // qi
{ L"稽" , L"ji" },        // qi
{ L"亟" , L"ji" },        // qi
{ L"藉" , L"ji" },        // jie
{ L"齐" , L"qi" },        // ji
{ L"系" , L"xi" },        // ji
{ L"荠" , L"ji" },        // qi
{ L"祭" , L"ji" },        // zhai
{ L"偈" , L"jie" },       // ji
{ L"嗧" , L"jia" },       // lun
{ L"茄" , L"qie" },       // jia
{ L"葭" , L"jia" },       // xia
{ L"假" , L"jia" },       // xia
{ L"价" , L"jia" },       // jie
{ L"浅" , L"qian" },      // jian
{ L"犍" , L"jian" },      // qian
{ L"囝" , L"jian" },      // nan
{ L"见" , L"jian" },      // xian
{ L"槛" , L"kan" },       // jian
{ L"将" , L"jiang" },     // qiang
{ L"降" , L"jiang" },     // xiang
{ L"强" , L"qiang" },     // jiang
{ L"蕉" , L"jiao" },      // qiao
{ L"徼" , L"jiao" },      // yao
{ L"嚼" , L"jiao" },      // jue
{ L"角" , L"jiao" },      // jue
{ L"侥" , L"jiao" },      // yao
{ L"脚" , L"jiao" },      // jue
{ L"湫" , L"jiu" },       // qiu jiao
{ L"缴" , L"jiao" },      // zhuo
{ L"峤" , L"qiao" },      // jiao
{ L"觉" , L"jiao" },      // jue
{ L"校" , L"xiao" },      // jiao
{ L"楷" , L"kai" },       // jie
{ L"桔" , L"jie" },       // ju
{ L"絜" , L"xie" },       // jie
{ L"解" , L"jie" },       // xie
{ L"廑" , L"jin" },       // qin
{ L"劲" , L"jing" },      // jin
{ L"倞" , L"liang" },     // jing
{ L"靓" , L"liang" },     // jing
{ L"且" , L"qie" },       // ju
{ L"苴" , L"ju" },        // zu
{ L"蛆" , L"qu" },        // ju
{ L"趄" , L"qie" },       // ju
{ L"咀" , L"ju" },        // zui
{ L"籧" , L"qu" },        // ju
{ L"苣" , L"ju" },        // qu
{ L"圈" , L"quan" },      // juan
{ L"卷" , L"juan" },      // quan
{ L"踡" , L"quan" },      // juan
{ L"隽" , L"jun" },       // juan
{ L"阙" , L"que" },       // jue
{ L"噱" , L"xue" },       // jue
{ L"筠" , L"jun" },       // yun
{ L"麇" , L"qun" },       // jun
{ L"浚" , L"jun" },       // xun
{ L"焌" , L"jun" },       // qu
{ L"凧" , L"ka" },        // yi
{ L"裃" , L"ka" },        // mi mo xi 日
{ L"聢" , L"li" },        // xi ka
{ L"鯑" , L"ke" },        // nou zi ka
{ L"鶍" , L"si" },        // yi ka
{ L"卡" , L"ka" },        // qia
{ L"厼" , L"mu" },        // wu ke
{ L"迲" , L"o" },         // pi ke
{ L"穒" , L"o" },         // ke
{ L"壳" , L"ke" },        // qiao
{ L"隗" , L"wei" },       // kui
{ L"鮱" , L"luo" },       // la
{ L"落" , L"luo" },       // lao  la
{ L"腊" , L"la" },        // xi
{ L"蜡" , L"la" },        // zha
{ L"癞" , L"lai" },       // la
{ L"莨" , L"liang" },     // lang
{ L"潦" , L"liao" },      // lao
{ L"姥" , L"lao" },       // mu
{ L"獠" , L"liao" },      // lao
{ L"络" , L"luo" },       // lao
{ L"烙" , L"lao" },       // luo
{ L"朰" , L"te" },        // wu le
{ L"榁" , L"mu" },        // le
{ L"肋" , L"lei" },       // le
{ L"乐" , L"yue" },       // le
{ L"勒" , L"lei" },       // le
{ L"漯" , L"luo" },       // ta lei
{ L"棱" , L"leng" },      // ling
{ L"甅" , L"li" },        // wa
{ L"蠡" , L"li" },        // luo
{ L"栎" , L"li" },        // yue
{ L"跞" , L"li" },        // luo
{ L"俩" , L"liang" },     // lia
{ L"飂" , L"liu" },       // liao
{ L"蓼" , L"liao" },      // lu
{ L"挘" , L"lie" },       // ri
{ L"六" , L"liu" },       // lu
{ L"陆" , L"lu" },        // liu
{ L"碌" , L"lu" },        // liu
{ L"泷" , L"long" },      // shuang
{ L"弄" , L"nong" },      // long
{ L"偻" , L"lou" },       // lv
{ L"露" , L"lu" },        // lou
{ L"绿" , L"lv" },        // lu
{ L"捋" , L"luo" },       // lv
{ L"率" , L"shuai" },     // lv
{ L"呣" , L"m" },         // mou
{ L"姆" , L"mu" },        // m
{ L"唜" , L"si" },        // ma
{ L"魸" , L"na" },        // zi ma 日
{ L"孖" , L"zi" },        // ma
{ L"抹" , L"mo" },        // ma
{ L"摩" , L"mo" },        // ma
{ L"埋" , L"mai" },       // man
{ L"脉" , L"mai" },       // mo
{ L"蔓" , L"wan" },       // man
{ L"尨" , L"meng" },      // mang
{ L"氓" , L"mang" },      // meng
{ L"冒" , L"mao" },       // mo
{ L"乄" , L"shi" },       // me 日
{ L"匁" , L"mo" },        // ne me 日
{ L"没" , L"mei" },       // mo
{ L"糜" , L"mi" },        // mei
{ L"谜" , L"mi" },        // mei
{ L"汶" , L"wen" },       // men
{ L"亹" , L"wei" },       // men
{ L"黾" , L"min" },       // meng
{ L"鼡" , L"ne" },        // zu mi 日
{ L"蓂" , L"ming" },      // mi
{ L"免" , L"mian" },      // wen
{ L"渑" , L"mian" },      // sheng
{ L"缪" , L"miu" },       // mou miao
{ L"乜" , L"mie" },       // nie
{ L"丆" , L"ne" },        // o ye mo
{ L"乮" , L"ri" },        // mo 韩
{ L"无" , L"wu" },        // mo
{ L"模" , L"mo" },        // mu
{ L"万" , L"wan" },       // mo
{ L"莫" , L"mo" },        // mu
{ L"袜" , L"wa" },        // mo
{ L"牟" , L"mou" },       // mu
{ L"那" , L"na" },        // ne nei nuo
{ L"南" , L"nan" },       // na
{ L"哪" , L"na" },        // nai ne nei
{ L"内" , L"nei" },       // na
{ L"呐" , L"na" },        // ne
{ L"娜" , L"na" },        // nuo
{ L"艿" , L"nai" },       // reng
{ L"呶" , L"nao" },       // nu
{ L"縇" , L"o" },         // se ne
{ L"唔" , L"wu" },        // ng
{ L"哛" , L"po" },        // pu ni
{ L"鳰" , L"o" },         // ni 日
{ L"溺" , L"ni" },        // niao
{ L"嶷" , L"yi" },        // ni
{ L"粘" , L"zhan" },      // nian
{ L"捻" , L"nian" },      // nie
{ L"辗" , L"zhan" },      // nian
{ L"尿" , L"niao" },      // sui
{ L"宁" , L"ning" },      // zhu
{ L"莻" , L"xi" },        // nu 韩
{ L"喏" , L"nuo" },       // re
{ L"疟" , L"nve" },       // yao
{ L"区" , L"qu" },        // ou
{ L"巼" , L"xi" },        // pa 韩
{ L"派" , L"pai" },       // pa
{ L"闏" , L"ying" },      // pai 韩
{ L"迫" , L"po" },        // pai
{ L"胖" , L"pang" },      // pan
{ L"拚" , L"pin" },       // pan
{ L"喸" , L"xi" },        // pao 韩
{ L"朴" , L"pu" },        // po  piao
{ L"娉" , L"pin" },       // ping
{ L"乶" , L"po" },        // ri 韩
{ L"栖" , L"qi" },        // xi
{ L"踦" , L"qi" },        // yi
{ L"蹊" , L"qi" },        // xi
{ L"圻" , L"qi" },        // yin
{ L"俟" , L"si" },        // qi
{ L"綮" , L"qing" },      // qi
{ L"契" , L"qi" },        // xie
{ L"砌" , L"qie" },       // qi
{ L"铅" , L"qian" },      // yan
{ L"嗛" , L"xian" },      // qian
{ L"荨" , L"qian" },      // xun
{ L"羬" , L"xian" },      // qian
{ L"纤" , L"xian" },      // qian
{ L"茜" , L"xi" },        // qian
{ L"倩" , L"qian" },      // qing
{ L"慊" , L"qie" },       // qian
{ L"雀" , L"que" },       // qiao
{ L"鞘" , L"qiao" },      // shao
{ L"亲" , L"qin" },       // qing
{ L"覃" , L"tan" },       // qin
{ L"溱" , L"qin" },       // zhen
{ L"鲭" , L"qing" },      // zheng
{ L"蝤" , L"qiu" },       // you
{ L"券" , L"quan" },      // xuan
{ L"芍" , L"shao" },      // que
{ L"荛" , L"yao" },       // rao
{ L"若" , L"ruo" },       // re
{ L"葚" , L"shen" },      // ren
{ L"乽" , L"za" },        // ri 韩
{ L"乼" , L"zu" },        // ri 韩
{ L"乺" , L"sao" },       // ri 韩
{ L"鑓" , L"ya" },        // ri 日
{ L"虄" , L"sa" },        // ri 韩
{ L"扨" , L"te" },        // sa 日
{ L"苆" , L"su" },        // sa 日
{ L"栍" , L"ying" },      // sa 韩
{ L"摋" , L"sa" },        // sha
{ L"思" , L"si" },        // sai
{ L"塞" , L"sai" },       // se
{ L"糁" , L"shen" },      // san
{ L"燥" , L"zao" },       // sao
{ L"色" , L"se" },        // shai
{ L"杉" , L"shan" },      // sha
{ L"莎" , L"sha" },       // suo
{ L"挲" , L"sha" },       // suo
{ L"噎" , L"ye" },        // sha
{ L"奢" , L"she" },       // sha
{ L"啑" , L"ti" },        // sha
{ L"厦" , L"xia" },       // sha
{ L"酾" , L"shi" },       // shai
{ L"栅" , L"shan" },      // zha
{ L"剡" , L"yan" },       // shan
{ L"汤" , L"tang" },      // shang
{ L"蛸" , L"xiao" },      // shao
{ L"苕" , L"shao" },      // tiao
{ L"畬" , L"she" },       // yu
{ L"折" , L"zhe" },       // she
{ L"蛇" , L"she" },       // yi
{ L"叶" , L"ye" },        // xie she
{ L"拾" , L"shi" },       // she
{ L"歙" , L"she" },       // xi
{ L"谁" , L"shui" },      // shei
{ L"籡" , L"shi" },       // shen 日
{ L"莘" , L"shen" },      // xin
{ L"什" , L"shen" },      // shi
{ L"椹" , L"shen" },      // zhen
{ L"狌" , L"sheng" },     // xing
{ L"省" , L"sheng" },     // xing
{ L"嘘" , L"xu" },        // shi
{ L"识" , L"shi" },       // zhi
{ L"食" , L"shi" },       // si yi
{ L"氏" , L"shi" },       // zhi
{ L"似" , L"si" },        // shi
{ L"峙" , L"zhi" },       // shi
{ L"螫" , L"shi" },       // zhe
{ L"熟" , L"shu" },       // shou
{ L"荼" , L"tu" },        // shu
{ L"属" , L"shu" },       // zhu
{ L"术" , L"shu" },       // zhu
{ L"庶" , L"shu" },       // zhu
{ L"说" , L"shuo" },      // tuo yue shui
{ L"忪" , L"song" },      // zhong
{ L"宿" , L"su" },        // xiu
{ L"缩" , L"suo" },       // su
{ L"燵" , L"tui" },       // ta 日
{ L"拓" , L"tuo" },       // ta
{ L"潭" , L"tan" },       // xun
{ L"陶" , L"tao" },       // yao
{ L"罀" , L"yo" },        // zhao te 日
{ L"忒" , L"tui" },       // te
{ L"擿" , L"ti" },        // zhi
{ L"荑" , L"yi" },        // ti
{ L"裼" , L"xi" },        // ti
{ L"僮" , L"tong" },      // zhuang
{ L"侻" , L"tuo" },       // tui
{ L"褪" , L"tui" },       // tun
{ L"屯" , L"tun" },       // zhun
{ L"崴" , L"wei" },       // wai
{ L"菀" , L"wan" },       // yu
{ L"尢" , L"you" },       // wang
{ L"亡" , L"wang" },      // wu
{ L"圩" , L"wei" },       // xu
{ L"尾" , L"wei" },       // yi
{ L"尉" , L"wei" },       // yu
{ L"遗" , L"yi" },        // wei
{ L"蔚" , L"wei" },       // yu
{ L"挝" , L"wo" },        // zhua
{ L"涴" , L"wan" },       // yuan wo
{ L"於" , L"yu" },        // wu
{ L"铻" , L"wu" },        // yu
{ L"夞" , L"yi" },        // xi 韩
{ L"硳" , L"ze" },        // xi 韩
{ L"褶" , L"zhe" },       // xi
{ L"洗" , L"xi" },        // xian
{ L"铣" , L"xi" },        // xian
{ L"县" , L"xian" },      // xuan
{ L"削" , L"xiao" },      // xue
{ L"邪" , L"xie" },        // ye
{ L"荥" , L"ying" },       // xing
{ L"褎" , L"you" },        // xiu
{ L"吁" , L"yu" },         // xu
{ L"芧" , L"zhu" },        // xu
{ L"窨" , L"yin" },        // xun
{ L"厌" , L"yan" },        // ya
{ L"咽" , L"yan" },        // ye
{ L"殷" , L"yin" },        // yan
{ L"芫" , L"yuan" },       // yan
{ L"约" , L"yue" },        // yao
{ L"繇" , L"yao" },        // you zhou
{ L"钥" , L"yao" },        // yue
{ L"拽" , L"zhuai" },      // ye
{ L"育" , L"yu" },         // yo
{ L"喁" , L"yong" },       // yu
{ L"柚" , L"you" },        // zhu
{ L"粥" , L"zhou" },       // yu
{ L"熨" , L"yun" },        // yu
{ L"员" , L"yuan" },       // yun
{ L"扎" , L"zha" },        // za
{ L"拶" , L"zan" },        // za
{ L"囋" , L"za" },         // zan
{ L"咋" , L"za" },         // ze zha
{ L"甾" , L"zai" },        // zi
{ L"仔" , L"zi" },         // zai
{ L"奘" , L"zang" },       // zhuang
{ L"责" , L"ze" },         // zhai
{ L"择" , L"ze" },         // zhai
{ L"综" , L"zong" },       // zeng
{ L"着" , L"zhuo" },       // zhao
{ L"啁" , L"zhou" },       // zhao
{ L"爪" , L"zhua" },       // zhao
{ L"这" , L"zhe" },        // zhei
{ L"吱" , L"zhi" },        // zi
{ L"祝" , L"zhu" },        // zhou
{ L"躅" , L"zhuo" },       // zhu
{ L"转" , L"zhuan" },      // zhuai
{ L"赚" , L"zhuan" },      // zuan
{ L"篹" , L"zuan" },       // zhuan
{ L"觜" , L"zui" },        // zi

{ L"鲅", L"ba" },           // bo
{ L"", L"pa" },           // ba
{ L"扳", L"ban" },          // pan
{ L"般", L"ban" },          // bo pan
{ L"剥", L"bao" },          // bo
{ L"趵", L"bao" },          // bo
{ L"蕃", L"fan" },          // bo
{ L"嗀", L"gu" },           // hu
{ L"桁", L"heng" },         // hang
{ L"珩", L"heng" },         // hang
{ L"牙", L"ya" },           // he
{ L"", L"song" },         // yu
{ L"嘬", L"zuo" },          // chuai
{ L"撮", L"cuo" },          // zuo
{ L"笮", L"zuo" },          // ze
{ L"琢", L"zhuo" },         // zuo
};

/*
0. 汉字拼音表，来源于 http://xh.5156edu.com/pinyi.html （需要自己获取数据）
1. 在'bo'添加'卜' ; 'de'添加'的' ; 'wan'添加'涴' ; 'ta'添加'他'
  （获取到的数据有缺失，是网站的问题，这里直接补全）
2. ü 用 v 代替
3. 更新
    去掉 '' 原来在'虱'的后面 20200410
    去掉 '' 原来在'驟'的后面 20200410
*/
hanziTableS hanziTables[g_length_hanziTables] =
{
{ L"a", L"a", L"吖阿呵啊腌锕錒嗄厑" },
{ L"a", L"ao", L"凹柪梎軪熬爊敖厫隞蔜遨廒嗷嗸獓嶅滶獒摮璈磝螯聱翱翶謷謸鳌翺嚣鏖鷔鰲鼇艹夭芺抝拗袄镺媪媼襖岙岰垇坳傲奡奥奧骜嫯慠懊墺澳嶴擙鏊驁澚鱜" },
{ L"a", L"ang", L"肮骯卬仰岇昂昻枊盎醠" },
{ L"a", L"ai", L"哎哀诶唉娭挨埃溾嗳锿鎄捱皑啀凒溰敱敳嘊皚癌騃佁毐昹欸娾矮蔼躷噯濭藹譪霭靄艾阨伌爱砹硋隘嗌嫒塧碍愛叆暧瑷僾噫壒懓嬡薆鴱餲璦曖懝皧瞹馤礙譺鑀靉閊魞﨟鱛鱫" },
{ L"a", L"an", L"厂广安侒峖桉氨庵偣谙菴萻葊媕腤痷鹌誝蓭鞍鞌諳盦馣鮟盫鵪鶕韽玵啽雸儑垵俺唵埯铵晻揞罯銨屵犴岸按洝荌胺豻案婩隌堓暗貋錌闇黯" },

{ L"b", L"bai", L"挀掰白犤百伯佰陌柏栢捭絔摆擺襬庍呗拝败拜敗猈稗粺薭贁韛瓸竡粨兡" },
{ L"b", L"ba", L"丷八仈巴叭朳玐吧岜扷芭夿疤柭釟蚆粑笆捌哵羓豝鲃叐茇妭拔炦胈癹菝軷詙跋颰魃鼥把钯鈀靶伯弝坝爸杷垻罢耙跁鲅罷鮁覇矲霸壩灞欛抜鎺鯐" },
{ L"b", L"ban", L"扳肦攽班般颁斑斒搬頒鳻瘢螌褩癍辬阪岅坂板版昄瓪钣粄舨鈑蝂魬闆办半伴扮拌姅绊坢怑柈秚絆湴鉡靽辦瓣螁" },
{ L"b", L"bang", L"邦帮垹梆捠浜邫幇幚縍幫鞤绑綁榜牓膀玤挷旁蚌棒棓傍谤蒡搒塝稖蜯镑磅艕謗鎊" },
{ L"b", L"bao", L"勹包苞孢炮枹胞剥剝笣龅煲裦褒蕔襃闁齙窇雹薄宝饱怉鸨保宲珤葆堡堢媬寚飽飹褓駂鳵鴇緥賲寳寶靌勽刨报抱铇豹趵蚫菢袌報鉋鲍骲髱暴虣鮑曓儤瀑爆犦曝忁鑤佨藵" },
{ L"b", L"ben", L"奔泍贲犇锛錛本苯奙畚翉楍夯坌倴逩桳笨捹渀撪" },
{ L"b", L"bei", L"陂卑杯柸背盃桮椑揹悲鹎碑藣鵯北鉳贝狈孛邶貝牬昁苝备郥钡被倍俻狽悖梖偝偹鄁珼琲惫軰備僃棓辈焙蓓蛽碚愂禙犕褙誖鞁骳鋇輩糒憊鞴鐾唄" },
{ L"b", L"beng", L"伻祊奟崩绷閍絣痭嵭嘣綳繃甭甮埄埲菶琫琣鞛迸泵蚌逬揼塴甏镚蹦鏰" },
{ L"b", L"bi", L"皀屄偪逼毴楅榌豍鵖螕鲾鎞鰏荸鼻匕比朼夶吡妣沘佊疕彼毞柀秕笔粃舭俾啚筆鄙箄聛貏币必毕闭庇佖诐芘邲迊坒怭怶苾妼咇泌畀畁哔荜陛贲毖柲珌疪秘铋毙狴畢袐粊笓閉閇婢庳萆萞梐敝赑堛愊愎皕禆弼弻湢詖筚賁貱蜌裨辟跸閟飶鉍滗滭嗶彃蓖蓽腷睥睤痹痺煏熚碧蔽弊鄪獙幣綼箅箆馝髲駜襅幤潷罼獘壁廦嬖避薜篦篳縪觱鮅蹕髀濞斃臂奰鏎饆鄨璧繴襣襞鞸魓韠躄躃驆鷝鐴贔朇鷩鼊萙蛯嬶" },
{ L"b", L"bian", L"边炞砭笾萹编猵煸牑甂箯蝙糄編鞕鍽鳊獱邉邊鞭鯿鯾籩贬扁窆匾貶惼褊稨碥鴘藊卞弁抃汳汴苄釆忭玣变変昪便覍徧遍缏揙閞辡諚緶艑辨辩辧辫辮辯變峅" },
{ L"b", L"biao", L"杓标飑骉髟彪淲猋脿颮滮摽骠蔈幖墂麃標熛膘镖瘭磦飙飚儦颷謤藨瀌爂鏢贆臕穮镳飆飇飈飊鑣驫嫑表婊裱諘錶褾檦俵鳔鋲" },
{ L"b", L"bie", L"憋瘪蟞鳖癟鱉鼈虌龞别別莂蛂徶襒蹩彆" },
{ L"b", L"bin", L"邠玢宾彬梹椕傧斌滨缤賓賔豩槟瑸镔儐濒頻豳濱濵虨璸檳瀕霦繽蠙鑌顮摈殡膑髩鬂擯殯臏髌鬓髕鬢" },
{ L"b", L"bing", L"冫仌氷并冰兵屏栟掤槟丙邴陃苪怲抦秉昞昺炳柄饼绠眪蛃偋寎棅鈵禀稟鉼餅餠鞞幷並併庰倂栤竝病窉傡摒誁鮩靐垪鞆" },
{ L"b", L"bo", L"卜癶癷波拨玻饽钵盋砵哱剥般趵缽紴袰菠啵溊碆鉢鲅僠蕃嶓播撥餑礡蹳驋鱍仢伯驳孛肑瓝泊狛帛郣勃侼胉柏袯瓟秡钹铂浡挬亳萡淿脖袹舶鹁渤葧博猼馎愽搏鈸鉑鲌魄馛駁艊箔牔煿膊僰镈踣鋍馞駮鮊薄謈襏簙餺鵓鎛嚗懪髆髉糪襮欂礴鑮跛簸孹檗擘譒蘗畓蔔" },
{ L"b", L"bu", L"逋庯峬钸晡鈽誧餔錻鳪轐醭卜卟补哺捕堡補鵏鸔不布吥佈步歨歩怖咘钚柨悑部勏捗埔埗荹埠瓿鈈蔀廍踄郶餢篰簿巭" },

{ L"c", L"ca", L"拆擦攃嚓礤礸遪乲" },
{ L"c", L"cai", L"偲猜才财材財裁纔毝采倸啋寀婇彩採埰棌睬跴綵踩宷菜蔡縩" },
{ L"c", L"can", L"参參叄骖飡湌叅喰傪嬠餐驂残蚕惭殘慚蝅慙蠺蠶惨朁慘憯穇篸黪黲灿掺孱粲薒澯燦璨謲儏爘" },
{ L"c", L"cang", L"仓仺伧苍沧鸧舱倉傖凔滄蒼獊嵢螥艙鶬臧藏鑶賶濸" },
{ L"c", L"cao", L"撡操糙曺曹蓸嘈嶆漕慒槽褿螬艚鏪艸草愺懆騲肏鄵襙鼜" },
{ L"c", L"ce", L"夨册冊侧厕荝拺测恻敇粣笧萗厠側萴策測廁惻筴筞蓛箣憡簎猠硛" },
{ L"c", L"cen", L"参嵾岑涔埁笒梣" },
{ L"c", L"ceng", L"噌层曾層嶒竲驓蹭" },
{ L"c", L"cha", L"叉扱扠杈臿差挿偛馇插揷嗏喳锸碴銟艖疀嚓鍤餷茬茶垞查査秅猹嵖搽靫詧楂槎察檫衩蹅镲鑔奼汊岔刹侘诧剎姹咤紁詫" },
{ L"c", L"chai", L"芆肞钗拆差釵犲侪柴豺祡喍儕茝虿訍袃瘥蠆囆" },
{ L"c", L"chan", L"辿觇梴掺搀覘裧摻鋓幨襜攙苂单谗婵馋湹孱棎禅煘缠蝉獑僝誗鋋儃廛嬋潺潹緾澶磛鄽螹毚蟬瀍酁儳蟾劖壥嚵瀺巉欃纏纒躔镵艬讒鑱饞产刬旵丳斺浐剗谄阐铲產産蒇剷摌滻蕆幝諂閳骣燀簅冁醦繟鏟譂闡囅灛讇忏硟摲懴颤懺羼韂顫" },
{ L"c", L"chang", L"伥昌倡倀菖阊娼猖淐琩锠裮錩閶鲳鯧鼚长仧仩场兏肠苌镸長尝倘偿萇徜常瓺場腸甞裳塲嫦嘗膓瑺嚐償鲿鱨厂昶惝敞厰僘廠氅鋹怅玚畅鬯唱悵焻暢畼誯韔椙蟐" },
{ L"c", L"che", L"车伡車俥砗莗唓硨蛼尺扯偖撦屮彻迠坼烢聅硩掣頙撤澈徹瞮勶爡" },
{ L"c", L"chao", L"吵抄弨怊欩钞绰訬超鈔焯剿窼牊晁巢巣朝鼌鄛漅潮樔嘲窲罺鼂轈謿炒眧焣煼麨巐仦仯耖觘" },
{ L"c", L"chen", L"抻郴捵棽琛嗔綝賝諃瞋謓尘臣辰忱沉陈迧茞莀莐宸陳栕桭谌訦軙敐晨鈂愖煁蔯樄塵敶瘎霃諶螴薼麎曟鷐趻硶碜墋夦踸磣鍖贂衬疢称龀趁趂榇齓齔儭谶嚫櫬襯讖烥" },
{ L"c", L"cheng", L"阷泟爯柽棦称秤浾琤偁铛碀蛏晿牚赪靗憆稱摚撑撐噌樘緽頳赬瞠橕檉竀罉蟶穪鏿鐣饓丞成朾呈郕诚枨承荿宬娍峸洆城乗乘埕挰珹珵窚掁脭铖盛程揨堘裎絾筬惩椉棖誠塍塖溗酲鋮畻澄澂憕橙檙瀓懲騬侱徎逞骋悜庱睈騁鯎" },
{ L"c", L"chi", L"吃妛彨哧胵鸱蚩粚笞眵瓻喫訵絺嗤媸摛痴瞝殦噄誺螭鴟鵄魑癡齝攡彲黐弛驰池迟迡茌坻竾荎持匙蚳赿貾遅筂遟馳箎墀漦遲踟篪鍉謘尺叺伬呎肔齿侈卶垑胣蚇耻恥豉袳歯欼袲裭鉹齒褫彳叱斥杘赤饬灻抶侙勅恜炽勑翅翄敕烾湁啻飭雴傺腟痸鉓銐翤瘈遫憏瘛慗翨熾趩懘鶒鷘麶" },
{ L"c", L"chong", L"冲充沖忡茺涌浺珫翀舂嘃摏憧衝憃罿艟蹖虫种重隀崇崈漴褈蝩緟蟲爞宠埫寵铳揰銃" },
{ L"c", L"chou", L"抽紬搊篘瘳犨犫仇俦帱栦菗绸惆絒椆畴愁皗稠筹詶酬酧裯踌綢雔儔薵懤幬嬦檮燽雠疇籌醻躊讎讐雦丑丒吜杻杽偢瞅醜矁魗臭臰遚殠鮘" },
{ L"c", L"chua", L"欻" },
{ L"c", L"chu", L"出岀初摴樗貙齣刍处助除芻厨蒢豠滁锄雏鉏趎蒭媰蜍耡犓鋤篨廚橱櫉幮躇雛蹰櫥鶵躕杵础處椘楮储禇楚褚濋儲檚礎齭齼亍処竌豖绌怵泏竐欪畜俶敊埱絀珿傗鄐滀搐触閦諔儊嘼憷斶黜臅歜觸矗榋璴蟵" },
{ L"c", L"chuan", L"巛川氚穿瑏传舡舩船剶遄椽傳暷篅輲舛荈喘歂僢踳汌玔串钏釧猭賗鶨" },
{ L"c", L"chuang", L"刅创疮窓窗牎摐牕瘡窻床牀幢噇闯傸磢闖怆刱剏剙創愴" },
{ L"c", L"chuai", L"揣搋膗啜嘬膪踹" },
{ L"c", L"chui", L"吹炊龡垂埀陲倕桘菙捶搥棰椎圌腄锤槌箠錘鎚顀" },
{ L"c", L"chun", L"旾杶春萅媋堾椿槆暙瑃蝽箺輴橁櫄鶞鰆纯陙莼唇浱純脣淳湻犉鹑滣蒓蓴漘醇醕錞鶉鯙偆萶惷睶賰蠢" },
{ L"c", L"cong", L"匆苁囱囪忩茐枞怱悤棇葱楤蔥蓯骢漗聡聪聦熜潨樅樬暰瑽璁瞛蟌聰篵鍯繱鏦鏓騘驄从丛徔従從徖婃淙悰孮琮潀漎賨賩誴錝樷藂叢灇欉爜愡憁謥" },
{ L"c", L"ci", L"刺差呲玼疵趀偨跐骴縒髊蠀齹词珁茈茨垐柌祠兹瓷辝詞辞慈甆鹚磁雌餈飺糍辤薋嬨濨鴜礠辭鷀鶿此佌泚皉鮆朿次伺佽刾庛茦栨莿赐蛓絘賜螆閊" },
{ L"c", L"chuo", L"逴趠踔戳繛辶辵哾娖娕婼婥啜涰绰惙辍酫踀綽輟龊擉餟磭歠嚽齪鑡" },
{ L"c", L"cu", L"怚粗觕麁麄橻麤徂殂卒促脨猝酢媨瘄蔟趗誎醋憱趣踧噈瘯踿縬簇鼀蹙蹴蹵顣" },
{ L"c", L"cou", L"凑湊辏楱腠輳" },
{ L"c", L"cun", L"邨村皴踆澊墫竴膥存侟拵蹲刌忖寸籿" },
{ L"c", L"cuan", L"汆撺镩蹿攛躥鑹菆攒櫕巑欑穳窜殩熶篡簒竄爨" },
{ L"c", L"cui", L"崔脺嵟凗催缞墔慛榱獕摧槯磪縗鏙漼璀趡皠伜忰疩脆脃倅粋紣翆萃啐啛淬悴焠毳琗瘁翠綷粹膵膬竁襊濢顇臎" },
{ L"c", L"cuo", L"搓遳瑳磋撮醝蹉鎈虘嵯嵳睉痤蒫矬蔖瘥鹾酂鹺脞剉剒莝莡厝挫夎措逪锉错蓌銼錯" },

{ L"d", L"da", L"咑哒耷笚答嗒搭褡撘墶噠鎝鎉打达迏迖迚怛呾妲沓荙荅炟羍畗畣惮匒剳逹笪詚達跶靼瘩薘鞑蟽鐽韃龖龘大亣汏垯眔畓繨躂鶎" },
{ L"d", L"dang", L"当珰裆铛筜當儅噹澢璫襠蟷艡簹鐺闣挡党谠擋譡黨攩灙欓讜氹凼圵宕砀荡垱档菪婸逿愓瓽雼嵣潒碭瞊趤蕩壋檔璗盪礑簜蘯" },
{ L"d", L"dan", L"丹妉担单単眈砃耽耼郸聃躭酖單殚媅瘅匰鄲頕褝箪勯儋殫擔甔襌簞聸刐伔抌瓭玬胆衴紞疸掸赕亶馾撣撢賧黕膽黮黵旦石帎但诞狚泹沊柦唌疍蛋弹惮啖啗淡萏啿弾氮蜑腅觛誕窞蓞僤噉髧嘾彈憚憺禫澹駳鴠餤癉癚繵贉嚪饏霮" },
{ L"d", L"dai", L"呆呔待獃懛歹歺逮傣大代轪甙侢迨帒骀岱绐垈贷带玳殆柋怠軑貣帯帶埭蚮紿軚袋軩貸瑇跢廗叇曃蝳緿鴏黛艜戴簤瀻霴黱襶靆" },
{ L"d", L"de", L"的嘚恴得淂棏惪悳锝徳德鍀地底" },
{ L"d", L"dao", L"刀刂叨忉朷氘舠釖鱽魛螩捯导岛陦島捣倒祷禂搗隝嶋嶌導隯嶹擣壔蹈禱辺到帱悼焘菿盗盜道翢稲稻噵艔衜衟檤燾翿軇瓙纛乭﨩椡槝" },
{ L"d", L"dei", L"嘚得" },
{ L"d", L"deng", L"灯登豋僜噔嬁燈璒竳簦蹬等戥邓鄧隥凳嶝澄墱镫瞪磴櫈覴鐙艠" },
{ L"d", L"den", L"扥扽" },
{ L"d", L"dia", L"嗲" },
{ L"d", L"di", L"氐仾低彽奃岻秪袛隄羝埞啲堤提趆滴嘀镝磾鞮廸狄苖迪的籴唙荻涤敌梑啇笛靮觌滌髢馰頔翟嫡蔋蔐樀敵藡嚁豴蹢鏑覿糴鸐厎邸阺诋坘坻弤底呧抵拞柢牴砥掋菧軧觝詆骶聜鯳地坔杕旳弟玓苐枤怟埅帝俤娣递逓埊焍谛梊祶菂偙眱珶第釱睇揥媂蒂棣缔楴禘遞僀腣鉪碲蝃摕遰蔕墬墑甋蝭締慸諦踶嶳螮嚸" },
{ L"d", L"die", L"爹跌褺苵迭咥峌挕绖垤恎昳胅瓞眣耊谍眰戜絰臷镻詄趃跕畳喋耋惵堞揲殜叠楪牃牒跮碟褋蜨嵽蝶艓諜蹀鴩疂螲鲽蹛曡疉鰈疊氎哋幉" },
{ L"d", L"diao", L"刁叼汈刟虭凋彫奝弴蛁貂琱鳭碉鮉瞗錭鲷雕簓鼦鯛鵰鸟扚屌弔吊伄钓盄窎訋调铞铫掉釣鈟竨蓧銱銚雿魡調窵瘹鋽藋鑃" },
{ L"d", L"dian", L"敁掂厧傎嵮滇槇槙瘨颠蹎顛顚巅癫巓攧巔癲齻典奌点婰敟碘蒧蕇踮點电甸阽佃店坫垫扂玷钿惦婝淀琔奠殿鈿蜔電墊壂澱橂靛磹癜簟驔椣" },
{ L"d", L"diu", L"丢丟铥颩銩" },
{ L"d", L"ding", L"丁仃帄叮玎钉盯疔町虰耵酊釘靪艼奵顶頂鼎鼑嵿濎薡鐤订饤忊矴定訂飣铤萣啶椗腚锭碇碠錠顁磸" },
{ L"d", L"du", L"厾剢都阇督嘟醏闍独毒读渎牍椟犊裻読錖獨凟匵嬻瀆殰犢櫝牘瓄皾騳黩髑韣讀贕豄鑟韇韥黷讟肚笃堵赌琽睹賭覩篤芏杜妒妬度荰秺靯渡镀螙鍍殬斁蠧蠹叾獤" },
{ L"d", L"dou", L"吺剅都唗兜兠蔸橷篼唞斗阧抖枓钭陡蚪鈄吋豆郖读荳逗饾浢鬥渎酘毭梪脰痘閗窦鬦餖斣闘竇鬪鬬鬭乧" },
{ L"d", L"dong", L"东冬東咚苳岽昸氡鸫倲菄崬崠涷埬娻笗氭蝀鮗鼕鯟鶇董蕫嬞懂箽諌动冻侗垌恫栋胨迵姛峒挏洞凍胴戙動硐湩腖棟働駧霘鶫" },
{ L"d", L"dui", L"垖堆塠痽磓鴭鐜鐓頧队对兊兌対兑祋怼陮隊敦碓綐對憞憝錞镦薱濧懟瀩譈譵轛" },
{ L"d", L"duan", L"耑偳媏端褍鍴短段断葮缎塅煅瑖腶椴锻碫緞毈簖鍛斷躖籪" },
{ L"d", L"duo", L"多夛咄哆剟掇毲敠敪裰嚉夺度铎敚敓剫喥痥奪凙澤踱鐸驮朵朶杕饳剁沲哚挆柮柂垛垜埵缍舵崜惰媠椯躲躱趓跺綞亸鬌軃嚲奲刴陊陏挅尮桗堕跥飿墮憜墯鵽﨣鈬鯲" },
{ L"d", L"dun", L"吨惇敦蜳撴墩墪噸撉犜镦礅蹲蹾驐盹趸躉伅庉沌囤炖逇钝盾砘顿鈍遁頓楯遯潡燉踲碷壿" },

{ L"e", L"e", L"阿妸妿娿婀屙讹迗吪囮俄峉峨峩涐恶娥莪哦珴訛鈋皒锇睋鹅蛾誐磀噁鋨頟魤额額鵝鵞譌厄阸苊呃扼轭枙垩砨饿胺阏鄂谔萼遌遏崿愕頋腭锷鹗頞餩噩鳄騀戹岋呝砐砈咹咢姶匎蚅軛硆悪卾偔堊堨堮湂惡軶豟鈪琧廅搤搹僫蝁蕚遻餓颚閼擜諤覨鍔顎歞礘櫮鶚鰐鰪齃讍齶鑩鱷仒厑蛯旕鵈襨欕" },
{ L"e", L"en", L"奀恩蒽煾峎摁" },
{ L"e", L"ei", L"欸誒" },
{ L"e", L"eng", L"鞥椧" },
{ L"e", L"er", L"乻儿而児陑侕荋耏峏洏栭胹唲鸸袻聏輀鲕髵隭鴯鮞臑轜尔尒尓耳迩饵洱毦栮珥铒鉺餌爾駬薾邇二弍弐佴刵咡贰貮貳衈誀髶樲粫趰" },

{ L"f", L"fa", L"发冹沷発發酦彂乏伐姂坺垡茷阀疺罚栰笩筏傠瞂罰閥罸墢橃藅佱法峜砝灋珐琺髪髮蕟浌鍅" },
{ L"f", L"fang", L"匚方邡芳汸坊枋牥钫蚄淓趽鈁錺鴋防妨房肪鲂魴访仿彷纺昉昘瓬眆紡舫旊倣訪髣鶭放堏" },
{ L"f", L"fan", L"帆忛畨番勫蕃幡噃嬏憣旙旛繙翻藩轓颿飜籓鱕凡凣凢匥杋柉钒矾籵舤舧袢烦笲釩棥煩緐墦樊璠膰薠燔襎繁羳蹯鐇礬蘩瀿蠜鷭反払仮返橎犯氾汎奿饭泛贩范畈軓訉販笵盕梵軬飯飰滼嬎範輽瀪" },
{ L"f", L"feng", L"丰风凨仹凬妦沣凮枫盽疯砜封風峰峯偑桻烽堼葑崶渢猦锋犎楓蜂碸瘋篈僼鄷鋒檒豐鎽鏠酆蘴寷灃蠭靊飌麷冯夆沨浲逢溄堸馮艂漨缝摓綘縫讽覂唪諷凤奉俸湗焨煈赗鳯鳳鴌賵琒" },
{ L"f", L"fen", L"分芬帉吩纷氛昐玢衯紛翂躮訜酚棻梤鈖雰馚餴朆饙妢岎汾坟炃朌枌羒蚠蚡焚棼蒶隫魵蕡幩獖墳濆燌燓橨豮鼢羵鼖豶轒鐼馩黂粉黺份弅坋忿奋秎偾粪愤僨憤膹奮糞鲼瀵鱝竕瞓" },
{ L"f", L"fei", L"飞妃非飛菲啡婓婔渄绯扉猆暃靟裶蜚緋鲱霏馡餥騑騛鯡飝肥淝腓蜰朏胐匪诽奜悱棐斐翡榧蕜誹篚发芾吠狒沸怫杮废肺胇昲费厞剕陫俷疿萉屝廃費痱镄廢曊癈鼣蟦濷櫠鐨靅" },
{ L"f", L"fou", L"紑缶否妚缻缹雬殕鴀" },
{ L"f", L"fo", L"仏佛坲梻" },
{ L"f", L"fu", L"夫伕邞孚呋妋姇玞肤胕砆衭怤柎荂荴尃娐旉麸趺紨跗鈇稃綒筟鄜孵粰膚鳺麩敷麬糐麱懯乀巿弗凫伏甶佛刜芾芙芣扶拂泭岪绂绋咈帗苻茀枎怫服韨氟祓玸枹柫炥畐畉罘茯郛鳬俘垘洑浮哹莩蚨袚栿砩翇桴烰琈袱虙艴紱紼符笰菔匐涪幅葍絥罦棴鳧艀鉘鉜颫辐福蜉綍箙稪榑韍豧髴鴔蝠幞澓輻踾鮄諨黻襆癁鮲襥鵩鶝阝父甫抚拊弣府斧郙俛俌俯釜釡捬脯辅腑盙焤蜅滏腐輔頫嘸撫鬴簠鯱黼讣付妇负附彿咐驸坿竎阜訃負赴复祔峊袝蚥蚹副婦婏冨偩傅復萯媍富赋蛗秿覄詂鲋腹椱缚赙複褔蝮蝜緮蕧賦駙鮒輹嬔縛賻鳆鍑鍢馥覆鰒酜﨓椨禣" },

{ L"g", L"ga", L"夹旮伽呷咖嘎嘠轧钆釓尜噶錷玍尕尬魀乫凩軈" },
{ L"g", L"gai", L"侅该陔郂荄姟峐垓赅晐祴畡絯隑賅賌豥該忋改絠丐乢匃匄芥钙盖鈣摡溉葢蓋戤概槩漑槪瓂" },
{ L"g", L"gang", L"冈冮刚扛纲岗杠肛疘矼牨岡钢缸罡剛堈掆釭犅棡摃堽罁綱鋼鎠崗港焵焹筻槓戆戅戇" },
{ L"g", L"gan", L"干甘迀奸忓杆攼玕肝姏泔苷坩矸竿柑酐疳粓凲尴尲筸鳱漧尶尷魐仠芉皯衦秆赶笴桿敢稈感澉趕橄澸擀簳鳡鱤汵旰盰绀凎倝淦紺詌骭幹榦檊贑赣贛灨" },
{ L"g", L"gao", L"羔皋高羙髙皐臯膏睾槔槹橰糕篙餻韟櫜鼛鷎鷱夰杲菒稁搞缟槁槀暠稿稾镐縞藁藳檺鎬告郜勂诰峼祮祰锆筶誥禞鋯吿" },
{ L"g", L"gei", L"给給" },
{ L"g", L"ge", L"戈仡犵扢纥圪戓肐牫疙饹咯哥胳格鸽袼搁割滒歌戨鴚鴿謌擱鎶呄匌佮茖阁挌革鬲敋葛隔裓蛤蛒臵愅觡嗝滆塥搿槅膈閤閣鞈骼韐镉獦諽輵鮯鎘韚騔鞷轕个合各哿盖舸嗰虼個铬硌箇鉻乬巪叾唟彁櫊" },
{ L"g", L"geng", L"更刯庚畊耕浭菮赓焿絚鹒縆緪賡羮鶊羹郠莄哽峺挭绠埂耿颈梗綆鲠骾鯁堩暅椩" },
{ L"g", L"gen", L"根跟哏艮亘亙茛揯搄" },
{ L"g", L"gu", L"估杚姑沽泒孤苽咕呱轱柧骨鸪罛唂唃家菰菇蛄笟軱軲觚辜酤蓇鈲毂稒箍箛篐嫴橭鴣鮕鹘夃古诂汩谷股苦牯羖贾钴罟蛊啒淈愲尳詁鹄馉鈷榾嗀鼓鼔榖嘏皷穀縎糓薣濲臌皼餶轂盬瞽瀔鶻蠱固故顾凅牿梏崮崓堌棝雇祻锢痼僱錮鲴鯝顧逧脵傦" },
{ L"g", L"gou", L"勾句沟佝枸钩痀袧鈎缑鉤溝褠緱篝簼鞲韝芶苟狗岣耇耉玽蚼笱耈豿诟坸购构姤垢冓够夠啂訽詬雊遘彀媾搆煹觏構撀購覯" },
{ L"g", L"gong", L"工弓公厷功共红杛攻供侊肱糼糿宫宮恭蚣躬龚匑幊愩塨觥躳慐匔碽髸觵龏龔廾巩汞拱栱拲珙輁鞏贡唝貢嗊熕赣" },
{ L"g", L"guai", L"乖摑叏拐柺枴罫箉夬怪恠" },
{ L"g", L"gua", L"瓜刮呱胍栝桰鸹歄煱趏劀緺踻颳鴰騧冎叧剐剮寡卦诖坬挂掛啩罣絓詿褂颪" },
{ L"g", L"guan", L"关观纶官冠矜覌倌莞蒄棺窤関瘝癏観闗鳏關鰥鱞觀馆琯筦痯管輨錧館璭舘鳤卝毌丱串贯泴掼涫惯悺貫悹祼慣潅摜遦樌盥罆雚躀鏆灌瓘爟矔鹳礶罐鑵鸛鱹欟" },
{ L"g", L"gui", L"归圭妫龟邽规茥闺皈胿珪帰亀硅袿規廆椝媯郌瑰摫閨鲑嫢嬀槻槼龜璝瞡鮭歸雟鬶嶲騩瓌鬹蘬宄氿轨庋匦陒佹诡姽垝恑攱癸軌鬼祪庪匭晷湀蛫觤詭厬簋蟡攰昋刿刽炅炔柜贵桂桧椢猤筀貴跪蓕瞆螝撌劌劊槶樻檜禬瞶癐襘櫃鐀鳜鞼鑎鱖鱥櫷" },
{ L"g", L"guang", L"光灮炗炚炛茪咣姯洸垙烡桄珖胱輄僙銧黆广広犷廣獷臩俇逛臦" },
{ L"g", L"gun", L"丨衮袞绲惃辊棍蓘滚滾蔉緄緷輥鲧磙鮌鯀睔謴" },
{ L"g", L"guo", L"过呙咶涡埚郭堝啯猓崞锅楇聒鈛瘑墎濄蝈彉嘓鍋彍蟈懖囯国囶囻圀國帼掴腘漍聝幗蔮慖虢膕馘簂果菓馃淉惈褁椁槨蜾粿綶裹輠餜過腂鐹" },

{ L"h", L"han", L"犴佄顸哻蚶酣頇谽嫨憨馠魽鼾邗汗邯含函凾虷唅娢浛圅焓梒晗琀涵崡嵅寒韩甝筨蜬鋡澏韓罕浫喊蔊豃厈汉屽扞闬旱垾悍猂莟捍涆菡焊晘釬閈皔睅蛿傼馯感颔漢撖蜭熯銲鋎暵頷憾螒翰撼顄駻雗譀瀚鶾兯爳" },
{ L"h", L"hai", L"咍咳嗨还孩骸海胲烸酼醢亥妎骇害氦餀嗐駭駴饚塰" },
{ L"h", L"ha", L"呵哈紦铪鉿虾蛤奤乤扖溌噺鎺鱩" },
{ L"h", L"hao", L"茠蒿薅薧嚆乚毜皋蚝毫椃嗥獆貉豪獔噑嘷獋儫濠壕嚎蠔籇譹好郝号昊昦侴秏悎耗哠浩恏晧淏傐皓鄗聕號滈暤暭皞皜澔镐薃皡曍皥颢顥鰝灏灝竓" },
{ L"h", L"hang", L"夯炕行苀迒吭斻杭肮绗桁珩蚢航笐颃貥裄絎筕頏魧沆巷垳" },
{ L"h", L"hen", L"拫痕鞎佷很哏狠詪恨" },
{ L"h", L"hei", L"黒黑嗨嘿潶" },
{ L"h", L"he", L"诃呵抲欱牙合訶喝嗬蠚禾纥何和咊郃劾姀河盇柇狢峆饸阂曷籺紇釛荷核敆盍盉害涸渮盒菏萂啝龁訸颌惒楁澕毼阖鲄詥貉貈鉌閡餄麧熆鹖頜魺螛翮篕餲鞨齕闔礉覈鶡皬鑉龢吓佫贺垎哬袔寉焃鹄猲賀碋嗃煂熇褐赫鹤翯癋謞壑嚇燺爀鶴鶮鸖靍粭遤靎靏" },
{ L"h", L"hong", L"叿吽呍灴轰哄訇烘軣焢硡揈渹谾薨輷鍧嚝轟仜弘妅屸红纮玒汯吰闳宏宖苰泓玜垬沗虹紅洪娂荭羾翃浤紘耾竑鸿硔紭谹鈜閎粠竤渱葓葒綋谼翝鉷鞃魟潂鋐篊黉霐彋蕻霟鴻黌唝晎讧訌閧銾撔澒闂鬨闀" },
{ L"h", L"heng", L"亨哼涥悙脝行恒恆姮珩胻烆桁鸻撗横橫衡鴴蘅鑅鵆啈" },
{ L"h", L"hu", L"乎匢戏虍芴苸呼泘垀昒忽曶恗烀轷匫唿惚淴虖軤雽雐滹嘑寣幠糊歑膴謼抇囫狐弧和瓳胡核壶隺壷斛焀鹄絗壺猢搰湖喖葫媩煳楜瑚鹘鹕蔛嘝蝴箶槲魱衚頶醐螜縠鍸餬觳鵠鬍瀫鶘鶦鰗乕汻虎浒俿萀唬虝琥滸錿互弖户戶戸冱芐护沪沍帍戽岵怙枑昈祜怘笏瓠扈婟楛雇綔嗀嗀鄠嫭嫮蔰滬摢槴熩鳸鍙豰簄嚛鹱護鳠頀鸌鱯粐" },
{ L"h", L"hua", L"化华花哗砉錵蘤划呚骅姡華铧釫釪猾滑嘩搳撶劃磆鲑螖鋘蕐譁鏵驊鷨夻话杹枠画桦崋婳畫畵嬅觟話摦樺槬澅嫿諙諣黊舙繣譮婲埖椛硴蒊糀誮" },
{ L"h", L"huan", L"欢犿狟歓鴅鵍酄嚾孉獾懽歡讙貛驩还郇环荁峘洹桓萑萈寏堚雈絙綄貆獂羦锾圜澴缳寰嬛還阛鍰環豲镮鹮糫繯轘鐶闤鬟瓛缓睆緩幻肒奂奐宦唤换涣浣眩烉焕梙逭患嵈喛喚渙換愌痪豢瑍煥瘓漶鲩槵澣擐藧鯇攌鯶鰀" },
{ L"h", L"huai", L"怀徊淮槐褢踝褱懐懷瀤櫰耲蘹坏壊壞蘾" },
{ L"h", L"hou", L"齁侯矦鄇葔帿喉猴睺瘊銗篌骺糇翭翵鍭餱鯸吼犼后郈厚茩後逅洉垕候堠豞鲎鲘鮜鱟" },
{ L"h", L"hun", L"昏昬荤阍婚涽惛殙棔葷睧睯蔒閽轋忶浑珲混馄渾魂琿餛鼲诨俒圂溷慁倱婫掍焝睴觨尡諢" },
{ L"h", L"huang", L"巟肓荒衁宺朚塃慌皇隍凰偟黄黃葟徨遑喤媓崲揘湟堭惶煌楻瑝锽墴潢獚熿蝗璜艎篁諻穔癀磺蟥簧餭鳇鍠韹趪騜鐄鰉鱑鷬怳恍炾晃晄谎奛幌詤熀縨謊兤櫎滉愰榥曂皝鎤皩" },
{ L"h", L"huo", L"吙秴耠锪劐嚄豁騞攉佸和活秮秳灬火邩伙钬鈥煷漷夥沎货或咟俰获捇眓閄貨掝祸喐剨湱禍惑旤蒦窢鍃霍濩獲奯擭檴雘謋穫镬矆彟瀖嚯藿蠖耯艧嚿曤臛矐癨鑊韄靃彠" },
{ L"h", L"hui", L"戏灰灳炜诙咴挥拻洃恢袆虺珲烣晖豗堕婎媈揮隓辉翚暉禈睢煇楎詼睳褘幑噅噕撝翬輝麾徽隳瀈蘳鰴囘回囬佪廻廽茴迴恛洄蚘烠逥痐蛔蛕蜖鮰虫悔毁毀毇燬檓譭卉屶屷汇讳会泋浍绘哕诲荟芔贿烩桧恚恵晦彗秽絵翙廆惠喙缋阓湏滙匯會彚彙賄詯誨瘣僡嘒蔧蕙潓寭圚憓槥暳慧橞諱嬒獩濊薈薉徻頮餯藱篲檅燴璯繢穢瞺蟪嚖懳繪翽譓櫘鏸儶闠靧鐬譿顪颒璤" },

{ L"j", L"ji", L"几讥叽击刉饥圾机刏乩芨玑肌鸡矶奇其枅咭唧剞姬屐积畟笄飢基庴喞嵇嵆幾赍犄筓缉朞稘畸嗘跻鳮銈僟綨緁箕毄稽鹡觭躸諆緝畿嘰槣齑錤機禨墼激隮襀積璣磯羁賷簊擊櫅耭雞韲鶏譏譤鐖饑躋鷄鞿魕癪羇虀鑇鑙齏覉羈鸄覊亼亽及伋彶吉汲岌级忣极即亟郆佶卽姞叝急皍級笈革觙揤疾堲楖焏偮卙谻集殛戢棘極湒塉嵴楫辑愱蒺嫉蝍趌銡耤膌槉嶯潗濈蕺蕀瘠箿踑踖輯螏檝藉磼襋蹐鍓艥籍鏶霵轚鶺齎躤雧己丮妀犱纪泲虮济给挤脊掎鱾戟麂魢撠橶穖擠蟣彑计旡记伎齐系忌坖际芰妓技剂季迹垍既紀荠茤茍洎哜計記剤紒觊继绩悸梞旣祭偈徛寄寂済葪蔇惎臮跡鬾魝裚痵継蓟際兾勣漈漃禝穊稩暨魥鲚霁跽誋諅鲫暩稷穄曁冀劑薊髻覬薺嚌濟檕績罽繋璾檵蹟鵋鯽齌鯚懻癠穧骥蘎蘮瀱繼鱀鰶鰿鷑霽蘻鱭驥﨤樭撃鯲廭" },
{ L"j", L"jiang", L"江茳将姜浆畕豇將葁畺摪翞僵螀漿薑缰壃殭橿螿鳉礓疅疆繮韁鱂讲奖桨蒋傋塂奨奬蔣槳獎膙耩講顜匞匠弜夅降洚绛弶强絳酱勥滰嵹摾犟糡醤醬糨謽櫤" },
{ L"j", L"jie", L"节阶疖皆结階接掲秸痎街揭嗟喈喼媘嫅堦椄湝脻楷煯稭鞂蝔擑謯癤鶛卩卪孑尐讦刧劫岊刦杢昅杰疌衱劼刼诘狤洁拮迼桔桀訐莭倢偈偼菨婕崨捷掶袺蛣絜結媫傑颉鉣嵥搩滐節睫詰蜐楬楶榤截鲒碣竭蓵潔镼鞊頡誱踕羯幯嶻擮鮚礍鍻巀蠞蠘蠽毑姐媎解觧飷檞丯介价芥岕庎吤戒届屆玠疥砎界畍衸诫借蚧悈徣唶堺楐琾骱蛶誡犗褯魪鎅藉桝" },
{ L"j", L"jiao", L"艽交郊茭茮骄娇姣峧浇胶教焦椒蛟跤虠鲛僬蕉澆憍嶕嶣嬌膠膲徼鮫穚鹪礁鵁簥轇蟭鐎驕鷦鷮矫嚼臫角侥佼狡饺挢绞烄晈捁笅皎脚铰搅湫絞筊賋勦剿腳敫煍暞僥摷踋鉸餃撟撹儌徺劋敽缴憿敿矯曒璬蟜皦繳譑孂灚攪鱎龣叫呌挍峤觉訆珓校轿较敎窌窖較滘漖嘄嘂嘦斠酵嶠噍潐嬓獥噭藠轎醮趭譥皭釂" },
{ L"j", L"jian", L"戋尖幵奸间歼坚浅戔冿玪肩艰姦姧兼监笺豜菅菺猏惤渐堅缄溅湔葌間雃犍牋瑊椷椾睷碊蒹搛缣煎蔪箋鲣緘鹣樫蕑蕳熞鳽熸縑鋻餰馢鞬艱鞯鳒瀐鵑鵳殱礛瀸鰔鰜鶼殲櫼譼韀礷鰹囏虃韉鑯暕囝枧拣俭茧柬笕倹捡挸湕帴减剪检梘趼詃検锏睑硷裥堿減揃揀谫弿瑐絸筧简戬戩碱儉翦篯撿藆襇襉檢謇蹇謭簡繭礆瞼鬋鹸鰎蠒鐧鐗瀽鹻譾籛襺鹼见件見建饯贱洊荐剑牮珔舰剣健俴涧栫剱谏徤袸毽臶腱践跈寋楗旔賎鉴键監槛榗漸僭劎劍澗箭糋諓賤踺踐趝餞諫鍵薦劒劔鍳瞷磵礀繝濺檻擶瀳譛鏩覵覸艦轞鐱鑑鑒鑬鑳豣彅墹麉" },
{ L"j", L"jia", L"加夹夾伽抸拁泇佳茄迦珈浃毠枷浹家痂耞笳袈梜葭傢跏猳腵筴鉫犌嘉镓豭貑鴐鎵麚甲扴圿忦郏郟荚莢唊恝脥铗戛戞裌蛱颊蛺跲頬鋏頰鴶鵊岬叚玾胛钾贾斚假婽徦斝椵賈鉀槚榎嘏瘕檟价驾架嫁幏榢價駕稼嗧糘" },
{ L"j", L"jiu", L"丩勼纠朻牞鸠究糺糾赳阄萛啾揪揂湫鳩揫摎樛鬏鬮九久乆乣氿汣奺灸玖舏韭紤镹酒韮匛旧臼疚咎柩柾桕倃匓厩救就廄廐舅廏僦慦殧舊鹫鯦麔匶齨鷲杦欍" },
{ L"j", L"ju", L"车凥且抅拘泃匊狙岨苴驹居陱毩捄挶眗疽砠罝梮蛆掬据涺崌娵婮毱趄跔跙椐琚腒锔裾雎蜛艍躹諊踘鋦駒鴡鮈鞠檋鞫鶋局泦侷狊桔郹焗菊啹婅淗湨椈輂犑閰跼粷趜橘駶鵙繘鵴蹫鶪鼰巈蘜鼳驧弆咀沮柜枸举莒矩挙椇筥龃榉榘蒟聥舉踽擧櫸齟欅襷籧巨句讵苣邭姖岠拒洰怇炬歫拠具昛秬钜剧俱倨倶袓蚷耟粔詎距埧埾惧犋鉅飓虡豦锯窭寠聚愳駏鮔踞屦劇勮遽據澽懅窶壉鋸颶屨貗簴醵躆鐻懼﨔" },
{ L"j", L"jiong", L"冂冋坰扃埛駉駫蘏蘔囧冏迥泂炅炯逈侰浻烱絅颎煚窘綗僒煛熲褧澃顈燛" },
{ L"j", L"jing", L"巠坕坙泾茎京径经亰荆荊秔涇婛猄惊旌旍菁経稉葏晶腈睛經粳精綡聙兢鲸麖鶄鶁鯨鼱驚麠井丼阱刭宑汫坓汬肼穽剄殌景儆頚幜澋憬璄璟璥憼暻頸蟼警劲妌迳弪净浄俓婙胫莖弳逕倞徑凈竞痉竟竫淨桱梷婧脛靓敬竧痙傹靖静獍誩踁境靚靜镜曔瀞鵛鏡競竸橸" },
{ L"j", L"jin", L"巾今仐斤钅金釒觔矜衿荕津珒紟矝琎惍釿堻筋禁璡黅鹶襟仅尽卺侭巹紧堇菫厪谨僅锦嫤馑漌蓳廑緊槿瑾儘錦謹饉伒劤妗劲进近枃浕勁荩浸赆烬晋晉祲進唫煡缙溍寖搢靳盡墐瑨歏殣凚僸觐縉賮噤濅濜嚍藎嬧燼璶覲贐齽兓砛琻壗" },
{ L"j", L"jun", L"军君汮均龟袀軍姰钧莙蚐桾菌皲鈞碅筠覠銞皸皹銁鲪頵麇鍕鮶麏麕呁郡陖俊骏峻馂捃浚埈隽焌晙珺葰竣畯棞雋蜠箘箟賐儁寯懏餕燇駿濬鵔鵕鵘攈攟" },
{ L"j", L"juan", L"姢娟捐涓圈焆朘鹃裐勬镌鋑鎸鐫蠲呟卷帣埍菤捲锩踡錈臇奆劵巻狷勌倦桊绢悁隽眷鄄淃瓹腃睊罥絭絹睠慻蔨餋獧羂讂" },
{ L"j", L"jue", L"噘撅撧屩屫亅孓孒决刔诀氒角芵弡決抉泬玦玨珏觉疦砄虳绝挗捔倔蚗欮脚桷斍覐觖訣赽掘崛崫趹鈌焳傕厥趉覚絶絕阙劂谲瑴駃鴃鴂瘚爴觮獗噊蕨蕝熦憰嶡嶥噱憠橛橜镢臄爵櫭蟩蟨譎爑蹶蹻蹷鐍鐝矍鳜嚼匷覺觼爝灍戄攫玃彏鷢矡貜躩钁" },

{ L"k", L"ka", L"咖咔喀卡佧咯胩鉲凧垰桛裃閊綛聢鯑鶍" },
{ L"k", L"kai", L"开奒開揩锎鐦凯剀闿恺垲铠慨剴蒈凱嘅嵦愷楷塏輆锴暟鍇鎧闓颽忾炌烗欬勓愾鎎" },
{ L"k", L"ken", L"肎肯肻垦恳啃豤貇錹墾懇掯硍裉褃" },
{ L"k", L"kao", L"尻嵪髛丂考攷拷洘烤栲铐熇犒銬鲓靠鮳鯌廤" },
{ L"k", L"kan", L"刊看栞龛勘嵁堪戡龕凵冚坎侃砍莰偘惂欿歁槛輡顑轗竷衎崁墈阚磡瞰闞鬫矙" },
{ L"k", L"ke", L"匼苛坷呵牱牁珂科轲柯钶疴砢趷蚵痾軻颏棵萪稞犐搕鈳窠颗薖榼樖頦瞌蝌磕顆髁醘礚壳咳殻殼翗揢可岢炣渇渴敤嵑嶱克刻勀勊客峇恪娔课骒氪堁衉愘缂溘愙锞嗑碦緙艐課錁騍礊厼迲硛嵙兡穒鯑" },
{ L"k", L"kang", L"忼砊粇康閌嫝嵻漮慷槺穅糠躿鏮鱇扛亢匟邟伉闶犺抗囥炕钪鈧" },
{ L"k", L"kua", L"夸咵姱誇侉垮銙挎胯趶跨骻舿" },
{ L"k", L"ku", L"刳郀矻枯桍哭堀圐跍窟骷鮬苦狜楛库绔俈秙庫焅袴裤絝喾瘔酷褲嚳萙鶎" },
{ L"k", L"kou", L"芤抠眍剾摳彄瞘口劶叩扣怐敂宼冦寇釦窛筘蔻蔲滱瞉簆鷇" },
{ L"k", L"kong", L"空倥崆涳埪悾硿箜躻錓鵼孔恐控鞚" },
{ L"k", L"keng", L"阬劥吭妔坑挳硁牼铿硜硻誙摼銵鍞鏗" },
{ L"k", L"kuan", L"宽寛寬臗髋髖梡欵款歀窽窾鑧" },
{ L"k", L"kuai", L"蒯擓巜凷会块快侩郐浍哙狯脍欳塊筷鲙墤鄶儈廥澮獪噲膾糩旝鱠圦" },
{ L"k", L"kui", L"亏岿刲悝盔窥聧窺虧顝闚巋奎晆隗鄈逵馗揆葵喹骙暌戣楏楑魁睽蝰頯鍨鍷櫆藈騤夔蘷虁巙犪躨傀煃跬頍磈蹞归尯匮蒉喟媿馈溃愦愧匱蕢嬇嘳憒潰聩聭篑謉殨膭餽簣聵籄饋" },
{ L"k", L"kuang", L"匡邼劻诓哐洭恇匩硄筐筺軭誆狂狅抂忹诳軖軠誑鵟夼儣懭邝纩圹况旷岲況矿昿贶眖砿框絋眶絖貺軦鉱鋛鄺壙黋爌曠懬穬矌礦纊鑛" },
{ L"k", L"kun", L"坤昆晜裈堃菎猑崑崐焜琨髠髡锟鹍裩褌蜫髨醌瑻熴錕鲲騉鵾鯤鶤捆悃阃壸梱祵稇硱裍綑稛壼閫閸困涃睏堒潉" },
{ L"k", L"kuo", L"扩拡括挄栝蛞筈萿葀阔廓頢髺韕鞟闊擴濶霩鞹鬠" },

{ L"l", L"lan", L"兰岚拦栏惏婪嵐阑葻蓝谰澜褴斓儖篮镧闌藍襕懢燷燣璼襤幱譋繿籃蘭蘫瀾灆攔欄斕襴灡囒籣讕躝欗襽鑭韊览浨揽缆榄漤罱醂覧壈懒擥懶嬾孄覽孏攬爦欖顲纜烂滥燗濫嚂爁爛瓓灠爤糷钄" },
{ L"l", L"la", L"拉垃柆菈啦喇搚邋旯剌砬揦磖嚹藞翋落腊楋揧蜡蝋辣辢瘌蝲臈癞鬎臘攋爉瓎櫴镴鯻蠟鑞凩溂鞡鮱" },
{ L"l", L"lai", L"来俫莱徕崃涞梾铼來倈郲徠逨庲唻婡猍崍淶萊赉棶琜睐筙赖箂錸濑癞騋麳鶆鯠籁襰睞賫賚賴頼顂鵣藾瀨瀬癩籟萙" },
{ L"l", L"lang", L"啷勆郎郞郎欴莨狼桹蓈廊嫏琅斏稂锒硠瑯榔蜋艆筤郒躴螂樃鋃鎯朗朖烺蓢塱誏朤阆崀浪埌蒗閬" },
{ L"l", L"lao", L"捞撈劳労牢窂涝浶唠哰崂勞铹痨僗嶗潦憥癆磱蟧簩醪鐒顟髝耂老佬荖咾姥狫恅栳珯铑銠獠轑络烙閖落嗠酪耢嫪嘮澇憦躼橯耮軂硓粩朥" },
{ L"l", L"leng", L"棱唥塄楞稜碐薐冷倰堎愣睖踜" },
{ L"l", L"le", L"肋嘞仂阞忇艻叻扐氻乐玏泐竻砳勒楽餎韷樂簕鳓鰳鱳朰榁" },
{ L"l", L"li", L"哩刕丽厘骊剓荲狸离梨梸犁琍悡菞喱犂棃鹂缡蜊艃筣漓蓠剺嫠孷樆璃盠貍鋫鲡黎褵犛蔾縭篱罹錅謧醨蟍釐離藜嚟邌斄瓈鏫鵹鯬蟸黧蠡蠫灕囄蘺孋廲劙鑗籬穲纚驪鱺鸝礼礼里李俚峛峢峲逦娌理锂裡裏裏豊鋰鲤澧禮鯉醴鳢邐鱧鱱欚力历厉屴立朸吏呖励利叓苈坜沥沴岦枥苙例戾疠隶疬砅赲俪俐荔茘郦栎栃轹猁悧珕栗栛涖浰莉莅娳砺砾秝鬲蛎蚸粝粒笠婯唳脷悷棙傈凓厤跞詈蛠痢雳鳨睙鉝厯蒞蒚搮溧塛慄暦歴瑮厲綟蜧蝷篥鴗隷勵歷曆巁濿檪隸鬁磿癘犡爄蠇櫔曞禲擽儮嚦攊藶瓅櫟瀝壢礪麗礫蠣爏糲盭櫪瓑皪酈儷癧礰麜鷅轢觻躒囇攦欐讈轣靂瓥攭靋唎甅睝粴魞聢竰糎鯏鯐" },
{ L"l", L"lei", L"勒累傫雷蔂缧嫘畾樏擂儡縲攂镭礌櫑瓃羸礧罍纍蘲鐳轠鑘靁虆欙纝鼺厽耒诔洡垒絫塁誄漯蕌磊磥蕾藟壘癗櫐礨蠝灅蘽讄儽壨鑸鸓肋泪类涙淚酹銇頛頪錑檑颣類纇蘱禷矋" },
{ L"l", L"lia", L"俩" },
{ L"l", L"lian", L"连奁怜帘涟連莲梿裢联廉慩蓮亷漣溓嗹匲奩槤熑覝鲢聨聫磏褳憐匳劆噒嫾濂濓薕螊聮縺翴聯謰蹥燫櫣臁镰鎌簾蠊瀮鬑鰱鐮籢籨敛琏脸裣摙璉蔹嬚鄻斂歛臉襝羷蘞蘝练炼恋殓堜僆萰媡湅链煉楝瑓潋練澰錬鍊殮鏈鰊瀲戀纞" },
{ L"l", L"liang", L"良俍莨凉凉梁涼椋辌量粮粱踉墚樑輬駺糧両两兩俩倆唡啢掚脼裲蜽緉魉魎亮谅哴悢倞辆晾喨湸靓輌諒輛鍄" },
{ L"l", L"liao", L"撩蹽辽疗聊尞憀膋僚寥嵺漻潦缭嘹嶚嶛寮嫽獠遼敹暸璙膫燎橑療鹩竂蟟繚簝賿豂蹘廫藔屪爎爒飂髎飉鷯了钌釕鄝蓼憭瞭镽尥尦炓料廖撂窷镣鐐" },
{ L"l", L"lie", L"裂列劣劽冽挒茢迾咧姴洌浖埒埓烈哷烮栵捩猎猟蛚聗趔煭巤颲鴷鮤儠獵擸犣躐鬛鬣鱲挘" },
{ L"l", L"lin", L"拎厸邻阾林临冧啉崊淋晽粦琳碄粼箖鄰隣隣遴潾嶙獜暽辚燐斴璘霖瞵磷疄臨繗翷麐轔鏻鳞瀶壣驎麟鱗菻亃僯凛凜撛澟懔懍廪廩檩檁癛癝吝恡悋赁焛賃蔺橉甐膦閵蹸藺躏躙躪轥" },
{ L"l", L"liu", L"溜熘澑蹓刘畄浏斿流留琉旈畱裗硫遛旒蒥蓅骝媹嵧馏飗榴瑠镏瘤瑬劉磂駠鹠橊疁镠璢癅蟉駵麍鎏鎦嚠瀏懰藰鏐飀騮鐂飅鶹鰡驑柳栁桞珋桺绺锍綹鋶罶熮橮羀嬼六陆翏廇塯碌鹨磟餾霤雡飂鬸鷚" },
{ L"l", L"ling", L"令伶刢灵坽囹夌苓彾呤姈狑泠柃朎昤瓴玲皊秢铃竛鸰砱陵羐凌菱淩崚掕婈棂琌蛉聆紷衑翎舲笭绫羚詅軨跉祾棱裬蓤龄鈴閝零綾蔆輘霊駖鹷鴒魿霗鲮錂蕶澪燯霛霝齢鯪酃孁齡櫺醽麢欞爧龗岭岺袊领領嶺另炩蘦靈" },
{ L"l", L"long", L"龙茏咙泷栊昽珑胧竜眬砻聋笼隆湰滝漋槞嶐窿篭龍癃鏧霳巃巄瀧嚨蘢爖櫳瓏曨襱朧矓礱礲龒龓籠豅躘聾蠪蠬靇鑨驡鸗陇拢垄垅篢隴儱壟壠攏竉弄哢梇徿贚" },
{ L"l", L"lou", L"搂瞜娄婁偻蒌溇喽楼漊慺蔞遱廔嘍熡樓蝼耧耬艛螻軁謱髅髏鞻鷜嵝嶁摟塿甊篓簍陋屚漏镂瘘瘺瘻鏤露" },
{ L"l", L"lu", L"噜撸謢擼嚕卢芦庐泸垆炉枦栌胪鸬舮舻玈颅鲈馿魲盧璷壚瀘蘆廬嚧獹攎爐櫨曥瓐臚矑艫籚蠦罏纑鑪髗顱鱸鸕黸卤虏掳鹵鲁硵虜蓾滷塷澛樐魯磠橹擄穞镥瀂氌櫓艣鏀鐪艪鑥六圥甪陆侓录彔坴峍赂辂陸勎娽逯菉渌淕淥硉绿鹿椂禄祿琭勠僇剹稑盝睩碌賂輅路粶箓蓼蔍廘漉摝塶辘戮熝樚膔踛醁趢録錄錴穋潞蕗璐簏螰鴼蹗騄轆簶鹭簬簵鏕鵦鵱麓鯥騼鏴露籙鷺虂轳焒閊鈩氇轤" },
{ L"l", L"lv", L"驴闾榈閭膢氀櫚藘驢吕呂郘侣侶挔捛捋旅梠祣偻铝稆絽屡缕僂屢膂褛鋁履褸膐縷儢穭律垏虑绿率氯葎嵂滤綠緑慮膟箻繂勴濾爈櫖鑢" },
{ L"l", L"luan", L"娈峦孪栾挛脟鸾脔滦銮鵉巒孌奱孿圝攣灓欒曫羉臠圞虊灤鑾癴癵鸞卵乱釠亂" },
{ L"l", L"lue", L"寽畧稤鋝鋢" },
{ L"l", L"lve", L"掠略锊圙" },
{ L"l", L"lun", L"抡掄仑伦论芲沦纶囵侖轮倫陯圇淪菕婨崘崙棆腀碖蜦耣綸輪踚錀鯩埨惀稐溣論嗧磮" },
{ L"l", L"luo", L"捋啰落頱囉罗萝逻猡脶腡椤锣骡箩镙螺羅覶鏍騾覼蠡儸邏蘿玀攞欏驘鸁籮鑼饠囖剆倮蓏裸躶瘰蠃臝曪癳泺洛咯骆峈荦络烙洜珞硌硦絡跞笿詻雒犖摞漯駱鵅鮥濼纙鮱" },

{ L"m", L"m", L"呒呣姆" },
{ L"m", L"mai", L"埋薶霾买荬買嘪鷶劢迈麦佅売卖脉脈麥衇勱賣邁霡霢蕒" },
{ L"m", L"ma", L"亇妈孖抹蚂麻媽嫲摩吗嗎痲痳蔴犘蟆马犸玛码馬獁溤瑪碼螞鎷鷌鰢杩祃骂閁唛傌睰嘜禡榪罵駡鬕唜嘛魸蟇" },
{ L"m", L"man", L"埋嫚颟顢悗蛮谩蔓馒摱慲樠瞒瞞鞔謾饅鳗鬘鬗鰻蠻娨屘満满滿螨蟎鏋矕曼鄤僈蔄幔獌漫缦墁慢熳槾镘澷縵鏝襔" },
{ L"m", L"mang", L"邙牤芒吂汒忙尨杧杗氓盲盳笀恾茫厖庬哤娏狵浝牻釯铓硭痝蛖鋩駹蘉莽莾硥茻壾漭蟒蠎" },
{ L"m", L"mao", L"猫貓毛矛枆茆茅牦旄罞軞酕渵堥楙锚髦鉾蝥氂髳錨蟊鶜冇夘卯戼峁泖昴铆笷鉚蓩冃芼皃茂冐冒贸柕眊耄覒袤貿鄚萺帽媢毷暓瑁愗鄮貌瞀蝐懋毟" },
{ L"m", L"mei", L"没沒坆苺枚玫栂眉脄莓郿脢梅珻睂堳湄湈葿媒猸嵋腜瑂禖楣楳煤酶槑镅鹛塺鋂霉鎇徾糜攗鶥黴毎每美凂挴浼羙嵄渼媄媺镁嬍燘躾鎂黣妹抺沬袂昧祙眛谜寐媚跊鬽痗煝魅韎睸蝞篃" },
{ L"m", L"me", L"乄么匁扖庅嚒濹嚜嚰" },
{ L"m", L"men", L"闷门们扪汶玧钔門閅們菛捫璊穈鍆亹虋焖悶暪燜懑懣椚" },
{ L"m", L"meng", L"掹蒙擝尨甿氓虻莔萌溕盟鄳甍蝱鄸儚蕄瞢橗幪濛懞檬曚氋朦鹲礞鯍矇艨矒饛霿靀顭鸏黾勐冡猛锰蜢艋錳獴懵蠓鯭鼆孟梦夢夣懜霥" },
{ L"m", L"mi", L"咪眯瞇弥祢迷猕谜蒾詸謎醚糜縻麋麊麿藌彌擟禰靡麛瀰獼蘪镾蘼戂攠瓕爢醾醿鸍釄米芈羋侎沵洣弭敉脒渳葞蔝銤濔孊灖冖糸汨沕泌怽宓觅祕峚宻秘覔覓密淧幂谧蓂幎覛塓蜜榓鼏蔤滵漞嘧熐冪樒幦濗謐簚櫁羃鼡袮粎裃椧嚸欕" },
{ L"m", L"mian", L"宀芇杣眠绵婂媔棉綿臱蝒緜嬵檰櫋矈矊矏丏汅沔免勉俛眄娩渑偭勔冕葂喕湎睌缅愐腼緬澠靦鮸靣面麪麫糆麺麵" },
{ L"m", L"miao", L"喵苗媌描瞄鹋緢嫹鶓劰杪秒眇渺缈淼緲篎藐邈妙庙竗玅庿缪廟" },
{ L"m", L"min", L"民玟苠姄岷怋旻旼盿砇珉罠崏捪缗琘琝瑉碈痻鈱緍緡錉鴖鍲皿冺刡忟闵黾抿泯忞敃勄闽悯敏笢閔黽惽湣敯暋愍閩僶潣憫慜簢鳘蠠鰵垊笽" },
{ L"m", L"mie", L"乜吀咩哶孭灭烕搣滅蔑薎鴓幭篾瀎懱櫗礣蠛衊鑖鱴旀" },
{ L"m", L"ming", L"名明鸣眀洺茗冥眳朙铭鄍蓂溟嫇猽詺銘鳴榠暝瞑螟覭佲姳凕慏酩命掵" },
{ L"m", L"miu", L"谬缪謬" },
{ L"m", L"mo", L"摸嚤无尛谟嫫馍模摹膜麽麼摩橅磨糢謨謩嬷嬤擵饃蘑髍魔劘饝万抹懡末圽没沫陌妺茉帓殁歾歿枺昩脉帞冒莫莈皌秣砞眜眿袜絈眽貃蛨貊塻蓦嗼漠寞獏銆靺魩黙嫼嘿墨瞐瞙瘼镆默貘蟔鏌藦爅癦驀纆礳耱丆匁乮裃酛魹囕" },
{ L"m", L"mou", L"哞牟劺侔呣恈谋眸蛑缪踎謀鍪麰鴾繆某" },
{ L"m", L"mu", L"毪氁模母牡亩姆畂拇畆畒姥峔牳胟砪畝畞畮鉧踇木目仫牟狇沐坶苜牧炑毣莫莯蚞钼雮募慔幕幙墓鉬睦楘慕暮暯艒霂縸穆鞪厼榁" },

{ L"n", L"na", L"那南拏拿嗱搻镎鎿乸哪雫内呐吶妠纳肭郍娜钠衲袦納笝軜豽捺貀鈉靹蒳魶凪魸噺" },
{ L"n", L"nai", L"腉孻乃艿奶氖疓廼迺哪倷釢嬭佴奈柰耐萘渿鼐褦螚錼" },
{ L"n", L"nan", L"囝囡男抩枏柟侽南莮畘难娚喃楠暔諵難赧萳揇湳煵腩蝻戁婻遖" },
{ L"n", L"nao", L"孬呶怓挠峱铙硇蛲詉猱碙撓嶩憹蟯獶譊夒鐃獿巎垴恼悩脑脳匘堖惱瑙嫐腦碯闹淖閙鬧臑" },
{ L"n", L"nang", L"囊囔乪嚢蠰馕欜饢擃曩攮灢儾齉" },
{ L"n", L"ne", L"哪疒那讷呐抐眲訥丆匁鼡縇" },
{ L"n", L"nei", L"哪娞馁脮腇餒鮾鯘内內那氝氞錗" },
{ L"n", L"nen", L"恁嫩嫰" },
{ L"n", L"neng", L"能" },
{ L"n", L"ng", L"嗯唔" },
{ L"n", L"ni", L"妮尼泥兒呢坭怩籾秜铌郳倪屔淣婗猊蚭埿棿跜鈮馜蜺聣輗觬貎鲵霓麑鯢齯臡拟你伲伱苨妳狔抳柅掜旎晲孴隬儗儞薿擬聻屰氼逆胒昵匿眤堄惄腻愵溺嫟睨暱縌誽膩嬺嶷檷哛鳰" },
{ L"n", L"nian", L"拈蔫年秊秊哖姩秥粘鲇鲶鮎黏鯰涊淰捻辇辗碾輦撵撚簐蹍攆蹨躎卄廿念唸埝惗艌焾" },
{ L"n", L"niang", L"娘嬢孃酿醸釀" },
{ L"n", L"niao", L"鸟茑袅鳥嫋裊蔦樢褭嬝嬲尿脲溺" },
{ L"n", L"nie", L"捏捻揑苶乜帇圼枿陧涅聂痆臬隉菍啮湼敜嵲嗫踂踗踙摰镊镍噛槷嶭篞臲錜颞蹑聶嚙鎳闑孽孼櫱蘖籋囁齧鑈巕蠥糱糵囓躡讘鑷顳钀" },
{ L"n", L"nin", L"囜您拰脌" },
{ L"n", L"ning", L"宁苧咛狞拧柠聍甯寍寕寗寜寧凝儜橣擰獰嚀薴嬣檸聹鑏鬡鸋矃佞侫泞倿澝濘" },
{ L"n", L"niu", L"妞牛牜汼狃扭纽忸炄杻钮紐莥鈕靵拗" },
{ L"n", L"nou", L"羺槈耨獳鎒檽鐞鯑" },
{ L"n", L"nong", L"农侬浓哝脓秾農辳儂蕽濃噥膿燶檂禯穠襛譨醲欁鬞繷弄挊挵癑齈" },
{ L"n", L"nu", L"奴伮驽孥笯駑努弩呶砮胬怒傉搙莻" },
{ L"n", L"nv", L"女钕籹釹沑衂恧朒衄" },
{ L"n", L"nuan", L"奻渜煗暖餪" },
{ L"n", L"nun", L"黁" },
{ L"n", L"nve", L"疟虐" },
{ L"n", L"nuo", L"那娜挪梛傩橠儺诺逽喏掿愞搦锘榒稬諾蹃鍩糑懧懦糥穤糯" },

{ L"o", L"ou", L"区讴沤欧殴瓯鸥塸熰歐鴎甌膒毆謳藲櫙鏂鷗呕吘偶腢嘔蕅耦藕怄慪漚" },
{ L"o", L"o", L"噢哦丆仒乯迲猠硛旕筽鳰縇穒纐" },

{ L"p", L"pa", L"叭汃妑苩派皅趴舥啪葩扒杷爬耙掱琶筢潖帊帕怕袙巼" },
{ L"p", L"pai", L"拍俳徘猅排棑牌箄輫簰簲迫沠派哌渒湃蒎鎃闏" },
{ L"p", L"pan", L"扳拌眅萠番潘攀丬爿洀柈胖般盘跘蒰幋媻槃搫盤磐縏磻蹒蹣鎜蟠瀊鞶坢冸判伴沜泮拚炍牉盼叛畔袢詊溿頖鋬鵥襻鑻" },
{ L"p", L"pang", L"乓胮雱滂膀膖霶仿彷厐庞逄旁舽嫎徬磅螃鳑龎龐鰟嗙耪覫髈炐肨胖眫" },
{ L"p", L"pao", L"抛拋泡脬萢刨庖咆狍垉炰炮爮袍匏袌軳跑鞄麃麅奅疱皰砲靤麭礟礮喸褜" },
{ L"p", L"pei", L"呸怌肧胚衃醅阫陪培赔毰锫裴裵賠錇俖伂犻沛佩帔姵斾旆珮配浿辔馷霈轡蓜" },
{ L"p", L"pen", L"喷噴濆歕瓫盆葐湓呠翸喯" },
{ L"p", L"pi", L"丕伓伾批纰邳坯炋枈披抷狉狓岯砒紕被秛秠铍悂旇耚翍豾鈚釽鉟銔髬駓磇劈噼錃魾錍憵鎞礔礕霹皮阰陂芘肶枇毗毘郫陴疲蚍蚾蚽豼埤啤崥琵焷脾腗椑裨鈹鲏蜱罴膍隦魮鮍壀篺螷鵧貔羆鼙蠯匹庀仳圮苉吡否脴痞銢鴄諀嶏擗噽癖嚭屁淠揊媲嫓睥辟稫潎僻澼甓疈譬闢鸊鷿迲" },
{ L"p", L"peng", L"匉抨泙怦恲砰硑烹梈軯閛剻漰嘭駍磞芃朋竼莑倗捀堋弸袶彭棚椖搒塜塳傰蓬稝鹏硼樥熢澎憉輣錋篷篣膨韸髼鬅蟛蟚纄蘕韼鵬鬔騯鑝捧淎皏掽椪碰槰踫輧" },
{ L"p", L"pian", L"片囨扁偏媥犏翩篇鶣便骈胼腁缏楄楩賆跰褊骿駢蹁騈谝覑貵諞骗騙騗" },
{ L"p", L"piao", L"票剽勡嘌彯漂缥飘旚螵翲犥飄飃魒朴嫖瓢薸闝莩殍瞟縹篻醥顠皫僄徱骠慓驃鰾" },
{ L"p", L"pie", L"氕覕撇暼撆瞥丿苤鐅嫳" },
{ L"p", L"ping", L"乒甹俜娉涄砯聠艵頩冯平评苹郱凭呯坪枰玶胓屏洴帡荓瓶蚲萍帲淜幈蓱蛢缾甁塀焩評鲆軿竮凴箳慿憑鮃檘簈屛岼" },
{ L"p", L"pin", L"拚拼姘砏礗穦馪驞贫玭娦貧琕嫔频嬪薲蘋嚬矉颦顰品榀牝汖娉聘朩" },
{ L"p", L"po", L"朴钋陂岥泊泼坡釙颇酦頗潑醗醱鏺婆鄱蔢嘙皤繁櫇嚩叵尀钷笸鉕箥駊廹迫岶洦敀昢珀破砶烞粕湐蒪魄乶哛桲" },
{ L"p", L"pou", L"剖娝抔抙捊垺掊裒箁咅哣婄犃" },
{ L"p", L"pu", L"仆攵攴扑抪炇陠铺痡鋪噗撲潽鯆圤匍莆菩脯葡菐蒱蒲僕酺墣獛璞穙镤瞨濮贌鏷纀朴浦埔圃烳普圑溥谱暜諩樸擈氆檏镨譜蹼鐠堡舖舗暴瀑曝巬哛" },

{ L"q", L"qi", L"七迉沏妻柒栖桤凄郪倛娸捿淒悽萋戚桼棲敧欺欹期攲紪缉傶僛嘁墄漆慽緀榿慼踦霋魌蹊鏚鶈丌亓祁齐圻忯芪岐岓奇其亝祈祇斉肵歧疧俟荠剘陭旂耆蚑蚔蚚脐斊竒颀畦軝跂釮埼萁萕帺骐骑猉崎掑淇棋棊祺蛴琪琦锜褀碕碁鬿頎愭﨑齊旗綥粸綦蜞蜝璂禥蕲錡鲯藄鄿濝懠檱櫀鳍騏騎臍鵸鶀鯕蘄麒鬐艩蠐騹鰭玂麡乞邔企芑岂屺杞玘盀启呇唘豈起啓啟啔婍绮棨晵綮綺稽諬闙气讫迄汔気汽芞弃矵呮泣炁亟盵契咠砌訖栔氣欫唭葺湆湇棄夡愒滊摖暣甈碶憇槭噐器憩碛磜磧磩藒蟿罊鐑嵜褄螧簯簱籏" },
{ L"q", L"qia", L"掐袷葜擖拤卡峠酠跒鞐圶冾帢洽恰胢硈殎髂" },
{ L"q", L"qian", L"千阡仟芊迁扦奷汘圱圲汧岍杄茾佥欦钎臤牵拪悭蚈铅谸釺婜牽孯掔谦鈆鉛鹐签愆僉嗛骞撁搴慳遷厱諐褰謙顅檶櫏攐攑簽鵮騫攓籖鬜鬝籤韆仱岒扲忴拑乹前荨钤钱钳虔歬軡乾偂掮揵亁媊葥鈐靬犍鉗銭墘榩箝蕁潜潛羬黔橬錢黚騝騚濳灊鰬浅肷淺遣膁蜸槏谴缱繾譴欠刋伣纤芡茜俔倩悓堑椠棈傔嵌皘蒨慊塹蔳綪歉篏儙槧篟輤縴壍嬱竏粁鎆鏲" },
{ L"q", L"qing", L"靑青轻氢郬卿倾寈清淸埥圊氫軽傾蜻輕錆鲭鯖鑋夝甠剠勍啨情殑棾葝氰晴暒擏樈檠擎黥苘顷请頃庼廎漀請謦檾庆亲凊倩掅殸碃綮箐靘慶磬罄濪儬硘櫦" },
{ L"q", L"qie", L"切癿伽茄聺且妾怯厒砌窃匧悏挈洯惬淁笡蛪趄愜慊朅锲箧篋踥鍥穕鯜竊" },
{ L"q", L"qin", L"侵亲钦衾骎媇嵚欽綅嵰誛嶔親顉駸鮼寴芹芩庈肣矜秦蚙菦埐珡耹捦菳禽覃鈙鈫雂琴琹溱勤靲嫀嗪廑慬嶜擒噙鳹斳澿檎懄螓瘽懃蠄鵭坅昑笉赾梫寑锓寝寢鋟螼吣吢抋沁唚菣揿搇撳藽瀙" },
{ L"q", L"qiao", L"悄郻硗雀跷鄡鄥勪踍敲毃锹劁骹頝墝墽燆橇幧缲磽鍫鍬繑繰趬蹺鐰乔侨荞荍峤桥菬硚喬翘僑谯槗墧憔蕉蕎嘺嫶鞒犞燋樵橋瞧癄礄翹譙趫櫵藮鐈鞽顦巧釥愀髜壳陗俏诮帩峭窍誚髚僺撬撽韒鞘鞩竅躈" },
{ L"q", L"qiang", L"羌呛抢斨枪戗戕玱羗将猐啌跄腔溬嗴獇椌蜣锖锵羫槍牄瑲戧嶈摤篬謒镪蹌蹡鎗鏘強强蔷嫱墙樯蔃漒薔彊廧墻嬙檣牆艢蘠羟羥搶墏襁繈繦鏹炝唴嗆熗羻" },
{ L"q", L"qiu", L"丘丠龟邱坵恘秋秌恷蚯媝湫萩楸湬蓲鹙蝵緧篍趥穐鳅鞦鞧蟗鶖鰌鰍蠤龝仇叴芁扏囚犰玌朹肍汓虬求虯泅俅訄訅酋觓釚唒莍逑逎浗紌毬球梂赇殏釻頄渞湭遒巯崷盚皳絿蛷煪裘觩巰賕蝤璆銶醔鼽鮂鯄鰽搝糗蘒蘒" },
{ L"q", L"qu", L"区曲匤阹佉伹诎驱岖岴屈抾坥浀胠祛袪蛆紶躯區焌煀詘趋筁蛐粬趍駆憈嶇敺駈誳麹魼髷麯趨軀覰麴鶌黢驅鰸鱋佢劬斪朐胊菃鸲絇翑渠淭葋軥蕖璖鴝磲螶蟝璩瞿鼩蘧忂灈戵爠臞氍欋籧癯蠷衢欔躣鑺蠼鸜苣取竘娶詓竬蝺龋齲去厺刞呿耝阒觑趣閴麮鼁闃覷覻衐" },
{ L"q", L"que", L"炔缺缼蒛阙瘸芍却卻崅埆琷悫雀确硞棤阕塙搉鹊皵碏榷愨慤碻確趞闋燩闕礐鵲礭" },
{ L"q", L"qiong", L"銎邛卭宆穷穹茕桏筇笻赹惸焪焭琼蛩蛬舼跫睘煢熍瞏窮憌橩璚儝藑藭瓊竆瓗嬛" },
{ L"q", L"quan", L"奍弮悛圈圏棬椦箞鐉全权卷诠佺姾荃峑洤恮泉牷辁拳铨痊硂惓埢婘啳葲湶絟筌犈瑔輇觠詮搼跧銓蜷権踡駩醛鳈鬈騡鰁巏權齤颧蠸顴犭犬犮畎烇绻綣虇劝券牶勧韏縓勸楾闎" },
{ L"q", L"qun", L"夋囷逡帬宭峮裙群羣裠麇" },

{ L"r", L"rao", L"荛娆饶桡嬈蕘橈襓饒扰隢擾绕遶繞" },
{ L"r", L"rang", L"嚷穣勷儴蘘獽瀼禳瓤穰躟鬤壌壤攘爙让懹譲讓" },
{ L"r", L"ran", L"呥肰衻袇袡蚦蚺然髥髯嘫燃繎冄冉苒姌染珃媣橪" },
{ L"r", L"re", L"若喏惹热熱" },
{ L"r", L"reng", L"扔仍辸礽芿陾艿" },
{ L"r", L"ren", L"人亻仁壬朲忈任芢忎秂魜銋鵀忍荏荵栠栣秹稔躵刃刄认讱仞仭纫屻饪牣纴轫杒妊韧肕祍姙衽紉紝軔訒袵梕葚腍絍鈓飪靭靱韌餁認" },
{ L"r", L"rong", L"戎肜栄茸荣茙狨绒毧峵容烿媶嵘搑傛絨羢搈溶嵤嫆蓉榵榕榮熔穁瑢縙镕褣蝾槦融螎駥嬫嶸爃鎔瀜曧蠑冗宂坈傇軵氄穃" },
{ L"r", L"ri", L"日驲囸衵釰釼鈤馹乤乬乫乮乭乶乽乼乺挘艝鑓虄" },
{ L"r", L"rou", L"厹禸柔粈脜葇媃揉渘楺瑈腬煣蝚糅輮蹂鍒鞣騥瓇鶔鰇韖肉宍譳" },
{ L"r", L"ru", L"邚如侞帤茹挐桇铷袽渪筎蒘銣蝡蕠儒鴑鴽嚅薷濡孺嬬曘襦蠕颥醹顬鱬汝肗乳辱鄏擩入洳溽缛蓐嗕媷褥縟扖杁嶿" },
{ L"r", L"rui", L"甤緌蕤桵蕊蕋橤繠蘂蘃壡芮汭枘蚋锐蜹瑞睿鋭銳叡" },
{ L"r", L"ruan", L"堧撋壖阮软朊耎軟偄媆瑌腝碝緛輭瓀礝" },
{ L"r", L"run", L"闰润閏閠潤橍膶" },
{ L"r", L"ruo", L"挼捼叒若鄀偌弱婼渃焫楉蒻箬篛爇鰙鰯鶸嵶" },

{ L"s", L"sang", L"丧桒桑喪槡嗓搡磉褬颡鎟顙" },
{ L"s", L"san", L"三弎参叁毵毶厁毿犙鬖伞傘散糁馓糝糣糤繖鏒鏾饊俕閐壭" },
{ L"s", L"sai", L"思毢愢揌塞腮毸嘥噻鳃顋鰓赛僿賽簺嗮" },
{ L"s", L"sa", L"仨撒洒訯靸潵灑躠卅钑飒脎萨鈒馺摋蕯颯薩櫒扨苆乷栍隡虄" },
{ L"s", L"sao", L"掻搔溞骚慅缫螦繅鳋颾騒騷鰠鱢扫掃嫂埽瘙燥氉臊矂髞乺" },
{ L"s", L"seng", L"僧鬙" },
{ L"s", L"sen", L"森椮槮襂" },
{ L"s", L"se", L"閪色洓涩栜啬渋铯雭歮嗇瑟塞摵歰銫澁濇濏擌懎瘷穑璱澀瀒穡繬轖穯鏼譅飋縇鱪" },
{ L"s", L"sha", L"杀杉沙纱刹砂殺莎唦猀粆紗挲铩桬痧硰摋煞蔱裟榝樧噎鲨魦閷髿鯊鯋鎩繺奢啥傻儍倽萐帹啑唼喢厦廈嗄歃翜翣箑閯霎" },
{ L"s", L"shai", L"筛酾篩簁簛籭色晒曬" },
{ L"s", L"shang", L"汤伤殇商觞禓傷蔏滳漡墒慯殤熵螪觴謪鬺上垧扄晌赏樉賞鋿鏛贘鑜丄尚尙恦绱緔鞝" },
{ L"s", L"shan", L"山彡邖删刪芟杉钐衫苫姗姍狦挻舢珊栅柵脠痁扇軕掺笘釤傓跚剼搧煽幓嘇潸澘鯅縿膻檆羴羶闪陕陝炶閃晱睒煔熌覢讪汕疝单訕剡赸掸掞善椫禅銏骟鄯僐缮墠墡樿敾歚擅嬗禪膳磰赡謆繕蟮蟺鐥饍鳝騸贍譱灗鱓鱔圸" },
{ L"s", L"she", L"奢猞赊畬畲畭輋賖賒檨舌佘折虵蛇阇揲蛥舍捨叶厍设社舎厙拾涉射赦設渉涻弽滠慑摄摂蔎慴歙蠂韘騇麝懾灄攝欇" },
{ L"s", L"shao", L"莦弰捎烧梢稍焼萷旓蛸艄筲輎鞘燒髾鮹勺芍杓苕柖玿韶少邵卲劭绍袑哨娋紹睄綤潲蕱" },
{ L"s", L"shei", L"谁" },
{ L"s", L"shen", L"申扟屾伸身籶侁参诜冞罙呻妽绅柛氠穼珅姺籸娠峷莘眒甡砷深紳敒兟訷棯裑葠蓡罧詵糁甧蔘糂鲹駪薓燊曑鵢鯓鯵鰺什神甚鉮鰰邥弞沈矤审哂矧谂谉婶訠渖諗審頣魫曋瞫瀋嬸讅覾肾胂侺昚涁眘脤渗祳葚腎瘆慎愼椹蜃蜄滲鋠瘮堔榊籡" },
{ L"s", L"shou", L"収收熟扌手守首垨艏寿受狩兽售授涭绶痩膄壽夀瘦綬獣獸鏉" },
{ L"s", L"shi", L"尸失师呞邿诗鸤虱狮施屍浉師絁釶葹湿湤溼溮蒒蓍鉇詩獅瑡酾鳲嘘鳾箷蝨褷鲺鍦濕鯴鰤鶳襹釃十饣什石时识实実旹飠食祏炻蚀拾姼峕埘莳時遈寔湜溡塒鉐實榯蝕鲥鼫鼭識鰣史矢乨豕使驶始屎宩兘笶鉂駛士氏礻示市世丗仕似卋忕式戺亊事侍势试呩饰视柹柿枾昰是贳恃恀眂峙拭冟室适逝眎眡铈舐轼烒栻秲釈視释貰弑谥徥揓崼嗜蒔勢弒軾筮睗觢試鈰鉃飾鉽誓舓適奭餝餙銴諡諟澨噬嬕遾螫謚簭釋襫乄辻佦竍嵵煶鮖籂鰘籡鱰" },
{ L"s", L"sheng", L"升生阩呏声斘枡昇泩狌苼陞珄牲殅陹笙湦焺甥鉎鍟聲鼪鵿渑绳憴縄繉繩譝省眚偗渻圣胜晟晠乘剰盛貹剩勝嵊琞聖墭榺蕂賸竔曻﨡橳" },
{ L"s", L"shu", L"书殳抒纾陎叔枢杸姝荼倏倐殊紓書焂梳鄃菽婌掓軗淑疏疎舒琡綀毹毺摅输跾踈蔬樞輸鮛橾儵攄鵨尗秫孰赎塾熟璹贖属暑暏黍鼠蜀数署潻薯薥曙癙藷襡襩屬术朮戍束沭述侸荗咰树怷竖恕捒庶庻蒁絉術裋尌鉥腧竪墅漱潄澍數豎錰霔濖樹鶐鏣虪瀭糬蠴" },
{ L"s", L"shua", L"刷唰耍誜" },
{ L"s", L"shuang", L"双泷爽霜雙骦孀孇騻欆鷞鹴礵艭驦鸘漺慡縔塽灀﨎鏯" },
{ L"s", L"shuan", L"闩拴閂栓涮腨" },
{ L"s", L"shuai", L"衰摔甩帅帥率蟀卛" },
{ L"s", L"shui", L"谁脽誰氵水氺说帨涗涚祱税稅裞睡" },
{ L"s", L"shun", L"楯吮顺順舜蕣橓瞚瞤瞬鬊" },
{ L"s", L"song", L"忪松枀枩柗娀凇倯菘庺崧淞梥硹嵩濍憽檧鬆怂悚耸竦愯楤傱嵷慫聳駷讼宋诵送訟颂頌誦鎹餸" },
{ L"s", L"shuo", L"说説說妁烁朔铄硕欶矟蒴搠獡槊碩箾鎙爍鑠" },
{ L"s", L"si", L"厶纟丝司糹私泀咝俬思恖鸶虒偲缌媤蛳斯絲鉰楒禗飔凘厮禠蜤锶銯罳鋖緦磃澌嘶噝撕蕬廝燍螄鍶颸蟖蟴騦鐁鷥鼶死巳亖四似寺汜泤姒兕伺佀祀孠杫価驷饲泗洠娰俟枱柶牭食飤肂涘洍耜耛梩笥釲覗竢肆嗣貄鈶鈻飼榹禩駟蕼儩瀃厑唜旕鯐鶍" },
{ L"s", L"sou", L"叟凁捜鄋搜蒐蓃廀廋嗖獀馊溲飕摉摗锼螋艘醙鎪餿颼騪叜傁嗾瞍擞薮藪櫢籔嗽瘶擻" },
{ L"s", L"su", L"苏甦酥窣稣穌鯂蘓蘇櫯囌俗玊夙诉泝肃洬涑莤速珟素粛殐梀骕宿谡傃粟訴肅鹔愫塑塐遡嫊嗉溯溸缩遬蔌僳榡愬膆趚觫鋉餗碿樎樕憟潥潚縤簌謖藗橚璛蹜驌鷫鱐苆" },
{ L"s", L"suan", L"狻痠酸匴祘笇筭蒜算" },
{ L"s", L"sui", L"夊芕尿虽浽荾哸倠隋眭睢滖熣鞖濉雖绥随遂遀綏隨髄瓍膸瀡髓亗岁砕祟谇埣嵗煫歲歳碎睟粹隧澻穂嬘賥誶燧檖禭璲穗穟邃襚繀繐繸旞譢鐆鐩韢荽" },
{ L"s", L"sun", L"孙狲荪孫飧飱猻搎蓀槂蕵薞笋损隼筍損榫箰簨鎨鶽潠" },
{ L"s", L"suo", L"莎莏唆娑挱桫梭挲傞睃嗍蓑羧摍缩趖簑簔縮鮻所唢索琐惢锁嗩溑暛褨瑣璅鎖鎻鎍鏁逤溹蜶琑嗦鱛" },

{ L"t", L"ta", L"他它她牠祂铊趿鉈溻塌榙禢褟踏溚塔墖獭鮙鳎獺鰨拓沓挞闼狧粏崉涾傝嗒遝阘搨漯毾榻澾撻誻錔橽嚃鞜蹋濌鞳闒蹹闥嚺譶躢侤萙遢燵襨鶎鱩" },
{ L"t", L"tan", L"坍贪怹痑啴舑貪滩摊嘽瘫潬擹攤灘癱坛昙郯倓谈弹婒埮惔覃锬痰榃谭潭憛墰墵談醈曇錟壇燂橝澹檀顃罈藫壜譚醰貚譠罎忐坦钽袒菼毯僋鉭嗿憳憻醓暺璮叹炭探湠嘆碳舕歎" },
{ L"t", L"tai", L"台囼孡苔胎邰旲坮骀抬炱炲菭跆鲐颱臺箈駘鮐儓薹擡嬯檯籉呔太夳冭汏汰汱忲肽态钛舦泰酞鈦溙態燤" },
{ L"t", L"tao", L"夲叨弢涛绦掏焘絛詜慆搯滔幍嫍槄瑫韬飸縚縧轁濤謟鞱韜饕迯匋洮逃咷陶桃梼萄淘绹啕祹裪蜪綯鞀鞉醄鋾駣騊饀鼗讨討套" },
{ L"t", L"tang", L"汤铴湯嘡羰劏蝪趟薚镗蹚鏜鞺鼞坣唐堂棠啺鄌傏蓎隚搪溏塘煻榶漟禟瑭膅膛磄糃樘橖糖螗篖踼赯醣螳糛鎕餹饄闛鶶伖帑倘偒淌惝傥耥躺镋鎲儻戃爣曭矘钂烫摥燙鐋" },
{ L"t", L"te", L"忑忒特铽慝鋱蟘朰扨脦罀" },
{ L"t", L"teng", L"膯鼟疼痋幐腾誊漛滕邆駦螣縢謄儯藤騰鰧籐籘虅驣霯" },
{ L"t", L"tiao", L"旫佻庣挑恌祧聎芀条苕迢岧岹祒條调萔笤蓚蓨龆樤蜩鋚鲦鞗髫鯈鎥齠鰷宨晀朓脁窕誂窱斢嬥眺粜絩覜趒跳糶" },
{ L"t", L"tian", L"天兲婖添酟靔黇靝田佃沺屇恬胋畋畑畠钿甜甛菾湉填塡嗔阗搷碵緂窴磌璳闐鷆鷏忝殄倎唺淟悿觍晪琠腆睓痶舔餂瑱賟覥錪掭舚鴫" },
{ L"t", L"ti", L"体剔梯锑踢銻擿鷉鷈厗荑绨偍媞崹提渧缇惿遆啼稊鹈罤题瑅綈嗁睼褆碮漽蕛徲緹醍趧蹄蹏鍗鳀謕鮷題鵜騠鶗鶙鯷禵鷤挮躰骵軆體戻屉洟剃俶倜逖涕悌惕屜掦逷啑笹悐惖替揥裼褅歒髰殢薙嚏鬀鬄瓋嚔籊趯" },
{ L"t", L"tie", L"帖怗贴萜聑貼铁蛈鉄銕僣鐡鐵驖呫飻餮" },
{ L"t", L"tou", L"偷偸媮婾鋀鍮亠头投骰頭妵紏敨黈蘣透" },
{ L"t", L"tu", L"凸宊秃禿怢突涋捸湥堗葖痜嶀鋵鵚鼵図图凃荼徒途庩峹捈涂悇梌屠菟揬稌瘏筡鈯嵞塗蒤腯廜潳瑹酴跿圖圗馟駼鍎鵌鶟鷋鷵土圡吐钍唋釷兎迌兔莵堍鵵汢溌" },
{ L"t", L"tong", L"恫炵通痌絧嗵蓪熥樋仝同彤佟侗庝峂峒峝哃狪茼垌烔晍桐浵砼蚒秱铜眮童粡赨詷酮鉖銅鉵餇鲖勭僮潼獞橦犝曈朣膧燑氃穜瞳鮦统捅桶統筒筩綂恸痛衕慟憅" },
{ L"t", L"ting", L"厅庁汀町听耓烃厛烴桯綎鞓聴聼廰聽廳邒廷莛庭亭停葶婷嵉渟蜓筳楟榳閮霆蝏聤諪鼮圢甼侹娗挺涏烶梃珽脡铤艇颋誔鋌頲" },
{ L"t", L"tuan", L"猯湍圕煓貒团団抟剸摶漙團慱槫篿檲鏄糰鷒鷻畽墥疃彖湪褖" },
{ L"t", L"tun", L"吞呑旽涒焞朜噋暾屯坉囤忳芚蛌軘豚豘飩鲀魨黗霕臀臋氽褪饨" },
{ L"t", L"tui", L"忒推蓷藬弚颓隤尵橔頹頺頽魋蘈穨蹪俀腿僓蹆骽侻退娧煺蜕蛻褪駾燵" },
{ L"t", L"tuo", L"乇仛讬饦托扡汑杔佗侂咜咃沰拖拕说侻莌捝挩袥託飥涶脱脫馲魠鮵阤驮陁陀驼狏岮沱坨柁鸵砣砤袉紽詑酡跎堶馱碢槖駄駝駞橐鴕鮀鼧鵎騨鼍驒驝鼉彵妥庹椭楕嫷橢鰖拓柝毤萚唾跅毻箨嶞魄蘀籜鵇" },

{ L"w", L"wa", L"屲凹穵劸洼哇挖娲窊畖窐媧啘嗗瓾蛙搲溛漥窪鼃韈攨娃瓦邷佤咓砙袜聉嗢腽膃襪韤瓸甅" },
{ L"w", L"wai", L"咼歪喎竵崴外顡" },
{ L"w", L"wei", L"厃危委威烓隈隇偎逶喴葳葨媙崴嵔揻揋愄溦椳楲詴煨微蜲蝛覣縅薇燰鳂癓鰃鰄巍霺囗为韦圩围囲闱违帏沩洈峗峞為韋桅涠帷唯维惟琟嵬媁圍喡幃違湋溈爲維潍鄬蓶潿潙醀鍏闈鮠濰壝矀覹犩欈伟伪苇芛尾纬炜玮洧浘娓荱诿隗偽偉萎崣梶痏硊骩骫骪愇猥渨蒍葦徫廆椲暐煒艉痿瑋韪腲鲔撱嶉僞寪蔿頠緯諉踓韑薳儰濻鍡鮪颹韙瀢韡亹斖卫未位苿味胃畏軎叞菋谓硙尉遗喂媦猬渭煟蔚碨蜼蝟磑犚慰緭熭衛衞餧鮇懀謂罻螱褽魏餵轊藯鏏鳚霨蘶饖讆躗躛讏捤墛嶶" },
{ L"w", L"wang", L"尢尣尪汪尫尩亾兦亡王仼莣蚟罓罒网彺往徃罔枉惘菵辋棢暀蛧蝄網輞誷魍瀇妄迋忘旺徍望朢" },
{ L"w", L"wen", L"昷温溫辒殟榅瑥瘟榲緼蕰豱輼轀鳁鞰鰛鰮文芠彣纹炆闻蚊蚉紋阌珳雯駇馼聞瘒鳼鴍魰螡閿閺闅蟁鼤繧闦刎伆吻呅抆呡肳紊桽脗稳穏穩问妏免汶莬問渂揾搵絻顐璺塭鎾饂" },
{ L"w", L"wan", L"涴弯剜帵婠湾塆睕蜿豌潫彎壪灣丸刓芄汍纨完岏抏玩紈捖顽貦烷頑翫宛倇莞挽盌唍绾埦惋梚菀萖婉脘晚晥晩晼琬皖椀碗畹綰綩輓踠鋔万卐卍忨妧捥脕腕萬蔓輐澫鋄錽薍瞣蟃贃鎫贎乛杤笂琓" },
{ L"w", L"weng", L"翁嗡滃鹟螉聬鎓鶲勜奣嵡蓊塕暡瞈攚瓮蕹甕罋齆" },
{ L"w", L"wo", L"挝涡倭莴萵唩猧渦涹窝喔窩蜗蝸踒我婑婐捰仴沃肟枂卧臥捾涴偓幄媉渥握焥硪楃腛斡瞃龌臒瓁濣齷遤" },
{ L"w", L"wu", L"兀乌邬弙污汙汚圬呜巫杇於屋洿诬钨恶烏剭窏鄔嗚誈誣歍箼螐鴮鎢鰞亡无毋芜吾吴吳呉郚茣莁唔娪峿浯洖梧祦珸铻鹀無蜈鋙蕪墲橆璑鵐蟱鯃譕鼯鷡五午伍仵迕妩庑怃忤玝武侮倵逜陚捂娒娬牾啎珷鹉碔摀熓瑦舞憮潕廡嫵儛甒瞴鵡躌兀勿阢务戊扤屼岉芴坞杌物忢旿矹卼敄俉误務悟悮悞粅晤焐痦婺隖骛嵍靰雾雺嵨奦溩塢鹜熃寤誤鋈窹霚鼿齀霧騖蘁鶩厼朰鯲" },

{ L"x", L"xi", L"夕兮邜吸汐忚西扸希卥析昔穸肸肹矽怸饻恓郗茜俙徆莃奚娭唏浠狶悕屖栖牺氥息悉硒琋赥釸欷晞桸惜烯焁焈淅渓唽菥傒鄎焟焬犀晰晳翕翖舾粞稀睎惁腊锡皙裼煕厀徯蒠溪嵠僖熙熈熄榽蜥緆餏覡豨瘜磎膝潝嘻噏嬉嬆凞樨橀暿歙熺熻熹螅螇窸羲錫貕蹊豯蟋谿豀瞦燨犠巂繥糦鵗譆醯觹鏭鐊隵酅巇嚱犧曦爔饎觽鼷鸂蠵觿鑴习郋席觋習袭喺媳蓆蒵椺嶍漝趘槢褶薂隰檄謵鎴鳛霫飁騱騽鰼襲驨洗枲玺铣徙喜葸葈鈢鉨鉩蓰漇屣憘歖禧憙諰謑縰壐蟢蹝璽鱚矖囍躧匸卌戏饩屃系呬细郄怬忥盻恄郤係咥屓绤欯阋細釳趇舄舃塈隙椞禊慀隟綌赩熂墍犔稧潟澙戯蕮覤縘黖戱戲磶虩餼鬩繫闟霼衋屭巪凩巼夞莻唟裃硳喸聢噺橲礂鯐" },
{ L"x", L"xia", L"呷虾谺閕傄颬煆瞎蝦鰕匣狎侠俠狭陜峡炠柙烚峽埉狹祫珨硖翈舺陿假葭硤遐筪瑕舝敮暇辖碬磍蕸縖赮魻霞鍜轄鎋黠騢鶷閜丅下吓疜夏唬厦睱諕懗罅夓鎼鏬圷梺" },
{ L"x", L"xian", L"仚仙屳纤先奾忺佡氙杴秈苮祆枮籼莶珗掀铦锨酰跹僊僲銛鲜嘕韯銽暹薟憸嬐鍁韱鮮褼繊蹮馦孅攕廯纎鶱躚襳纖鱻闲伭弦咁妶贤胘涎盷咸挦娴娹婱蚿絃衔舷閑閒蛝鹇痫湺啣嗛嫌甉銜誸賢羬稴澖憪嫻嫺撏諴醎輱癇癎瞯藖礥鹹麙贒鷼鷳鷴冼狝险洗显烍毨蚬崄険猃赻铣筅蜆跣禒搟尠尟銑箲險獫嶮獮藓鍌燹顕幰攇蘚櫶譣玁韅顯灦见县苋岘限现线臽県陥宪姭娊峴陷莧哯涀垷埳現晛馅羡缐睍絤腺粯塪献羨僩僴誢綫線鋧撊憲橺橌錎餡縣豏壏麲臔瀗獻糮霰鼸咞衘鑦" },
{ L"x", L"xiang", L"乡芗相香郷鄉鄊厢廂湘缃鄕葙萫薌箱緗膷襄麘忀骧欀瓖镶纕鑲驤瓨降佭详庠栙祥絴翔詳跭享亯响饷蚃晑飨想銄餉鲞鮝蠁鯗響饗饟鱶向姠巷项珦象項缿衖勨像嶑橡曏襐蟓嚮鐌鱌" },
{ L"x", L"xiao", L"灱灲肖枭呺哓削侾骁枵绡庨烋宵宯逍消鸮虓婋猇萧梟焇销痚痟翛硝硣窙蛸綃揱箫嘐潇踃歊銷霄獢撨嘵憢膮蕭彇颵魈鴞鴵簘蟏蟂藃穘嚣瀟蟰簫髇櫹囂嚻髐鷍驍蠨毊虈洨郩崤淆訤殽誵小晓暁筱筿皛篠謏曉皢孝効恔咲哮涍俲笑校效啸傚敩詨誟嘨嘋嘯熽歗斆斅﨧" },
{ L"x", L"xing", L"兴狌星垶骍猩惺煋瑆腥觪篂箵鮏興觲騂曐皨鯹刑邢饧行陉形侀郉陘荥洐型钘娙铏硎鈃蛵滎銒鉶鋞餳省睲醒擤杏性幸姓荇莕倖婞悻涬葕緈﨨嬹臖哘謃" },
{ L"x", L"xin", L"忄心邤辛芯妡忻炘杺欣昕盺莘俽惞訢鈊锌歆新廞鋅噷嬜薪馨鑫馫枔镡襑鐔伈阠伩囟孞信軐訫脪衅焮馸顖舋釁" },
{ L"x", L"xie", L"些娎猲揳楔歇蝎蠍叶邪劦协旪胁協奊垥恊峫挟拹挾脇脋脅衺斜谐偕絜翓綊瑎愶嗋携熁膎鲑鞋蝢緳缬撷擕縀勰諧燲嚡擷鞵襭攜孈讗龤写血冩寫藛伳灺绁泄泻祄缷洩炧炨契卸卨屑烲禼徢偰偞焎紲械絏絬亵谢屟媟渫塮僁解靾榭榍褉暬緤噧屧獬嶰澥懈廨邂薤薢糏韰謝褻燮夑瀉鞢齘繲蟹蠏瀣爕齛齥纈齂躞" },
{ L"x", L"xiong", L"匂凶兄兇匈讻芎忷汹洶恟哅胸胷訩詾賯雄熊熋焸焽诇詗夐敻楿" },
{ L"x", L"xu", L"吁圩戌盱疞砉欨胥须顼訏許裇虚虗偦谞媭揟湑欻虛須綇楈需魆墟嘘噓蕦嬃歔縃緰蝑諝歘燸譃魖繻驉鬚鑐俆徐冔禑蒣许诩呴姁浒栩珝喣暊詡稰鄦糈諿醑盨旭旴伵芧序汿侐卹怴沀恤昫叙洫晇殈烅珬垿欰畜酗烼绪续敍敘勖勗溆婿壻聓訹絮朂続賉頊滀蓄慉煦槒漵潊銊聟緒盢瞁稸魣緖獝藇藚續鱮﨏蓿" },
{ L"x", L"xiu", L"休俢修庥咻脩烌羞脙鸺臹貅馐髤銝樇髹鵂鎀鏅饈鱃飍苬朽宿滫潃糔秀岫峀绣珛袖臭琇锈綉溴嗅璓褏褎銹螑繍嚊繡鏥鏽齅鮴" },
{ L"x", L"xue", L"削疶蒆靴薛辥辪鞾穴斈乴茓峃学泶鸴袕踅學嶨壆噱燢澩觷鷽彐雪鳕鱈吷狘岤坹桖谑趐謔瞲瀥樰膤轌" },
{ L"x", L"xuan", L"吅轩昍宣弲晅軒梋谖萱萲喧媗揎塇愃愋煖煊蓒暄瑄睻蝖禤箮翧儇鋗鞙蕿嬛懁諠諼駽鍹翾蠉矎蘐藼譞玄县玹痃悬琁旋蜁嫙漩璇暶檈璿懸咺选烜選癣癬券泫怰炫昡绚眩铉袨琄眴衒渲絢楦楥鉉碹蔙镟颴縼繏鏇贙" },
{ L"x", L"xun", L"坃勋荤埙焄勛塤熏窨勲勳薫薰壎獯曛臐燻蘍矄纁爋壦醺廵巡寻旬杊郇询畃荨荀浔洵峋恂紃珣栒桪毥偱循尋揗詢鲟鄩噚潭潯駨璕攳燖燅樳蟳鱏鱘灥卂讯训迅伨驯汛侚狥逊迿巺徇殉訊訓訙浚奞殾巽稄馴遜愻蕈噀顨鑂嚑" },

{ L"y", L"ya", L"ㄚ丫圧吖压厌呀庘押枒鸦哑鸭桠孲铔雅椏鴉鴨錏壓鵶鐚牙伢芽岈厓玡琊蚜笌堐猚崖崕涯釾睚衙漄齖疋厊庌疨唖啞痖瘂蕥劜圠轧覀襾冴亚讶迓亜犽亞軋砑挜娅垭俹氩掗訝埡婭猰聐揠氬稏圔窫齾鯲鑓軈" },
{ L"y", L"yan", L"咽恹烟殷珚胭焉淹淊阏阉崦湮腌硽煙歅鄢傿嫣漹嶖醃閹燕懨嬮篶懕臙黫讠延闫妍芫严阽言訁郔岩沿炎炏昖狿埏莚姸娫研铅盐娮阎啱琂硏訮閆蜒綖筵嵒嵓喦塩揅楌詽碞蔅颜虤閻厳檐顔顏簷壛巌嚴櫩巖巗壧鹽礹麣夵抁沇奄乵兖兗匽弇俨衍剡眼酓偃掩郾厣萒遃隒嵃揜渰渷扊棪愝晻琰罨裺椼演嵼褗蝘魇戭噞躽縯黡檿厴黤甗鶠鰋龑黭黬儼孍顩鼴鼹魘巘巚曮齴黶厌妟觃牪砚姲彦彥烻唁验宴艳晏覎偐谚隁焔焰焱堰喭雁敥猒硯椻鳫滟溎墕熖厭酽暥鴈谳嬊餍燄赝鬳諺鴳曕嚈酀騐験艶贋嚥嬿爓曣騴醶齞鷃贗灔囐鷰驗醼讌觾饜艷釅驠灎灧讞豓豔灩剦樮軅" },
{ L"y", L"yao", L"幺夭吆约妖殀祅要訞喓葽楆腰鴁鴢徼邀爻尧尭肴侥荛姚峣轺垚烑陶倄珧窑铫堯揺傜谣軺滧徭遥遙嗂媱猺摇搖愮摿榣暚飖瑶瑤餆窯窰磘嶢嶤餚繇謡謠鎐鳐颻蘨邎顤鰩鱙仸宎岆抭杳枖狕苭咬柼眑窅窈舀偠婹崾溔蓔榚闄騕齩鷕疟穾药钥袎窔葯筄詏靿覞熎鹞獟鼼薬藥燿曜艞矅耀纅鷂讑" },
{ L"y", L"yang", L"央姎抰泱殃胦秧眏鸯鉠雵鞅鴦鍈阳阦扬羊飏炀杨旸钖疡氜劷佯徉洋垟昜羏珜烊陽眻蛘揚崵崸煬楊敭瑒暘瘍輰諹鍚鴹颺鰑霷鸉卬仰佒咉岟坱炴柍养氧痒紻軮楧傟慃氱飬蝆養駚懩攁瀁癢怏恙样羕詇漾様樣礢" },
{ L"y", L"ye", L"吔耶倻掖椰暍歋潱噎擨蠮邪爷捓揶铘爺瑘鋣鎁ㄝ也冶野埜嘢漜壄业叶曳页曵邺抴夜枼拽亱咽頁捙枽烨晔液谒葉腋殗業煠馌墷璍僷燁曅曄皣瞱擛鄴靥餣謁嶪嶫澲擫瞸曗鍱鎑饁擪礏爗鵺鐷靨驜鸈丆亪" },
{ L"y", L"yi", L"一弌衤伊衣医吚壱依祎洢咿郼渏悘铱猗蛜壹揖椅禕漪稦銥嫛嬄撎夁噫瑿鹥繄檥檹醫毉黟譩鷖黳乁义匜仪夷圯宐诒冝杝沂沶侇迤宜狋怡饴拸姨恞贻峓迻荑瓵珆咦訑貤胰栘桋巸眙袘宧扅萓蛇痍移椬蛦貽詒羠遗媐颐飴頉誃跠椸暆疑熪遺儀彛彜嶬螔頤頥顊鴺鮧簃嶷寲彝彞謻鏔籎觺讉乙已以迆钇攺矣苡佁尾苢迱庡舣蚁釔笖酏扆逘倚偯旑崺鈘鉯鳦裿蛾旖踦輢螘敼嬟礒蟻艤顗轙齮乂亿弋刈艺忆艾阣仡议肊伇芅亦异忔屹抑坄呓劮役苅佚译耴杙邑枍炈易衪秇诣佾呹呭驿泆怿怈绎峄浂帟帠俋弈奕疫羿昳玴轶枻食栧欭袣益谊唈浥浳挹悒垼埸埶逸勚萟殹翊翌悥豙豛異訲訳隿釴羛鈠軼骮跇詍晹敡殔棭焲蛡鄓湙幆嗌溢缢兿義亄睪獈竩痬意詣肄裔裛駅榏瘗膉蜴蓺勩廙嫕潩億鹝鹢毅镒瘞槸熠熤熼篒誼黓艗燚曀殪瘱瞖穓螠褹縊劓薏澺嬑嶧墿圛懌憶寱翳翼臆斁歝曎燡燱檍賹貖鮨鎰贀镱癔藝藙繹繶豷霬鯣鶂鶃饐醷醳譯議蘙瀷囈鐿鷊鷁懿襼鷧驛鷾鸃虉齸讛辷匇凧弬夞畩鶍鶎" },
{ L"y", L"yin", L"囙因阴阥侌茵骃姻洇垔音栶氤殷陰隂陻凐秵铟裀絪筃堙愔喑婣溵蔭蒑禋慇瘖銦鞇磤緸諲霒駰霠闉噾濦齗韾冘乑吟犾圻烎斦泿垠圁狺峾荶珢訚訔訡银淫寅婬崟崯鈝龂滛碒鄞蔩夤銀龈誾璌殥噖嚚蟫檭霪齦鷣廴引尹饮吲蚓隐赺鈏飲淾隠飮靷輑朄趛瘾檃隱嶾濥螾檼蘟櫽癮讔印茚荫洕胤垽堷湚猌廕窨酳癊慭憖憗鮣懚岃粌" },
{ L"y", L"ying", L"应応英莺珱偀渶绬婴媖瑛煐朠锳碤嫈嘤缨撄甇緓蝧罂賏樱璎鹦噟霙罃褮鴬韺嬰膺應鹰甖鶑鶧罌譍孆嚶攖蘡孾瀴櫻瓔礯譻鶯鑍鷪蠳纓鷹鸎鸚迎盁茔荥荧盈莹萤营萦蛍営萾溁溋滢蓥塋楹僌颖熒蝇潆蝿禜瑩螢營嬴縈覮謍赢濙濚濴藀瀅蠅鎣巆攍瀛瀯瀠贏櫿灐籝灜籯郢矨浧梬颍颕摬影潁穎瘿頴鐛廮巊癭映暎硬媵膡鱦栍桜愥闏" },
{ L"y", L"yo", L"育哟唷喲罀" },
{ L"y", L"yong", L"佣拥邕痈庸傭嗈鄘雍嫞滽墉慵牅壅澭擁噰镛郺臃癕雝鳙鏞灉廱饔鷛鱅癰喁颙顒鰫永甬咏泳勇勈俑栐柡悀涌埇恿惥愑湧詠硧蛹塎嵱彮愹慂踊鲬踴鯒用苚蒏醟怺砽" },
{ L"y", L"you", L"优忧攸怮呦泑幽峳浟逌悠麀羪滺憂鄾優瀀嚘懮櫌耰纋尢尤由甴沋邮犹油怞肬怣疣柚庮郵莜莸秞铀蚰訧偤逰遊猶游鱿鲉鈾楢猷輏駀魷蝤蝣蕕鮋輶繇友有酉丣卣苃羑莠栯梄铕聈湵蜏禉銪槱牖牗黝又右幼佑侑狖峟囿牰祐迶哊宥姷诱唀蚴亴釉貁酭誘褎鼬櫾孧" },
{ L"y", L"yue", L"曰曱约約箹矱哕噦月乐戉刖妜岄抈礿玥泧岳说恱栎钥钺蚏蚎阅軏悦悅捳跃跀鈅越粤粵鉞閲閱篗樾嬳嶽龠籆蘥瀹黦躍爚禴籥鑰鸑籰鸙" },
{ L"y", L"yuan", L"囦肙鸢剈冤鸳眢寃涴渊渁渆渕淵葾惌蒬棩鹓裷蜎箢鳶駌蜵鴛鵷嬽灁鼘鼝元円邧贠沅园芫员茒杬垣爰貟笎蚖袁圆原員厡媛猨援圎湲鼋缘鈨源溒園圓塬猿嫄媴蒝辕榞榬緣魭縁褤蝯蝝螈黿羱薗橼圜轅謜鎱櫞邍騵鶢鶰厵远盶逺遠鋺夗苑妴院怨衏垸傆掾禐瑗愿裫褑噮願" },
{ L"y", L"yu", L"込迂迃吁扝扜纡於穻陓紆盓菸淤唹瘀箊与于亐予邘伃余妤扵杅欤玙玗盂衧臾鱼舁竽虶禺茰俞兪谀娱娛娯馀狳桙酑雩魚渔萸隅隃萮渝湡揄堣堬嵎嵛崳逾喁楰愉腴畬骬虞艅觎愚瑜歈榆楡牏舆窬睮褕漁蕍蝓歶雓餘諛羭踰覦嬩澞璵歟螸輿鍝謣髃鮽騟籅旟轝蘛鰅鷠鸆齵屿宇伛羽妪雨俣俁语挧禹圄祤圉敔匬鄅偊庾萭斞铻瘐楀與瑀傴寙語窳頨龉貐懙噳嶼斔穥麌齬肀驭玉聿芋芌圫饫汩忬谷欥育郁茟狱秗昱浴峪彧俼预钰砡粖袬谕逳菀尉阈淯淢惐悆欲域堉棫棛棜琙焴寓媀喻喅喩庽御遇馭飫粥鹆硲硢矞裕鈺誉罭預蓣蒮煜滪愈稢戫蔚僪隩嶎獄嫗緎蜮蜟毓瘉銉輍豫鋊鳿遹薁蓹熨潏稶慾澦燠燏蕷鴥鴪鴧錥諭閾礇禦鹬魊儥鵒礜癒醧篽饇櫲蘌霱譽鐭雤鬻驈欎鷸鱊籞鸒欝龥鬰鬱籲灪爩礖軉" },
{ L"y", L"yun", L"晕蒀缊蒕煴氲氳熅奫蝹赟馧贇匀勻云伝芸员妘沄纭囩昀秐眃畇郧涢耺耘紜雲鄖蒷溳愪筠筼熉澐蕓鋆篔縜橒允阭狁抎夽陨荺殒隕喗鈗馻殞磒賱霣齫齳孕运郓枟恽酝鄆傊運愠惲慍暈韫腪韵褞熨蕴薀縕醖醞餫韞韗藴蘊韻抣" },

{ L"z", L"za", L"帀扎匝沞咂拶桚鉔魳臜臢杂沯砸韴雑襍雜囃囋雥咋乽橴" },
{ L"z", L"zan", L"兂糌橵篸簪簮鵤鐟鐕咱偺喒拶昝寁揝撍噆儧攅攒儹攢趱趲暂暫賛赞錾鄼酂濽蹔鏨贊瓉瓒酇囋灒讃瓚禶襸讚饡" },
{ L"z", L"zao", L"傮遭糟醩蹧凿鑿早枣蚤棗澡璪薻藻灶皂皁造唣唕梍慥煰喿艁簉噪燥竃竈譟趮躁栆" },
{ L"z", L"zang", L"匨赃牂脏羘賍賘臧贓髒贜驵駔奘弉塟葬蔵銺藏臓臟欌" },
{ L"z", L"zai", L"灾災甾哉烖栽渽溨睵賳仔宰载崽再扗在洅傤載酨儎縡岾" },
{ L"z", L"ze", L"则沢泽泎责迮咋择則帻啧啫舴笮責矠滜溭箦嘖嫧幘蔶赜樍歵諎擇瞔皟簀賾礋襗謮蠌齚齰鸅仄庂汄昃昗侧捑崱択硳" },
{ L"z", L"zeng", L"曽曾増鄫缯增憎橧璔磳矰罾繒譄综锃鋥赠熷甑鬵贈囎" },
{ L"z", L"zen", L"怎谮譖" },
{ L"z", L"zei", L"贼戝賊鲗蠈鰂鱡" },
{ L"z", L"zha", L"扎吒咋抯挓查柤奓紥哳偧紮渣溠喳猹揸楂劄摣皶觰樝皻譇齄齇轧札闸炸铡蚻喋牐閘箚耫鍘譗厏苲拃眨砟鲊鲝鮓鮺乍诈灹咤栅柞痄宱蚱詐搾槎榨蜡霅醡蓙" },
{ L"z", L"zhai", L"侧夈捚斋斎摘榸齋宅择翟檡窄鉙责柴债砦祭債寨粂瘵" },
{ L"z", L"zhan", L"占沾枬毡旃栴蛅粘飦趈詀惉詹閚谵薝邅噡嶦霑氊氈瞻鹯旜譫饘鳣魙驙鸇鱣讝斩飐盏展崭斬琖盞搌辗嶄嶃榐颭醆嫸橏輾黵佔战栈桟站绽偡菚湛棧戦綻輚嶘戰虥虦襢覱轏譧驏蘸" },
{ L"z", L"zhao", L"佋钊妱招巶昭釗着啁朝鉊鼌駋嘲鍣皽爫爪找沼瑵召兆诏枛炤狣垗赵笊肁棹旐詔罩照肇肈箌趙曌燳鮡瞾櫂羄罀" },
{ L"z", L"zhang", L"仉张張章鄣傽蔁遧粻嫜獐彰漳慞樟暲璋餦蟑騿麞鱆长涨掌漲礃丈仗扙帐杖胀账涱帳脹障痮幛嶂墇賬瘴瘬瞕粀幥鏱" },
{ L"z", L"zhe", L"折蜇遮嗻嫬螫厇歽矺砓虴籷袩埑哲啠辄晢晣悊喆詟蛰谪摺輒輙銸磔辙蟄鮿謫謺嚞轍讁讋者锗褚赭踷鍺褶襵这柘這浙淛蔗樜鹧蟅鷓粍" },
{ L"z", L"zhei", L"这" },
{ L"z", L"zhong", L"中伀汷彸刣忪妐炂忠泈终钟柊盅衳舯衷終鈡蜙锺幒蔠銿鴤螤螽鍾鼨蹱鐘籦肿种冢喠尰煄腫歱塚種瘇徸踵众仲妕狆祌衶重茽蚛眾偅堹媑筗衆諥" },
{ L"z", L"zheng", L"丁正争佂诤征姃怔爭糽埩炡政挣狰峥烝脀钲眐症聇睁铮掙崝崢猙揁媜筝踭鉦睜徰蒸錚箏篜鲭鬇癥鏳氶抍拯掟晸愸撜整证郑証幁塣諍靕鄭鴊證" },
{ L"z", L"zhi", L"之氏支只卮汁芝汦汥吱巵知肢泜织枝栀祗胝胑秓衼疷隻脂祬栺倁梔椥臸綕禔稙搘馶蜘榰憄鳷鴲織鼅蘵执侄妷直姪值値聀釞职淔埴執殖戠植犆禃跖絷瓡馽摭潪嬂漐慹踯膱樴縶蹢蹠職蟙軄躑夂止阯劧旨帋芷扺沚纸址坁坧抧茋祉秖恉轵枳砋衹咫指洔淽茝紙疻訨趾黹軹酯徴墌徵藢襧芖至豸扻伿识忮志炙质治垁郅迣厔制帜帙挃庢庤陟峙洷栉柣祑挚桎晊歭秩贽轾徏娡狾致袟紩畤窒痔痓铚鸷貭翐觗袠猘徝掷乿剬偫秷梽智滞崻傂骘痣彘蛭置锧跱輊筫雉寘搱廌滍稚滯墆銍製覟誌瘈疐觯踬質鋕熫稺膣摯摨幟擳隲璏旘瀄鴙駤緻螲懥櫛穉儨劕擿擲懫贄觶騭鯯櫍瓆豑礩騺驇鷙躓鑕豒俧潌" },
{ L"z", L"zhou", L"州舟诌侜周洲诪炿烐珘调郮辀婤淍啁週徟鸼矪粥喌赒輈銂輖賙霌鵃謅盩嚋騆譸妯轴軸肘疛帚菷晭睭箒鯞纣伷咒呪绉宙冑祝昼咮荮紂胄皱酎粙舳晝葤詋甃僽駎皺縐噣骤繇籀籕籒驟碡駲" },
{ L"z", L"zhua", L"抓挝撾檛膼簻髽爪" },
{ L"z", L"zhu", L"朱邾侏诛茱洙诸珠株猪秼铢硃袾蛛絑誅跦銖槠蝫潴蕏橥諸豬駯鴸鮢鼄藸瀦鯺櫫櫧蠩术竹竺笁柚茿炢烛逐窋笜逫蓫瘃篴燭蠋躅鱁劚孎灟爥斸欘曯蠾钃丶主劯宔拄柱罜陼帾渚煮煑属詝褚濐嘱燝麈瞩囑鸀矚宁伫住佇芧苎助纻坾贮驻迬杼拀注祝柷炷殶壴莇祩竚眝疰砫蛀紵紸著庶羜铸筑貯軴註跓嵀鉒筯飳馵箸翥樦鋳駐麆築篫簗鑄墸" },
{ L"z", L"zhen", L"贞针侦帧浈胗珍珎貞針祯桢真眞砧帪偵酙葴幀寊湞遉斟溱嫃獉搸蓁蒖甄椹楨禎鉁禛瑧榛碪殝潧箴臻樼澵薽錱轃鍼籈鱵诊枕抮轸昣弫姫屒眕疹畛袗聄紾裖軫覙診缜駗稹縝縥辴鬒黰阵圳纼甽鸩陣侲挋振栚朕紖眹赈塦揕絼賑誫镇震鴆鎭鎮鋴" },
{ L"z", L"zhuai", L"拽转跩" },
{ L"z", L"zhui", L"隹追骓椎锥錐騅鵻沝坠笍娷缀缒甀腏惴畷膇硾墜綴赘縋諈醊錣礈贅鑆" },
{ L"z", L"zhuang", L"庄妆妝庒荘莊娤桩梉粧装湷裝樁糚奘壮壯状狀壵焋僮幢撞戆" },
{ L"z", L"zhuan", L"专叀専砖專鄟嫥塼甎瑼膞磗颛磚諯顓蟤鱄转孨竱轉传沌灷啭転堟蒃瑑腞赚僎馔撰篆篹襈縳賺譔饌籑囀" },
{ L"z", L"zhun", L"屯迍宒肫窀谆啍諄衠准埻凖準綧訰稕" },
{ L"z", L"zhuo", L"拙炪捉倬桌棁梲涿棳焯槕穛擢鐯穱彴犳汋圴灼妰卓叕茁浊斫烵浞诼丵酌娺啄啅着椓晫斮斱琢琸硺罬窡禚斲撯擆劅諑諁鋜篧缴濁濯斵斀謶镯櫡鵫躅蠗灂鐲鷟籗蠿籱窧" },
{ L"z", L"zou", L"邹驺陬郰诹菆掫棷棸鄒緅箃諏鲰鄹黀鯫騶齱齺赱走奏揍" },
{ L"z", L"zong", L"宗枞倧骔综堫惾腙葼猣嵏嵕棕椶朡稯嵸潈綜緃翪踪踨緵熧蝬磫繌鍐鬃騌蹤騣鯮鬉鬷鯼鑁总倊偬捴揔搃惣焧傯蓗摠総縂緫燪總纵昮疭猔碂粽糉瘲縦縱豵糭" },
{ L"z", L"zi", L"仔孖孜吱甾茊茲兹姿姕咨赀资玆栥紎赼缁秶崰淄谘菑葘鄑滋湽嵫椔粢辎嗞孳孶锱禌趑觜訾資貲緇緕龇鈭稵镃輜鼒鲻髭輺錙諮趦澬鍿鎡頾頿齍鶅鯔鰦纃齜蓻子吇杍姊姉胏秄矷虸耔籽秭呰茈笫釨梓啙紫滓訿榟字芓自荢茡剚倳牸恣眦眥渍胾胔漬嗭魸鯑" },
{ L"z", L"zu", L"苴租菹葅蒩卆足卒哫崒崪族椊箤踤镞鏃阻诅组祖珇爼俎唨組詛靻鼡乼" },
{ L"z", L"zun", L"尊嶟遵樽罇繜鐏鳟鷷鱒僔噂撙譐捘銌" },
{ L"z", L"zui", L"咀厜脧嗺樶蟕纗觜嶊嘴噿璻栬冣絊酔晬祽最稡罪辠酻槜醉蕞嶵鋷錊檇檌" },
{ L"z", L"zuan", L"钻鉆劗鑚躜躦鑽篹繤缵纂纉纘籫赚攥" },
{ L"z", L"zuo", L"作嘬穝昨莋秨笮捽琢筰鈼稓左佐撮繓阼坐怍岞岝侳祚胙袏座唑做葃葄飵糳咗" }
};



int getComPingyinForStr(const wstring & inStr, wstring& outFrist_py, wstring& outFull_py)
{
    // --- 条件返回
    outFrist_py.clear();
    outFull_py.clear();
    if (inStr.empty())
    {
        return -1;
    }


    // --- 获取每个字的所有读音
    size_t numOfWord = inStr.size();
    vector<vector<wstring>> fristPys;
    vector<vector<wstring>> fullPys;
    for (size_t i_word = 0; i_word < numOfWord; i_word++)
    {
        vector<wstring> fristPy;
        vector<wstring> fullPy;
        getAllPingyinForWord(inStr.substr(i_word,1), fristPy, fullPy);

        fristPys.push_back(fristPy);
        fullPys.push_back(fullPy);
    }


    // --- 开始排列组合
    vector<int> nowIndexList;
    vector<int> maxIndexList;
    int sum_maxIndexList = 0;
    for (size_t i = 0; i < numOfWord; i++)
    {
        nowIndexList.push_back(0);
        maxIndexList.push_back(int(fullPys[i].size()) - 1);
        sum_maxIndexList += maxIndexList[i];
    }


    // --- 第一次组合（所有采用第一个）
    bool mustCombination = sum_maxIndexList > 0 ? true : false;
    for (size_t i = 0; i < numOfWord; i++)
    {
        outFrist_py += fristPys[i][0];
        outFull_py += fullPys[i][0];
    }


    // --- 循环遍历
    while (mustCombination)
    {
        // --- 组合排列
        bool alreadyRunOnce = false;
        for (size_t i = 0; i < numOfWord; i++)
        {
            if (alreadyRunOnce)
            {
                break;
            }

            if (maxIndexList[i] != 0)
            {
                if (nowIndexList[i] < maxIndexList[i])
                {
                    alreadyRunOnce = true;
                    nowIndexList[i]++;
                }
                else if (nowIndexList[i] == maxIndexList[i])
                {
                    nowIndexList[i] = 0;
                }
            }
        }

        // --- 组合输出字符
        outFrist_py += L" ";
        outFull_py += L" ";
        for (size_t i = 0; i < numOfWord; i++)
        {
            outFrist_py += fristPys[i][nowIndexList[i]];
            outFull_py += fullPys[i][nowIndexList[i]];
        }

        // --- 退出条件
        bool canOut = true;
        for (size_t i = 0; i < numOfWord; i++)
        {
            if (nowIndexList[i] != maxIndexList[i])
            {
                canOut = false;
                break;
            }
        }
        if (canOut)
        {
            break;
        }
    }


    // --- 返回
    return 0;
}

wstring getNamePingyin(const wstring& inStr, bool isLastName)
{
    wstring outStr;

    // ----- 姓氏
    if (isLastName)
    {
        // --- 在百家姓中查找
        for (size_t i = 0; i < g_length_lastNameTable; i++)
        {
            if (inStr == lastNameTable[i].hanzi)
            {
                outStr = lastNameTable[i].pinyi;
                break;
            }
        }
    }

    // --- 直接汉字库查找
    if (outStr.empty())
    {
        for (size_t i = 0; i < inStr.size(); i++)
        {
            outStr += getNoRepeatPingyinForWord(inStr.substr(i,1));
        }
    }

    return outStr;
}

void myNameSplit(const wstring & inFullName, wstring& outLastName, wstring& outFirstName)
{
    const int doubleLastNameLength = 90;
    static wstring doubleLastName[doubleLastNameLength] =
    {
        L"欧阳" , L"太史" , L"端木" , L"上官" , L"司马" , L"东方" , L"独孤" , L"南宫" , L"万俟" , L"闻人" ,
        L"夏侯" , L"诸葛" , L"尉迟" , L"公羊" , L"赫连" , L"澹台" , L"皇甫" , L"宗政" , L"濮阳" , L"公冶" ,
        L"太叔" , L"申屠" , L"公孙" , L"慕容" , L"仲孙" , L"钟离" , L"长孙" , L"宇文" , L"司徒" , L"鲜于" ,
        L"司空" , L"闾丘" , L"子车" , L"亓官" , L"司寇" , L"巫马" , L"公西" , L"颛孙" , L"壤驷" , L"公良" ,
        L"漆雕" , L"乐正" , L"宰父" , L"谷梁" , L"拓跋" , L"夹谷" , L"轩辕" , L"令狐" , L"段干" , L"百里" ,
        L"呼延" , L"东郭" , L"南门" , L"羊舌" , L"微生" , L"公户" , L"公玉" , L"公仪" , L"梁丘" , L"公仲" ,
        L"公上" , L"公门" , L"公山" , L"公坚" , L"左丘" , L"公伯" , L"西门" , L"公祖" , L"第五" , L"公乘" ,
        L"贯丘" , L"公皙" , L"南荣" , L"东里" , L"东宫" , L"仲长" , L"子书" , L"子桑" , L"即墨" , L"达奚" ,
        L"褚师" , L"吴铭" , L"纳兰" , L"归海" , L"东皇" , L"泽翁" , L"阿扎" , L"泽朗" , L"索朗" , L"邓真"
    };

    // --- 如果有非汉字字符，直接返回
    for (size_t i = 0; i < inFullName.size(); i++)
    {
        if (!isHanziChar(inFullName[i]))
        {
            outLastName = L"";
            outFirstName = inFullName;
            return;
        }
    }


    //
    outLastName = L"";
    outFirstName = L"";

    if (inFullName.empty())
    {
    }
    else if (inFullName.size() == 1)
    {
        outFirstName = inFullName;
    }
    else if (inFullName.size() == 2)
    {
        outLastName = inFullName[0];
        outFirstName = inFullName[1];
    }
    else
    {
        wstring guessLastName = inFullName.substr(0,2);
        for (int i = 0; i < doubleLastNameLength; i++)
        {
            if (guessLastName == doubleLastName[i])
            {
                outLastName = doubleLastName[i];
                outFirstName = inFullName.substr(2);
                break;
            }
        }

        if (outLastName.empty())
        {
            if (inFullName.size() == 4)
            {
                outLastName = inFullName.substr(0,2);
                outFirstName = inFullName.substr(2);
            }
            else
            {
                outLastName = inFullName[0];
                outFirstName = inFullName.substr(1);
            }
        }
    }

}

int getAllPingyinForWord(const wstring& inWord, vector<wstring>& outFrist_py, vector<wstring>& outFull_py)
{
    // 只能输入一个字符
    if (inWord.size() > 1)
    {
        return -1;
    }

    //
    outFrist_py.clear();
    outFull_py.clear();

    wchar_t wch = inWord[0];
    if (isHanziChar(wch))
    {
        for (int index_table = 0; index_table < g_length_hanziTables; index_table++)
        {
            if (hanziTables[index_table].hanzis.find(wch) != -1)
            {
                outFrist_py.push_back(hanziTables[index_table].first_py);
                outFull_py.push_back(hanziTables[index_table].full_py);
            }
        }
    }

    if (outFrist_py.empty())
    {
        outFrist_py.push_back(inWord);
    }
    if (outFull_py.empty())
    {
        outFull_py.push_back(inWord);
    }

    return 0;
}

wstring getNoRepeatPingyinForWord(const wstring& inWord)
{
    wstring outPingyin;

    // 只能输入一个字符
    if (inWord.size() > 1)
    {
        return inWord;
    }

    // ----- 先在多音字里面查询
    for (int i = 0; i < g_length_multiToneWordTable; i++)
    {
        if (inWord == multiToneWordTable[i].hanzi)
        {
            outPingyin = multiToneWordTable[i].pinyi;
            break;
        }
    }

    // ----- 继续查询
    if (!outPingyin.empty())
    {
        return outPingyin;
    }

    // ----- 在全字库查找
    wchar_t wch = inWord[0];
    if (isHanziChar(wch))
    {
        for (int index_table = 0; index_table < g_length_hanziTables; index_table++)
        {
            if (hanziTables[index_table].hanzis.find(wch) != -1)
            {
                outPingyin = hanziTables[index_table].full_py;
                break;
            }
        }
    }

    //
    if (outPingyin.empty())
    {
        outPingyin = inWord;
    }

    // ----- 返回结果
    return outPingyin;
}

bool isHanziChar(wchar_t wch) {
    // 在vs2019 上使用 qstring 时
    // return (wch >= 0x4E00 && wch <= 0x9FA5) ? true : false;

    // 在vs2019 上使用 wstring 时
    //return (wch >= 12570 && wch <= 64041) ? true : false;

    // 这是一种折中方案 => 汉字不会有任何遗漏，能适应大多数编码方式（可过滤掉绝大多数常用非汉字字符）
    // 如果想获取准确的区间，使用testHanziRang()方法；
    return wch > 127 ? true : false;
}

void testHanziRang() {
    wstring str;
    for (size_t i = 0; i < g_length_hanziTables; i++)
    {
        str += hanziTables[i].hanzis;
    }

    int maxVal = 0;
    int minVal = 1000000000;
    wchar_t maxStr = L' ';
    wchar_t minStr = L' ';
    for (size_t i = 0; i < str.size(); i++)
    {
        int uncd = str[i];
        if (uncd > maxVal)
        {
            maxVal = uncd;
            maxStr = str[i];
        }
        if (uncd < minVal)
        {
            minVal = uncd;
            minStr = str[i];
        }
    }

    printf("\n汉字编码测试：\n");
    printf("最小编码值：%d , 最大编码值:%d , 总汉字数量(未去重)：%zd \n", minVal, maxVal,str.size());

    printf("最小编码值的汉字：%wc , 最大编码值的汉字: %wc \n", minStr, maxStr);

    // 【注意】
    // 如果想使printf可以打印wchar_t
    // setlocale(LC_ALL, "");  // 在初始化时调用这个
    // #include <iostream>     // 对应的头文件
}
