// @jung june

#pragma once

#include "SC.h"

#include <GameFramework/CheatManager.h>

#include "SCCheatManager.generated.h"

struct FAutoCompleteCommand;
struct FSCCheatData
{
	FString Command;
	FString Desc;
	FColor Color;
	FString FunctionName;
};
/**
 * 
 */
UCLASS()
class SC_API USCCheatManager : public UCheatManager
{
	GENERATED_BODY()

public:
	virtual void InitCheatManager() override;
	virtual bool ProcessConsoleExec(const TCHAR* Cmd, FOutputDevice& Ar, UObject* Executor) override;
	virtual void BeginDestroy() override;
	void RegisterAutoCompleteEntries(TArray<FAutoCompleteCommand>& Commands);

private:
	inline static FString Prefix = "SP.";
	inline static FColor CommandColor = FColor::Green;

	TArray<FSCCheatData> Commands;

	void ParseCommands();

public:
	UFUNCTION(Exec, meta = (Cheat = "test", Desc = "this is reflection"))
	void CheatTestFunction(FString Argument);
	
};
