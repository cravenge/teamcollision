#ifndef _INCLUDE_SOURCEMOD_EXTENSION_CONFIG_H_
#define _INCLUDE_SOURCEMOD_EXTENSION_CONFIG_H_

#define SMEXT_CONF_NAME			"[L4D2] Team Collision"
#define SMEXT_CONF_DESCRIPTION	"Improves collision rules between players of different teams"
#define SMEXT_CONF_VERSION		"1.5"
#define SMEXT_CONF_AUTHOR		"Evgeniy \"shqke\" Kazakov"
#define SMEXT_CONF_URL			"https://github.com/shqke/teamcollision"
#define SMEXT_CONF_LOGTAG		"teamcollision"
#define SMEXT_CONF_LICENSE		"GPL"
#define SMEXT_CONF_DATESTRING	__DATE__

#define GAMEDATA_FILE			"teamcollision"

#define SMEXT_LINK(name) SDKExtension *g_pExtensionIface = name;

#define SMEXT_CONF_METAMOD
#define SMEXT_ENABLE_GAMEHELPERS
#define SMEXT_ENABLE_GAMECONF
#define SMEXT_ENABLE_PLAYERHELPERS

#endif // _INCLUDE_SOURCEMOD_EXTENSION_CONFIG_H_
