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
	unsigned _count3;
	unsigned _count4;
    void Init() override;
    void Show() override;
    void setShowPrice(bool questionMark) { _isShowPrice = questionMark;}
private:
    bool _isShowPrice = false;
    game_framework::Bittermap _frame;
    game_framework::Bittermap _itemSprite;
	Digit _d1 = Digit(&_count1, 1.2f);
	Digit _d2 = Digit(&_count2, 1.2f);
	Digit _d3 = Digit(&_count3, 1.2f);
	Digit _d4 = Digit(&_count4, 1.2f);
	const unsigned kPrice1 = 20;
	const unsigned kPrice2 = 80;
	const unsigned kPrice3 = 200;
	const unsigned kPrice4 = 40;
	Digit _d1_price = Digit(&kPrice1, 1.2f);
	Digit _d2_price = Digit(&kPrice2, 1.2f);
	Digit _d3_price = Digit(&kPrice3, 1.2f);
	Digit _d4_price = Digit(&kPrice4, 1.2f);
};

#endif /* TOOLBAR_H */
