#ifndef __ITEM_H__
#define __ITEM_H__

#include "Sprite.h"
#include "Camera.h"
#include "Texture.h"
#include "BaseObject.h" 
#include "Global.h" 

class Item : public BaseObject
{
protected:

	DWORD TimeDisplayMax; // thời gian tối đa cho phép hiển thị.
	DWORD TimeDisplayed; // Thời gian đã hiển thị.

	DWORD TimeWaited; // Thời gian đã chờ trước khi hiển thị
	DWORD TimeWaitMax; // Thời gian tối đa phải chờ trước khi hiển thị

	bool isFinish; // đã kết thúc chưa?

public:
	//virtual void Update(int t);
	void setFireDie(int a);
	void setXFire(int a);
	void setYFire(int a);

	Item();

	int			getIsDie();
	void		setIsDie(bool a);
	void		setX(int a);
	void        setY(int a);
	void setCountTime();
	virtual void Update(int t);
	~Item();
};



#endif // !__ITEM_H__




