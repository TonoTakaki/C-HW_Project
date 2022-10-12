//
//  main.cpp
//  BinomialTree
//
//

#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

enum CALL_PUT {Call, Put};
enum AMER_EURO {European, American};

int CRRBinomialTree(
    CALL_PUT    callOrPut,                /* (I) put or call flag (use Call or Put) */
    AMER_EURO    amerOrEuro,                /* (I) option type (use European, American) */
    double        spotPrice,                /* (I) spot price of underlying */
    double        strike,                    /* (I) strike price of option */
    double        maturity,                /* (I) maturity of option in years */
    double        vol,                    /* (I) annual volatility of underlying */
    double        rate,                    /* (I) annual continuous compounded discount rate */
    int            nStep,                    /* (I) number of steps in tree */
    double        *value)                    /* (O) option value */
/*-----------------------------------------------------------------------------
** FUNCTION:    CRRBinomialTree.
**
** DESCRIPTION:    Calculates the price of an option using the Cox, Ross and Rubinstein
**                binomial tree model.
**
** RETURNS:        SUCCESS and the premium, otherwise FAILURE.
**
**---------------------------------------------------------------------------*/
{
    double deltaT = maturity / nStep;
    double discount = exp(-rate * deltaT);
    double u = exp(vol * sqrt(deltaT));
    double d = 1/u;
    double p = (exp(rate * deltaT)-d)/(u-d);
    bool FAILURE = false, SUCCESS = true;
    double premium;
    
    if (nStep <= 0)
    {
        cout << "CRRBinomialTree: Negative number of steps." << endl;
        return FAILURE;
    }
    
    if (spotPrice <= 0.0 || strike <= 0.0 || maturity < 0.0 || vol < 0.0 || rate < 0.0)
    {
        cout << "CRRBinomialTree: Invalid input detected." << endl;
        return FAILURE;
    }
    
//    *value = 0.0;
    
    // TO-BE-COMPLETED
    vector <double> prices(nStep+1);
    
    // We rank the price from the smallest to the largest
    // The prices are the price of stock at time T
    prices[0] = spotPrice * pow(d, nStep);
    for (int i = 1; i <=nStep; ++i){
        prices[i] = u*u*prices[i-1];
    }
    
    // Calculate the call option values at time T
    if (callOrPut == Call){
        vector<double> call_values(nStep+1);
        for (int i = 0; i <= nStep; ++i){
            call_values[i] = max(0.0, (prices[i] - strike));
        }
        
        // Using Binomial Tree to calculate the option price
        for (int step = nStep - 1; step >= 0; --step){
            for (int i=0; i<=step; ++i){
                call_values[i] = (p*call_values[i+1] + (1-p)*call_values[i])*discount;
            }
        }
        premium = call_values[0];
        
    }
    else if (callOrPut == Put && amerOrEuro == European) {
        vector<double> put_values(nStep+1);
        for (int i = 0; i <= nStep; ++i){
            put_values[i] = max(0.0, (strike - prices[i]));
        }
        for (int step = nStep - 1; step >= 0; --step){
            for (int i=0; i<=step; ++i){
                put_values[i] = (p*put_values[i+1] + (1-p)*put_values[i])*discount;
            }
        }
        premium = put_values[0];
    }
    else if (callOrPut == Put && amerOrEuro == American) {
        vector<double> put_values(nStep+1);
        for (int i = 0; i <= nStep; ++i){
            put_values[i] = max(0.0, (strike - prices[i]));
        }
        for (int step = nStep - 1; step >= 0; --step){
            for (int i=0; i<=step; ++i){
                put_values[i] = max((strike - prices[i]*u),(p*put_values[i+1] + (1-p)* put_values[i]) * discount);
                prices[i] = prices[i]*u;
            }
        }
        premium = put_values[0];
    }
    
    cout << "The premium of the option is "<<premium << "." <<endl;
    return SUCCESS;
}

int main() {
    cout << CRRBinomialTree(Put, American, 100, 100, 1, 0.2, 0.05, 10, 0) <<endl;
}
