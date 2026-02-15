#include <iostream>
#include <sqlite3.h>

using namespace std;

int Createdb(const char * s);
int CreateTable(const char* s);
int InsertData(const char* s);
int SelectData(const char* s);
int Callback(void* NotUsed, int argc, char** argv, char** azColName);

int main()
{
	const char* db = R"(C:\\Users\\nacer\\OneDrive\\Documents\\C++\\sql.db)";

	Createdb(db);
	CreateTable(db);
	InsertData(db);
	SelectData(db);

	_getwch();
	return 0;

}

int Createdb(const char* s) {
	sqlite3* DB;

	int exit = 0;
	exit = sqlite3_open(s, &DB);

	cout << "The Data base has been created succesfully" << endl;

	return 0;

}

int CreateTable(const char* s) {
	sqlite3* DB;

	string sql = "CREATE TABLE IF NOT EXISTS GRADES("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT,"
		"NAME TEXT NOT NULL,"
		"AGE INT NOT NULL,"
		"GRADE CHAR(1));";

	try {
		int exit = 0;
		exit = sqlite3_open(s, &DB);

		exit = sqlite3_exec(DB, sql.c_str(), NULL, NULL, NULL);

		if (exit != SQLITE_OK) {
			cerr << "Error in create table" << endl;
		}
		else {
			cout << "Table created Successfully" << endl;
		}

		sqlite3_close(DB);
	}
	catch(const exception &e){
		cerr << e.what() << endl;
	}

	return 0;
}

int InsertData(const char* s) {
	sqlite3* DB;
	string sql = "INSERT INTO GRADES(NAME , AGE , GRADE)  VALUES ('Nacer' , 19 , 'A')";

	int exit = 0;
	exit = sqlite3_open(s, &DB);
	exit = sqlite3_exec(DB, sql.c_str(), NULL, NULL, NULL);

	if (exit != SQLITE_OK) {
		cerr << "Error in inserting data" << endl;
	}
	else {
		cout << "Data inserted successfully" << endl;
	}

	cout << endl;

	return 0;
}

int SelectData(const char* s) {
	sqlite3* DB;
	string sql = "SELECT * FROM GRADES";

	int exit = 0;
	exit = sqlite3_open(s, &DB);
	exit = sqlite3_exec(DB, sql.c_str(), Callback, NULL, NULL);

	if (exit != SQLITE_OK) {
		cerr << "Error in selecting data" << endl;
	}
	else {
		cout << "Data selected successfully" << endl;
	}

	return 0;
}

int Callback(void* NotUsed, int argc, char** argv, char** azColName) {
	for (int i = 0; i < argc; i++) {
		cout << azColName[i] << ":" << argv[i] << endl;
	}

	cout << endl;

	return 0;
}


