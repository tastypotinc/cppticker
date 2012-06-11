//============================================================================
// Name        : cppticker.cpp
// Author      : Matthew Frost
// Version     : 0.1
// Copyright   : "BEER-WARE LICENSE"
// Description : Stock ticker
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Instrument.h"
using namespace std;

void parseData(std::string input, Instrument &i);
double parseQuote(std::string rawData, std::string cid);
std::string parseCID(std::string rawData);
std::string parseSymbol(std::string rawData);

int main() {

	ifstream in("msft");
	Instrument i;

	if (!in) {
		cerr << "Error reading from file" << endl;
	} else {
		while(in) {
			std::string input;
			getline(in, input);
			parseData(input, i);
		}
	}
	in.close();

	cout << "Symbol:\t" << i.getSymbol() << endl;
	cout << "CID:\t" << i.getCID() << endl;
	cout << "Last:\t" << "$" << i.getLast() << endl;

	return 0;
}

void parseData(std::string input, Instrument &i) {
	if (i.getSymbol().length() == 0) {
		std::string sym = parseSymbol(input);
		if (sym.length() > 0) {
			i.setSymbol(sym);
		}
	}

	if (i.getCID().length() == 0) {
		std::string cid = parseCID(input);
		if (cid.length() > 0) {
			i.setCID(cid);
		}
	}

	if (i.getLast() == 0.0) {
		double quote = parseQuote(input, i.getCID());
		if (quote > 0.0) {
			i.setLast(quote);
		}
	}
}

std::string parseCID(std::string rawData) {
	std::string cid = "";
	std::string cidLine = "setCompanyId";
	size_t foundCID = rawData.find(cidLine);
	if (foundCID != string::npos) {
		size_t start = rawData.find("(");
		size_t end = rawData.find(")", start);
		if (start != string::npos && end != string::npos) {
			cid = rawData.substr(start+1, (end-start-1));
		}
	}

	return cid;
}

double parseQuote(std::string rawData, std::string cid) {
	double quote = 0.0;
	std::string quoteLine = string("ref_")+cid+string("_l\">");
	size_t foundQuote = rawData.find(quoteLine);
	if (foundQuote != string::npos) {
		size_t start = rawData.find(quoteLine);
		std::string endString = "</span>";
		size_t end = rawData.find(endString, start);
		if (start != string::npos && end != string::npos) {
			std::string quoteString = rawData.substr(start+quoteLine.length(), (end-start-quoteLine.length()));
			std::istringstream dbl(quoteString);
			dbl >> quote;
		}
	}
	return quote;
}

std::string parseSymbol(std::string rawData) {
	std::string symbol = "";
	std::string tickerLine = "var _ticker =";
	size_t foundTicker = rawData.find(tickerLine);
	if (foundTicker != string::npos) {
		size_t start = rawData.find(":");
		size_t end = rawData.find("'", start);
		if (start != string::npos && end != string::npos) {
			symbol = rawData.substr(start+1, (end-start-1));
		}
	}

	return symbol;
}
