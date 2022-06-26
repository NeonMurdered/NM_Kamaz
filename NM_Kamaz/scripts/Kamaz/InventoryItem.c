class Kamaz_Wheel extends CarWheel
{
	override void EEKilled(Object killer)
	{
		string newWheel = "";
		switch( GetType() )
		{
			case "Kamaz_Wheel":
				newWheel = "Kamaz_Wheel_destroyed";
			break;
		}
		if ( newWheel != "" )
		{
			ReplaceWheelLambda lambda = new ReplaceWheelLambda ( this, newWheel, NULL);
			lambda.SetTransferParams(true, true, true);
			GetInventory().ReplaceItemWithNew(InventoryMode.SERVER, lambda);
		}
	}

	override int GetMeleeTargetType()
	{
		return EMeleeTargetType.NONALIGNABLE;
	}
	
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionDetach);
		AddAction(ActionAttachOnSelection);
	}
}

class Kamaz_Wheel_destroyed extends ItemBase {};

class Kamaz_doors_Driver_Military extends CarDoor {};
class Kamaz_Doors_coDriver_Military extends CarDoor {};
class Kamaz_doors_trunk_Military extends CarDoor {};