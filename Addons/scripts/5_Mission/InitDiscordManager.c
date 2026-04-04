modded class MissionServer
{
	override void OnInit()
	{
		super.OnInit();
		GetDiscordManagerConfig();
		GetDiscordHook();

		ref JSON_CFG_D_MANAGER cfg = GetDiscordManagerConfig().DataCfg;

		if (cfg.WebHookURL_JoinLeave != "")
			GetDiscordHook().SetAlias("joinleave", cfg.WebHookURL_JoinLeave);

		if (cfg.WebHookURL_KillFeed != "")
			GetDiscordHook().SetAlias("killfeed", cfg.WebHookURL_KillFeed);

		if (cfg.WebHookURL_Admin != "")
			GetDiscordHook().SetAlias("admin", cfg.WebHookURL_Admin);

		if (cfg.WebHookURL_Restart != "")
			GetDiscordHook().SetAlias("restart", cfg.WebHookURL_Restart);
	}
}