#include "../includes_usr/fileIO.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "../includes_usr/datastructures.h"
#include <vector>
using namespace std;

/**
    CPSC 327 Proj3, fileIO.cpp
    Purpose: performs the I/O functions for library.cpp

    @author Anthony Russell
    @version 02/14/2019
*/

/* clears, then loads books from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries in books
 * 			SUCCESS if all data is loaded
 * */

int loadBooks(std::vector<book> &books, const char* filename) {
	ifstream myfile;
	myfile.open(filename);
	if (myfile.is_open() == false) {
		return COULD_NOT_OPEN_FILE;
	} else {

		string tempToken;

		while (getline(myfile, tempToken)) {

			book newBook;
			stringstream ss(tempToken);
			string substring;
			vector<string> extracted;
			while (getline(ss, substring, ',')) {
				extracted.push_back(substring);
			}
			if (extracted.size() != 0) {
				newBook.book_id = atoi(extracted[0].c_str());
				newBook.title = extracted[1];
				newBook.author = extracted[2];
				newBook.state = book_checkout_state(atoi(extracted[3].c_str()));
				newBook.loaned_to_patron_id = atoi(extracted[4].c_str());

				books.push_back(newBook);
			}
		}

		if (myfile.is_open()) {
			myfile.close();
		}
		if (books.size() == 0) {
			return NO_BOOKS_IN_LIBRARY;
		} else {
			return SUCCESS;
		}
	}
}

/* serializes books to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries books (do not create file)
 * 			SUCCESS if all data is saved
 * */
int saveBooks(std::vector<book> &books, const char* filename) {
	ofstream myfile;
	myfile.open(filename);
	if (myfile.is_open() == false) {
		return COULD_NOT_OPEN_FILE;
	} else if (books.size() == 0) {
		return NO_BOOKS_IN_LIBRARY;
	} else {
		int max = books.size();
		for (int i = 0; i < max; i++) {
			;
			string toWrite = to_string(books[i].book_id) + "," + books[i].title
					+ "," + books[i].author + "," + to_string(books[i].state)
					+ "," + to_string(books[i].loaned_to_patron_id);
			myfile << toWrite;
			myfile << endl;
		}
		if (myfile.is_open()) {
			myfile.close();
		}
		return SUCCESS;
	}

}

/* clears, then loads patrons from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons
 * 			SUCCESS if all data is loaded
 * */
int loadPatrons(std::vector<patron> &patrons, const char* filename) {

	ifstream myfile;
	myfile.open(filename);
	if (myfile.is_open() == false) {
		return COULD_NOT_OPEN_FILE;
	} else {

		string tempToken;

		while (getline(myfile, tempToken)) {
			patron newPatron;
			stringstream ss(tempToken);
			string substring;
			vector<string> extracted;
			while (getline(ss, substring, ',')) {
				extracted.push_back(substring);
			}
			if (extracted.size() != 0) {
				newPatron.patron_id = atoi(extracted[0].c_str());
				newPatron.name = extracted[1];
				newPatron.number_books_checked_out = atoi(extracted[2].c_str());

				patrons.push_back(newPatron);
			}
		}

		if (myfile.is_open()) {
			myfile.close();
		}
		if (patrons.size() == 0) {
			return NO_PATRONS_IN_LIBRARY;
		} else {
			return SUCCESS;
		}
	}
}

/* serializes patrons to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons  (do not create file)
 * 			SUCCESS if all data is saved
 * */
int savePatrons(std::vector<patron> &patrons, const char* filename) {
	ofstream myfile;
	myfile.open(filename);
	if (myfile.is_open() == false) {
		return COULD_NOT_OPEN_FILE;
	} else if (patrons.size() == 0) {
		return NO_BOOKS_IN_LIBRARY;
	} else {
		int max = patrons.size();
		for (int i = 0; i < max; i++) {
			;
			string toWrite = to_string(patrons[i].patron_id) + ","
					+ patrons[i].name + ","
					+ to_string(patrons[i].number_books_checked_out);
			myfile << toWrite;
			myfile << endl;
		}
		if (myfile.is_open()) {
			myfile.close();
		}
		return SUCCESS;
	}
}
