#include <iostream>
#include <vector>
#include <conio.h>
#include <cassert>
#include <string>
#include <cstdlib>
#include <algorithm>

#pragma region "Error Messeges"
//GENERAL FUNCTION FOR WHEN INCORRECT DATA TYPE IS ENTERED
void InputNumberDataTypeError() {
	system("cls");
	std::cout << "Invalid input. Please enter a valid Number.\n";
	std::cout << "PRESS ENTER TO TRY AGAIN";
	_getch();
	system("cls");
}

void WrongMenuOptionSelection() {
	std::cout << "Invalid choice. Please choose from one of the menu options.\n";
	std::cout << "PRESS ENTER TO TRY AGAIN";
	_getch();
	system("cls");
}

#pragma endregion



#pragma region "Main Code"

//GETS THE NUMBER OF JOURNEYS FROM THE USER TO USE FOR THE LOOP TO TAKE THE JOURNEY COSTS
int getJourneyNum() {

	std::string JourneyNumInput;
	int ValidJourneyNum;
	bool ValidJourneyInput = false;
	while (ValidJourneyInput == false)
	{
		std::cout << "Please enter the number of journeys you have taken: ";
		std::cin >> JourneyNumInput;
		system("cls");

		try
		{
			ValidJourneyNum = std::stoi(JourneyNumInput); // Convert input to an integer
			if (ValidJourneyNum < 1)
			{
				InputNumberDataTypeError();
				continue;
			}
			return ValidJourneyNum;

		}
		catch (std::invalid_argument& e) {
			InputNumberDataTypeError();
		}
	}
}
//GETS THE TYPE OF CLAIM FROM THE USER WHEATHER IT IS TRAVEL AND EXPENSE OR JUST TRAVEL
int getClaimType() {
	std::string ClaimTypeInput;
	int ValidClaimType;
	bool ValidClaimTypeSel = false;
	while (!ValidClaimTypeSel)
	{
		std::cout << "Please select a claim option from below? \n";
		std::cout << "\n";
		std::cout << "1. travel and expenses\n";
		std::cout << "2. travel\n";
		std::cout << "Choice: ";
		std::cin >> ClaimTypeInput;
		try
		{
			ValidClaimType = std::stoi(ClaimTypeInput)
				; // TRYS TO CONVERT INPUT TO INTEGER TO VALIDIDATE USER INPUT
			system("cls");
			if (ValidClaimType != 1 && ValidClaimType != 2)
			{
				WrongMenuOptionSelection();
				continue;
			}
			else
			{
				return ValidClaimType;
			}
		}
		catch (std::invalid_argument& e)
		{
			InputNumberDataTypeError();
		}
	}
	system("cls");
}
//GETS THE USERS TRAVEL COSTS
int getTravelCosts(int loopCounter) {
	std::string TravelCostInput;
	int ValidTravelCost;
	bool ValidTravelCostInput = false;
	while (ValidTravelCostInput == false) {
		if (loopCounter == 1) {

			std::cout << "What were the travel costs for your first journey?: ";
			std::cin >> TravelCostInput;
			system("cls");
			try
			{
				ValidTravelCost = std::stoi(TravelCostInput);
				if (ValidTravelCost <= 0)
				{
					InputNumberDataTypeError();
					continue;
				}
				return ValidTravelCost;
			}
			catch (const std::exception&)
			{
				InputNumberDataTypeError();
			}
		}
		else
		{
			std::cout << "What were the travel costs for journey number " << loopCounter << "?: ";
			std::cin >> TravelCostInput;
			system("cls");
			try
			{
				ValidTravelCost = std::stoi(TravelCostInput);
				if (ValidTravelCost <= 0)
				{
					InputNumberDataTypeError();
					continue;
				}
				return ValidTravelCost;
			}
			catch (const std::exception&)
			{
				InputNumberDataTypeError();
			}
		}

	}


}

int getExpenses(int loopCounter) {
	std::string ExpensesInput;
	int ValidExpensesInputVal;
	bool ValidExpensesInput = false;
	while (ValidExpensesInput == false) {
		if (loopCounter == 1) {
			std::cout << "What were the Expenses for your first journey?: ";
			std::cin >> ExpensesInput;
			system("cls");
			try
			{
				ValidExpensesInputVal = std::stoi(ExpensesInput);
				if (ValidExpensesInputVal <= 0)
				{
					InputNumberDataTypeError();
					continue;
				}
				return ValidExpensesInputVal;
			}
			catch (const std::exception&)
			{
				InputNumberDataTypeError();
			}
		}
		else
		{
			std::cout << "What were the Expenses for journey number " << loopCounter << " ?: ";
			std::cin >> ExpensesInput;
			system("cls");
			try
			{
				ValidExpensesInputVal = std::stoi(ExpensesInput);
				if (ValidExpensesInputVal <= 0)
				{
					InputNumberDataTypeError();
					continue;
				}
				return ValidExpensesInputVal;
			}
			catch (const std::exception&)
			{
				InputNumberDataTypeError();
			}
		}
	}

}

int reclaimableTax(int TravelCost) {
	int reclaimableTax = TravelCost * 0.2;
	return reclaimableTax;
}

void showResultsKeyTemplate(int ClaimType) {
	std::cout << "Key:\n";
	std::cout << "---------------------------------------------\n";
	std::cout << "T = Travel E = Expenses C=Company tax claim\n";
	std::cout << "\n";
	std::cout << "Travel costs total:\n";
	std::cout << "---------------------------------------------\n";
	std::cout << "T   E   Total C\n";
}

int employeesClaim(int nonRefundableTotal, std::vector<std::vector<int>>& totalJourneyCosts) {
	int elementCount = 0;
	int rowCount = 0;
	for (const auto& row : totalJourneyCosts) {
		rowCount += 1;
		for (const auto& element : row) {
			elementCount += 1;
			if (elementCount == 2) {
				if (element > 50) {
					nonRefundableTotal += element - 50;
					return nonRefundableTotal;
				}
			}
		}
		elementCount = 0;
	}
}

void claimableExpense(int& journeyExpenseCosts, int& claimableExpenses) {
	if (journeyExpenseCosts > 50) {
		claimableExpenses += 50;
	}
	else
	{
		claimableExpenses += journeyExpenseCosts;
	}
}
int main()
{
	int journeyNum = getJourneyNum();
	int claimType = getClaimType();


	if (claimType == 1)
	{
		std::vector<std::vector<int>> totalJourneyCosts;
		int journeyTravelCosts;
		int journeyExpenseCosts;
		int claimableExpenses = 0;
		for (size_t i = 1; i <= journeyNum; i++)
		{

			journeyTravelCosts = getTravelCosts(i);
			journeyExpenseCosts = getExpenses(i);

			claimableExpense(journeyExpenseCosts, claimableExpenses);

			std::vector <int> currentJourney = { journeyTravelCosts,journeyExpenseCosts };
			totalJourneyCosts.push_back(currentJourney);
		}

		showResultsKeyTemplate(claimType);
		int previousElement = 0;
		int rowCount = 1;
		int elementCount = 0;
		int expensesTotal = 0;
		int travelTotal = 0;
		int totalCost = 0;
		std::vector<int> LargestPaymentCalcVector;
		for (const auto& row : totalJourneyCosts) {
			for (const auto& element : row) {
				elementCount += 1;
				LargestPaymentCalcVector.push_back(element);
				if (elementCount == 1) {
					std::cout << element << " ";
				}
				else {
					int travelCost = element + previousElement;
					std::cout << element << " " << travelCost << "   " << reclaimableTax(travelCost);
				}
				previousElement = element;
				if (elementCount == 2)
				{
					expensesTotal += element;
				}
				else if (elementCount == 1) {
					travelTotal += element;
				}
				totalCost += element;
			}
			std::cout << std::endl;
			elementCount = 0;
		}
		std::cout << "Expenses Total: " << expensesTotal << "\n";
		std::cout << "\n";
		std::cout << "Employees will be payed back 100% of travel costs which is " << travelTotal << "\n";
		std::cout << "\n";
		std::cout << "Employees will be payed back up to 50 pounds of their expenses anything over that will have to be covered by the employee\n";
		std::cout << "\n";
		std::cout << "The claimable amount is : " << claimableExpenses << "\n";
		std::cout << "\n";
		int nonRefundableTotal = 0;
		employeesClaim(nonRefundableTotal, totalJourneyCosts);

		if (nonRefundableTotal < 0) {
			std::cout << "there is no non-refundable costs involved in these journeys";
		}
		else {
			std::cout << "The non-refundable amount is " << nonRefundableTotal;
		}
		double AveragePayment = totalCost / journeyNum;
		std::cout << "\nThe average payment is " << AveragePayment;

		int MaxPayment = *std::max_element(LargestPaymentCalcVector.begin(), LargestPaymentCalcVector.end());
		std::cout << "\nThe max payment is " << MaxPayment;
	}
	else if (claimType == 2) {

		std::vector<int>totalJourneyCosts;
		int journeyTravelCosts;
		int claimableExpenses = 0;
		for (size_t i = 1; i <= journeyNum; i++)
		{

			journeyTravelCosts = getTravelCosts(i);
			totalJourneyCosts.push_back(journeyTravelCosts);
		}
		int elementCount = 1;
		for (const auto& element : totalJourneyCosts) {
			std::cout << "Journey Number " << elementCount << "\n";
			std::cout << "----------------------------------\n";
			std::cout << "Travel: " << element << "\n";
			std::cout << "Company tax deduction: " << reclaimableTax(element) << "\n";
			std::cout << "Employees will be payed back 100% of travel costs which is " << element << "\n";
			std::cout << "\n";
			elementCount += 1;
		}


	}
	_getch();
}
#pragma endregion
