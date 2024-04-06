.import "com.js" as Com

let platform = $app.getPlatform();

/////////////////MAC/////////////////
let nav_width = 70;
let nav_tab_height = 52;
let main_st_height = 0;
let nav_btn_imp_font_size = 25;
let nav_btn_serv_font_size = 15;
let nav_btn_more_font_size = 25;
let book_edit_label_font_size = 16;
let book_btn_view_font_size = 15;
let book_btn_tag_font_size = 22;
let book_btn_add_font_size = 25;
let col_font_size = 16;
let btn_font_size = 14;
let btn_font_smybol_size = 20;
let total_font_size = 12;
let date_font_size = 12;
let note_font_size = 15;
let detail_time_font_size = 13;
let tag_off = 18;
let about_label_font_size = 12;
let my_feild_font_size = 12;

let ui_pk_list_margin = 10;
let ui_pk_text_margin = 10;
let ui_date_height = 20;
let ui_col_row_height = 30;
let ui_pk_cont_space = 8;
let ui_separate_height = 1;
let ui_separate_color = "#cacaca";
let ui_font_pk = 16;
let ui_font_pk_time = 11;
let ui_line_height_pk = 1.2;
let ui_highlight_color = $app.getCfgVal("ui_highlight_color");

let font_size_title1 = 18;
let font_size_title2 = 12;
let font_size_btn = 12;
let font_size_h1 = 40;
let font_size_h2 = 33;
let font_size_h3 = 25;
let font_size_normal = 14;
let font_size_quote = 12;
let font_size_0 = 10;
let color_quote_bg = "#181818";
let color_quote_text = "#FFFFFF";
let color_link = "#0066ff";
let color_tool_bar = "transparent";

/////////////////WIN/////////////////
if(platform === Com.platform_win) {
    nav_width = 70;
    main_st_height = 24;
    nav_btn_imp_font_size = 20;
    nav_btn_more_font_size = 20;
    book_edit_label_font_size = 12;
    book_btn_view_font_size = 11;
    book_btn_tag_font_size = 14;
    book_btn_add_font_size = 20;
    col_font_size = 16;
    btn_font_size = 11;
    total_font_size = 10;
    date_font_size = 8;
    note_font_size = 12;
    detail_time_font_size = 10;
    tag_off = 22;
    about_label_font_size = 10;
    my_feild_font_size = 8;

    ui_pk_list_margin = 10;
    ui_pk_text_margin = 10;
    ui_date_height = 20;
    ui_col_row_height = 30;
    ui_pk_cont_space = 15;
    ui_separate_height = 1;
    ui_font_pk = 12;
    ui_font_pk_time = 10;
    ui_line_height_pk = 1.2;

    font_size_normal = 12;
    font_size_title1 = 15;
    font_size_title2 = 10;

    font_size_btn = 9;
}

/////////////////LINUX/////////////////
if(platform === Com.platform_linux) {
    nav_width = 70;
    main_st_height = 0;
    nav_btn_imp_font_size = 20;
    nav_btn_more_font_size = 20;
    book_edit_label_font_size = 12;
    book_btn_view_font_size = 11;
    book_btn_tag_font_size = 14;
    book_btn_add_font_size = 20;
    col_font_size = 16;
    btn_font_size = 11;
    total_font_size = 10;
    date_font_size = 10;
    note_font_size = 12;
    detail_time_font_size = 10;
    tag_off = 22;
    about_label_font_size = 8;
    my_feild_font_size = 8;

    ui_pk_list_margin = 10;
    ui_pk_text_margin = 10;
    ui_date_height = 20;
    ui_col_row_height = 30;
    ui_pk_cont_space = 15;
    ui_separate_height = 1;
    ui_font_pk = 12;
    ui_font_pk_time = 10;
    ui_line_height_pk = 1.2;

    font_size_normal = 12;
    font_size_title2 = 8;
}
