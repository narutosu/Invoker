#pragma once
#include "Invoker/System/SM/StateType.h"

class StateBase
{
public:
	virtual StateType GetStateType()=0;
	virtual bool CheckGotoState()=0;
	virtual void OnEnter();
	virtual void OnLeave();
};
