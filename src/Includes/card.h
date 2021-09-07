#ifndef __CARD_H__
#define __CARD_H__

#include "../Infrastructure/types.h"

#define MAX_CARD_HOLDER_NAME 25
#define MAX_PRIMARY_ACCCOUNT_NUMBER 20
#define MAX_CARD_EXPIRATION_DATE 6

typedef struct ST_cardData_t
{
  uint8_t cardHolderName[MAX_CARD_HOLDER_NAME];
  uint8_t primaryAccountNumber[MAX_PRIMARY_ACCCOUNT_NUMBER];
  uint8_t cardExpirationDate[MAX_CARD_EXPIRATION_DATE];
} ST_cardData_t;

void getCardData(ST_cardData_t *cardData);

#endif /* __CARD_H__ */
