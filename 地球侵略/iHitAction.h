#pragma once
class iHitAction
{
//private:
//	virtual ~iHitAction() {}
public:
	virtual int doHitAction(int id) = 0;
};

// インタフェースを取得する関数
//iHitAction* GetHitAction(int n);