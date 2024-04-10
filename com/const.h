#ifndef CONST_H
#define CONST_H

#include <QString>
#define PAGE_SIZE 50
#define SIMPLE_SIZE 200
#define MAX_TAG 6
#define GEN_PDF_MAX_WIDTH 520
#define FILE_PRE "file:///"
#define FILE_PRE_MAC "file://"
#define WIN 0
#define UNIX 1
#define MAC 2
#define VERSION "1.34.3"

#define CB_VAR std::function<QVariantList()>

const static QString sql_work_table =
"create table if not exists work("
    "id INTEGER not null primary key,"
    "name TEXT default '' not null,"
    "author TEXT default '' not null,"
    "time INTEGER default 0 not null,"
    "t INTEGER default 0 not null,"
    "fro INTEGER default 0 not null,"
    "tag TEXT default '' not null,"
    "extra TEXT default '' not null"
")";

const static QString sql_note_table =
"CREATE TABLE IF NOT EXISTS `note` ("
    "id INTEGER not null primary key,"
    "wid INTEGER default 0 not null,"
    "pos0 INTEGER default 0 not null,"
    "pos1 INTEGER default 0 not null,"
    "time INTEGER default 0 not null,"
    "cont TEXT default '' not null,"
    "tags TEXT default '' not null,"
    "bj INTEGER default 0 not null," //只是标记导入时是否是笔记，导入后是否是笔记不能根据此字段识别，而是看:[xxxx]
    "del INTEGER default 0 not null,"
    "refids TEXT default '' not null,"
    "refimgids TEXT default '' not null"
")";
const static QString sql_note_script = "create unique index note_time_uindex on note (time);";

const static QString sql_col_table =
"CREATE TABLE IF NOT EXISTS `col` ("
    "id INTEGER not null primary key,"
    "name TEXT default '' not null,"
    "i INTEGER default 0 not null,"
    "x INTEGER default 0 not null"
")";
const static QString sql_pk_table =
"CREATE TABLE IF NOT EXISTS `pk` ("
    "id INTEGER not null primary key,"
    "cid INTEGER default 0 not null,"
    "cont TEXT default '' not null,"
    "img TEXT default '' not null,"
    "time INTEGER default 0 not null,"//秒
    "lst INTEGER default 0 not null,"//秒
    "stime INTEGER default 0 not null,"//解决时间
    "tags TEXT default '' not null,"
    "jm INTEGER default 0 not null,"
    "bj INTEGER default 0 not null,"
    "refids TEXT default '' not null,"
    "refimgids TEXT default '' not null"
")";

const static QString sql_tag_table =
"CREATE TABLE IF NOT EXISTS `tag` ("
    "id INTEGER not null primary key,"
    "tag TEXT default '' not null"
")";

const static QString sql_env_table =
"create table if not exists `env` ("
    "k varchar constraint env_pk primary key,"
    "v text default '' not null"
");";
const static QString ENV_K_LAST_IMP_PATH = "LAST_IMP_PATH";
const static QString ENV_K_LAST_IMP_TIME = "LAST_IMP_TIME";
const static QString ENV_K_LAST_EXCHANGE_VERSION = "LAST_EXCHANGE_VERSION";
const static QString ENV_K_LAST_SORT = "LAST_SORT";
const static QString ENV_K_LAST_VIEW_TYPE = "LAST_VIEW_TYPE";
const static QString ENV_K_LAST_WH = "LAST_WH";
const static QString ENV_K_LAST_COLLECT_LEFT_WIDTH = "LAST_COLLECT_LEFT_WIDTH";
const static QString ENV_K_LAST_BOOK_LEFT_WIDTH = "LAST_BOOK_LEFT_WIDTH";
const static QString Tag1 = "<font color='red'>";
const static QString Tag2 = "</font>";
const static uint CONT_TYPE_PK = 0;
const static uint CONT_TYPE_BOOK = 1;
const static QString NOTE_BJ_STYLE = " style='color:gray;text-align: right;font-style: italic; font-size: 14px;'";

const static QString LOG_LEVEL_TRACE = "trace";
const static QString LOG_LEVEL_DEBUG = "debug";
const static QString LOG_LEVEL_INFO = "info";
const static QString LOG_LEVEL_WARN = "warn";
const static QString LOG_LEVEL_ERROR = "error";
const static uint LOG_LEVEL_TRACE_VAL = 0;
const static uint LOG_LEVEL_DEBUG_VAL = 1;
const static uint LOG_LEVEL_INFO_VAL = 2;
const static uint LOG_LEVEL_WARN_VAL = 3;
const static uint LOG_LEVEL_ERROR_VAL = 4;

const static uint FILE_TYPE_IMG = 1;
const static uint FILE_TYPE_TXT = 2;
const static uint FILE_TYPE_PDF = 3;
const static uint FILE_TYPE_HTML = 4;
const static uint FILE_TYPE_XM = 5;
const static uint FILE_TYPE_SITE = 6;

const static QString CODE_TABLE = "~r9y.2s=79#)aef^_kno%4h|u6?5wlz`({dc;vp<q3,0&x/!'7[-+mb@>gt*i}ja$";
const static QString CODE36 = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const static QString HTTP_PRE = "http://";
const static QString HTTPS_PRE = "https://";
const static QString SM_FLAG = "SHAREMEMORY_XXMOON";
const static QString FOLDER_RESOURCES = "resources";

const static uint MAX_XM_IMG_COUNT = 10000;
const static uint SIZE_1G = 1*1024*1024*1024;

//==============================//
const int Cmd_EnableServer = 0;
const int Cmd_DisableServer = 1;
const int Cmd_GenQRCode = 2;
const int Cmd_DeviceList = 3;
const int Cmd_DelDevice = 4;
const int Cmd_SendToPhone = 5;
const int Cmd_GetCurQRCode = 6;

const int PUSH_SERVER = 0;
const int PUSH_OPENFILE = 1;
const int PUSH_OPEN_ABOUT = 2;
const int PUSH_UP_TAGS = 3;

//
const static QString WEBSITE = "https://xxmoon.com";
const static QString PAGE_Xxmoonpc = "xxmoon_pc.html";
#endif //CONST_H
