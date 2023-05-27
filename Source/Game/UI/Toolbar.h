#ifndef TOOLBAR_H
#define TOOLBAR_H

#include "../Bittermap.h"
#include "./UI.h"
#include "../Bag.h"
#include "../UI/Digit.h"

class Toolbar : public UI {
public: //FIXME: too many ptr magic
	Bag const  *_bag;
	unsigned _count1;
	unsigned _count2;
    void Init() override;
    void Show() override;
private:
    game_framework::Bittermap _frame;
    game_framework::Bittermap _itemSprite;
	Digit _d1 = Digit(&_count1, 1.2f);
	Digit _d2 = Digit(&_count2, 1.2F);
};

#endif /* TOOLBAR_H */
