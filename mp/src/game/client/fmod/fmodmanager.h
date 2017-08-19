#ifndef FMODMANAGER_H
#define FMODMANAGER_H

#include <fmod.hpp>

#include "igamesystem.h"

// Channel group types
enum eChannelGroupType
{
	CHANNELGROUP_STANDARD = 0,
	CHANNELGROUP_MUSIC,
	NUM_CHANNELGROUPS
};

static const char *g_pChannelGroupNames[NUM_CHANNELGROUPS] =
{
	"STANDARD",
	"MUSIC"
};

class CFMODManager : public CAutoGameSystemPerFrame
{
public:
	CFMODManager();

	// Initilaztion and Shutdown functions
	virtual bool Init();
	virtual void Shutdown();

	// Called on Level Init before entities are created
	virtual void LevelInitPreEntity();

	// Called on Level Shutdown before entities are released
	virtual void LevelShutdownPreEntity();

	// Per frame update function
	virtual void Update( float frametime );

	// Get the full path to a sound relative to the mod folder
	const char *GetFullPathToSound( const char *pszSoundPath );

	// Get one of our channel groups
	FMOD::ChannelGroup *GetChannelGroup( eChannelGroupType channelgroupType ) { return m_pChannelGroups[channelgroupType]; }

	// Used to check for errors when using FMOD
	static FMOD_RESULT CheckError( FMOD_RESULT result );

	FMOD::System *GetSystem() { return m_pSystem; }

private:
	// This is our FMOD system, the core of everything FMOD related
	FMOD::System *m_pSystem;

	// These are our channel groups, used for managing channel volumes
	FMOD::ChannelGroup *m_pChannelGroups[NUM_CHANNELGROUPS];

	// This points to the master channel group which all other channel groups are a part of
	FMOD::ChannelGroup *m_pMasterChannelGroup;
};

CFMODManager *GetFMODManager();

#endif // FMODMANAGER_H