#include "SystemSpecsFunctionLibrary.h"
#include "HAL/PlatformMisc.h"
#include "HAL/PlatformMemory.h"
#include "HAL/PlatformProcess.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "Misc/Paths.h"
#include "Misc/OutputDeviceNull.h"
#include "RHI.h"
#if PLATFORM_WINDOWS
#include "Windows/AllowWindowsPlatformTypes.h"
#include <dxgi.h>
#include "Windows/HideWindowsPlatformTypes.h"
#endif

#define VENDOR_ID_NVIDIA 0x10DE
#define VENDOR_ID_AMD    0x1002
#define VENDOR_ID_INTEL  0x8086

FString USystemSpecsFunctionLibrary::GetCPUBrand()
{
    return FPlatformMisc::GetCPUBrand();
}

int32 USystemSpecsFunctionLibrary::GetPhysicalCoreCount()
{
    return FPlatformMisc::NumberOfCores();
}

int32 USystemSpecsFunctionLibrary::GetLogicalCoreCount()
{
    return FPlatformMisc::NumberOfCoresIncludingHyperthreads();
}

FString USystemSpecsFunctionLibrary::GetGPUBrand()
{
    return FPlatformMisc::GetPrimaryGPUBrand();
}

void USystemSpecsFunctionLibrary::GetDiskSpaceInfo(const FString& FolderPath, int64& TotalSpaceMB, int64& FreeSpaceMB)
{
    uint64 TotalSpaceBytes = 0;
    uint64 FreeSpaceBytes = 0;

    if (FPlatformMisc::GetDiskTotalAndFreeSpace(FolderPath, TotalSpaceBytes, FreeSpaceBytes))
    {
        TotalSpaceMB = static_cast<int64>(TotalSpaceBytes / (1024 * 1024));
        FreeSpaceMB = static_cast<int64>(FreeSpaceBytes / (1024 * 1024));
    }
    else
    {
        TotalSpaceMB = -1;
        FreeSpaceMB = -1;
    }
}


int32 USystemSpecsFunctionLibrary::GetTotalRandomAccessMemoryMB()
{
    return FPlatformMemory::GetConstants().TotalPhysical / (1024 * 1024);
}


FString USystemSpecsFunctionLibrary::GetOSVersion()
{
    return FPlatformMisc::GetOSVersion();
}

FString USystemSpecsFunctionLibrary::GetGPUDriverVersion()
{
    return GRHIAdapterInternalDriverVersion;
}

FString USystemSpecsFunctionLibrary::GetRHIName()
{
    return GDynamicRHI ? GDynamicRHI->GetName() : TEXT("Unknown");
}

int64 USystemSpecsFunctionLibrary::GetDedicatedVideoMemoryMB()
{
#if PLATFORM_WINDOWS
    IDXGIFactory* DXGIFactory = nullptr;
    if (SUCCEEDED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&DXGIFactory)))
    {
        IDXGIAdapter* Adapter = nullptr;
        if (SUCCEEDED(DXGIFactory->EnumAdapters(0, &Adapter)))
        {
            DXGI_ADAPTER_DESC Desc;
            if (SUCCEEDED(Adapter->GetDesc(&Desc)))
            {
                Adapter->Release();
                DXGIFactory->Release();
                return static_cast<int64>(Desc.DedicatedVideoMemory) / (1024 * 1024);
            }
            Adapter->Release();
        }
        DXGIFactory->Release();
    }
#endif
    return -1;

}

FString USystemSpecsFunctionLibrary::GetGPUDescription()
{
#if PLATFORM_WINDOWS
    IDXGIFactory* DXGIFactory = nullptr;
    if (SUCCEEDED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&DXGIFactory)))
    {
        IDXGIAdapter* Adapter = nullptr;
        if (SUCCEEDED(DXGIFactory->EnumAdapters(0, &Adapter)))
        {
            DXGI_ADAPTER_DESC Desc;
            if (SUCCEEDED(Adapter->GetDesc(&Desc)))
            {
                Adapter->Release();
                DXGIFactory->Release();

                return FString(Desc.Description); // full model name
            }
            Adapter->Release();
        }
        DXGIFactory->Release();
    }
#endif

    return TEXT("Unavailable");
}

FString USystemSpecsFunctionLibrary::GetGPUVendorName()
{
#if PLATFORM_WINDOWS
    IDXGIFactory* DXGIFactory = nullptr;
    if (SUCCEEDED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&DXGIFactory)))
    {
        IDXGIAdapter* Adapter = nullptr;
        if (SUCCEEDED(DXGIFactory->EnumAdapters(0, &Adapter)))
        {
            DXGI_ADAPTER_DESC Desc;
            if (SUCCEEDED(Adapter->GetDesc(&Desc)))
            {
                Adapter->Release();
                DXGIFactory->Release();

                switch (Desc.VendorId)
                {
                case 0x10DE: return TEXT("NVIDIA");
                case 0x1002: return TEXT("AMD");
                case 0x8086: return TEXT("Intel");
                default:     return TEXT("Unknown");
                }
            }
            Adapter->Release();
        }
        DXGIFactory->Release();
    }
#endif

    return TEXT("Unavailable");
}

bool USystemSpecsFunctionLibrary::IsRunningOnBattery()
{
    return FPlatformMisc::IsRunningOnBattery();
}

#if PLATFORM_WINDOWS
bool USystemSpecsFunctionLibrary::HasBattery()
{
    SYSTEM_POWER_STATUS status;
    if (GetSystemPowerStatus(&status))
    {
        return !(status.BatteryFlag == 128); // 128 = no system battery
    }
    return false;
}
#endif