#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SystemSpecsFunctionLibrary.generated.h"


UCLASS()
class HARDWARECHECK_API USystemSpecsFunctionLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintPure, Category = "System Specs")
    static FString GetCPUBrand();

    UFUNCTION(BlueprintPure, Category = "System Specs")
    static int32 GetPhysicalCoreCount();

    UFUNCTION(BlueprintPure, Category = "System Specs")
    static int32 GetLogicalCoreCount();

    UFUNCTION(BlueprintPure, Category = "System Specs")
    static FString GetGPUBrand();

    UFUNCTION(BlueprintPure, Category = "System Specs")
    static FString GetGPUVendorName();

    UFUNCTION(BlueprintPure, Category = "System Specs")
    static FString GetGPUDescription();

    UFUNCTION(BlueprintPure, Category = "System Specs")
    static FString GetOSVersion();

    UFUNCTION(BlueprintPure, Category = "System Specs")
    static FString GetGPUDriverVersion();

    UFUNCTION(BlueprintPure, Category = "System Specs")
    static FString GetRHIName();

    UFUNCTION(BlueprintPure, Category = "System Specs")  // C:/ i path för C drive
    static void GetDiskSpaceInfo(const FString& FolderPath, int64& TotalSpaceMB, int64& FreeSpaceMB);

    UFUNCTION(BlueprintPure, Category = "System Specs")
    static int32 GetTotalRandomAccessMemoryMB();
    
    UFUNCTION(BlueprintPure, Category = "System Specs")
    static int64 GetDedicatedVideoMemoryMB();


    UFUNCTION(BlueprintPure, Category = "System Specs")
    static bool IsRunningOnBattery();

    UFUNCTION(BlueprintPure, Category = "System Specs")
    static bool HasBattery();
};
