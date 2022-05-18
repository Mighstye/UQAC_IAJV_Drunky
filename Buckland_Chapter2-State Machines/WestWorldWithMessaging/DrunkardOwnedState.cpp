#include "DrunkardOwnedState.h"
#include "FSM/State.h"
#include "Drunkard.h"
#include "Locations.h"
#include "Messaging/Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "Time/CrudeTimer.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;


#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif // TEXTOUTPUT

// Methods for DrinkInSaloon

DrinkInSaloon* DrinkInSaloon::Instance()
{
	static DrinkInSaloon instance;

	return &instance;
}

void DrinkInSaloon::Enter(Drunkard* pDrunkard)
{
	if (pDrunkard->Location() != saloon)
	{
		cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Wanna drink again... Going to the saloon.";

		pDrunkard->ChangeLocation(saloon);
	}
}

void DrinkInSaloon::Execute(Drunkard* pDrunkard)
{
	pDrunkard->Drink();

	pDrunkard->IncreaseFatigue();

	cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Drinking...";

	if (pDrunkard->Fatigued())
	{
		pDrunkard->GetFSM()->ChangeState(GoHomeAndRest::Instance());
	}
}

void DrinkInSaloon::Exit(Drunkard* pDrunkard)
{
	cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": "
		<< "Leaving the Saloon...";
}

bool DrinkInSaloon::OnMessage(Drunkard* pDrunkard, const Telegram& msg)
{
	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	switch (msg.Msg)
	{
	case Msg_Hello:
		cout << "\nMessage handled by " << GetNameOfEntity(pDrunkard->ID())
			<< "at time: " << Clock->GetCurrentTime();

		cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << "replying to message.";

		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
			pDrunkard->ID(),
			ent_Miner_Bob,
			Msg_Threaten,
			NO_ADDITIONAL_INFO);
		return true;
	default:
		break;
	}

	return false;
}

GoHomeAndRest* GoHomeAndRest::Instance()
{
	static GoHomeAndRest instance;

	return &instance;
}

void GoHomeAndRest::Enter(Drunkard* pDrunkard)
{
	if (pDrunkard->Location() != drunkard_home)
	{
		cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "Returning Home after a good day o' liqor inspection.";

		pDrunkard->ChangeLocation(drunkard_home);
	}
}

void GoHomeAndRest::Execute(Drunkard* pDrunkard) 
{
	if (pDrunkard->FullyRested())
	{
		cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": "
			<< "Ready for ah new day of drinkin' !";

		pDrunkard->GetFSM()->ChangeState(DrinkInSaloon::Instance());
	}

	else
	{
		pDrunkard->DecreaseFatigue();

		cout << "\n" << GetNameOfEntity(pDrunkard->ID()) << ": " << "ZZZ... ";
	}
}

void GoHomeAndRest::Exit(Drunkard* pDrunkard)
{

}

bool GoHomeAndRest::OnMessage(Drunkard* agent, const Telegram& msg)
{
	return false;
}