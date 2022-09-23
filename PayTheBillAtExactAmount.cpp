#include <iostream>

using namespace std;


int main() {
int        n10Dollar, n20Dollar, n50Dollar, n100Dollar, n500Dollar, bill,temp, rest;
int        c10, c20, c50, c100, c500;

// Original number of coins in pocket
cout << "Original number of bills in wallet:" << endl;
cout << "Number of 10-Dollar bills: "; cin >> n10Dollar;
cout << "Number of 20-Dollar bills: "; cin >> n20Dollar;
cout << "Number of 50-Dollar bills: "; cin >> n50Dollar;
cout << "Number of 100-Dollar bills: "; cin >> n100Dollar;
cout << "Number of 500-Dollar bills: "; cin >> n500Dollar;
cout << endl;

// First we need to know the sum of money we have
int original_money = n10Dollar + n20Dollar*2 + n50Dollar*5 + n100Dollar*10 + n500Dollar*50;

// Bill to pay.
// Assume bill amount is a whole integer multiples of 10
cout << "Bill Amount : "; cin >> bill;
cout << endl;
bill = bill / 10;

// Fill in the code to calculate payment in terms of number of x-Dollar bills.
// If not enough money, number of x-Dollar bills in payment should all be 0s.
// Bill should be settled in exact amount; otherwise, number of x-Dollar bills
// in payment should all be 0s.

// Second, we pay the bill from the largest value of face value of dollar
// from 500-dollar to 10-dollar.

// If the the total money we have is not enough,
// all numbers should be 0.
if (bill > original_money) {
	c10 = 0; c20 = 0; c50 = 0; c100 = 0; c500 = 0;
}
else{
	// We define temp as a variable that does the comparison between
	// the rest of bill and the total value of x-Dollar bills
	temp = bill - 50 * n500Dollar;
	if (temp < 0 and bill >= 50) {
		// When the x-Dollar bills are greater, we only take the integer part
		c500 = static_cast<int>(bill/50);
	}
	if (temp < 0 and bill < 50) {
		// When the bills are below the x face value, we just drop x-dollar bills
		c500 = 0;
	}
	if (temp >= 0) {
		// When x-Dollar bills are not enough, we first all in
		c500 = n500Dollar;
	}
	
	// Then we minus the bills we have paid to get the rest of bill
	rest = bill - 50 * c500;
	
	// Do the comparison again
	temp = rest - 10 * n100Dollar;

	if (temp < 0 and rest >= 10) {
		c100 = static_cast<int>(rest/10);
	}
	if (temp < 0 and rest < 10) {
		c100 = 0;
	}
	if (temp >= 0) {
		c100 = n100Dollar;
	}
	rest = rest - 10 * c100;
	
	temp = rest - 5 * n50Dollar;
	if (temp < 0 and rest >= 5) {
		c50 = static_cast<int>(rest/5);
	}
	if (temp < 0 and rest < 5) {
		c50 = 0;
	}
	if (temp >= 0) {
		c50 = n50Dollar;
	}
	rest = rest - 5 * c50;
	
	temp = rest - 2*n20Dollar;
	if (temp < 0 and rest >= 2) {
		c20 = static_cast<int>(rest/2);
	}
	if (temp < 0 and rest < 2) {
		c20 = 0;
	}
	if (temp >= 0) {
		c20 = n20Dollar;
	}
	rest = rest - 2 * c20;
	
	temp = rest - n10Dollar;
	
	// If the balance is 0, it is done
	if (temp <= 0) {
		c10 = static_cast<int>(rest);
	}
	
	// If the balance is not 0, we can do some make-ups
	if (temp > 0) {
		// We put in all the 10-Dollar bills
		c10 = n10Dollar;
		// Because 20 is not the multiplier of 50
		// we need to reconsider the combination of 50 and 20-Dollar bills
		// For example, if the leftover is 10, and we have put in extra 1 50-Dollar bill
		// and we still have 3 more 20-Dollar bills, we can take out 1 50-Dollar bill and
		// put in extra 3 20-Dollar bills
		if (n20Dollar >= 3 and c50 >= 1 and n20Dollar > c20 + 2.5) {
			rest = rest + 5;
			c50 = c50 - 1;
			// It is important to add the former c20
			// because the new rest have excluded the 20-Dollar we put in before
			c20 = c20 + static_cast<int>(rest/2);
		}
		
		// If we have 110 left, according to the design of the system,
		// it will put in 100 first, but if we don't have 10-Dollar bills,
		// the outcomes will all be 0s. So we need to take out 1 100-Dollar bill,
		// and reconsider the combination of 50 and 20-Dollar bills
		if (n20Dollar >= 3 and c100 >= 1 and n50Dollar >= c50 + 1 and n20Dollar > c20 + 2.5) {
			rest = rest + 5;
			c100 = c100 - 1;
			c50 = c50 + 1;
			c20 = c20 + static_cast<int>(rest/2);
		}
		if (n20Dollar <3) {
			c10 = 0; c20 = 0; c50 = 0; c100 = 0; c500 = 0;
		}
	}
}

cout << "Payment:" << endl;
cout << "Number of 10-Dollar bills: " << c10 << endl;
cout << "Number of 20-Dollar bills: " << c20 << endl;
cout << "Number of 50-Dollar bills: " << c50 << endl;
cout << "Number of 100-Dollar bills: " << c100 << endl;
cout << "Number of 500-Dollar bills: " << c500 << endl;
return 0;
}
