modded class MissionServer
{
	override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
	{
		super.InvokeOnConnect(player, identity);

		if (!identity) return;

		string playerName = identity.GetName();
		string playerId = identity.GetPlainId();

		ref DiscordJSON dataJSON = new DiscordJSON();

		ref DiscordObject_SettingsMessage msg = new DiscordObject_SettingsMessage();
		msg.SetField("username", "DayZ Server");

		ref DiscordObject_Embeds embeds = new DiscordObject_Embeds();
		embeds.SetField("title", "Player Joined");
		embeds.SetField("color", "3066993");
		embeds.SetField("timestamp", TimeStampNow_Discord());
		embeds.SetEmbedField("Player", playerName, true);
		embeds.SetEmbedField("Steam64", playerId, true);

		dataJSON.SetSettings(msg);
		dataJSON.SetEmbeds(embeds);

		GetDiscordHook().Send("joinleave", dataJSON);
	}

	override void InvokeOnDisconnect(PlayerBase player)
	{
		if (player)
		{
			PlayerIdentity identity = player.GetIdentity();
			if (identity)
			{
				string playerName = identity.GetName();
				string playerId = identity.GetPlainId();

				ref DiscordJSON dataJSON = new DiscordJSON();

				ref DiscordObject_SettingsMessage msg = new DiscordObject_SettingsMessage();
				msg.SetField("username", "DayZ Server");

				ref DiscordObject_Embeds embeds = new DiscordObject_Embeds();
				embeds.SetField("title", "Player Left");
				embeds.SetField("color", "15158332");
				embeds.SetField("timestamp", TimeStampNow_Discord());
				embeds.SetEmbedField("Player", playerName, true);
				embeds.SetEmbedField("Steam64", playerId, true);

				dataJSON.SetSettings(msg);
				dataJSON.SetEmbeds(embeds);

				GetDiscordHook().Send("joinleave", dataJSON);
			}
		}

		super.InvokeOnDisconnect(player);
	}
}
