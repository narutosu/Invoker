// Fill out your copyright notice in the Description page of Project Settings.


#include "CampInterface.h"

//是否可以通过点击 移动到它旁边并攻击或交互
bool UCampInterface::CanClickMoveTo(UCampInterface* target)
{
	return CampTag!=target->CampTag;
}