#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

struct Company 
{
	string name;
	string profit_tax;
	string address;
};

vector<Company> readCompanyList(string file_name)
{
	ifstream file(file_name);
	vector<Company> list;
	if (!file.is_open()) 
	{
		cout << "Khong mo duoc file" << endl;
		return list;
	}
	string line;
	getline(file, line); // bỏ qua dòng đầu tiên
	while (getline(file, line)) 
	{
		stringstream ss(line);
		string name, tax, addr;
		getline(ss, name, '|');
		getline(ss, tax, '|');
		getline(ss, addr);
		list.push_back({ name, tax, addr });
	}
	return list;
}

long long hashString(string company_name)
{
	int p = 31;
	int m = 2000;
	int p_pow = 1;
	int hash = 0;
	if (company_name.length() > 20)
		company_name = company_name.substr(company_name.length() - 20); // lấy 20 ký tự cuối
	for (char c : company_name)
	{
		hash = (hash + (int(c) * p_pow) % m) % m;
		p_pow = (p_pow * p) % m;
	}
	return hash;
}

struct HashTable
{
	vector<Company> table[2000];
};
	
HashTable* createHashTable(vector<Company> listCompany)
{
	HashTable* ht = new HashTable();
	for (Company& c : listCompany)
	{
		long long index = hashString(c.name);
		ht->table[index].push_back(c);
	}
	return ht;
}

void insert(HashTable* hash_table, Company company)
{
	long long index = hashString(company.name);
	hash_table->table[index].push_back(company);
}

Company* search(HashTable* hash_table, string company_name) 
{
	long long index = hashString(company_name);
	for (Company& c : hash_table->table[index]) 
	{
		if (c.name == company_name) 
		{
			return &c;
		}
	}
	return nullptr; // không tìm thấy
}

void processQueries(HashTable* ht, string input_file, string output_file) 
{
	ifstream fin(input_file);
	ofstream fout(output_file);
	string company_name;
	while (getline(fin, company_name)) 
	{
		Company* result = search(ht, company_name);
		if (result != nullptr) 
		{
			fout << result->name << "|" << result->profit_tax << "|" << result->address << endl;
		}
	}
	fin.close();
	fout.close();
}

int main(int argc, char* argv[]) 
{
	if (argc < 4) 
	{
		cout << "Error" << endl;
		return 1;
	}
	string mst_file = argv[1];
	string input_file = argv[2];
	string output_file = argv[3];
	vector<Company> companies = readCompanyList(mst_file);
	HashTable* ht = createHashTable(companies);
	processQueries(ht, input_file, output_file);
	delete ht;
	return 0;
}
