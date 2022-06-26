class Kamaz_Cargo_Military extends CarScript
{
	void Kamaz_Cargo_Military()
	{
		m_dmgContactCoef = 0.070;
		
		m_CarDoorOpenSound 		= "offroad_door_open_SoundSet";
		m_CarDoorCloseSound 	= "offroad_door_close_SoundSet";
	}

    override float GetActionDistanceCoolant()
	{
		return 6.0;
	}
	
	override float GetActionDistanceFuel()
	{
		return 4.0;
	}

	override float GetActionDistanceOil()
	{
		return 4.0;
	}
	
	override float GetActionDistanceBrakes()
	{
		return 4.0;
	}

	override float GetTransportCameraDistance()
	{
		return 8.0;
	}

	override int GetAnimInstance()
	{
		return VehicleAnimInstances.V3S;
	}

	override int GetSeatAnimationType( int posIdx )
	{
		switch( posIdx )
		{
		case 0:
			return DayZPlayerConstants.VEHICLESEAT_DRIVER;
		case 1:
			return DayZPlayerConstants.VEHICLESEAT_CODRIVER;
		}

		return 0;
	}
	
	override CarRearLightBase CreateRearLight()
	{
		return CarRearLightBase.Cast( ScriptedLightBase.CreateLight(KamazRearLight) );
	}
	
	override CarLightBase CreateFrontLight()
	{
		return CarLightBase.Cast( ScriptedLightBase.CreateLight(KamazFrontLight) );
	}

	override bool CanReleaseAttachment( EntityAI attachment )
	{
		super.CanReleaseAttachment( attachment );
		
		string attType = attachment.GetType();
		
		switch( attType )
		{			
			case "SparkPlug":
				if ( GetCarDoorsState("") == CarDoorState.DOORS_CLOSED || EngineIsOn() )
					return false;
			break;
			case "CarRadiator":
				if ( GetCarDoorsState("") == CarDoorState.DOORS_CLOSED || EngineIsOn() )
					return false;
			break;
			case "CarBattery": 
				if ( GetCarDoorsState("") == CarDoorState.DOORS_CLOSED || EngineIsOn() )
					return false;
			break;
		}

		return true;
	}
	
	override int GetCarDoorsState( string slotType )
	{
		CarDoor carDoor;

		Class.CastTo( carDoor, FindAttachmentBySlotName( slotType ) );
		if ( !carDoor )
			return CarDoorState.DOORS_MISSING;
	
		switch( slotType )
		{
			case "Kamaz_doors_Driver":
				if ( GetAnimationPhase("DoorsDriver") > 0.5 )
					return CarDoorState.DOORS_OPEN;
				else
					return CarDoorState.DOORS_CLOSED;

			break;
			
			case "Kamaz_Doors_coDriver":
				if ( GetAnimationPhase("DoorsCoDriver") > 0.5 )
					return CarDoorState.DOORS_OPEN;
				else
					return CarDoorState.DOORS_CLOSED;

			break;

			case "Kamaz_doors_trunk":
				if ( GetAnimationPhase("DoorsTrunk") > 0.5 )
					return CarDoorState.DOORS_OPEN;
				else
					return CarDoorState.DOORS_CLOSED;

			break;
		}

		return CarDoorState.DOORS_MISSING;
	}
	

	override bool CrewCanGetThrough( int posIdx )
	{
		switch( posIdx )
		{
			case 0:
				if ( GetCarDoorsState( "Kamaz_doors_Driver" ) == CarDoorState.DOORS_CLOSED )
					return false;

				return true;
			break;
			
			case 1:
				if ( GetCarDoorsState( "Kamaz_Doors_coDriver" ) == CarDoorState.DOORS_CLOSED )
					return false;

				return true;
			break;

			case 2:
			case 3:
				return true;
			break;

		}

		return false;
	}

	override string GetDoorSelectionNameFromSeatPos(int posIdx)
	{
		switch( posIdx )
		{
		case 0:
			return "doors_driver";
		break;
		case 1:
			return "doors_codriver";
		break;
		case 2:
		case 3:
			return "doors_trunk";
		break;
		}
		
		return super.GetDoorSelectionNameFromSeatPos(posIdx);
	}

	override string GetDoorInvSlotNameFromSeatPos(int posIdx)
	{
		switch( posIdx )
		{
		case 0:
			return "Kamaz_doors_Driver";
		break;
		case 1:
			return "Kamaz_Doors_coDriver";
		break;
		case 2:
		case 3:
			return "Kamaz_doors_trunk";
		break;
		}
		
		return super.GetDoorInvSlotNameFromSeatPos(posIdx);
	}
	
	override float OnSound( CarSoundCtrl ctrl, float oldValue )
	{
		switch ( ctrl )
		{
			case CarSoundCtrl.DOORS:
				float newValue = 0;
				
				//-----
				if ( GetCarDoorsState( "Kamaz_doors_Driver" ) == CarDoorState.DOORS_CLOSED )
					newValue += 0.25;

				//-----
				if ( GetCarDoorsState( "Kamaz_Doors_coDriver" ) == CarDoorState.DOORS_CLOSED )
					newValue += 0.25;

				//-----
				if ( GetHealthLevel( "WindowFR") == GameConstants.STATE_RUINED )
					newValue -= 0.6;

				//-----
				if ( GetHealthLevel( "WindowFL") == GameConstants.STATE_RUINED )
					newValue -= 0.6;

				//-----
				if ( GetHealthLevel( "WindowRL") == GameConstants.STATE_RUINED )
					newValue -= 0.6;

				//-----
				if ( GetHealthLevel( "WindowRR") == GameConstants.STATE_RUINED )
					newValue -= 0.6;
			
				if ( newValue > 1 )
					newValue = 1;
			
				if ( newValue < 0 )
					newValue = 0;
			
				return newValue;
			break;
		}

		return oldValue;
	}
	
	override string GetAnimSourceFromSelection( string selection )
	{
		switch( selection )
		{
		case "doors_driver":
			return "DoorsDriver";
		case "doors_codriver":
			return "DoorsCoDriver";
		case "doors_trunk":
			return "DoorsTrunk";
		}
		return "";
	}


	override bool IsVitalTruckBattery()
	{
		return false;
	}

	override bool IsVitalGlowPlug()
	{
		return false;
	}
	
	override bool CanReachSeatFromSeat( int currentSeat, int nextSeat )
	{
		switch( currentSeat )
		{
		case 0:
			if ( nextSeat == 1 )
				return true;
			break;
		}
		
		return false;
	}

	override bool CanReachDoorsFromSeat( string pDoorsSelection, int pCurrentSeat )
	{
		switch( pCurrentSeat )
		{
		case 0:
			if (pDoorsSelection == "DoorsDriver")
			{
				return true;
			}
		break;
		case 1:
			if (pDoorsSelection == "DoorsCoDriver")
			{
				return true;
			}
		break;
		case 2:
		case 3:
			if (pDoorsSelection == "DoorsTrunk")
			{
				return true;
			}
		break;
		}
	
		return false;
	}

	override string GetDoorConditionPointFromSelection( string selection )
	{
		switch( selection )
		{
			case "seat_driver":
				return "seat_con_1_1";
			break;

			case "seat_codriver":
				return "seat_con_2_1";
			break;

			case "seat_cargo1":
				return "seat_con_1_2";
			break;

			case "seat_cargo2":
				return "seat_con_2_2";
			break;
		}
		
		return "";
	}

	override void OnDebugSpawn()
	{
		EntityAI entity;
		
		if ( Class.CastTo(entity, this) )
		{
			entity.GetInventory().CreateInInventory( "Kamaz_doors_Driver_Military" );
			entity.GetInventory().CreateInInventory( "Kamaz_Doors_coDriver_Military" );
			entity.GetInventory().CreateInInventory( "Kamaz_doors_trunk_Military" );
			
			entity.GetInventory().CreateInInventory( "Kamaz_Wheel" );
			entity.GetInventory().CreateInInventory( "Kamaz_Wheel" );
			entity.GetInventory().CreateInInventory( "Kamaz_Wheel" );
			entity.GetInventory().CreateInInventory( "Kamaz_Wheel" );
			entity.GetInventory().CreateInInventory( "Kamaz_Wheel" );
			entity.GetInventory().CreateInInventory( "Kamaz_Wheel" );
			entity.GetInventory().CreateInInventory( "Kamaz_Wheel" );

			entity.GetInventory().CreateInInventory( "CarBattery" );
			entity.GetInventory().CreateInInventory( "SparkPlug" );
			entity.GetInventory().CreateInInventory( "CarRadiator" );

			entity.GetInventory().CreateInInventory( "HeadlightH7" );
			entity.GetInventory().CreateInInventory( "HeadlightH7" );
		};

		Fill( CarFluid.FUEL, 70 );
		Fill( CarFluid.COOLANT, 6.0 );
		Fill( CarFluid.OIL, 4.0 );
	}
}