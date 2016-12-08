#ifndef NCINPUTMANAGER_H
#define NCINPUTMANAGER_H

#include <Arduino.h>
#include "NCPadState.h"

class NCInputManager
{
public:
	static NCInputManager& Get()
	{
		static NCInputManager Instance;
		return Instance;
	}

	void Update();

	NCPadState& GetPadState() { return PadState; };

protected:
	NCInputManager() {};
	NCInputManager(const NCInputManager&);
	NCInputManager& operator=(const NCInputManager&);
	~NCInputManager() {};

private:
	NCPadState PadState;
};

#endif // NCINPUTMANAGER_H
