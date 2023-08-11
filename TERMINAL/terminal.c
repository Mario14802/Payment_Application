#include "terminal.h"

#define transactionDateMaxLen 10
#define TerminalMaxAmount 10000.00

#define TransDateYearThousands   6
#define TransDateYearhundredths  7
#define YearThousands 2
#define Yearhundredths 0


#define CardDateYearTens   3
#define TransDateYearTens  8

#define CardDateYearOnes   4
#define TransDateYearOnes  9

#define CardDateMonTens    0
#define TransDateMonTens   3

#define CardDateMonOnes    1
#define TransDateMonOnes   4


EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {

	uint8_t  counter, length = 0;

	printf("Please enter the TransactionDate in this EXACT FORM : DD/MM/YYYY ");
	scanf("%s", &termData->transactionDate);


	for (counter = 0; termData->transactionDate[counter] != '\0'; counter++)
	{
		length++; //Counting the length.
	}

	if ((length != transactionDateMaxLen || (termData->transactionDate) == NULL))
	{

		printf("the Card expiry Date must be 10 characters:\n");
		return  WRONG_DATE;


	}

	if (!isdigit(termData->transactionDate[0]) || !isdigit(termData->transactionDate[1]))
		return  WRONG_DATE;

	if ((termData->transactionDate[2]) != '/')
		return  WRONG_DATE;

	if (!isdigit(termData->transactionDate[3]) || !isdigit(termData->transactionDate[4]))
		return  WRONG_DATE;

	if ((termData->transactionDate[5]) != '/')
		return  WRONG_DATE;

	if (!isdigit(termData->transactionDate[6]) || !isdigit(termData->transactionDate[7]))
		return  WRONG_DATE;

	if (!isdigit(termData->transactionDate[8]) || !isdigit(termData->transactionDate[9]))
		return  WRONG_DATE;

	printf("Your TransactionDate is:%s\n", termData->transactionDate);


	return  CARD_OK;

}

//------------------------------//

EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
	if ((termData->transactionDate[TransDateYearThousands])!= '2' || ((termData->transactionDate[TransDateYearhundredths]) != '0')) // i needed to make those numbers cont because in card expiration date  there wasnt thoundth or hundredth in it's date only MM/YY
		return EXPIRED_CARD;

		if ((cardData->cardExpirationDate[CardDateYearTens]) < (termData->transactionDate[TransDateYearTens]))
			return EXPIRED_CARD;
		if ((cardData->cardExpirationDate[CardDateYearTens]) == (termData->transactionDate[TransDateYearTens]))
		{
			if ((cardData->cardExpirationDate[CardDateYearOnes]) < (termData->transactionDate[TransDateYearOnes]))
				return EXPIRED_CARD;

			if ((cardData->cardExpirationDate[CardDateYearOnes]) == (termData->transactionDate[TransDateYearOnes]))
			{
				if ((cardData->cardExpirationDate[CardDateMonTens]) < (termData->transactionDate[TransDateMonTens]))
					return EXPIRED_CARD;
			}
			if ((cardData->cardExpirationDate[CardDateMonTens]) == (termData->transactionDate[TransDateMonTens]))
			{
				if ((cardData->cardExpirationDate[CardDateMonOnes]) < (termData->transactionDate[TransDateMonOnes]))
				{
					return EXPIRED_CARD;
				}
			}

			printf("Your Card is NOT Expired\n");
			return TERMINAL_OK;
		}
}

//------------------------------//

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {

	f32 amount;

	printf("Please enter the Transaction Amount: ");

	scanf("%f", &termData->transAmount);


	if ((termData->transAmount) <= 0) {
		printf("INVALID_AMOUNT\n\n");
		return INVALID_AMOUNT;
	}

	printf("The Transaction Amount is:%.2f\n\n ", termData->transAmount);
	amount= termData->transAmount;

	return	amount;
}

//------------------------------//

//------------------------------//

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{

	termData->maxTransAmount = TerminalMaxAmount;

	printf("Max Transaction Amount is:%.2f\n", termData->maxTransAmount);

	if ((termData->maxTransAmount) <= 0) {
		printf("INVALID_MAX_AMOUNT");
		return INVALID_MAX_AMOUNT;
	}


	return TERMINAL_OK;
}


EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {

	if ((termData->transAmount) > (termData->maxTransAmount)) {
		return EXCEED_MAX_AMOUNT;
	}
	
	return TERMINAL_OK;


}
