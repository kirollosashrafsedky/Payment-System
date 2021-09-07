#ifndef __TERMINAL_H__
#define __TERMINAL_H__

#include "../Infrastructure/types.h"
#define MAX_TRANSACTION_DATE 11

typedef struct ST_terminalData_t
{
  float transAmount;
  float maxTransAmount;
  uint8_t transactionDate[MAX_TRANSACTION_DATE];
} ST_terminalData_t;

uint8_t checkTransAmount(ST_terminalData_t *terminalData);
uint8_t checkTransDate(const ST_cardData_t *cardData,
                       ST_terminalData_t *terminalData);

#endif /* __TERMINAL_H__ */
