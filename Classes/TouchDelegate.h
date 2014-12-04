#ifndef BLOCK_TOUCH_DELEGATE
#define BLOCK_TOUCH_DELEGATE



class TouchDelegate
{

public:

	virtual void onLeft() = 0;

	virtual void onRight() = 0;

	virtual void onRotate() = 0;

	virtual void onDown() = 0;

	virtual void onHardDrop() = 0;

	virtual void onSoftDropStart() = 0;

	virtual void onSoftDropStop() = 0;

	virtual void onHold() = 0;


};







#endif