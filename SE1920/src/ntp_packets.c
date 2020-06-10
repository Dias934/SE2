/*
 * ntp_packets.c
 *
 *  Created on: 14/05/2020
 *      Author: Manuel Dias, Ricardo Romano
 */

#include "ntp_packets.h"
#include "stdlib.h"

void init_packet(Pntp_packet packet){
	packet->li_vn_mode = DEFAULT_LI_VN_MODE;
	packet->stratum = DEFAULT_STRATUM;
	packet->poll = DEFAULT_POLL;
	packet->precision = DEFAULT_PRECISION;
}

void correct_answer_packet(Pntp_packet packet){
	packet->txTm_f=__builtin_bswap32(packet->txTm_f);
	packet->txTm_s=__builtin_bswap32(packet->txTm_s);
}
