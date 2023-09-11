// @jung june


#include "SCSocketWorker.h"

#include <SocketSubsystem.h>
#include <Interfaces/IPv4/IPv4Address.h>
#include <IPAddress.h>
#include <Sockets.h>
#include <Async/Async.h>

FSCSocketWorker::FSCSocketWorker()
{
}

FSCSocketWorker::~FSCSocketWorker()
{
	AsyncTask(ENamedThreads::GameThread,
		[]()
		{
			// thread destroy
		});

	FSCSocketWorker::Stop();
	RemoveThread();
}

bool FSCSocketWorker::Init()
{
	bRun = false;
	bConnected = false;

	return true;
}

void FSCSocketWorker::Start()
{
	if (Thread.IsValid())
	{
		RemoveThread();
	}

	if (IpAddress.IsEmpty())
	{
		IpAddress = TEXT("127.0.0.1");
		Port = 9999;
	}

	auto* SocketThread = FRunnableThread::Create(this, *FString::Printf(TEXT("FSCSocketWorker %s:%d"), *IpAddress, Port, 0, TPri_Normal));

	Thread.Reset();
}


uint32 FSCSocketWorker::Run()
{
	AsyncTask(ENamedThreads::GameThread,
		[]()
		{
			//Starting thread loopeffect

		});

	while (bRun)
	{
		FDateTime TickStartTime = FDateTime::UtcNow();
		if (bConnected == false)
		{
			if (CreateSocket() == false)
			{
				bRun = false;
				continue;
			}

			bConnected = SocketConnect();

			if (bConnected == false)
			{
				bRun = false;
				continue;
			}
		}

		if (IsValidSocketObject() == false)
		{
			bRun = false;
			continue;
		}

		if (SendData() == false)
		{
			bRun = false;
			continue;
		}

		ReadData();
		Sleep(TickStartTime);
	}

	bool IsClearBox = Outbox.IsEmpty();

	AsyncTask(ENamedThreads::GameThread,
		[IsClearBox]()
		{
			// exit loop
		});

	bConnected = false;
	SocketShutdown();

	return 0;
}

void FSCSocketWorker::Stop()
{
	bRun = false;
}

void FSCSocketWorker::Exit()
{
}



TArray<uint8> FSCSocketWorker::ReadFromInbox()
{
	TArray<uint8> msg;
	Inbox.Dequeue(msg);
	return MoveTemp(msg);
}

void FSCSocketWorker::AddToOutbox(const TArray<uint8>& Message)
{
	Outbox.Enqueue(Message);
}

bool FSCSocketWorker::CreateSocket()
{
	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateUniqueSocket(NAME_Stream, TEXT("GameSocket"), false); 
	ESCSocketStatus Status = Socket.IsValid() ? ESCSocketStatus::ConnectionReady : ESCSocketStatus::CreationFailed;
	AsyncTask(ENamedThreads::GameThread,
		[=]()
		{
			//create socket
		});

	if (Status == ESCSocketStatus::CreationFailed)
	{
		return false;
	}

	Socket->SetReceiveBufferSize(RecvBufferSize, ActualRecvBufferSize);
	Socket->SetSendBufferSize(SendBufferSize, ActualSendBufferSize);

	return true;
}

bool FSCSocketWorker::SocketConnect()
{

	FIPv4Address IPAddr;
	uint32 TargetIP = 0;
	FIPv4Address::Parse(IpAddress, IPAddr);
	TargetIP = IPAddr.Value;
	TSharedRef<FInternetAddr> InternetAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr(); InternetAddr->SetIp(TargetIP);
	InternetAddr->SetPort(Port);

	const ESCSocketStatus Status = Socket->Connect(InternetAddr.Get()) ? ESCSocketStatus::Connected : ESCSocketStatus::ConnectionError; 
	const ESocketErrors ErrorCode = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetLastErrorCode();
	AsyncTask(ENamedThreads::GameThread,
		[=]()
		{
			// ChangeConnectionStatus
		});

	return Status == ESCSocketStatus::Connected;
}

void FSCSocketWorker::SocketShutdown()
{
	if(Socket.IsValid() == false)
	{
		return;
	}

	Socket->Close();
	Socket.Reset();

	AsyncTask(ENamedThreads::GameThread,
		[=]()
		{
			//Socket shutdown

		});
}

void FSCSocketWorker::RemoveThread()
{
	if (Thread.IsValid() == false)
	{
		return;
	}

	Thread->WaitForCompletion();
	Thread.Reset();
}

bool FSCSocketWorker::BlockingSend(const uint8* Data, int32 BytesToSend)
{
	return false;
}

bool FSCSocketWorker::SendData()
{
	while (Outbox.IsEmpty() == false)
	{
		TArray<uint8> SendItem;
		Outbox.Dequeue(SendItem);

		if (BlockingSend(SendItem.GetData(), SendItem.Num()) == false)
		{
			AsyncTask(ENamedThreads::GameThread,
				[]()
				{
					// Send data fail, stop running
				});
		}
	}

	return false;
}

void FSCSocketWorker::ReadData()
{
	TArray<uint8> ReceivedData;
	uint32 PendingDataSize = 0;
	int32 BytesReadTotal = 0;
	while (Socket->HasPendingData(PendingDataSize))
	{
		ReceivedData.SetNumUninitialized(BytesReadTotal + PendingDataSize);

		int32 BytesRead = 0;
		if (Socket->Recv(ReceivedData.GetData() + BytesReadTotal, PendingDataSize, BytesRead) == false)
		{
			ESocketErrors ErrorCode = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetLastErrorCode();

			AsyncTask(ENamedThreads::GameThread,
				[ErrorCode]()
				{
					// recevie failed
				});

			break;
		}

		BytesReadTotal += BytesRead;
	}

	if (ReceivedData.IsEmpty() == false)
	{
		Inbox.Enqueue(ReceivedData);
	}
}

void FSCSocketWorker::Sleep(const FDateTime& TickStartTime)
{
	float TickElapsedTime = (FDateTime::UtcNow() - TickStartTime).GetTotalSeconds();
	float TimeToSleep = TimeBetweenTicks - TickElapsedTime;
	if (TimeToSleep > 0.f)
	{
		FPlatformProcess::Sleep(TimeToSleep);
	}
}

bool FSCSocketWorker::IsValidSocketObject()
{
	bool bValidSocket = Socket.IsValid();
	if (bValidSocket == false)
	{
		AsyncTask(ENamedThreads::GameThread,
			[=]()
			{
				//Missing socket object
			});
	}

	return bValidSocket;
}
