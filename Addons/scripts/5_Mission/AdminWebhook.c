class DiscordAdminLog
{
	static void Send(string adminName, string action, string details = "")
	{
		ref DiscordJSON dataJSON = new DiscordJSON();

		ref DiscordObject_SettingsMessage msg = new DiscordObject_SettingsMessage();
		msg.SetField("username", "DayZ Admin Log");

		ref DiscordObject_Embeds embeds = new DiscordObject_Embeds();
		embeds.SetField("title", "Admin Action");
		embeds.SetField("color", "15844367");
		embeds.SetField("timestamp", TimeStampNow_Discord());
		embeds.SetEmbedField("Admin", adminName, true);
		embeds.SetEmbedField("Action", action, true);

		if (details != "")
			embeds.SetEmbedField("Details", details, false);

		dataJSON.SetSettings(msg);
		dataJSON.SetEmbeds(embeds);

		GetDiscordHook().Send("admin", dataJSON);
	}
}
