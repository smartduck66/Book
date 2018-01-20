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
	// n1-n2-n3-x : 3 entiers entre 1 et 5 digits, séparés par un tiret, et UN seul digit ou lettre
	
	regex pat{R"(\d{1,5}-\d{1,5}-\d{1,5}-\w)"};

	return regex_match(ISBN,pat);
}

class Book {  
public:
	enum Genre {
		fiction = 0, nonfiction, periodical, biography, children
	};

	// Constructeur par défaut
	Book() { "", "", "", 0, "", false; };
		
	// Constructeur
	Book(string i, string t, string a, Genre g,string d, bool c):book_ISBN(i), book_title(t), book_author(a), book_genre(g), book_copyright_date(d), book_checkout(c) 
	{
		if (!is_ISBN_OK(i)) throw Invalid();
	}
	
	class Invalid { };                 // to throw as exception

// non-modifying operations
string ISBN() const { return book_ISBN; }
string title() const { return book_title; }
string author() const { return book_author; }
Genre genre() const { return book_genre; }
string c_date() const { return book_copyright_date; }
bool checkout() const { return book_checkout; }

// modifying operations
// none ***************

private:
	string book_ISBN;
	string book_title;
	string book_author;
	Genre  book_genre;
	string book_copyright_date;
	bool book_checkout;		// True : l'ouvrage est sorti, false: l'ouvrage est toujours à la bibliothèque

};


// -------------------------------------------------------------------------------------------------------------------------------------------------------
// Helper function definitions et redéfinition d'opérateurs pour la classe Book **************************************************************************
void is_book_out(const Book& livre) {  
// Vérification si un bouquin est sortie de la bibliothèque

	cout << "L'ouvrage '" << livre.title() << "' de l'auteur '" << livre.author()<< (livre.checkout() ? "' a été emprunté\n" : "' est toujours à la bibliothèque\n");

}

bool operator==(const Book& livre1, const Book& livre2)
{
	return livre1.ISBN() == livre2.ISBN();
}

bool operator!=(const Book& livre1, const Book& livre2)
{
	return !(livre1 == livre2);
}

ostream& operator<<(ostream& os, const Book& livre)
{
	vector<string>genre = { "fiction", "non fiction", "periodical", "biography", "children" };
	return os << '(' << livre.title()<< ',' << livre.author()<< ',' <<genre[livre.genre()] << ',' << livre.ISBN()<< ')';
}
// ------------------------------------------------------------------------------------------------------------------------------------------****************

// helper fonctions (définis avant la classe Patron que son constructeur utilise)
bool is_CN_OK(string CardNumber)
{
	// Vérification du format du numéro de la carte d'adhérent passé en paramètre : 6 chiffres

	regex pat{ R"(\d{6})" };

	return regex_match(CardNumber, pat);
}

class Patron {
public:
	
	// Constructeur par défaut
	Patron() { "", "", 0, false; };
	
	// Constructeur
	Patron(string u, string c, int l, bool o) :patron_username(u), patron_cardnumber(c), patron_libraryfees(l), patron_owefees(o)
	{
		if (!is_CN_OK(c)) throw Invalid();
	}

	class Invalid { };                 // to throw as exception

	// non-modifying operations
	string username() const { return patron_username; }
	string cardnumber() const { return patron_cardnumber; }
	int libraryfees() const { return patron_libraryfees; }
	bool owefees() const { return patron_owefees; }

	// modifying operations
	// none ***************

private:
	string patron_username;
	string patron_cardnumber;
	int patron_libraryfees;
	bool patron_owefees;		// True : l'usager doit de l'argent à la bibliothèque

};

// -------------------------------------------------------------------------------------------------------------------------------------------------------
// Helper function definitions pour la classe Patron **************************************************************************
void is_user_owes_fees(const Patron& user) {
	// Vérification si l'usager doit de l'argent à la bibliothèque

	cout << "L'usager '" << user.username() << (user.owefees() ? "' doit de l'argent à la bibliothèque\n" : "' ne doit rien à la bibliothèque\n");

}


class Library {
public:
	struct Transaction
	{
		Book livre_emprunte;
		Patron usager;
		string date_emprunt;
	};
	// Constructeur par défaut
	Library() { };
	
	// non-modifying operations
	void print_mauvais_payeurs();

	// modifying operations
	void add_book(string i, string t, string a, Book::Genre g, string d, bool c);
	void add_patron(string u, string c, int l, bool o);
	bool add_transaction(string booktitle_to_borrow, string nom_usager_qui_se_presente, string date);

private:
	vector <Book> library_book;
	vector <Patron> library_patron;
	vector <Transaction> library_transaction;

};

// Fonctions membre de la classe Library
void Library::print_mauvais_payeurs(){
	cout << "\nMauvais payeurs : ";
	for (const Patron& u : library_patron)
		if (u.owefees()) cout << u.username()<< ' ';
	cout << '\n';
}




void Library::add_book(string i, string t, string a, Book::Genre g, string d, bool c) {
	// Ajout d'un livre dans la librairie
	library_book.push_back(Book{i,t,a,g,d,c});

}

void Library::add_patron(string u, string c, int l, bool o) {
	// Ajout d'un usager dans la librairie
	library_patron.push_back(Patron{u,c,l,o});

}

bool Library::add_transaction(string booktitle_to_borrow, string nom_usager_qui_se_presente, string date){
	// Ajout d'une transaction et contrôles *****************************************************
	
	// 1er contrôle : l'usager doit exister dans la base de la bibliothèque
	Patron emprunteur{};
	for (const Patron& u : library_patron)
		if (u.username() == nom_usager_qui_se_presente) emprunteur = u; 

	// 2ème contrôle : le livre souhaité ne doit pas déjà avoir été prêté par la bibliothèque
	Book livre_emprunte{};
	for (const Book& b : library_book)
		if (b.title() == booktitle_to_borrow&& !b.checkout()) livre_emprunte = b;

	// 3ème contrôle : l'usager ne doit pas être redevable d'une somme d'argent (fees)
	if (emprunteur.owefees())return false;

	// Si tous les contrôles sont passés, on peut créer la transaction
	if (emprunteur.username() != "" && livre_emprunte.title() != "") {
	
		library_transaction.push_back(Transaction{livre_emprunte, emprunteur,date });
		return true;
	}
	
	return false;

}

// -------------------------------------------------------------------------------------------------------------------------------------------------------
int main()
{
	try
	{
		// A mettre dans la 1ère ligne du "main" pour afficher les caractères accentués sous la console Windows
		std::locale::global(std::locale("fr-FR"));

		
		// Manipulation des classes de base "Book" et "Patron" ----------------------------------------------------------
		Book b1{ "111-222-333-A","Géant","Steinbeck",Book::fiction,"10/10/1900",true };
		cout << "Livre : " << b1 << "\n";
		is_book_out(b1);

		Book b2{ "111-222-334-A","Petit","Dumas",Book::children,"10/10/1900",false };
		if (b1 == b2)cout << "Les deux ouvrages ont le même code ISBN\n";
		if (b1 != b2)cout << "Les deux ouvrages n'ONT PAS le même code ISBN...\n";

		Patron u1{ "M. Tonic","569785",0,false };
		is_user_owes_fees(u1);
		// --------------------------------------------------------------------------------------------------------------

		// Manipulation de la classe avancée "Library" -------========---------------------------------------------------
		Library lb; // Instanciation de la classe Library : fourniture des fonctions-membre

		lb.add_book("111-422-334-A", "Croc Blanc", "London", Book::children, "10/10/1900", false);
		lb.add_book("131-222-334-A", "L'aube des ténèbres", "Hamilton", Book::fiction, "10/10/1900", false);
		lb.add_book("131-222-334-B", "Trésor", "Cussler", Book::fiction, "10/10/1900", true);
		lb.add_patron("M. Jean", "987562", 0, false);
		lb.add_patron("Melle Henry", "111111", 0, false);
		lb.add_patron("Mme Pierre", "999999", 60, true);
		
		if (!lb.add_transaction("Trésor","M. Jean","20/01/2018"))
			cout << "La transaction n'a pas pu être générée !!!!!!!!!!!!!!!!!!!!!!!!\n";
		else
			cout << "La transaction est OK\n";
		
		// Affichage de tous les usagers qui doivent de l'argent à la bibliothèque
		lb.print_mauvais_payeurs();

		keep_window_open();

		return 0;
	}
	catch (Book::Invalid&) {
		cerr << "error: le format ISBN n-n-n-x du livre est incorrect\n";
		keep_window_open("q");	// For some Windows(tm) setup
		return 1;
	}
	catch (Patron::Invalid&) {
		cerr << "error: le format du numéro de la carte d'adhérent (6 chiffres) est incorrect\n";
		keep_window_open("q");	// For some Windows(tm) setup
		return 1;
	}
	catch (runtime_error& e) {	// this code is to produce error messages
		cout << e.what() << '\n';
		keep_window_open("q");	// For some Windows(tm) setups
	}
	
}

