//
// Book : Version du chapitre 9 de l'ouvrage.
// "Programming -- Principles and Practice Using C++" de Bjarne Stroustrup (2ème édition : 2014)
// Commit initial : 16 janvier 2018
// Commit en cours : Exercices 5 à 9 de la page 339 à 340
// Caractères spéciaux : [ ]   '\n'   {  }   ||   ~   _     @

// Librairie indispensable sous Windows et VC++
#include "stdafx.h"


// Librairie restreinte fournie par BS
#include "std_lib_facilities.h"

// helper fonctions (définis avant la classe Book que son constructeur utilise)
bool is_ISBN_OK(string ISBN)
{
	// Vérification du format de la référence ISBN passée en paramètre
	// n1-n2-n3-x : 3 entiers et UN seul digit ou lettre
	for (int i = 0; i<ISBN.size(); i++)
		////////////////////////////////////////////////////////////////////////////////// CODE A TERMINER

		return true;
}

class Book {  
public:

// Constructeur
	Book(string i, string t, string a, string d, bool c):book_ISBN(i), book_title(t), book_author(a), book_copyright_date(d), book_checkout(c) 
	{
		if (!is_ISBN_OK(i)) throw Invalid();
	}
	
	class Invalid { };                 // to throw as exception

// non-modifying operations
string ISBN() const { return book_ISBN; }
string title() const { return book_title; }
string author() const { return book_author; }
string c_date() const { return book_copyright_date; }
bool checkout() const { return book_checkout; }

// modifying operations

private:
	string book_ISBN;
	string book_title;
	string book_author;
	string book_copyright_date;
	bool book_checkout;		// True : l'ouvrage est sorti, false: l'ouvrage est toujours à la bibliothèque

};


// -------------------------------------------------------------------------------------------------------------------------------------------------------
// member function definitions::
void is_book_out(const Book& livre) {  
// Vérification si un bouquin est sortie de la bibliothèque

	if (livre.checkout())
		cout << "L'ouvrage '" << livre.title() << "' de l'auteur '" << livre.author() << "' a été emprunté\n";
	else
		cout << "L'ouvrage '" << livre.title() << "' de l'auteur '" << livre.author() << "' est toujours à la bibliothèque\n";

}




// -------------------------------------------------------------------------------------------------------------------------------------------------------
int main()
{
	try
	{
		// A mettre dans la 1ère ligne du "main" pour afficher les caractères accentués sous la console Windows
		std::locale::global(std::locale("fr-FR"));

		Book b{ "ISBN","Géant","Steinbeck","10/10/1900",false };
		cout << "Titre : " << b.title() << "\n";
		is_book_out(b);
		keep_window_open();

		return 0;
	}
	catch (Book::Invalid&) {
		cerr << "error: le format ISBN n-n-n-x du livre est incorrect\n";
		keep_window_open("~");	// For some Windows(tm) setup
		return 1;
	}
	catch (runtime_error& e) {	// this code is to produce error messages
		cout << e.what() << '\n';
		keep_window_open("~");	// For some Windows(tm) setups
	}
	
}

/*
class Date {
public:
enum Month {
jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

class Invalid { };                 // to throw as exception

Date(int y, Month m, int d);       // check for valid date and initialize
Date();                            // default constructor
// the default copy operations are fine

// non-modifying operations:
int   day()   const { return d; }
Month month() const { return m; }
int   year()  const { return y; }

// modifying operations:
void add_day(int n);
void add_month(int n);
void add_year(int n);
private:
int   y;
Month m;
int   d;
};

// member function definitions:


Date::Date(int yy, Month mm, int dd)
: y(yy), m(mm), d(dd)
{
if (!is_date(yy, mm, dd)) throw Invalid();
}

const Date& default_date();

Date::Date()
:y(default_date().year()),
m(default_date().month()),
d(default_date().day())
{
}


*/