#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Infrastructure/types.h"
#include "card.h"
#include "terminal.h"

// checks on input of the user and saves to gstr_currentTerminalData.transAmount
// if valid then returns 1 if valid and 0 otherwise
uint8_t checkTransAmount(ST_terminalData_t *terminalData)
{
  uint8_t u8_errorFlag = 1;

  printf("Please Enter the transaction amount:\n");

  while (u8_errorFlag)
  {
    u8_errorFlag = 0;
    scanf("%f", &terminalData->transAmount);
    fflush(stdin);
    if (terminalData->transAmount <= 0)
    {
      u8_errorFlag = 1;
      printf("Invalid transaction amount, Re-enter the transaction amount:\n");
    }
  }
  if (terminalData->transAmount <= terminalData->maxTransAmount)
  {
    return 1;
  }
  return 0;
}

// compare between user input and gstr_currentCardData.cardExpirationDate and
// saves to gstr_currentTerminalData.transactionDate if valid, then returns 1 if
// valid and 0 otherwise
uint8_t checkTransDate(const ST_cardData_t *cardData,
                       ST_terminalData_t *terminalData)
{
  uint8_t u8_errorFlag = 1;

  printf("Please Enter the transaction date:\n");
  printf("Ex: 29/08/2021\n");
  while (u8_errorFlag)
  {
    fgets((char *)terminalData->transactionDate, MAX_TRANSACTION_DATE, stdin);
    fflush(stdin);
    terminalData->transactionDate[strcspn((char *)terminalData->transactionDate,
                                          "\n")] = 0;

    /*check the format of the Transaction Date*/
    for (uint8_t i = 0; i < MAX_TRANSACTION_DATE - 1; i++)
    {
      u8_errorFlag = 1;
      switch (terminalData->transactionDate[i])
      {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
          if ((i != 2) && (i != 5))
          {
            u8_errorFlag = 0;
          }
          break;

        case '/':
          if (i == 2 || i == 5)
          {
            u8_errorFlag = 0;
          }
          break;
      }
      if (u8_errorFlag == 1)
      {
        break;
      }
    }
    uint8_t u8_month = (terminalData->transactionDate[4] - '0')
                       + (terminalData->transactionDate[3] - '0') * 10;
    if (u8_month < 1 || u8_month > 12)
    {
      u8_errorFlag = 1;
    }
    if (u8_errorFlag == 1)
    {
      printf(
          "Invalid Date, Re-enter in the transaction date in the format dd/mm/yyyy:\n");
    }
  }

  /*array for comparing the dates*/
  uint8_t au8_transdate[2], au8_expDate[2];
  uint8_t u8_transDateTotal, u8_expDateTotal;

  /*convert all elements of the card Expiration Date to numbers*/
  au8_expDate[0] = (cardData->cardExpirationDate[1] - '0')
                   + (cardData->cardExpirationDate[0] - '0') * 10;
  au8_expDate[1] = (cardData->cardExpirationDate[4] - '0')
                   + (cardData->cardExpirationDate[3] - '0') * 10;

  /*convert all elements of the transaction Date to numbers*/
  au8_transdate[0] = (terminalData->transactionDate[4] - '0')
                     + (terminalData->transactionDate[3] - '0') * 10;
  au8_transdate[1] = (terminalData->transactionDate[9] - '0')
                     + (terminalData->transactionDate[8] - '0') * 10;

  u8_transDateTotal = au8_transdate[0] + (au8_transdate[1] * 100);
  u8_expDateTotal   = au8_expDate[0] + (au8_expDate[1] * 100);

  if (u8_transDateTotal > u8_expDateTotal)
  {
    return 0;
  }
  return 1;
}
