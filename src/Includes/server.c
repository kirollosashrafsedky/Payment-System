#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Infrastructure/types.h"
#include "card.h"
#include "terminal.h"
#include "server.h"

ST_accountBalance_t accounts[] = {{100.00f, "123456789"},
      {6000.00f, "234567891"},
      {3250.25f, "567891234"},
      {1500.12f, "456789123"},
      {500.00f, "258649173"},
      {2100.00f, "654823719"},
      {0.00f, "971362485"},
      {1.00f, "793148625"},
      {10.12f, "123123456"},
      {0.55f, "456789321"}};

ST_transaction_t transactions[MAX_TRANSACTIONS];
uint8_t gu8_transactionsCounter = 0;

// uses gstr_currentTransactionData.cardHolderData.primaryAccountNumber
// and gstr_currentTransactionData.transData.transAmount and compare it to the
// array acccounts if valid : sets gstr_currentTransactionData.transStat =
// APPROVED else : sets gstr_currentTransactionData.transStat = DECLINED
void checkServerApproval(ST_transaction_t *transaction)
{
   transaction->transStat = DECLINED;
   for (uint8_t i = 0; i < 10; i++)
   {
      if (strcmp((char *)transaction->cardHolderData.primaryAccountNumber,
            (char *)accounts[i].primaryAccountNumber)
            == 0)
      {
         // if PAN is exist then go to check is there is enough balance to withdraw
         // from it
         if (transaction->transData.transAmount <= accounts[i].balance)
         {
            accounts[i].balance -= transaction->transData.transAmount;
            transaction->transStat =
                  APPROVED;  // when there is enough balance then make state approved
            saveToDatabase(transaction);
            break;
         }
      }
   }
}

// saves parm transaction to global array transactions
// using index gu8_transactionsCounter
// transactions[gu8_transactionsCounter] and increments gu8_transactionsCounter
// also make sure gu8_transactionsCounter is < MAX_TRANSACTIONS "50"
void saveToDatabase(ST_transaction_t *transaction)
{
   if (gu8_transactionsCounter >= MAX_TRANSACTIONS)
      return;
   transactions[gu8_transactionsCounter++] = *transaction;
   sortDatabase(transactions);
}

// sorts according to PAN
void sortDatabase(ST_transaction_t *transaction)
{
   // bubble sort
   for (uint8_t i = gu8_transactionsCounter - 1; i > 0; i--)
   {
      for (uint8_t j = 0; j < i; j++)
      {
         if (strncmp((char *)transaction[j].cardHolderData.primaryAccountNumber,
               (char *)transaction[j + 1].cardHolderData.primaryAccountNumber,
               20)
               > 0)
         {
            // swap elements
            ST_transaction_t temp = transactions[j];
            transactions[j]       = transactions[j + 1];
            transactions[j + 1]   = temp;
         }
      }
   }
}

// loop through transactions array and print cardHolderName,
// primaryAccountNumber, cardExpirationDate transAmount, transactionDate,
// transStat in a neat way with titles for each one
void printDatabase(void)
{
   printf("** Server Database **\n");
   for (uint8_t i = 0; i < gu8_transactionsCounter ; i++)
   {
      printf("Account %d:\n", i);
      printf("Card Holder Name:\t%s\n",
            transactions[i].cardHolderData.cardHolderName);
      printf("Primary Account Number:\t%s\n",
            transactions[i].cardHolderData.primaryAccountNumber);
      printf("Card Expiry Date:\t%s\n",
            transactions[i].cardHolderData.cardExpirationDate);
      printf("Transaction Amount:\t%f\n",
            transactions[i].transData.transAmount);
      printf("Transaction Date:\t%s\n",
            transactions[i].transData.transactionDate);
      printf("-------------------------------------------------\n");
   }
}
