/********************************************************************
*  
*  Copyright (c) 2011, Institute of Embedded Systems at
*                      Zurich University of Applied Sciences 
*                      (http://ines.zhaw.ch)
*  
*  All rights reserved.
* 
* 
*  Redistribution and use in source and binary forms, with or  
*  without modification, are permitted provided that the 
*  following conditions are met:
*  
*  - Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer. 
*
*  - Redistributions in binary form must reproduce the above 
*    copyright notice, this list of conditions and the following 
*    disclaimer in the documentation and/or other materials provided
*    with the distribution. 
*
*  - Neither the name of the Zurich University of Applied Sciences
*    nor the names of its contributors may be used to endorse or 
*    promote products derived from this software without specific 
*    prior written permission. 
*
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
*  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
*  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
*  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS 
*  BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED 
*  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON 
*  ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
*  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY 
*  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
*  POSSIBILITY OF SUCH DAMAGE.
*  
*********************************************************************/


/********************************************************************
*   _____       ______  _____                                       *
*  |_   _|     |  ____|/ ____|                                      *
*    | |  _ __ | |__  | (___    Institute of Embedded Systems       *
*    | | | '_ \|  __|  \___ \   Zurich University of Applied        *
*   _| |_| | | | |____ ____) |  Sciences                            *
*  |_____|_| |_|______|_____/   8401 Winterthur, Switzerland        *
*                                                                   *
*********************************************************************
* 
*  Project     : Parallel Redundancy Protocol
* 
*  Version     : 1.1
*  Author      : itin
* 
*********************************************************************
*  Change History
*
*  Date     | Name     | Modification
************|**********|*********************************************
*  17.06.11 | itin     | file created
*********************************************************************/

#ifndef PRP_DiscardAlgorithm_PRP1_T_H
#define PRP_DiscardAlgorithm_PRP1_T_H

#include "PRP_Package_T.h"
#include "PRP_RedundancyControlTrailer_T.h"
#include "PRP_DataTypes_T.h"
#include <sys/time.h>

#define DISCARD_ITEM_COUNT          1024

#define DISCARD_LIST_ENTRY_COUNT    256      // 2^n, n is 8 in this case
#define DISCARD_HASH_MASK           0x00FF   // Must select n bit in a range from 1 to 16

struct PRP_DiscardAlgorithm_PRP1_T
{
	struct PRP_DiscardAlgorithm_DiscardItem_PRP1_T **hash_list;           // first list orded by hash, second list orded from newest to oldest because we dont want to process dead items all the time
	struct PRP_DiscardAlgorithm_DiscardItem_PRP1_T *free_list;            // list of free items to use
	struct PRP_DiscardAlgorithm_DiscardItem_PRP1_T *chronology;           // from oldest to newest
	struct PRP_DiscardAlgorithm_DiscardItem_PRP1_T *newest;               // shortcut to newest item

	int used_item_count;

};

struct PRP_DiscardAlgorithm_DiscardItem_PRP1_T
{
	unsigned short seq_nr;
	unsigned char src_mac[6];
	
	struct timeval tv;           // timestamp

	unsigned short hash;         // hash code

	struct PRP_DiscardAlgorithm_DiscardItem_PRP1_T *previous;             // Used only for hash_list
	struct PRP_DiscardAlgorithm_DiscardItem_PRP1_T *next;                 // Used only for hash_list

	struct PRP_DiscardAlgorithm_DiscardItem_PRP1_T *previous_alt;         // Used only for chronology
	struct PRP_DiscardAlgorithm_DiscardItem_PRP1_T *next_alt;             // Used only for free_list and chronology
};

void PRP_DiscardAlgorithm_PRP1_T_print(PRP_DiscardAlgorithm_PRP1_T* const me, uinteger32 level);
integer32 PRP_DiscardAlgorithm_PRP1_T_search_entry(PRP_DiscardAlgorithm_PRP1_T* const me, octet* mac, octet* seq_nr);
void PRP_DiscardAlgorithm_PRP1_T_do_aging(PRP_DiscardAlgorithm_PRP1_T* const me);
void PRP_DiscardAlgorithm_PRP1_T_init(PRP_DiscardAlgorithm_PRP1_T* const me);
void PRP_DiscardAlgorithm_PRP1_T_cleanup(PRP_DiscardAlgorithm_PRP1_T* const me);

#endif  

