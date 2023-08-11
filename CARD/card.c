

#include "card.h"


#define MaxSizeofCardName    24
#define MinSizeofCardName    20
#define ExpirtionDatelenght  5
#define MaxPanLen            19
#define MinPanLen            16



EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{

	uint8_t  counter, length = 0;

	//Accepting input.

	printf("NOTE that the card holder name must be between (20_24 Characters)\n");
	printf("Please enter the Card Holder's Name: ");
	scanf("%s", &cardData->cardHolderName);

	//Initializing for loop.
	for (counter = 0; cardData->cardHolderName[counter] != '\0'; counter++)
	{
		if ((isalpha(cardData->cardHolderName[counter]) == 0)) {
			printf("Invalid form must be Alpabitic\n\n");
			return WRONG_NAME;
		}

		length++; //Counting the length.
	}

	if ((length < MinSizeofCardName) || (length > MaxSizeofCardName))
	{

		printf("Invalid form must be between (20_24 Characters)\n\n");
		return WRONG_NAME;

	}


	printf("your card holder name is :%s\n", cardData->cardHolderName);
	return CARD_OK;



}

//-------------------------//

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {


	uint8_t  counter, length = 0;

	printf("Please enter the Card expiry date in this EXACT FORM :  MM/YY\n ");
	scanf("%s", &cardData->cardExpirationDate);

	//Initializing for loop.
	for (counter = 0; cardData->cardExpirationDate[counter] != '\0'; counter++)
	{
		length++; //Counting the length.
	}

	if ((length != ExpirtionDatelenght))
	{

		printf("the  Card expiry date must be 5 characters: \n\n");
		//exit(WRONG_EXP_DATE);
		return WRONG_EXP_DATE;

	}

	if (!isdigit(cardData->cardExpirationDate[0]) || !isdigit(cardData->cardExpirationDate[1])) {
		printf("invalid form\n\n");
		return WRONG_EXP_DATE;
	}

	if ((cardData->cardExpirationDate[2]) != '/') {
		printf("invalid form\n\n");
		return WRONG_EXP_DATE;
	}

	if (!isdigit(cardData->cardExpirationDate[3]) || !isdigit(cardData->cardExpirationDate[4])) {
		printf("invalid form\n\n");
		return WRONG_EXP_DATE;
	}


	printf("Your Card Expiry Date is:%s\n", cardData->cardExpirationDate);

	return  CARD_OK;
}

//-------------------------//

EN_cardError_t getCardPAN(ST_cardData_t* cardData) {

	uint8_t  counter, length = 0;

	printf("NOTE that the primary account number must be between (16_19 Charcters)\n");
	printf("Please enter the Primary account number: ");
	scanf("%s", &cardData->primaryAccountNumber);

	for (counter = 0; cardData->primaryAccountNumber[counter] != '\0'; counter++)
	{
		if (!isdigit(cardData->primaryAccountNumber[counter])) {
			printf("invalid form must be Numeric\n\n");
			return WRONG_PAN;
		}
		length++; //Counting the length.
	}

	if ((length < MinPanLen) || (length > MaxPanLen))
	{

		printf("invalid form must be between (16_19 Characters)\n\n");
		return WRONG_PAN;

	}

	printf("the Primary account number :%s\n\n", cardData->primaryAccountNumber);
	return  CARD_OK;
}






