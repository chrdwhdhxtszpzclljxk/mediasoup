#define MS_CLASS "RTC::RTCP::FeedbackPsTst"
// #define MS_LOG_DEV

#include "RTC/RTCP/FeedbackPsTst.hpp"
#include "Logger.hpp"
#include <cstring>

namespace RTC
{
	namespace RTCP
	{
		template<typename T>
		FeedbackPsTstItem<T>::FeedbackPsTstItem(uint32_t ssrc, uint8_t sequenceNumber, uint8_t index)
		{
			MS_TRACE();

			this->raw    = new uint8_t[sizeof(Header)];
			this->header = reinterpret_cast<Header*>(this->raw);

			// Set reserved bits to zero.
			std::memset(this->header, 0, sizeof(Header));

			this->header->ssrc           = uint32_t{ htonl(ssrc) };
			this->header->sequenceNumber = sequenceNumber;
			this->header->index          = index;
		}

		template<typename T>
		size_t FeedbackPsTstItem<T>::Serialize(uint8_t* buffer)
		{
			MS_TRACE();

			std::memcpy(buffer, this->header, sizeof(Header));

			return sizeof(Header);
		}

		template<typename T>
		void FeedbackPsTstItem<T>::Dump() const
		{
			MS_TRACE();

			MS_DEBUG_DEV("<FeedbackPsTstItem>");
			MS_DEBUG_DEV("  ssrc            : %" PRIu32, this->GetSsrc());
			MS_DEBUG_DEV("  sequence number : %" PRIu32, this->GetSequenceNumber());
			MS_DEBUG_DEV("  index           : %" PRIu32, this->GetIndex());
			MS_DEBUG_DEV("</FeedbackPsTstItem>");
		}

		/* Specialization for Tstr class. */

		template<>
		const FeedbackPs::MessageType FeedbackPsTstItem<Tstr>::messageType =
		  FeedbackPs::MessageType::TSTR;

		/* Specialization for Tstn class. */

		template<>
		const FeedbackPs::MessageType FeedbackPsTstItem<Tstn>::messageType =
		  FeedbackPs::MessageType::TSTN;

		// Explicit instantiation to have all definitions in this file.
		template class FeedbackPsTstItem<Tstr>;
		template class FeedbackPsTstItem<Tstn>;
	} // namespace RTCP
} // namespace RTC
