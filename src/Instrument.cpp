/*
 * Instrument.cpp
 *
 *  Created on: Jun 10, 2012
 *      Author: frost
 */

#include "Instrument.h"
#include <string>
#include <iostream>
#include <iomanip>

Instrument::Instrument() {
	symbol = "";
	last = "";
	change = "";
	changePercent = "";
}

void Instrument::setSymbol(std::string symbol) {
	size_t hasDot = symbol.find(".");
	if (hasDot != std::string::npos) {
		this->symbol = symbol.substr(hasDot+1);
	} else {
		this->symbol = symbol;
	}
}

void Instrument::setLast(std::string last) {
	this->last = last;
}

void Instrument::setChange(std::string change) {
	this->change = change;
}

void Instrument::setChangePercent(std::string changePercent) {
	if (changePercent.length() > 0) {
		this->changePercent = changePercent + "%";
	}
}

std::string Instrument::getSymbol() {
	return symbol;
}

std::string Instrument::getLast(){
	return last;
}

std::string Instrument::getChange(){
	return change;
}

std::string Instrument::getChangePercent(){
	return changePercent;
}

Instrument::~Instrument() {

}

bool isPositive(const std::string& change) {
	size_t plus = change.find("+");
	if (plus != std::string::npos) {
		return true;
	} else {
		return false;
	}
}

std::ostream& operator<<(std::ostream& out, const Instrument& i) {
	out << std::setw(6) << std::left << i.symbol << std::right << std::setw(10) << i.last;
	if (isPositive(i.change)) {
		out << "\033[1;32m" << std::setw(10) << i.change << std::setw(8) << i.changePercent;
	} else {
		out << "\033[1;31m" << std::setw(10) << i.change << std::setw(8) << i.changePercent;
	}
	out << "\033[0m";
	return out;
}

