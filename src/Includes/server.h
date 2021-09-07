#ifndef __SERVER_H__
#define __SERVER_H__

#include "../Infrastructure/types.h"

#define MAX_TRANSACTIONS 50
#define MAX_PRIMARY_ACCCOUNT_NUMBER 20

typedef enum EN_transStat_t
{
  DECLINED,
  APPROVED
} EN_transStat_t;

typedef struct ST_transaction_t
{
  ST_cardData_t cardHolderData;
  ST_terminalData_t transData;
  EN_transStat_t transStat;
} ST_transaction_t;

typedef struct ST_accountBalance_t
{
  float balance;
  uint8_t primaryAccountNumber[MAX_PRIMARY_ACCCOUNT_NUMBER];
} ST_accountBalance_t;

void checkServerApproval(ST_transaction_t *transaction);

void saveToDatabase(ST_transaction_t *transaction);

void sortDatabase(ST_transaction_t *transaction);

void printDatabase(void);

#endif /* __SERVER_H__ */
