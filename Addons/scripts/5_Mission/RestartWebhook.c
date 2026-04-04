modded class MissionServer
{
	override void OnMissionStart()
	{
		super.OnMissionStart();

		ref DiscordJSON dataJSON = new DiscordJSON();

		ref DiscordObject_SettingsMessage msg = new DiscordObject_SettingsMessage();
		msg.SetField("username", "DayZ Server");

		ref DiscordObject_Embeds embeds = new DiscordObject_Embeds();
		embeds.SetField("title", "Server Started");
		embeds.SetField("description", "The server is now online and ready to play.");
		embeds.SetField("color", "3447003");
		embeds.SetField("timestamp", TimeStampNow_Discord());

		dataJSON.SetSettings(msg);
		dataJSON.SetEmbeds(embeds);

		GetDiscordHook().Send("restart", dataJSON);
	}

	override void OnMissionFinish()
	{
		ref DiscordJSON dataJSON = new DiscordJSON();

		ref DiscordObject_SettingsMessage msg = new DiscordObject_SettingsMessage();
		msg.SetField("username", "DayZ Server");

		ref DiscordObject_Embeds embeds = new DiscordObject_Embeds();
		embeds.SetField("title", "Server Shutting Down");
		embeds.SetField("description", "The server is restarting. Please wait...");
		embeds.SetField("color", "15158332");
		embeds.SetField("timestamp", TimeStampNow_Discord());

		dataJSON.SetSettings(msg);
		dataJSON.SetEmbeds(embeds);

		GetDiscordHook().Send("restart", dataJSON);

		super.OnMissionFinish();
	}
}
