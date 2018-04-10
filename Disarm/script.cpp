#include "script.h"

#define BONE_RIGHT_HAND     0xDEAD
#define BONE_RIGHT_FOREARM	0x6E5C

Player player;
Ped playerPed;

void update()
{
	player = PLAYER::PLAYER_ID();
	playerPed = PLAYER::PLAYER_PED_ID();

	if (!ENTITY::DOES_ENTITY_EXIST(playerPed) || !PLAYER::IS_PLAYER_CONTROL_ON(player))
		return;

	if (ENTITY::IS_ENTITY_DEAD(playerPed) || PLAYER::IS_PLAYER_BEING_ARRESTED(player, TRUE))
		return;

	Ped peds[2048];
	int nPeds = worldGetAllPeds(peds, 2048);
	for (int i = 0; i < nPeds; i++) {
        if (peds[i] == playerPed) 
            continue;
		Weapon weapon = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(peds[i]);
		if (weapon) {
            int bone;
            PED::GET_PED_LAST_DAMAGE_BONE(peds[i], &bone);
		    if (bone == BONE_RIGHT_HAND || bone == BONE_RIGHT_FOREARM) {
				WEAPON::SET_PED_DROPS_WEAPON(peds[i]);
				PED::CLEAR_PED_LAST_DAMAGE_BONE(peds[i]);
			}
            else {
                PED::CLEAR_PED_LAST_DAMAGE_BONE(peds[i]);
            }
            if (ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ANY_PED(weapon)) {
                WEAPON::SET_PED_DROPS_WEAPON(peds[i]);
                ENTITY::CLEAR_ENTITY_LAST_DAMAGE_ENTITY(weapon);
            }
            else {
                ENTITY::CLEAR_ENTITY_LAST_DAMAGE_ENTITY(weapon);
            }
		}
	}
}

void main()
{
	while (true)
	{
		update();
		WAIT(0);
	}
}

void ScriptMain()
{
	srand(GetTickCount());
	main();
}
