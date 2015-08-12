/*--------------------------------------------
 * 楽譜を描画するクラス
--------------------------------------------*/
#ifndef SCORERENDERER_H
#define SCORERENDERER_H
#include <qpainter.h>
#include "Score.h"

class ScoreRenderer {
    Score* _score;
    QPainter canvas;
public:
    ScoreRenderer(Score* s);
    Score* score()              {return _score;}
    void setScore(Score* s)     {_score = s;}
};

#endif // SCORERENDERER_H
