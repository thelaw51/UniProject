#include <iostream>
#include <vector>
#include <conio.h>
#include <cassert>
#include <string>
#include <cstdlib>

//GETS THE NUMBER OF JOURNEYS FROM THE USER TO USE FOR THE LOOP TO TAKE THE JOURNEY COSTS
int getJourneyNum() {

	std::string JourneyNumInput;
	int ValidJourneyNum;
	bool ValidJourneyInput = false;
	while (ValidJourneyInput == false)
	{
	std::cout << "Please enter the number of journeys you have taken: ";
	std::cin >> JourneyNumInput;

	try {
		ValidJourneyNum = std::stoi(JourneyNumInput); // Convert input to an integer
		ValidJourneyInput = true;
		system("cls");
		return ValidJourneyNum;
	}
	catch (std::invalid_argument& e) {
		std::cout << "Invalid input. Please enter a valid integer.\n";
		std::cout << "PRESS ENTER TO TRY AGAIN";
		_getch();
		system("cls");
	}
	}
}
//GETS THE TYPE OF CLAIM FROM THE USER WHEATHER IT IS TRAVEL AND EXPENSE OR JUST TRAVEL
int getClaimType() {
	int claimType;
	std::cout << "Please select a claim option from below? \n";
	std::cout << "\n";
	std::cout << "1. travel and expenses\n";
	std::cout << "2. travel\n";
	std::cout << "Choice: ";
	std::cin >> claimType;
	system("cls");
	return claimType;
}
//GETS CALL THROUGH OUT THE
int getTravelCosts(int loopCounter) {
	int journeyTravelCosts;
	if (loopCounter == 1) {
		
		std::cout << "What were the travel costs for your first journey?: ";
		std::cin >> journeyTravelCosts;
		system("cls");
		return journeyTravelCosts;
	}
	else
	{
		std::cout << "What were the travel costs for journey number " << loopCounter << "?: ";
		std::cin >> journeyTravelCosts;
		system("cls");
		return journeyTravelCosts;
	}
	
}

int getExpenses(int loopCounter) {
	int journeyExpenseCosts;
	if (loopCounter == 1) {
		std::cout << "What were the Expenses for your first journey?: ";
		std::cin >> journeyExpenseCosts;
		system("cls");
		return journeyExpenseCosts;
	}
	else 
	{
		std::cout << "What were the Expenses for journey number " << loopCounter << "?: ";
		std::cin >> journeyExpenseCosts;
		system("cls");
		return journeyExpenseCosts;
	}
	
}

int reclaimableTax(int TotalCost) {
	int reclaimableTax = TotalCost * 0.2;
	return reclaimableTax;
}

void showResultsTemplate() {
	std::cout << "Key:\n";
	std::cout << "---------------------------------------------\n";
	std::cout << "T = Travel E = Expenses C=Company tax claim\n";
	std::cout << "\n";
	std::cout << "Travel costs total:\n";
	std::cout << "---------------------------------------------\n";
	std::cout << "T   E   Total C\n";
}

int employeesClaim(int nonRefundableTotal,std::vector<std::vector<int>> &totalJourneyCosts) {
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

void claimableExpense(int &journeyExpenseCosts,int &claimableExpenses) {
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
				
				claimableExpense(journeyExpenseCosts,claimableExpenses);
	
				std::vector <int> currentJourney = { journeyTravelCosts,journeyExpenseCosts };
				totalJourneyCosts.push_back(currentJourney);
		}

		showResultsTemplate();
		int previousElement = 0;
		int rowCount = 0;
		int elementCount = 0;
		int expensesTotal = 0;
		int travelTotal = 0;
		for (const auto& row : totalJourneyCosts) {
			rowCount += 1;
			for (const auto& element : row) {
				elementCount += 1;
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
		employeesClaim(nonRefundableTotal,totalJourneyCosts);

		if (nonRefundableTotal < 0) {
			std::cout << "there is no non-refundable costs involved in these journeys";
		}
		else {
			std::cout << "The non-refundable amount is " << nonRefundableTotal;
		}

	}
	else if (claimType == 2) {
	}
	_getch();
}