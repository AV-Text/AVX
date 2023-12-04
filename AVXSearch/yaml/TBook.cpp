///////////////////////////////////////////////////////////
//  TBook.cpp
//  Implementation of the Class TBook
//  Created on:      29-Nov-2023 11:27:00 PM
//  Original author: Me
///////////////////////////////////////////////////////////

#include "TBook.h"
#include <map>

TBook::TBook(byte num)
{
	this->book_num = (num >= 1 && num <= 66) ? num : 0;

	// TO DO (TODO): call AVXText to fill other properties
}

TBook::~TBook(){

}

std::map<byte,TChapter*> TBook::fetch_results(){

	return this->chapters;
}