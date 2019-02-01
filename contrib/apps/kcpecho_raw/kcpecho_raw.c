/*
 * Copyright (c) 2016 Stephan Linz <linz@li-pro.net>, Li-Pro.Net
 * All rights reserved.
 *
 * Based on examples provided by
 * Iwan Budi Kusnanto <ibk@labhijau.net> (https://gist.github.com/iwanbk/1399729)
 * Juri Haberland <juri@sapienti-sat.org> (https://lists.gnu.org/archive/html/lwip-users/2007-06/msg00078.html)
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of and a contribution to the lwIP TCP/IP stack.
 *
 * Credits go to Adam Dunkels (and the current maintainers) of this software.
 *
 * Stephan Linz rewrote this file to get a basic echo example.
 */

/**
 * @file
 * UDP echo server example using raw API.
 *
 * Echos all bytes sent by connecting client,
 * and passively closes when client is done.
 *
 */

#include "lwip/opt.h"
#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/udp.h"
#include "kcpecho_raw.h"
#include "ikcp.h"

#if LWIP_UDP

static struct udp_pcb *udpecho_raw_pcb;

u16_t dstPort;
u32_t addr_v=0;
ip_addr_t *dstAddr=((ip_addr_t *)&addr_v);
ikcpcb *kcp1;


int udp_output(const char *buf, int len, ikcpcb *kcp, void *user);

static void
udpecho_raw_recv(void *arg, struct udp_pcb *upcb, struct pbuf *p,
                 const ip_addr_t *addr, u16_t port)
{
  struct pbuf *pq;
  u8_t pcnt=1;

  LWIP_UNUSED_ARG(arg);
  if (p != NULL) {

    pq=p;
    while(pq->tot_len!=pq->len)
    {
      pq=pq->next;
      pcnt+=1;
    }
    printf("packs = %d\r\n",pcnt);

    pq=p;

    /* send received packet back to sender */
    //udp_sendto(upcb, p, addr, port);

    memcpy(dstAddr, addr, sizeof(ip_addr_t));
    dstPort = port;
    //printf("port = %d, dstAddr->addr=%d\n", dstPort, dstAddr->addr);

    u8_t pcnt=1;
    while(p->tot_len!=p->len)
	{
		p=p->next;
		pcnt+=1;
//		TRACE_ZZG("%d\r\n",pcnt+1);
	}

	u8_t buf[p->tot_len];
	memset(buf, 0, sizeof(buf));
	u16_t len_tmp=0;
	{
		for(u8_t i;i<pcnt;i++)
		{
			memcpy(buf,p->payload,p->len);
			len_tmp+=p->len;
			p=p->next;
		}
	}
    udpecho_raw_pcb = upcb;
    ikcp_input(kcp1, (const char *)buf, len_tmp);

    /* free the pbuf */
    if(p!=NULL)
    {
       pbuf_free(p);
    }
  }
}

int udp_output(const char *buf, int len, ikcpcb *kcp, void *user)
{
    kcp = kcp;
    user = user;
    struct pbuf *p;

    //printf("len = %d, dstAddr->addr=%d\n", len, dstAddr->addr);
    if(buf!=NULL)
    {
        p = pbuf_alloc(PBUF_TRANSPORT, len, PBUF_POOL);
        if(p!=NULL)
        {
            pbuf_take(p, (char*)buf, len);
	        udp_sendto(udpecho_raw_pcb, p, dstAddr, dstPort);
            pbuf_free(p);
        }
    }

	return 0;
}

void
kcpecho_raw_init(void)
{
  udpecho_raw_pcb = udp_new_ip_type(IPADDR_TYPE_ANY);
  if (udpecho_raw_pcb != NULL) 
  {
    err_t err;

    err = udp_bind(udpecho_raw_pcb, IP_ANY_TYPE, 8000);
    if (err == ERR_OK) 
    {
      udp_recv(udpecho_raw_pcb, udpecho_raw_recv, NULL);
    } 
    else 
    {
      /* abort? output diagnostic? */
    }

    kcp1 = ikcp_create(0x11223344, (void*)0);
    kcp1->output = udp_output;
  } 
  else 
  {
    /* abort? output diagnostic? */
  }
}

#endif /* LWIP_UDP */
