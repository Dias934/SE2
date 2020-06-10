/*
 * ntp_packets.h
 *
 *  Created on: 14/05/2020
 *      Author: Manuel
 */

#include "stdint.h"
#ifndef NTP_PACKETS_H_
#define NTP_PACKETS_H_

typedef struct {
	 uint8_t li_vn_mode; // Eight bits. li, vn, and mode.
	 	 	 	 	 	 // li. Two bits. Leap indicator.
	 	 	 	 	 	 // vn. Three bits. Version number of the protocol.
	 	 	 	 	 	 // mode. Three bits. Client will pick mode 3 for client.
	 uint8_t stratum; // Eight bits. Stratum level of the local clock.
	 uint8_t poll; // Eight bits. Maximum interval between successive messages.
	 uint8_t precision; // Eight bits. Precision of the local clock.

	 uint32_t rootDelay; // 32 bits. Total round trip delay time.
	 uint32_t rootDispersion; // 32 bits. Max error aloud from primary clock source.
	 uint32_t refId; // 32 bits. Reference clock identifier.

	 uint32_t refTm_s; // 32 bits. Reference time-stamp seconds.
	 uint32_t refTm_f; // 32 bits. Reference time-stamp fraction of a second.

	 uint32_t origTm_s; // 32 bits. Originate time-stamp seconds.
	 uint32_t origTm_f; // 32 bits. Originate time-stamp fraction of a second.

	 uint32_t rxTm_s; // 32 bits. Received time-stamp seconds.
	 uint32_t rxTm_f; // 32 bits. Received time-stamp fraction of a second.

	 uint32_t txTm_s; // 32 bits. Transmit time-stamp seconds. Important
	 uint32_t txTm_f; // 32 bits. Transmit time-stamp fraction of a second.
} ntp_packet, *Pntp_packet; // Total: 384 bits or 48 bytes.

#define PACKET_SIZE 48

#define DEFAULT_LI_VN_MODE 0xE3
#define DEFAULT_STRATUM 0
#define DEFAULT_POLL 6
#define DEFAULT_PRECISION 0xEC

void init_packet(Pntp_packet packet);

void correct_answer_packet(Pntp_packet packet);

#endif /* NTP_PACKETS_H_ */
