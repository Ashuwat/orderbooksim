#pragma once

#include "../orderbook/ticket.h"
#include <memory>

struct LatentTicket {
    Ticket ticket;
    int date;

    LatentTicket(Ticket ticket, int date);
};