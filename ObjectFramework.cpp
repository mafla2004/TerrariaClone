#include "EngineBase.h"

// ==================================================================
// OBJECT
// ==================================================================

bool Object::hasTag(const string& tag)
{
	for (string t : tags)
	{
		if (t == tag)
		{
			return true;
		}
	}
	return false;
}

// ==================================================================
// ACTOR
// ==================================================================

Actor::Actor()
{
	Object::Object();

	parent = nullptr;

	
}