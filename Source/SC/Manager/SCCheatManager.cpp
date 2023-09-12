// @jung june


#include "SCCheatManager.h"

#include <Engine/Console.h>
#include <AssetRegistry/AssetRegistryModule.h>

void USCCheatManager::InitCheatManager()
{
	ParseCommands();
	UConsole::RegisterConsoleAutoCompleteEntries.AddUObject(this, &USCCheatManager::RegisterAutoCompleteEntries);
}



bool USCCheatManager::ProcessConsoleExec(const TCHAR* Cmd, FOutputDevice& Ar, UObject* Executor)
{
	bool bForceExecute = false;
	FString Source = Cmd;
	FString Key;
	if (FParse::Token(Cmd, Key, true))
	{
		auto* FindItem = Commands.FindByPredicate([Key](const FSCCheatData& Item)
			{
				return Item.Command == Key;
			});

		if (FindItem != nullptr)
		{
			bForceExecute = true;
			Source = FindItem->FunctionName + Cmd;
		}
	}

	return CallFunctionByNameWithArguments(*Source, Ar, Executor, bForceExecute);
}

void USCCheatManager::BeginDestroy()
{
	Super::BeginDestroy();
	UConsole::RegisterConsoleAutoCompleteEntries.RemoveAll(this);
}

void USCCheatManager::RegisterAutoCompleteEntries(TArray<FAutoCompleteCommand>& AutoCompleteList)
{
	for (const auto& Item : Commands)
	{
		FAutoCompleteCommand Entry;
		Entry.Command = Item.Command;
		Entry.Desc = Item.Desc;
		Entry.Color = Item.Color;
		AutoCompleteList.Emplace(Entry);
	}
}

void USCCheatManager::ParseCommands()
{
	const UClass* CurrentClass = GetClass();

	TArray<FName> FunctionNames;
	CurrentClass->GenerateFunctionList(FunctionNames);

	for (const auto& Name : FunctionNames)
	{
		const UFunction* Func = CurrentClass->FindFunctionByName(Name);
		if (Func == nullptr)
		{
			continue;
		}

		FString CheatName = Prefix + Func->GetMetaData(TEXT("Cheat"));
		FString Desc = Func->GetMetaData(TEXT("Desc"));

		for (TFieldIterator<FProperty> PropIt(Func); PropIt && (PropIt->PropertyFlags & CPF_Parm); ++PropIt)
		{
			FProperty* Prop = *PropIt;
			Desc += FString::Printf(TEXT(" %s [%s]"), *Prop->GetName(), *Prop->GetCPPType());
		}

		FSCCheatData Data;
		Data.Command = CheatName;
		Data.Desc = Desc;
		Data.Color = CommandColor;
		Data.FunctionName = Name.ToString();

		Commands.Emplace(Data);
	}
}

void USCCheatManager::CheatTestFunction(FString Argument)
{
	SC_LOG(Log, TEXT("Excute CheatTestFunction"));
}
