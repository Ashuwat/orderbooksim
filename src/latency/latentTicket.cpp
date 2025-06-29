#include "../../include/latency/latentTicket.h"
#include "../../include/orderbook/ticket.h"

LatentTicket::LatentTicket(Ticket ticket, int date) : date(date), ticket(ticket) {};