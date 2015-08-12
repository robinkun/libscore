/*--------------------------------------------
 * 用紙に合わせた、楽譜要素の位置などをまとめる場所
 * vが付くものはvertical、hが付くものはhorizontal
 * 最後にpを付けるとpixel
--------------------------------------------*/
#ifndef SCOREFORM_H
#define SCOREFORM_H
#include "ScoreFormVal.h"
#include <string>

extern const float MMPI; // mm per inch
class ScoreForm;
class DefaultScoreForm;

void initScoreForm();
int mmToPixel(float mm, int dpi);

class DefaultScoreForm {
protected:
    ScoreFormVal form_type;
    std::string form_name;
    int form_width;
    int form_height;
    float h_form_blank;
    float up_form_blank;
    float down_form_blank;
    float h_center_space;
    float v_piano_space;
    float note_radius;
public:
    void setFormType(ScoreFormVal t) {form_type = t;}
    void setFormWidth(int w)         {form_width = w;}
    void setFormHeight(int h)        {form_height = h;}
    void setHFormBlank(int b)        {h_form_blank = b;}
    void setUpFormBlank(int b)       {up_form_blank = b;}
    void setDownFormBlank(int b)     {down_form_blank = b;}
    void setHCenterSpace(int s)      {h_center_space = s;}
    void setVPianoSpace(int s)       {v_piano_space = s;}
    void setNoteRadius(int r)        {note_radius = r;}
    void setFormName(std::string str){form_name = str;}
    ScoreFormVal formType()          {return form_type;}
    int formWidth()                  {return form_width;}
    int formHeight()                 {return form_height;}
    float hFormBlank()               {return h_form_blank;}
    float upFormBlank()              {return up_form_blank;}
    float downFormBlank()            {return down_form_blank;}
    float hCenterSpace()             {return h_center_space;}
    float vPianoSpace()              {return v_piano_space;}
    float noteRadius()               {return note_radius;}
    std::string formName()           {return form_name;}
};

class ScoreForm : public DefaultScoreForm {
    int _column;
    int score_row;
    int score_column;
    int _dpi;
public:
    ScoreForm();
    ScoreForm(ScoreFormVal t, int d = 720);
    void setColumn(int c)        {_column = c;}
    void setDpi(int d)           {_dpi = d;}
    void setScoreRow(int r)      {score_row = r;}
    void setScoreColumn(int c)   {score_column = c;}
    int setForm(ScoreFormVal t);
    int column()                 {return _column;}
    int scoreRow()               {return score_row;}
    int scoreColumn()            {return score_column;}
    int dpi()                    {return _dpi;}
    int formWidthP()             {return mmToPixel(form_width, _dpi);}
    int formHeightP()            {return mmToPixel(form_height, _dpi);}
    int hFormBlankP()            {return mmToPixel(h_form_blank, _dpi);}
    int upFormBlankP()           {return mmToPixel(up_form_blank, _dpi);}
    int downFormBlankP()         {return mmToPixel(down_form_blank, _dpi);}
    int hCenterSpaceP()          {return mmToPixel(h_center_space, _dpi);}
    int vPianoSpaceP()           {return mmToPixel(v_piano_space, _dpi);}
    int hScoreSpaceP();
    int vScoreSpaceP();
    int vMeasureSpaceP();
    int NoteRadiusP()            {return mmToPixel(note_radius, _dpi);}
};

#endif // SCOREFORM_H
