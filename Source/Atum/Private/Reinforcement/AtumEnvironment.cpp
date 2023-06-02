// © 2023 Kaya Adrian.

#include "Reinforcement/AtumEnvironment.h"

#include "Reinforcement/IAtumEnvironmentStateFinder.h"


#define LOCTEXT_NAMESPACE "AtumEnvironment"

UObject* AAtumEnvironment::ResetState() const
{
	OnEnvironmentResetState.Broadcast(this);
	return GetState();
}

UObject* AAtumEnvironment::GetState() const
{
	UObject* const StateObject = StateFinder.GetObject();
	return StateObject && IAtumEnvironmentStateFinder::Execute_FindStateIn(StateObject, this) ? StateObject : nullptr;
}

#undef LOCTEXT_NAMESPACE
