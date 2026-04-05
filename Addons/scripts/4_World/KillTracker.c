class KillTracker
{
	void PostEvent(string killerName, string killerId, string victimName, string victimId, string cause)
	{
		string botUrl = GetDiscordManagerConfig().DataCfg.BotURL_KillTracker;
		if (botUrl == "") return;

		string apiKey = GetDiscordManagerConfig().DataCfg.BotAPIKey;

		killerName.Replace("\"", "\\\"");
		victimName.Replace("\"", "\\\"");

		string json = "{";
		json += "\"apiKey\":\"" + apiKey + "\",";
		json += "\"killerName\":\"" + killerName + "\",";
		json += "\"killerId\":\"" + killerId + "\",";
		json += "\"victimName\":\"" + victimName + "\",";
		json += "\"victimId\":\"" + victimId + "\",";
		json += "\"cause\":\"" + cause + "\"";
		json += "}";

		RestCallback cbx = new DiscordCallBack;
		RestApi clCore = GetRestApi();
		if (!clCore) clCore = CreateRestApi();

		RestContext ctx = clCore.GetRestContext(botUrl);
		ctx.SetHeader("application/json");
		ctx.POST(cbx, "", json);
	}
}

static ref KillTracker g_KillTracker;
static ref KillTracker GetKillTracker()
{
	if (!g_KillTracker) g_KillTracker = new KillTracker();
	return g_KillTracker;
}
