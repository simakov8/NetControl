#include <exception>
#include <iostream>

#include <initguid.h>
#include <fwpmtypes.h>
#include <fwpmu.h>

#include "../../../include/core/Windows/WinNetManager.h"

#pragma comment(lib, "Fwpuclnt.lib")


WinNetManager::WinNetManager()
{
  EngineOpen();
  AddProvider();
  AddSublayer();
  AddCallout();
}

void WinNetManager::StartFilteringOutgoingRequests()
{

}

void WinNetManager::StopFilteringOutgoingRequests()
{

}

void WinNetManager::EngineOpen()
{
  FWPM_SESSION0   Session;

  RtlZeroMemory(&Session, sizeof(Session));

  Session.displayData.name = L"Net Manager session";
  Session.displayData.description = L"Net Manager session";

  DWORD status = FwpmEngineOpen0(
    NULL,
    RPC_C_AUTHN_DEFAULT,
    NULL,
    &Session,
    &m_hEngine
  );

  if (ERROR_SUCCESS != status)
    std::cerr << "FwpmEngineOpen0 failed with status: " << status << std::endl;
}

void WinNetManager::AddProvider()
{
	FWPM_PROVIDER0 Provider;

	RtlZeroMemory(&Provider, sizeof (Provider));
	 
  if (CoCreateGuid(&m_WfpProviderGuid) != S_OK)
    std::cerr << "CoCreateGuid failed" << std::endl;

	Provider.providerKey             = m_WfpProviderGuid;
	Provider.displayData.name        = L"Net Manager provider";
	Provider.displayData.description = L"Net Manager provider";
	Provider.flags                   = FWPM_PROVIDER_FLAG_PERSISTENT;
	 
	DWORD status = FwpmProviderAdd0(m_hEngine, &Provider, NULL);
	 
	if (ERROR_SUCCESS != status)
    std::cerr << "FwpmProviderAdd0 failed with status: " << status << std::endl;
}

void WinNetManager::AddSublayer()
{
  FWPM_SUBLAYER0 Sublayer;
  RtlZeroMemory(&Sublayer, sizeof(Sublayer));

  if (CoCreateGuid(&m_WfpSublayerGuid) != S_OK)
    std::cerr << "CoCreateGuid failed" << std::endl;
  Sublayer.subLayerKey = m_WfpSublayerGuid;

  Sublayer.displayData.name = L"Net Manager sublayer";
  Sublayer.displayData.description = L"Net Manager sublayer";
  Sublayer.flags = FWPM_SUBLAYER_FLAG_PERSISTENT;
  Sublayer.providerKey = &m_WfpProviderGuid;
  Sublayer.weight = 0x1;

  DWORD status = FwpmSubLayerAdd0(m_hEngine, &Sublayer, NULL);

	if (ERROR_SUCCESS != status)
    std::cerr << "FwpmSublayerAdd0 failed with status: " << status << std::endl;
}

void WinNetManager::AddCallout()
{
  FWPM_CALLOUT0 Callout;
  RtlZeroMemory(&Callout, sizeof(Callout));

  if (CoCreateGuid(&m_WfpCalloutGuid) != S_OK)
    std::cerr << "CoCreateGuid failed" << std::endl;
  Callout.calloutKey = m_WfpCalloutGuid;

  Callout.displayData.name = L"Net Manager sublayer";
  Callout.displayData.description = L"Net Manager sublayer";
  Callout.flags = FWPM_CALLOUT_FLAG_PERSISTENT;
  Callout.providerKey = &m_WfpProviderGuid;
  Callout.applicableLayer = FWPM_LAYER_ALE_AUTH_CONNECT_V4;

  UINT32 CalloutId;
  DWORD status = FwpmCalloutAdd0(m_hEngine, &Callout, NULL, &CalloutId);

	if (ERROR_SUCCESS != status)
    std::cerr << "FwpmCalloutAdd0 failed with status: " << status << std::endl;
}
