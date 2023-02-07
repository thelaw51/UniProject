#include <iostream>
#include <vector>


int getJourneyNum() {
	int JourneyNum;
	std::cout << "how many journeys have you taken?: ";
	std::cin >> JourneyNum;
	return JourneyNum;
}

int getClaimType() {
	int claimType;
	std::cout << "Please select a claim option from below? \n";
	std::cout << "\n";
	std::cout << "1. travel and expenses\n";
	std::cout << "2. travel\n";
	std::cout << "Choice: ";
	std::cin >> claimType;
	return claimType;
}
int getTravelCosts() {
	int journeyTravelCosts;
	std::cout << "What were the travel costs for your first journey?: ";
	std::cin >> journeyTravelCosts;
	return journeyTravelCosts;
}

int getExpenses() {
	int journeyExpenseCosts;
	std::cout << "What were the Expenses for your first journey?: ";
	std::cin >> journeyExpenseCosts;
	return journeyExpenseCosts;
}

int reclaimableTax(int TotalCost) {
	int reclaimableTax = TotalCost * 0.2;
	return reclaimableTax;
}

void showResultsTemplate() {
	std::cout << "\n";
	std::cout << "Key:\n";
	std::cout << "---------------------------------------------\n";
	std::cout << "T = Travel E = Expenses C=Company tax claim\n";
	std::cout << "\n";
	std::cout << "Travel costs total:\n";
	std::cout << "---------------------------------------------\n";
	std::cout << "T   E   Total C\n";
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
			if (i == 1) {
				journeyTravelCosts = getTravelCosts();
				journeyExpenseCosts = getExpenses();
				
				std::vector <int> firstJourney = { journeyTravelCosts,journeyExpenseCosts };
				totalJourneyCosts.push_back(firstJourney);
				if (journeyExpenseCosts > 50) {
					claimableExpenses += 50;
				}
				else
				{
					claimableExpenses += journeyExpenseCosts;
				}
			}
			else {
				std::cout << "What were the travel costs for journey number " << i << "?: ";
				std::cin >> journeyTravelCosts;

				std::cout << "What were the Expenses for journey number " << i << "?: ";
				std::cin >> journeyExpenseCosts;

				std::vector <int> currentJourney = { journeyTravelCosts,journeyExpenseCosts };
				totalJourneyCosts.push_back(currentJourney);
				if (journeyExpenseCosts > 50) {
					claimableExpenses += 50;
				}
				else
				{
					claimableExpenses += journeyExpenseCosts;
				}
			}
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
		std::cout << "Employees will be payed back 100% of travel costs which is " << travelTotal << "\n";
		std::cout << "Employees will be payed back up to 50 pounds of their expenses anything over that will have to be covered by the employee\n";
		std::cout << "The claimable amount is : " << claimableExpenses << "\n";

		int nonRefundableTotal = 0;
		elementCount = 0;
		rowCount = 0;
		for (const auto& row : totalJourneyCosts) {
			rowCount += 1;
			for (const auto& element : row) {
				elementCount += 1;
				if (elementCount == 2) {
					if (element > 50) {
						nonRefundableTotal += element - 50;

					}
				}
			}
			elementCount = 0;
		}
		if (nonRefundableTotal < 0) {
			std::cout << "there is no non-refundable costs involved in these journeys";
		}
		else {
			std::cout << "The non-refundable amount is " << nonRefundableTotal;
		}

	}
	else if (claimType == 2) {
	}
}