#include "server.h"





ST_accountsDB_t accountsDB[255] = { {9000.00, RUNNING,"123456789123456789"},
									 { 8000.00,RUNNING,"234567891234567890"},
									 { 7000.00,BLOCKED,"345678901234567890"},
									 { 600.00, RUNNING,"456789012345678901"},
									 { 500.00, RUNNING,"567890123456789012"},
									 { 400.00, BLOCKED,"678901234567890123"},
									 { 30.00,  RUNNING,"789012345678901234"},
									 { 20.00,  RUNNING,"890123456789012345"},
									 { -100,  BLOCKED,"901234567890123456"}

};





ST_transaction_t Transactions[255] = { 0 };

uint32_t TransactionNumber = 0;

uint16_t acc_num = 0;


EN_transState_t recieveTransactionData(ST_transaction_t* transData) {

	ST_accountsDB_t accountsDB[255];
	ST_accountsDB_t* accountref = &accountsDB[255];

	ST_terminalData_t terminalData;
	ST_terminalData_t* termData = &terminalData;

	ST_cardData_t cardHolderData;
	ST_cardData_t* cardData = &cardHolderData;


	if ((isValidAccount(transData, accountref)) == ACCOUNT_NOT_FOUND)
	{
		printf("FRAUD_CARD\n");
		return FRAUD_CARD;
	}

	if ( isAmountAvailable(transData,accountref) == LOW_BALANCE)
	{
		printf("DECLINED_INSUFFECIENT_FUND\n\n");
		return DECLINED_INSUFFECIENT_FUND;
	}

	if (isBlockedAccount(accountref) == BLOCKED)
	{
		printf("DECLINED_STOLEN_CARD\n\n");
		return DECLINED_STOLEN_CARD;
	}

	if (saveTransaction(transData) == SAVING_FAILED)
	{
		printf("INTERNAL_SERVER_ERROR\n");
		return INTERNAL_SERVER_ERROR;
	}

	
	printf("APPROVED");
	return APPROVED;
}

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence) {



	for (acc_num = (0 + acc_num); acc_num < 255; acc_num++)
	{
		if (strcmp(cardData->primaryAccountNumber, accountsDB[acc_num].primaryAccountNumber) == APPROVED)

		{
			accountRefrence->state = accountsDB[acc_num].state;
			if ((accountRefrence->state) != RUNNING)
			{
				printf("DECLINED_STOLEN_CARD\n\n");
				acc_num = 0;
				return ACCOUNT_NOT_FOUND;

			}
			printf("the Account is VALID\n");
			return SERVER_OK;

		}
	}
	acc_num = 0;
	printf("FRAUD_CARD\n\n");
	return ACCOUNT_NOT_FOUND;

}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence) {

	for (acc_num = (0 + acc_num); acc_num < 255; acc_num++)
	{
		
			accountRefrence->state = accountsDB[acc_num].state;
			if ((accountRefrence->state) != RUNNING)
			{
				

				return BLOCKED;

			}
			return SERVER_OK;
		}
	
	printf("THIS Account State:RUNNING\n");

	return APPROVED;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence) {

	f32 trans, accref;

	
		accountRefrence->state = accountsDB[acc_num].state;
		if (accountRefrence->state == RUNNING)
		{

			accref = accountsDB[acc_num].balance;
			printf("your Account Balance is:%.2f\n\n", accountsDB[acc_num].balance);

			trans = termData->transAmount;
			if (trans > accref) {
				acc_num = 0;
				return LOW_BALANCE;
				
			}
			else {
				accountsDB[acc_num].balance = (accountsDB[acc_num].balance - termData->transAmount);
				printf("your Account Balance Now is:%.2f\n", accountsDB[acc_num].balance);
			}
		}
}

EN_serverError_t saveTransaction(ST_transaction_t* transData) {

	transData->transactionSequenceNumber = 0 + TransactionNumber;

	if (transData->transactionSequenceNumber < 255)                      
	{
		Transactions[transData->transactionSequenceNumber].cardHolderData = transData->cardHolderData;
		Transactions[transData->transactionSequenceNumber].terminalData = transData->terminalData;
		Transactions[transData->transactionSequenceNumber].transState = transData->transState;
		Transactions[transData->transactionSequenceNumber].transactionSequenceNumber = transData->transactionSequenceNumber + 1;

		TransactionNumber++;
	
	
		return  transData->transactionSequenceNumber;

	}
	return SAVING_FAILED;
}









