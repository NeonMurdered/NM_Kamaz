modded class PlayerBase extends ManBase
{
	override void Init()
    {
        if ( !GetGame().IsServer() || !GetGame().IsMultiplayer() ) 
		{
			DayzPlayerItemBehaviorCfg heavyItemBehaviour = new DayzPlayerItemBehaviorCfg;
			heavyItemBehaviour.SetHeavyItems();

			GetDayZPlayerType().AddItemInHandsProfileIK("Kamaz_Wheel", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", heavyItemBehaviour,					        "dz/anims/anm/player/ik/vehicles/hatchback_02/Hatchback_02_wheel.anm");
			GetDayZPlayerType().AddItemInHandsProfileIK("Kamaz_Wheel_destroyed", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", heavyItemBehaviour,				"dz/anims/anm/player/ik/vehicles/hatchback_02/Hatchback_02_wheel.anm");
			GetDayZPlayerType().AddItemInHandsProfileIK("Kamaz_doors_Driver_Military", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", heavyItemBehaviour,			"dz/anims/anm/player/ik/vehicles/hatchback_02/Hatchback_02_Door_driver.anm");
			GetDayZPlayerType().AddItemInHandsProfileIK("Kamaz_Doors_coDriver_Military", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", heavyItemBehaviour,		"dz/anims/anm/player/ik/vehicles/hatchback_02/Hatchback_02_Door_driver.anm");
			GetDayZPlayerType().AddItemInHandsProfileIK("Kamaz_doors_trunk_Military", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", heavyItemBehaviour,			"dz/anims/anm/player/ik/vehicles/hatchback_02/Hatchback_02_Door_driver.anm");
		}
        super.Init();
    }
}
