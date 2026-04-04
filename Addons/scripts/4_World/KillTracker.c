class KillEntry
{
	string m_Name;
	string m_SteamId;
	int m_Kills;
	int m_Deaths;

	void KillEntry(string name, string steamId)
	{
		m_Name = name;
		m_SteamId = steamId;
		m_Kills = 0;
		m_Deaths = 0;
	}
}

class KillTracker
{
	protected ref map<string, ref KillEntry> m_Players;
	protected string m_FilePath = "$profile:DiscordWebhookManager/leaderboard.json";

	void KillTracker()
	{
		m_Players = new map<string, ref KillEntry>;
		Save();
	}

	void RecordKill(string killerName, string killerId)
	{
		if (killerId == "") return;

		if (!m_Players.Contains(killerId))
			m_Players.Set(killerId, new KillEntry(killerName, killerId));

		ref KillEntry entry = m_Players.Get(killerId);
		entry.m_Name = killerName;
		entry.m_Kills++;
		Save();
	}

	void RecordDeath(string victimName, string victimId)
	{
		if (victimId == "") return;

		if (!m_Players.Contains(victimId))
			m_Players.Set(victimId, new KillEntry(victimName, victimId));

		ref KillEntry entry = m_Players.Get(victimId);
		entry.m_Name = victimName;
		entry.m_Deaths++;
		Save();
	}

	protected void Save()
	{
		FileHandle fh = OpenFile(m_FilePath, FileMode.WRITE);
		if (!fh) return;

		array<string> keys = m_Players.GetKeyArray();

		FPrintln(fh, "{");
		FPrintln(fh, "  \"players\": [");

		for (int i = 0; i < keys.Count(); i++)
		{
			ref KillEntry e = m_Players.Get(keys[i]);
			string comma = (i < keys.Count() - 1) ? "," : "";
			string safeName = e.m_Name;
			safeName.Replace("\"", "\\\"");

			FPrintln(fh, "    {");
			FPrintln(fh, "      \"name\": \"" + safeName + "\",");
			FPrintln(fh, "      \"steamId\": \"" + e.m_SteamId + "\",");
			FPrintln(fh, "      \"kills\": " + e.m_Kills + ",");
			FPrintln(fh, "      \"deaths\": " + e.m_Deaths);
			FPrintln(fh, "    }" + comma);
		}

		FPrintln(fh, "  ],");
		FPrintln(fh, "  \"lastUpdated\": \"" + TimeStampNow_Discord() + "\"");
		FPrintln(fh, "}");

		CloseFile(fh);
	}
}

static ref KillTracker g_KillTracker;
static ref KillTracker GetKillTracker()
{
	if (!g_KillTracker) g_KillTracker = new KillTracker();
	return g_KillTracker;
}
