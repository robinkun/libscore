#include "ScoreForm.h"
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <sprout/string.hpp>
#include <iostream>

std::vector<DefaultScoreForm> default_score_form;
static bool is_inited = false; // 外から見える必要はない
constexpr float MMPI = 25.4;
const int DEFAULT_SCORE_COLUMN = 8;
const int DEFAULT_SCORE_ROW = 4;

void copy_form(DefaultScoreForm &source, DefaultScoreForm &dst);
int read_form_file(std::string path);

/*--------------------------------------------
 * formをコピーする関数
 * ScoreForm内の関数で使うために作ったので、
 * それ以外で使う必要はない
--------------------------------------------*/
void copy_form(DefaultScoreForm &source, DefaultScoreForm &dst) {
    // sourceは書き換えてはならない
    dst = source;
}

/*--------------------------------------------
 * コンストラクタ
--------------------------------------------*/
ScoreForm::ScoreForm() {
    // initScoreForm()が実行されてないと使うことは許さない
    try {
        if(!is_inited) {
            throw "paper setting isn't inited.";
        }
    }
    catch (char *str){
        printf("[ScoreForm] %s¥n", str);
        exit(1);
    }
    _column = 2;
    score_column = DEFAULT_SCORE_COLUMN;
    score_row = DEFAULT_SCORE_ROW;
    setForm(A4);
}

/*--------------------------------------------
 * コンストラクタ
 * デフォルトの用紙設定で初期化される
--------------------------------------------*/
ScoreForm::ScoreForm(ScoreFormVal t, int d) {
    // initScoreForm()が実行されてないと使うことは許さない
    try {
        if(!is_inited) {
            throw "paper setting isn't inited.";
        }
    }
    catch (char *str){
        printf("[ScoreForm] %s¥n", str);
        exit(1);
    }
    setForm(t);
    _dpi = d;
    _column = 2;
    score_column = DEFAULT_SCORE_COLUMN;
    score_row = DEFAULT_SCORE_ROW;
    form_type = t;
}

/*--------------------------------------------
 * 用紙設定をtの設定で初期化
 * tはA4とかで指定する
--------------------------------------------*/
int ScoreForm::setForm(ScoreFormVal t) {
    // この関数を実行すると、クラスのすべての値が
    // 一斉に変わるようにしたい
    // この関数いらないかも
    // やっぱいるかも…
    copy_form(default_score_form[t], *this);
    form_type = t;

    return 0;
}

/*--------------------------------------------
 * column width
--------------------------------------------*/
int ScoreForm::hScoreSpaceP() {
    // bimyou
    float tmp = (float)form_width - h_form_blank * 2.0;
    tmp -= h_center_space * ((float)_column - 1.0);
    tmp /= (float)_column;
    return mmToPixel(tmp, _dpi);
}

/*--------------------------------------------
 * row height
--------------------------------------------*/
int ScoreForm::vScoreSpaceP() {
    // `mikannsei
    float tmp = (float)form_height - up_form_blank - down_form_blank;
    tmp -= v_piano_space * 2.0;
    return mmToPixel(tmp, _dpi);
}

/*--------------------------------------------
 * measure height
--------------------------------------------*/
int ScoreForm::vMeasureSpaceP() {
    float tmp = (float)form_height - up_form_blank - down_form_blank;
    tmp -= v_piano_space * 2.0;
    tmp /= score_row;
    return mmToPixel(tmp, _dpi);
}

/*--------------------------------------------
 * 楽譜用紙の大きさをmm単位で初期化する
 * score_formをあわせて初期化する
--------------------------------------------*/
void initScoreForm() {
    default_score_form = std::vector<DefaultScoreForm>(0);
    is_inited = true;/*
    default_score_form[ScoreFormVal::A0].setFormWidth(841);
    default_score_form[ScoreFormVal::A1].setFormWidth(594);
    default_score_form[ScoreFormVal::A2].setFormWidth(420);
    default_score_form[ScoreFormVal::A3].setFormWidth(297);
    default_score_form[ScoreFormVal::A4].setFormWidth(210);
    default_score_form[ScoreFormVal::A5].setFormWidth(148);

    default_score_form[ScoreFormVal::A0].setFormHeight(1189);
    default_score_form[ScoreFormVal::A1].setFormHeight(841);
    default_score_form[ScoreFormVal::A2].setFormHeight(594);
    default_score_form[ScoreFormVal::A3].setFormHeight(420);
    default_score_form[ScoreFormVal::A4].setFormHeight(297);
    default_score_form[ScoreFormVal::A5].setFormHeight(210);

    default_score_form[ScoreFormVal::B0].setFormWidth(1030);
    default_score_form[ScoreFormVal::B1].setFormWidth(728);
    default_score_form[ScoreFormVal::B2].setFormWidth(515);
    default_score_form[ScoreFormVal::B3].setFormWidth(364);
    default_score_form[ScoreFormVal::B4].setFormWidth(257);
    default_score_form[ScoreFormVal::B5].setFormWidth(182);

    default_score_form[ScoreFormVal::B0].setFormHeight(1456);
    default_score_form[ScoreFormVal::B1].setFormHeight(1030);
    default_score_form[ScoreFormVal::B2].setFormHeight(728);
    default_score_form[ScoreFormVal::B3].setFormHeight(515);
    default_score_form[ScoreFormVal::B4].setFormHeight(364);
    default_score_form[ScoreFormVal::B5].setFormHeight(257);*/
    //std::cout << default_score_form[0].formWidth() << std::endl;
    if(read_form_file("./score_form_list.dat")) exit(1);

    //std::cout << default_score_form[1].formWidth() << std::endl;
}

/*--------------------------------------------
 * ファイルからデフォルトのscore_formの値を読み込む
 * セキュリティガン無視
--------------------------------------------*/
int read_num(std::ifstream &ifs) {
    std::string str_tmp;
    wchar_t chr;

    for(chr = ifs.get(); chr; chr = ifs.get()) {
        if(chr >= '0' && chr <= '9') {
            str_tmp.append(1, chr);
        } else if(chr == ',' || chr == '\n') {
            break;
        } else if(chr == EOF) {
            throw 0;
            return 0;
        } else {
            throw "[ScoreForm] syntax error of default score_form file .";
            return -1;
        }
    }

    return std::stoi(str_tmp);
}

/*--------------------------------------------
 * ファイルからデフォルトのscore_formの値を読み込む
--------------------------------------------*/
int read_form_file(std::string path) {
    std::ifstream ifs = std::ifstream(path);
    std::string name; // 用紙の名前
    std::string str_tmp;
    wchar_t chr;

    if(ifs.fail()) {
        std::cout << "couldn't read file." << std::endl;
        return 1;
    }


    for(;;) {
        for(chr = ifs.get(); chr; chr = ifs.get()) {
            if(chr == L'=') break;
            else if(chr == '\n' || chr == EOF) {
                puts("[ScoreForm] syntax error of default score_form file .");
                return 1;
            }
            name.append(1, chr);
        }

        DefaultScoreForm tmp;
        try {
            tmp.setFormWidth(read_num(ifs));
            tmp.setFormHeight(read_num(ifs));
            tmp.setVPianoSpace(read_num(ifs));
            tmp.setUpFormBlank(read_num(ifs));
            tmp.setDownFormBlank(read_num(ifs));
            tmp.setHCenterSpace(read_num(ifs));

            tmp.setFormName(name);
        }
        catch(char *str) {
            printf("%s¥n", str);
        }
        catch(int num) {
            if(num == 0) {
                default_score_form.push_back(tmp);
                break;
            }
        }

        default_score_form.push_back(tmp);

    }

    ifs.close(); // 書く意味ないけど書きたい
    return 0;
}

/*--------------------------------------------
 * mmをdpiを使ってピクセル値に変換
--------------------------------------------*/
int mmToPixel(float mm, int dpi) {
    return mm * dpi / MMPI;
}
