#ifndef DRUNKARD_H
#define DRUNKARD_H
//------------------------------------------------------------------------
//
//  Name:   Drunkard.h
//
//  Desc:   A class defining a drunkard.
//
//  Author: Begin Florian & Audiffret Sam
//
//------------------------------------------------------------------------
#include <string>
#include <cassert>
#include <iostream>

#include "BaseGameEntity.h"
#include "Locations.h"
#include "misc//ConsoleUtils.h"
#include "DrunkardOwnedState.h"
#include "FSM/StateMachine.h"

template <class entity_type> class State;
struct Telegram;

//Above this value a drunkhard is thirsty
const int DrunkThirstLevel = 2;

//Above this value a drunkhard is sleepy
const int DrunkTirednessThreshold = 8;

class Drunkard : public BaseGameEntity
{
private:
	StateMachine<Drunkard>* m_pStateMachine;

	location_type			m_Location;

	int						m_iThirst;

	int						m_iFatigue;

public:

	Drunkard(int id) :m_Location(drunkard_home),
		m_iThirst(0),
		m_iFatigue(0),
		BaseGameEntity(id)
	{
		m_pStateMachine = new StateMachine<Drunkard>(this);

		m_pStateMachine->SetCurrentState(GoHomeAndRest::Instance());
	}

	~Drunkard() { delete m_pStateMachine; }

	void Update();

	virtual bool HandleMessage(const Telegram& msg);

	StateMachine<Drunkard>* GetFSM()const { return m_pStateMachine; }

	//-------------------------------------------------------------accessors
	location_type Location()const { return m_Location; }
	void		  ChangeLocation(location_type loc) { m_Location = loc; }

	bool Fatigued()const;
	void DecreaseFatigue() { m_iFatigue -= 1; m_iThirst += 1; }
	void IncreaseFatigue() { m_iFatigue += 1; }

	bool Thirsty()const;
	void Drink() { m_iThirst -= 1; }

	bool FullyRested()const;
};

#endif

