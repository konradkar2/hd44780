#include "pin.h"

void set_out(digital_pin *pin)
{
    *pin->dir |= pin->mask;
}

void set_in(digital_pin *pin)
{
    *pin->dir &= ~pin->mask;
}

void set_high(digital_pin *pin)
{
    *pin->value |= pin->mask;
}

void set_low(digital_pin *pin)
{
    *pin->value &= ~pin->mask;
}