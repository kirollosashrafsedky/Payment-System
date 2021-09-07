#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Infrastructure/types.h"
#include "card.h"

// saves to gstr_currentCardData
void getCardData(ST_cardData_t *cardData)
{
   uint8_t u8_errorFlag = 1;

   /*ask for Card Holder Name*/
   printf("Please Enter Card Data:\n");
   printf("Please Enter the Card Holder Name:\n");
   fgets((char *)cardData->cardHolderName, MAX_CARD_HOLDER_NAME, stdin);
   fflush(stdin);
   cardData->cardHolderName[strcspn((char *)cardData->cardHolderName, "\n")] = 0;

   /*ask for primary Account Number*/
   printf("Please Enter the Primary Account Number:\n");
   fgets((char *)cardData->primaryAccountNumber,
         MAX_PRIMARY_ACCCOUNT_NUMBER,
         stdin);
   fflush(stdin);
   cardData->primaryAccountNumber[strcspn((char *)cardData->primaryAccountNumber,
         "\n")] = 0;

   /*ask for card Expiration Date*/
   printf("Please Enter the card Expiration Date:\n");
   printf("Ex: 02/22\n");
   while (u8_errorFlag != 0)
   {
      fgets(
            (char *)cardData->cardExpirationDate, MAX_CARD_EXPIRATION_DATE, stdin);
      fflush(stdin);
      cardData->cardExpirationDate[strcspn((char *)cardData->cardExpirationDate,
            "\n")] = 0;

      /*check the format of the Expiration Date*/
      for (uint8_t i = 0; i < MAX_CARD_EXPIRATION_DATE - 1; i++)
      {
         u8_errorFlag = 1;
         switch (cardData->cardExpirationDate[i])
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
            if ((i != 2))
            {
               u8_errorFlag = 0;
            }
            break;

         case '/':
            if (i == 2)
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
      uint8_t u8_month = (cardData->cardExpirationDate[1] - '0')
                             + (cardData->cardExpirationDate[0] - '0') * 10;
      if (u8_month < 1 || u8_month > 12)
      {
         u8_errorFlag = 1;
      }
      if (u8_errorFlag == 1)
      {
         printf(
               "Invalid Expiration Date, Re-enter in the card Expiration Date in the format mm/yy:\n");
      }
   }
}
