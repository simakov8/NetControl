#pragma once

#include "../../../interfaces/NetManager.h"
#include <wtypes.h>

class WinNetManager : public INetManager
{
public:
	WinNetManager();

	void StartFilteringOutgoingRequests() override;
	void StopFilteringOutgoingRequests() override;

private:
	void EngineOpen();
	void AddProvider();
	void AddSublayer();
	void AddCallout();

private:
  HANDLE m_hEngine;
	GUID m_WfpProviderGuid;
	GUID m_WfpSublayerGuid;
	GUID m_WfpCalloutGuid;
};
