#pragma once

#include "packetfactory.h"
#include "entitycomponents.h"


namespace RoseCommon {

REGISTER_RECV_PACKET(ePacketType::PAKCS_STOP, CliStop)
class CliStop : public CRosePacket {
	private:
		static const RecvPacketFactory::Initializer<uint8_t*> init;
	public:
		CliStop();
		CliStop(uint8_t buffer[MAX_PACKET_SIZE]);
		CliStop(float x, float y);

		virtual ~CliStop() = default;

		float x() const;
		float y() const;

	protected:
		virtual void pack() override;

	private:
		float x_;
		float y_;
};

}
