modded class PlayerBase
{
	override void EEKilled(Object killer)
	{
		super.EEKilled(killer);

		if (!GetGame().IsServer()) return;

		PlayerIdentity victimIdentity = GetIdentity();
		if (!victimIdentity) return;

		string victimName = victimIdentity.GetName();
		string killerName;
		string causeOfDeath;
		string weaponName = "";
		string distance = "";
		string embedColor;

		PlayerBase killerPlayer;
		if (killer && killer.IsMan() && Class.CastTo(killerPlayer, killer))
		{
			if (killerPlayer == this)
			{
				causeOfDeath = "Suicide";
				killerName = victimName;
				embedColor = "9807270";
			}
			else
			{
				PlayerIdentity killerIdentity = killerPlayer.GetIdentity();
				if (killerIdentity)
					killerName = killerIdentity.GetName();
				else
					killerName = "Unknown Player";

				causeOfDeath = "PvP Kill";

				EntityAI weapon = killerPlayer.GetItemInHands();
				if (weapon)
				{
					weaponName = weapon.GetDisplayName();
					if (weaponName == "")
						weaponName = weapon.GetType();
				}
				else
				{
					weaponName = "Fists";
				}

				int dist = vector.Distance(GetPosition(), killerPlayer.GetPosition());
				distance = dist.ToString() + "m";

				embedColor = "15158332";
			}
		}
		else if (killer && killer.IsKindOf("DayZInfected"))
		{
			causeOfDeath = "Killed by Infected";
			killerName = "Zombie";
			embedColor = "2067276";
		}
		else if (killer && killer.IsKindOf("AnimalBase"))
		{
			causeOfDeath = "Killed by Animal";
			killerName = killer.GetType();
			embedColor = "11027200";
		}
		else
		{
			causeOfDeath = "Environment / Unknown";
			killerName = "N/A";
			embedColor = "9807270";
		}

		ref DiscordJSON dataJSON = new DiscordJSON();

		ref DiscordObject_SettingsMessage msg = new DiscordObject_SettingsMessage();
		msg.SetField("username", "DayZ Kill Feed");

		ref DiscordObject_Embeds embeds = new DiscordObject_Embeds();
		embeds.SetField("title", causeOfDeath);
		embeds.SetField("color", embedColor);
		embeds.SetField("timestamp", TimeStampNow_Discord());
		embeds.SetEmbedField("Victim", victimName, true);
		embeds.SetEmbedField("Killer", killerName, true);

		if (weaponName != "")
			embeds.SetEmbedField("Weapon", weaponName, true);

		if (distance != "")
			embeds.SetEmbedField("Distance", distance, true);

		dataJSON.SetSettings(msg);
		dataJSON.SetEmbeds(embeds);

		GetDiscordHook().Send("killfeed", dataJSON);
	}
}
