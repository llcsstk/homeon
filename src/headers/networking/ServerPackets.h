#pragma once
#ifndef SERVERPACKETS_H
#define SERVERPACKETS_H

#include "Packet.h"

#define WELCOME_PACKET 0x0001
#define SIMPLE_ACTION_PACKET 0x00C8


#define PING_PACKET 0x00FE

namespace ServerPackets
{
	Packet* Welcome(Packet *packet)
	{
		const uint8_t* welcome_packet = new uint8_t[4] {WELCOME_PACKET, 0x04, 0x06, 0x08};
		packet->body_length(4);
		
		memcpy(packet->body(), welcome_packet, 4);
		
		return packet;
	}	
	
	Packet* Ping(Packet *packet)
	{
		const uint8_t* ping_packet = new uint8_t[2] {PING_PACKET, 0x00};
		packet->body_length(2);
		
		memcpy(packet->body(), ping_packet, 2);
		
		return packet;
	}
	
	Packet* SimpleAction(Packet *packet, uint8_t value)
	{
		const uint8_t* ping_packet = new uint8_t[2] {SIMPLE_ACTION_PACKET, value};
		packet->body_length(2);
		
		memcpy(packet->body(), ping_packet, 2);
		
		return packet;
	}
}

#endif