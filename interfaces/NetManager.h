#pragma once

class INetManager
{
public:
	~INetManager() = default;

	virtual void StartFilteringOutgoingRequests() = 0;
	virtual void StopFilteringOutgoingRequests() = 0;
};
