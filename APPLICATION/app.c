#include "app.h"
#define TerminalMaxAmount 10000.0


void appStart(void) {


	                                            ////card module////

	ST_cardData_t cardHolderData;
	ST_cardData_t* cardData = &cardHolderData;

	if (getCardHolderName(cardData) == WRONG_NAME)
		return (WRONG_NAME);


	if (getCardExpiryDate(cardData) == WRONG_EXP_DATE)
		return (WRONG_EXP_DATE);
		

	if (getCardPAN(cardData) == WRONG_PAN)
		return (WRONG_PAN);

	//-------------------------------------/

									  ////terminal module////

	ST_terminalData_t terminalData;
	ST_terminalData_t* termData = &terminalData;


	
	if (getTransactionDate(termData) == WRONG_DATE)
	{
		printf("Wrong Date form\n\n");
		return WRONG_DATE;
	}

	if (isCardExpired(cardData, termData) == EXPIRED_CARD)
	{
		printf("Your Card is Expired\n\n");
		return EXPIRED_CARD;
	}

	

	if (setMaxAmount(termData) == INVALID_MAX_AMOUNT)
	{
		printf("Invalid Max Amount");
		return INVALID_MAX_AMOUNT;
	}
	
	if (getTransactionAmount(termData) == INVALID_AMOUNT)
		return  INVALID_AMOUNT;

	
	if (isBelowMaxAmount(termData) == EXCEED_MAX_AMOUNT)
	{
		printf("Exceeded Max Amount:10000.00\n\n");
		return EXCEED_MAX_AMOUNT;
	}
	
	//-------------------------------//
	
										////server module////
	
	ST_accountsDB_t accountsDB[255];
	ST_accountsDB_t* accountref = &accountsDB[255];

	ST_transaction_t state;
	ST_transaction_t* transData = &state;

	
	if (isValidAccount(cardData, accountref) == ACCOUNT_NOT_FOUND) {
		return ACCOUNT_NOT_FOUND;
	}
	
	if (isBlockedAccount(accountref) == BLOCKED_ACCOUNT) {
		printf("DECLINED_STOLEN_CARD\n\n");
		return BLOCKED_ACCOUNT;
	}

	if ((isAmountAvailable(termData, accountref)) == LOW_BALANCE)
	{
		printf("DECLINED_INSUFFECIENT_FUND\n\n");
		return LOW_BALANCE;
	}
		
	if ((saveTransaction(transData)) == SAVING_FAILED)
		printf("INTERNAL_SERVER_ERROR\n");
	else {
		printf("APPROVED\n\n");

		printf("############################################\n");
		printf("Transaction sequance number is:%d\n", transData->transactionSequenceNumber);
		printf("Transaction Date is:%s\n", termData->transactionDate);
		printf("Transction Amountis:%.2f\n", termData->transAmount);
		printf("Card state is:RUNNING\n");
		printf("Max transction amount is:%.2f\n", termData->maxTransAmount);
		printf("Card holder name is:%s\n", cardData->cardHolderName);
		printf("Card pan is:%s\n", cardData->primaryAccountNumber);
		printf("Card Expiration date is:%s\n", cardData->cardExpirationDate);
		printf("############################################\n");

	}
		
	

}

















	
	
	
	
	
	
	