#pragma once
#include <utility>

#include "CoreMinimal.h"
#include "Memorystream.h"
#include "Message.h"
#include "Containers/CircularQueue.h"

DECLARE_STATS_GROUP(TEXT("KBEngine_MessageReader"), STATGROUP_KBEngine_MessageReader, STATCAT_Advanced);

namespace KBEngine
{

#define MessageID uint16
#define MessageLength uint16
#define MessageLengthEx uint32
#define ReceivedPacketSize 1024

	struct FReceivedPacket
	{
		TArray<uint8> PacketBytes;
		uint32 NextReadIndex = 0;
	};

	class MessagesHandler;

	class KBENGINE_API MessageReader
	{
	public:
		MessageReader(MessagesHandler* handler, Messages *messages, uint32 SocketRecvQueueSize = 65535);
		~MessageReader();

		enum READ_STATE
		{
			// ��ϢID
			READ_STATE_MSGID = 0,

			// ��Ϣ�ĳ���65535����
			READ_STATE_MSGLEN = 1,

			// ���������Ϣ���ȶ��޷�����Ҫ��ʱʹ����չ����
			// uint32
			READ_STATE_MSGLEN_EX = 2,

			// ��Ϣ������
			READ_STATE_BODY = 3
		};

		// �������̴߳�������
		void Process();

		void Reset();

	public:
		TCircularQueue<FReceivedPacket> SocketRecvQueue;
	private:
		MessagesHandler* messagesHandler_ = nullptr;
		Messages *messages_ = nullptr;

		FReceivedPacket nowProcessPacket;
		TArray<uint8> expectBuff;

		MessageID msgid = 0;
		MessageLength msglen = 0;
		MessageLengthEx expectSize = 2;
		READ_STATE state = READ_STATE::READ_STATE_MSGID;
		MemoryStream stream;

		double NowFrameMaxProcessTime = FrameMaxProcessTime;
	};

}
