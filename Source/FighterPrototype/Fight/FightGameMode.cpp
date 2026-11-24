#include "FightGameMode.h"
#include "FighterCharacter.h"

AFightGameMode::AFightGameMode()
{
	DefaultPawnClass = AFighterCharacter::StaticClass();
}
