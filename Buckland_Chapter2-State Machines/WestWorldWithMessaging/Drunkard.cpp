#include "Drunkard.h"

bool Drunkard::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}

void Drunkard::Update() 
{
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

	m_pStateMachine->Update();
}

bool Drunkard::Thirsty()const
{
	if (m_iThirst >= DrunkThirstLevel) { return true; }

	return false;
}

bool Drunkard::Fatigued()const
{
	if (m_iFatigue > DrunkTirednessThreshold)
	{
		return true;
	}

	return false;
}

bool Drunkard::FullyRested()const
{
	if(m_iFatigue <= 0)
	{
		return true;
	}

	return false;
}

