class CfgPatches
{
	class DiscordWebhooks
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};

class CfgMods
{
	class DiscordWebhooks
	{
		dir = "DiscordWebhooks";
		picture = "";
		action = "";
		hideName = 0;
		hidePicture = 1;
		name = "DiscordWebhooks";
		credits = "76561198727370586";
		author = "danvahsh";
		authorID = "76561198727370586";
		version = "1.0";
		extra = 0;
		type = "mod";

		dependencies[] = {"Game", "World", "Mission"};

		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"DiscordWebhooks/scripts/3_Game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"DiscordWebhooks/scripts/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"DiscordWebhooks/scripts/5_Mission"};
			};
		};
	};
};