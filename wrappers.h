#ifndef _INCLUDE_WRAPPERS_H_
#define _INCLUDE_WRAPPERS_H_

#include "smsdk_ext.h"
#include <extensions/IBinTools.h>

// iclientrenderable.h (included in toolframework/itoolentity.h) has explicit NULL-dereference in CDefaultClientRenderable::GetRefEHandle
// Don't need to add compiler option -Wnull-dereference if can just ignore this file alone
#define ICLIENTRENDERABLE_H
class IClientRenderable;
typedef unsigned short ClientShadowHandle_t;
#include <toolframework/itoolentity.h>

extern IServerGameEnts* gameents;

class CBaseEntity :
	public IServerEntity
{
public:
	static int vtblindex_ShouldCollide;

	edict_t* edict()
	{
		return gameents->BaseEntityToEdict(this);
	}
};

class CEnv_Blocker :
	public CBaseEntity
{
public:
	static int shookid_ShouldCollide;
};

class CEnvPhysicsBlocker :
	public CBaseEntity
{
public:
	static int shookid_ShouldCollide;
};

class CBasePlayer :
	public CBaseEntity
{
public:
	static int sendprop_m_fFlags;

	static int vtblindex_PlayerSolidMask;

	static ICallWrapper* vcall_PlayerSolidMask;

	int GetFlags()
	{
		return *(int*)((byte*)(this) + CBasePlayer::sendprop_m_fFlags);
	}

	bool IsBot()
	{
		return (GetFlags() & FL_FAKECLIENT) != 0;
	}

	unsigned int PlayerSolidMask(bool brushOnly)
	{
		struct {
			CBasePlayer* pPlayer;
			int brushOnly;
		} stack{ this, brushOnly };

		unsigned int ret;
		vcall_PlayerSolidMask->Execute(&stack, &ret);

		return ret;
	}
};

class CTerrorPlayer :
	public CBasePlayer
{
public:
	static int sendprop_m_carryVictim;
	static int sendprop_m_jockeyAttacker;

	CTerrorPlayer* GetCarryVictim()
	{
		edict_t* pEdict = gamehelpers->GetHandleEntity(*(CBaseHandle*)((byte*)(this) + CTerrorPlayer::sendprop_m_carryVictim));
		if (pEdict == NULL) {
			return NULL;
		}

		// Make sure it's a player
		if (engine->GetPlayerUserId(pEdict) == -1) {
			return NULL;
		}

		return (CTerrorPlayer*)gameents->EdictToBaseEntity(pEdict);
	}

	CTerrorPlayer* GetJockeyAttacker()
	{
		edict_t* pEdict = gamehelpers->GetHandleEntity(*(CBaseHandle*)((byte*)(this) + CTerrorPlayer::sendprop_m_jockeyAttacker));
		if (pEdict == NULL) {
			return NULL;
		}

		// Make sure it's a player
		if (engine->GetPlayerUserId(pEdict) == -1) {
			return NULL;
		}

		return (CTerrorPlayer*)gameents->EdictToBaseEntity(pEdict);
	}
};

CBasePlayer* UTIL_PlayerByIndex(int playerIndex)
{
	if (playerIndex > 0 && playerIndex <= playerhelpers->GetMaxClients()) {
		IGamePlayer* pPlayer = playerhelpers->GetGamePlayer(playerIndex);
		if (pPlayer != NULL) {
			return (CBasePlayer*)gameents->EdictToBaseEntity(pPlayer->GetEdict());
		}
	}

	return NULL;
}

class CGameMovement
{
public:
	static int vtblindex_PlayerSolidMask;
	static int shookid_PlayerSolidMask;

	virtual unsigned int PlayerSolidMask(bool brushOnly = false, CBasePlayer* testPlayer = NULL) const;	///< returns the solid mask for the given player, so bots can have a more-restrictive set
	CBasePlayer* player;
};

#define INTERFACENAME_GAMEMOVEMENT	"GameMovement001"

#endif // _INCLUDE_WRAPPERS_H_
