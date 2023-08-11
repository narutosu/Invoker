#pragma once
#include "State/StateBase.h"

class StateMachine
{
public:
	void Init(StateType defaultState);
	void Release();

	StateBase* GetCurState();
	StateType GetCurStateType();
	bool GotoState(StateType type);
private:
	StateBase* CurState=nullptr;
};
