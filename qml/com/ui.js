.import "com.js" as Com

let platform = $a.getPlatform();

/////////////////MAC/////////////////
let nav_width = 70;
let nav_tab_height = 52;
let main_st_height = 0;
let nav_btn_imp_font_size = 25;
let nav_btn_serv_font_size = 15;
let nav_btn_more_font_size = 25;
let book_edit_label_font_size = 16;
let book_btn_view_font_size = 12;
let book_btn_tag_font_size = 20;
let book_btn_add_font_size = 25;
let tag_font_size = 16;
let tag_simple_font_size = 12;
let tag_count_font_size = 10;
let col_font_size = 16;
let col_font_size2 = 12;
let btn_font_smybol_size = 20;
let btn_close_font_size = 18;
let total_font_size = 12;
let date_font_size = 12;
let note_font_size = 15;
let detail_time_font_size = 13;
let tag_off = 18;
let about_label_font_size = 12;
let space_note_list_row = 15;

let ui_xm_list_margin = 10;
let ui_pk_text_margin = 10;
let ui_date_height = 20;
let ui_col_row_height = 30;
let ui_pk_cont_space = 8;
let ui_separate_height = 1;
let ui_separate_color = "#cacaca";
let ui_font_pk = 16;
let ui_font_pk_time = 11;
let ui_line_height_pk = 1.2;
let ui_highlight_color = $a.getCfgVal("ui_highlight_color");

let font_size_title1 = 18;
let font_size_title2 = 12;
let font_size_btn = 14;
let font_size_h1 = 40;
let font_size_h2 = 33;
let font_size_h3 = 25;
let font_size_normal = 14;
let font_size_small = 12;
let font_size_quote = 12;
let font_size_0 = 10;
let color_quote_bg = "#181818";
let color_quote_text = "#FFFFFF";
let color_link = "#0066ff";
let color_tool_bar = "transparent";

let width_text_date = 80;

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
    tag_font_size = 10;
    tag_simple_font_size = 8;
    tag_count_font_size = 6;
    col_font_size = 12;
    col_font_size2 = 8;
    btn_close_font_size = 13;
    total_font_size = 8;
    date_font_size = 8;
    note_font_size = 12;
    detail_time_font_size = 10;
    tag_off = 22;
    about_label_font_size = 10;
    space_note_list_row = 15;

    ui_xm_list_margin = 10;
    ui_pk_text_margin = 10;
    ui_date_height = 20;
    ui_col_row_height = 30;
    ui_pk_cont_space = 15;
    ui_separate_height = 1;
    ui_font_pk = 12;
    ui_font_pk_time = 10;
    ui_line_height_pk = 1.2;

    font_size_h1 = 32;
    font_size_h2 = 25;
    font_size_h3 = 17;

    font_size_normal = 10;
    font_size_small = 8;
    font_size_title1 = 15;
    font_size_title2 = 10;

    font_size_btn = 10;
    width_text_date = 110;
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
    total_font_size = 10;
    date_font_size = 10;
    note_font_size = 12;
    detail_time_font_size = 10;
    tag_off = 22;
    about_label_font_size = 8;

    ui_xm_list_margin = 10;
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
