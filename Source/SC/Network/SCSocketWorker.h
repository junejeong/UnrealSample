// @jung june

#pragma once

#include "SC.h"

#include <SocketSubsystem.h>

/**
 * 
 */
enum class ESCSocketStatus
{
	Unknown,
	CreationFailed,
	ConnectionReady,
	ConnectionError,
	Connected,
	Disconnected
};

class SC_API FSCSocketWorker : public FRunnable
{
public:
	FSCSocketWorker();
	virtual ~FSCSocketWorker();

	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;

	void Start();
	TArray<uint8> ReadFromInbox();
	void AddToOutbox(const TArray<uint8>& Message);

protected:
	bool CreateSocket();
	bool SocketConnect();
	void SocketShutdown();
	void RemoveThread();
	bool BlockingSend(const uint8* Data, int32 BytesToSend);
	bool SendData();
	void ReadData();
	void Sleep(const FDateTime& TickStartTime);
	bool IsValidSocketObject();

private:
	static constexpr int32 RecvBufferSize = 0;
	static constexpr int32 SendBufferSize = 0;
	static constexpr float TimeBetweenTicks = 0.f;

	TUniquePtr<FRunnableThread> Thread;
	FUniqueSocket Socket;

	TQueue<TArray<uint8>, EQueueMode::Spsc> Inbox;
	TQueue<TArray<uint8>, EQueueMode::Spsc> Outbox;

	FThreadSafeBool bConnected = false;
	FThreadSafeBool bRun = false;
	FString IpAddress;
	int32 Port;

	int32 Id;
	int32 ActualRecvBufferSize;
	int32 ActualSendBufferSize;
};
