/*
 ============================================================================
 Name         : Payment System
 Team		  : Conquerors Team
 Organization : Sprints Internship
 Version      : 1.0
 Description  :

 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "../Infrastructure/types.h"
#include "paymentSystem.h"
#include "../Includes/card.h"
#include "../Includes/terminal.h"
#include "../Includes/server.h"

/* Defines */
#define APPROVAL_MSG "The Transaction is APPROVED\n"
#define ERROR_MSG "The Transaction is DECLINED\n"
#define MAX_TRANS_AMOUNT 5000;

int main(void)
{
  setvbuf(stdout, NULL, _IONBF, 0);  // solve eclipse issue in printf and scanf
  ST_cardData_t str_currentCardData;
  ST_terminalData_t str_currentTerminalData;
  ST_transaction_t str_currentTransactionData;
  str_currentTerminalData.maxTransAmount = MAX_TRANS_AMOUNT;
  uint8_t u8_finalChoice;
  do
  {
    getCardData(&str_currentCardData);
    if (checkTransAmount(&str_currentTerminalData)
        && checkTransDate(&str_currentCardData, &str_currentTerminalData))
    {
      str_currentTransactionData.cardHolderData = str_currentCardData;
      str_currentTransactionData.transData      = str_currentTerminalData;
      printf("Verifying Data from the server...\n");
      checkServerApproval(&str_currentTransactionData);
      if (str_currentTransactionData.transStat == APPROVED)
      {
        printf(APPROVAL_MSG);
      }
      else
      {
        printf(ERROR_MSG);
      }
    }
    else
    {
      printf(ERROR_MSG);
    }
    u8_finalChoice = anotherTrial();
    while (u8_finalChoice == 2)
    {
      printDatabase();
      u8_finalChoice = anotherTrial();
    }
  } while (u8_finalChoice);
  printf("\nEnd of the program\n");
  return 0;
}

uint8_t anotherTrial(void)
{
  uint8_t u8_errorFlag = 1;
  printf(
      "Do you want to continue (y/n) or type (p) to print server database:\n");
  uint8_t u8_input;
  while (u8_errorFlag)
  {
    scanf("%c", &u8_input);
    fflush(stdin);
    switch (u8_input)
    {
      case 'y':
      case 'Y':
        return 1;
      case 'n':
      case 'N':
        return 0;
      case 'p':
      case 'P':
        return 2;
    }
    printf("Invalid input. Do you want to continue (y/n):\n");
  }

  return 0;
}
