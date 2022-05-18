#ifndef DRUNKARD_OWNED_STATE_H
#define DRUNKARD_OWNED_STATE_H
//------------------------------------------------------------------------
//
//  Name:   DrunkardOwnedState.h
//
//  Desc:   All the states that can be assigned to the Drunkard class.
//			Note that a global state has not been implemented.
//
//  Author: Begin Florian & Audiffret Sam
//
//------------------------------------------------------------------------
#include "FSM/State.h"

class Drunkard;
struct Telegram;

//------------------------------------------------------------------------
//
//  In this state the Drunkard will go to the Saloon. When he is not more
//  thirsty, then it'll change state to GoHomeAndRest and when it's rested
//	it'll change state to DrinkInSaloon again.
//------------------------------------------------------------------------

class DrinkInSaloon : public State<Drunkard>
{
private:
	DrinkInSaloon() {}

	//copy ctor and assignment should be private
	DrinkInSaloon(const DrinkInSaloon&);
	DrinkInSaloon& operator=(const DrinkInSaloon&);

public:

	//this is a singleton
	static DrinkInSaloon* Instance();

	virtual void Enter(Drunkard* miner);

	virtual void Execute(Drunkard* miner);

	virtual void Exit(Drunkard* miner);

	virtual bool OnMessage(Drunkard* agent, const Telegram& msg);

};

//------------------------------------------------------------------------
//
//  Sleeppity sloupitty
// 
//------------------------------------------------------------------------
class GoHomeAndRest : public State<Drunkard>
{
private:

	GoHomeAndRest() {}

	//copy ctor and assignment should be private
	GoHomeAndRest(const GoHomeAndRest&);
	GoHomeAndRest& operator=(const GoHomeAndRest&);

public:

	//this is a singleton
	static GoHomeAndRest* Instance();

	virtual void Enter(Drunkard* drunkard);

	virtual void Execute(Drunkard* drunkard);

	virtual void Exit(Drunkard* drunkard);

	virtual bool OnMessage(Drunkard* agent, const Telegram& msg);
};


#endif // !DRUNKARD_OWNED_STATE_H

