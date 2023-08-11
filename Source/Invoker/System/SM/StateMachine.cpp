#include "StateMachine.h"


void StateMachine::Init(StateType defaultState)
{
	check(CurState==nullptr);
}

void StateMachine::Release()
{
	
}

StateBase* StateMachine::GetCurState()
{
	return CurState;
}

StateType StateMachine::GetCurStateType()
{
	return StateType::Attack;
}

bool StateMachine::GotoState(StateType type)
{
	return true;
}
