#ifndef CONST_H
#define CONST_H

#define PAGE_SIZE 20
#define FILE_PRE "file:///"
#define FILE_PRE_MAC "file://"
#define WIN 0
#define UNIX 1
#define MAC 2

#define CB_VAR std::function<QVariantList()>
#define CB_JSON std::function<void(QJsonObject&)>
#define CB std::function<void()>
#define CB_STR std::function<void(const QString&)>
#define CB_BL_STR std::function<bool(const QString&)>
#define CB_ERR std::function<void(QNetworkReply::NetworkError)>
#define CB_INT64_2 std::function<void(qint64,qint64)>

const static char* sql_work_table =
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

const static char* sql_note_table =
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
    "refimgids TEXT default '' not null,"
    "lst INTEGER default 0 not null"
")";
const static char* sql_note_script = "create unique index note_time_uindex on note (time);";

const static char* sql_category_table =
"CREATE TABLE IF NOT EXISTS `category` ("
    "id INTEGER not null primary key,"
    "name TEXT default '' not null,"
    "i INTEGER default 0 not null,"
    "x INTEGER default 0 not null,"
    "m TEXT default '',"
    "ty INTEGER default 0 not null"
")";
const static char* sql_xm_table =
"CREATE TABLE IF NOT EXISTS `xm` ("
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
    "refimgids TEXT default '' not null,"
    "top INTEGER default 0 not null,"
    "dtime INTEGER default 0 not null"
")";

const static char* sql_tag_table =
"CREATE TABLE IF NOT EXISTS `tag` ("
    "id INTEGER not null primary key,"
    "tag TEXT default '' not null"
")";

const static char* sql_env_table =
"create table if not exists `env` ("
    "k varchar constraint env_pk primary key,"
    "v text default '' not null"
");";

const static char* sql_task_log_table =
"create table if not exists `task_log` ("
    "id INTERGER not null primary key,"
    "xmid INTERGER not null default 0,"
    "ct INTERGER not null,"
    "cont TEXT not null default ''"
");";

const static char* VERSION = "v1.54.0";

const static char* ENV_K_LAST_IMP_PATH = "LAST_IMP_PATH";
const static char* ENV_K_LAST_IMP_TIME = "LAST_IMP_TIME";
const static char* ENV_K_LAST_EXCHANGE_VERSION = "LAST_EXCHANGE_VERSION";
const static char* ENV_K_LAST_SORT = "LAST_SORT";
const static char* ENV_K_LAST_VIEW_TYPE = "LAST_VIEW_TYPE";
const static char* ENV_K_LAST_WH = "LAST_WH";
const static char* ENV_K_LAST_CATEGORY_LEFT_WIDTH = "LAST_CATEGORY_LEFT_WIDTH";
const static char* ENV_K_LAST_BOOK_LEFT_WIDTH = "LAST_BOOK_LEFT_WIDTH";
const static char* ENV_K_SCRIPTS = "SCRIPTS";

const static char* Tag1 = "<font color='red'>";
const static char* Tag2 = "</font>";
const static unsigned int CONT_TYPE_PK = 0;
const static unsigned int CONT_TYPE_BOOK = 1;
const static char* NOTE_BJ_STYLE = " style='color:gray;text-align: right;font-style: italic; font-size: 14px;'";

const static char* LOG_LEVEL_TRACE = "trace";
const static char* LOG_LEVEL_DEBUG = "debug";
const static char* LOG_LEVEL_INFO = "info";
const static char* LOG_LEVEL_WARN = "warn";
const static char* LOG_LEVEL_ERROR = "error";
const static unsigned int LOG_LEVEL_TRACE_VAL = 0;
const static unsigned int LOG_LEVEL_DEBUG_VAL = 1;
const static unsigned int LOG_LEVEL_INFO_VAL = 2;
const static unsigned int LOG_LEVEL_WARN_VAL = 3;
const static unsigned int LOG_LEVEL_ERROR_VAL = 4;

const static unsigned int FILE_TYPE_IMG = 1;
const static unsigned int FILE_TYPE_TXT = 2;
const static unsigned int FILE_TYPE_PDF = 3;
const static unsigned int FILE_TYPE_HTML = 4;
const static unsigned int FILE_TYPE_XM = 5;
const static unsigned int FILE_TYPE_SITE = 6;

const static char* CODE_TABLE = "~r9y.2s=79#)aef^_kno%4h|u6?5wlz`({dc;vp<q3,0&x/!'7[-+mb@>gt*i}ja$";
const static char* CODE36 = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const static char* HTTP_PRE = "http://";
const static char* HTTPS_PRE = "https://";
const static char* SM_FLAG = "SHAREMEMORY_XXMOON";
const static char* FOLDER_RESOURCES = "resources";

const static unsigned int MAX_XM_IMG_COUNT = 10000;
const static unsigned int SIZE_1G = 1*1024*1024*1024;
const static unsigned int SIMPLE_SIZE = 250;
const static unsigned int MAX_TAG = 50;
const static unsigned int GEN_PDF_MAX_WIDTH = 50;

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
const int PUSH_ERR = 4;

const static char* DOLOG_XM_NEW = "nx %1";
const static char* DOLOG_XM_DEL = "dx %1 %2";
const static char* DOLOG_NOTE_NEW = "nn %1";
const static char* DOLOG_NOTE_DEL = "dn %1";
const static char* DOLOG_NOTE_BY_WID_DEL = "dnw %1";
const static char* DOLOG_CATEGORY_NEW = "nc %1";
const static char* DOLOG_CATEGORY_DEL = "dc %1";
const static char* DOLOG_WORK_NEW = "nw %1";
const static char* DOLOG_WORK_DEL = "dw %1";
const static char* DOLOG_ENV_NEW = "ne %1";
const static char* DOLOG_ENV_DEL = "de %1";
const static char* DOLOG_TAG_NEW = "nt %1";
const static char* DOLOG_TAG_DEL = "dt %1";
const static char* DOLOG_SQL = "sql %1";
const static char* DOLOG_TaskLog_NEW = "nl %1";
#endif //CONST_H
