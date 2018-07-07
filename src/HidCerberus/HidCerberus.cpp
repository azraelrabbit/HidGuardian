#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "HidCerberus.h"
#include "ZerberusService.h"
#include "HidCerberusInternal.h"


HC_API PHC_HANDLE hc_init()
{
    auto handle = (PHC_HANDLE)malloc(sizeof(HC_HANDLE));

    if (!handle) {
        return nullptr;
    }

    handle->MainManager = new TaskManager();

    handle->MainManager->start(new ZerberusService("ZerberusService", handle));

    return handle;
}

HC_API VOID hc_shutdown(PHC_HANDLE handle)
{
    if (!handle) {
        return;
    }

    handle->MainManager->cancelAll();
    handle->MainManager->joinAll();

    free(handle);
}

HC_API VOID hc_register_access_request_event(PHC_HANDLE handle, PFN_HC_PROCESS_ACCESS_REQUEST callback)
{
    handle->EvtProcessAccessRequest = callback;
}