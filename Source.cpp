#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<list>
#include<set>
#include<map>
using namespace std;


class Exceptie :exception
{
public:
	string mesajEroare;
	Exceptie()
	{
		this->mesajEroare = "Eroare necunoscuta";
	}

	Exceptie(string mesaj)
	{
		this->mesajEroare = mesaj;
	}
};

class MateriePrimaDeBaza
{
public:
	virtual void scriereInFBinarMPrima(fstream& file) = 0;
	virtual void citireFBinarMPrima(fstream& file) = 0;
	virtual string tipMaterie() = 0;
};

class MateriePrima: public MateriePrimaDeBaza
{
protected:
	char* denumireMateriePrima;
	int nrBucatiPeStoc;
	float kcal;

public:
	//constructorul fara parametri
	MateriePrima()
	{
		this->denumireMateriePrima = new char[strlen("Necunoscuta") + 1];
		strcpy(this->denumireMateriePrima, "Necunoscuta");
		this->nrBucatiPeStoc = 0;
		this->kcal = 0;
	}

	//constructorul cu toti parametrii , cu validari
	MateriePrima(const char* denumireMateriePrima, int nrBucatiPeStoc, float kcal)
	{
		if (strlen(denumireMateriePrima) >= 4)
		{
			this->denumireMateriePrima = new char[strlen(denumireMateriePrima) + 1];
			strcpy(this->denumireMateriePrima, denumireMateriePrima);
		}
		else
		{
			this->denumireMateriePrima = new char[strlen("Necunoscuta") + 1];
			strcpy(this->denumireMateriePrima, "Necunoscuta");
		}

		if (nrBucatiPeStoc > 0)
			this->nrBucatiPeStoc = nrBucatiPeStoc;
		else this->nrBucatiPeStoc = 0;

		if (kcal > 0)
			this->kcal = kcal;
		else
			this->kcal = 0;
	}

	//constructorul de copiere
	MateriePrima(const MateriePrima& obj)
	{
		this->denumireMateriePrima = new char[strlen(obj.denumireMateriePrima) + 1];
		strcpy(this->denumireMateriePrima, obj.denumireMateriePrima);
		this->nrBucatiPeStoc = obj.nrBucatiPeStoc;
		this->kcal = obj.kcal;
	}

	//getteri
	const char* getDenumireMateriePrima()
	{
		return this->denumireMateriePrima;
	}

	int getNrBucPeStoc()
	{
		return this->nrBucatiPeStoc;
	}

	float getKcal()
	{
		return this->kcal;
	}

	//setteri
	void setDenumireMateriePrima(const char* denumireNouaMateriePrima)
	{
		if (this->denumireMateriePrima != nullptr)
		{
			delete[] this->denumireMateriePrima;
		}

		if (strlen(denumireNouaMateriePrima) >= 4)
		{
			this->denumireMateriePrima = new char[strlen(denumireNouaMateriePrima) + 1];
			strcpy(this->denumireMateriePrima, denumireNouaMateriePrima);
		}
		else 
		{
			this->denumireMateriePrima = new char[strlen("Necunoscuta") + 1];
			strcpy(this->denumireMateriePrima, "Necunoscuta");
		}
	}

	void setNrBucMateriePrima(int nrNouMateriePrima)
	{
		if (nrNouMateriePrima > 0)
			this->nrBucatiPeStoc = nrNouMateriePrima;
		else this->nrBucatiPeStoc = 0;
	}

	void setKcal(float nrNouKcal)
	{
		if (nrNouKcal > 0)
			this->kcal = nrNouKcal;
		else this->kcal = 0;
	}

	//operatorul de atribuire
	MateriePrima& operator=( const MateriePrima& obj)
	{
		if (this!=&obj)
		{
			if (this->denumireMateriePrima != nullptr)
			{
				delete[] this->denumireMateriePrima;
			}
			this->denumireMateriePrima = new char[strlen(obj.denumireMateriePrima) + 1];
			strcpy(this->denumireMateriePrima, obj.denumireMateriePrima);
			this->nrBucatiPeStoc = obj.nrBucatiPeStoc;
			this->kcal = obj.kcal;
		}
		return *this;
	}

	//operatorul <<
	friend ostream& operator<<(ostream& out, const MateriePrima& obj)
	{
		out << "Denumire materie prima: " << obj.denumireMateriePrima << endl;
		out << "Numar bucati pe stoc: " << obj.nrBucatiPeStoc << endl;
		out << "Numar de kcal: " << obj.kcal;

		return out;
	}

	//operatorul de citire(>>) cu validari
	friend istream& operator>>(istream& in, MateriePrima& obj)
	{
		if (obj.denumireMateriePrima != nullptr)
		{
			delete[] obj.denumireMateriePrima;
		}
		char aux[1000];
		cout << "Denumire materie prima: ";
		in >> aux;
		if (strlen(aux) >= 4)
		{
			obj.denumireMateriePrima = new char[strlen(aux) + 1];
			strcpy(obj.denumireMateriePrima, aux);
		}
		else
		{
			obj.denumireMateriePrima = new char[strlen("Necunoscuta") + 1];
			strcpy(obj.denumireMateriePrima, "Necunoscuta");
		}
		int nrBuc;
		cout << "Numar bucati pe stoc: ";
		in >> nrBuc;
		if (nrBuc > 0)
			obj.nrBucatiPeStoc = nrBuc;
		else obj.nrBucatiPeStoc = 0;
		cout << "Numar de kcal: ";
		float kc;
		in >> kc;
		if (kc > 0)
			obj.kcal = kc;
		else obj.kcal = 0;

		return in;
	}

	//metoda de marire a stocului de materie prima
	void adaugaBucMateiePrima(int nrBucInPlus)
	{
		if (nrBucInPlus > 0)
			this->nrBucatiPeStoc += nrBucInPlus;
	}

	//metoda de scadere a stocului de materie prima
	void scadeBucMateriePrima(int nrBucInMinus)
	{
		if (nrBucInMinus > this->nrBucatiPeStoc)
			this->nrBucatiPeStoc = 0;
		else this->nrBucatiPeStoc -= nrBucInMinus;
	}

	string tipMaterie()
	{
		return "Sunt o materie prima";
	}

	//destructor
	~MateriePrima()
	{
			delete[] denumireMateriePrima;
			denumireMateriePrima = nullptr;
	}


	//FISIERE
	//FISIER TEXT
	//scriere in fisier text

	friend ofstream& operator<<(ofstream& file, MateriePrima& obj)
	{
		//char* denumireMateriePrima;
		file << obj.denumireMateriePrima << endl;
		//int nrBucatiPeStoc;
		file << obj.nrBucatiPeStoc<<endl;
		//float kcal;
		file << obj.kcal;

		return file;
	}

	//citire din fisierul text
	friend ifstream& operator>>(ifstream& file, MateriePrima& obj)
	{
		delete[] obj.denumireMateriePrima;

		//char* denumireMateriePrima;
		char aux[100];
		file >> aux;
		obj.denumireMateriePrima = new char[strlen(aux) + 1];
		strcpy(obj.denumireMateriePrima, aux);

		//int nrBucatiPeStoc;
		file >> obj.nrBucatiPeStoc;

		//float kcal;
		file >> obj.kcal;

		return file;
	}

	//FISIERE BINARE
	//scriere in fisier binar
	virtual void scriereInFBinarMPrima(fstream& file)
	{
		//char* denumireMateriePrima;
		int nrLitere = strlen(this->denumireMateriePrima);
		file.write((char*)&nrLitere, sizeof(int));
		for (int i = 0; i < nrLitere; i++)
		{
			file.write((char*)&this->denumireMateriePrima[i], sizeof(char));
		}

		//int nrBucatiPeStoc;
		file.write((char*)&this->nrBucatiPeStoc, sizeof(int));

		//float kcal;
		file.write((char*)&this->kcal, sizeof(float));
	}

	//citire din fisier binar
	virtual void citireFBinarMPrima(fstream& file)
	{
		delete[] this->denumireMateriePrima;

		//char* denumireMateriePrima;
		int nrLitere;
		file.read((char*)&nrLitere, sizeof(int));
		this->denumireMateriePrima = new char[nrLitere + 1];
		for (int i = 0; i < nrLitere; i++)
		{
			file.read((char*)&this->denumireMateriePrima[i], sizeof(char));
		}
		this->denumireMateriePrima[nrLitere] = '\0';
		
		//int nrBucatiPeStoc;
		file.read((char*)&this->nrBucatiPeStoc, sizeof(int));
		
		//float kcal;
		file.read((char*)&this->kcal, sizeof(float));
	}

	//Raport stoc sub 50 buc de materie prima
	static void raportStocMateriePrima(ofstream& file, int nrMateriePrima, MateriePrima* vectorMateriePrima)
	{
		int nrMateriiPrimeStocSub50 = 0;

		for (int i = 0; i < nrMateriePrima; i++)
		{
			if (vectorMateriePrima[i].getNrBucPeStoc() < 50)
			{
				nrMateriiPrimeStocSub50++;
			}
		}

		file << nrMateriiPrimeStocSub50 << endl;
		for (int i = 0; i < nrMateriePrima; i++)
		{
			if (vectorMateriePrima[i].getNrBucPeStoc() < 50)
			{
				file << vectorMateriePrima[i] << endl;
			}
		}
	}

	static void afisareRaport(ifstream& file)
	{
		int nrMateriiPrimeStocSub50 = 0;
		file >> nrMateriiPrimeStocSub50;
		cout << "Numarul de materii prime care au stocul sub 50 buc este: " << nrMateriiPrimeStocSub50 << endl;
		cout << "Materiile prime au stocul sub 50 buc sunt:" << endl;
		for (int i = 0; i < nrMateriiPrimeStocSub50; i++)
		{
			cout << i << ". ";
			MateriePrima mp;
			file >>mp;
			cout << mp << endl << endl;
		}
	}
};

class MateriePrimaVegana :public MateriePrima
{
	bool esteCertificatVegan;
	int nrAlergeni;
	string* vectorAlergeni;

public:
	//getteri
	bool getEsteCertificatVegan()
	{
		return this->esteCertificatVegan;
	}

	int getNrAlergeni()
	{
		return this->nrAlergeni;
	}

	string* getVectorAlergeni()
	{
		return this->vectorAlergeni;
	}

	//setteri
	void setEsteCertificatVegan(bool esteCertificatVeganNou)
	{
		this->esteCertificatVegan = esteCertificatVeganNou;
	}

	void setAlergeni(int nrNouAlergeni, string* vectorNouAlergeni)
	{
		delete[] this->vectorAlergeni;
		this->nrAlergeni = nrNouAlergeni;
		this->vectorAlergeni = new string[this->nrAlergeni];
		for (int i = 0; i < this->nrAlergeni; i++)
		{
			this->vectorAlergeni[i] = vectorNouAlergeni[i];
		}
	}

	//constr fara param
	MateriePrimaVegana():MateriePrima()
	{
		this->esteCertificatVegan = true;
		this->nrAlergeni = 0;
		this->vectorAlergeni = nullptr;
	}

	//constr cu toti param
	MateriePrimaVegana(bool esteCertificatVegan, int nrAlergeni, string* vectorAlergeni, const char* denumireMateriePrima, int nrBucatiPeStoc, float kcal):MateriePrima(denumireMateriePrima, nrBucatiPeStoc,kcal)
	{
		this->esteCertificatVegan = esteCertificatVegan;
		this->nrAlergeni = nrAlergeni;
		this->vectorAlergeni = new string[this->nrAlergeni];
		for (int i = 0; i < this->nrAlergeni; i++)
		{
			this->vectorAlergeni[i] = vectorAlergeni[i];
		}
	}

	//constr de copiere
	MateriePrimaVegana(const MateriePrimaVegana& materieVegana) :MateriePrima(materieVegana)
	{
		this->esteCertificatVegan = materieVegana.esteCertificatVegan;
		this->nrAlergeni = materieVegana.nrAlergeni;
		this->vectorAlergeni = new string[this->nrAlergeni];
		for (int i = 0; i < this->nrAlergeni; i++)
		{
			this->vectorAlergeni[i] = materieVegana.vectorAlergeni[i];
		}
	}

	//operatorul =
	MateriePrimaVegana& operator=(MateriePrimaVegana& materieVegana)
	{
		if (this != &materieVegana)
		{
			MateriePrima::operator=(materieVegana);
			this->esteCertificatVegan = materieVegana.esteCertificatVegan;
			this->nrAlergeni = materieVegana.nrAlergeni;
			this->vectorAlergeni = new string[this->nrAlergeni];
			for (int i = 0; i < this->nrAlergeni; i++)
			{
				this->vectorAlergeni[i] = materieVegana.vectorAlergeni[i];
			}
		}
		return *this;
	}


	//constr pt downcasting
	MateriePrimaVegana(const MateriePrima& materiePrima) :MateriePrima(materiePrima)
	{
		this->esteCertificatVegan = true;
		this->nrAlergeni = 1;
		this->vectorAlergeni = new string[this->nrAlergeni];
		this->vectorAlergeni[0] = "gluten";
	}

	//destructor
	~MateriePrimaVegana()
	{
		delete[] this->vectorAlergeni;
		this->vectorAlergeni = nullptr;
	}

	//op de scriere
	friend ostream& operator<<(ostream& out, MateriePrimaVegana& obj)
	{
		out << "Materie prima este certificata vegan? 1-da, 0-nu. : " << obj.esteCertificatVegan<<endl;
		out << "Materia prima contine un nr de " << obj.nrAlergeni << " alergeni" << endl;
		out << "Alergenii sunt: " << endl;
		for (int i = 0; i < obj.nrAlergeni; i++)
		{
			out << obj.vectorAlergeni[i] << " ";
		}
		out << endl;
		out << (MateriePrima&)obj;

		return out;
	}

	//op de citire
	friend istream& operator>>(istream& in, MateriePrimaVegana& obj)
	{
		delete[] obj.vectorAlergeni;
		obj.vectorAlergeni = nullptr;

		in >> (MateriePrima&)obj;
		cout << endl << "este certificat vegan? 1-da, 0-nu. ";
		in >> obj.esteCertificatVegan;
		cout << "Introduceti numarul de alergeni ";
		in >> obj.nrAlergeni;
		obj.vectorAlergeni = new string[obj.nrAlergeni];
		cout << "Introduceti alergenii ";
		for (int i = 0; i < obj.nrAlergeni; i++)
		{
			in >> obj.vectorAlergeni[i];
		}
		return in;
	}

	//scriere fisier binar
	void scriereInFBinarMPrima(fstream& file)
	{
		MateriePrima::scriereInFBinarMPrima(file);

		//bool esteCertificatVegan;
		file.write((char*)&this->esteCertificatVegan, sizeof(bool));

		//int nrAlergeni;
		file.write((char*)&this->nrAlergeni, sizeof(int));

		//string* vectorAlergeni;
		for (int i = 0; i < this->nrAlergeni; i++)
		{
			int nrLitere1=0;
			nrLitere1 = this->vectorAlergeni[i].length();
			file.write((char*)&nrLitere1, sizeof(int));
			file.write(this->vectorAlergeni[i].c_str(), nrLitere1);
		}
	}

	//citire fisier binar
	void citireFBinarMPrima(fstream& file)
	{
		delete[] this->vectorAlergeni;

		MateriePrima::citireFBinarMPrima(file);

		//bool esteCertificatVegan;
		file.read((char*)&this->esteCertificatVegan, sizeof(bool));

		//int nrAlergeni;
		file.read((char*)&this->nrAlergeni, sizeof(int));

		//string* vectorAlergeni;
		this->vectorAlergeni = new string[this->nrAlergeni];
		for (int i = 0; i < this->nrAlergeni; i++)
		{
			int nrLitereA;
			file.read((char*)&nrLitereA, sizeof(int));
			string aux1;
			aux1.resize(nrLitereA);
			file.read((char*)aux1.c_str(), nrLitereA);
			this->vectorAlergeni[i] = aux1;
		}

	}

	string tipMaterie()
	{
		return "Sunt o materie prima vegana ";
	}

	//sa se compare nr de kcal a doua obiecte
	bool operator<(const MateriePrimaVegana& obj) const
	{
		if (this->kcal < obj.kcal)
			return 1;

		else return 0;
	}

};

template <typename tipData>
class Producator
{
	int nrElemente;
	tipData* vectorElemente;
	string numeProducator;

public:
	//getteri
	string getNumeProducator()
	{
		return this->numeProducator;
	}

	int getNrElemente()
	{
		return this->nrElemente;
	}

	tipData* getVectorElemente()
	{
		return this->vectorElemente;
	}

	//setteri
	void setNumeProducator(string numeNouProducator)
	{
		this->numeProducator = numeNouProducator;
	}

	void setElemente(int nrNouElemente, tipData* vectorNouElemente)
	{
		delete[] this->vectorElemente;
		this->vectorElemente = nullptr;

		if (nrNouElemente > 0)
		{
			this->nrElemente = nrNouElemente;
			this->vectorElemente = new tipData[this->nrElemente];
			for (int i = 0; i < this->nrElemente; i++)
			{
				this->vectorElemente[i] = vectorNouElemente[i];
			}
		}
		else this->nrElemente = 0;
	}

	//constructorul fara parametri
	Producator()
	{
		this->numeProducator = "Necunoscut";
		this->nrElemente = 0;
		this->vectorElemente = nullptr;
	}

	//constructorul cu toti parametri
	Producator(string numeProducator, int nrElemente, tipData* vectorElemente)
	{
		this->numeProducator = numeProducator;
		if (nrElemente > 0)
		{
			this->nrElemente = nrElemente;
			this->vectorElemente = new tipData[this->nrElemente];
			for (int i = 0; i < this->nrElemente; i++)
			{
				this->vectorElemente[i] = vectorElemente[i];
			}
		}
		else {
			this->nrElemente = 0;
			this->vectorElemente = nullptr;
		}
	}

	//constructorul de copiere
	Producator(const Producator& obj)
	{
		this->numeProducator = obj.numeProducator;
		if (obj.nrElemente > 0)
		{
			this->nrElemente = obj.nrElemente;
			this->vectorElemente = new tipData[this->nrElemente];
			for (int i = 0; i < this->nrElemente; i++)
			{
				this->vectorElemente[i] = obj.vectorElemente[i];
			}
		}
		else {
			this->nrElemente = 0;
			this->vectorElemente = nullptr;
		}
	}

	//operatorul egal
	Producator& operator=(const Producator& obj)
	{
		if (this != &obj)
		{
			delete[] this->vectorElemente;
			this->vectorElemente = nullptr;

			this->numeProducator = obj.numeProducator;
			if (obj.nrElemente > 0)
			{
				this->nrElemente = obj.nrElemente;
				this->vectorElemente = new tipData[this->nrElemente];
				for (int i = 0; i < this->nrElemente; i++)
				{
					this->vectorElemente[i] = obj.vectorElemente[i];
				}
			}
			else {
				this->nrElemente = 0;
				this->vectorElemente = nullptr;
			}
		}
		return *this;
	}


	//operatorul de afisare
	friend ostream& operator<<(ostream& out, Producator& obj)
	{
		out << "Numele producatorului este: " << obj.numeProducator << endl;
		out << "Numarul de elemente pe care acesta le produce este: " << obj.nrElemente << endl;
		out << "Elementele sunt: "<<endl<<endl;
		for (int i = 0; i < obj.nrElemente; i++)
		{
			out << obj.vectorElemente[i] << endl << endl;
		}

		return out;
	}

	//operatorul de citire
	friend istream& operator>>(istream& in, Producator& obj)
	{
		delete[] obj.vectorElemente;
		obj.vectorElemente = nullptr;

		cout << "Introduceti numele producatorului: ";
		in >> obj.numeProducator;
		cout << "Introduceti numarul de elemente pe care acesta le produce: ";
		in >> obj.nrElemente;
		obj.vectorElemente = new tipData[obj.nrElemente];
		for (int i = 0; i < obj.nrElemente; i++)
		{
			in >> obj.vectorElemente[i];
		}

		return in;
	}


	//destructorul
	~Producator()
	{
		delete[] this->vectorElemente;
		this->vectorElemente = nullptr;
	}

};


class Preparat
{
	string denumirePreparat;
	float pretPreparat;
	int nrMateriiPrime;
	MateriePrima* vectorMateriiPrime; 
	int* nrBucatiMateriePrima;
	bool necesitaPreparareTermica;

public:
	//constructorul fara parametri
	Preparat()
	{
		this->denumirePreparat = "Necunoscut";
		this->pretPreparat = 0;
		this->nrMateriiPrime = 0;
		this->vectorMateriiPrime = nullptr;
		this->nrBucatiMateriePrima = nullptr;
		this->necesitaPreparareTermica = true;
	}

	//constructorul cu toti parametri
	Preparat(string denumirePreparat, float pretPreparat, int nrMateriiPrime, MateriePrima* vectorMateriiPrime, int* nrBucatiMateriePrima, bool necesitaPreparareTermica)
	{
		if (denumirePreparat.length() > 3)
			this->denumirePreparat = denumirePreparat;
		else this->denumirePreparat = "Necunoscut";

		if (pretPreparat > 0)
			this->pretPreparat = pretPreparat;
		else this->pretPreparat = 0;

		if (nrMateriiPrime > 0)
		{
			this->nrMateriiPrime = nrMateriiPrime;
			this->vectorMateriiPrime = new MateriePrima[this->nrMateriiPrime];
			this->nrBucatiMateriePrima = new int[this->nrMateriiPrime];

			for (int i = 0; i < this->nrMateriiPrime; i++)
			{
				this->vectorMateriiPrime[i] = vectorMateriiPrime[i];
				this->nrBucatiMateriePrima[i] = nrBucatiMateriePrima[i];
			}
		}
		else
		{
			this->nrMateriiPrime = 0;
			this->vectorMateriiPrime = nullptr;
			this->nrBucatiMateriePrima = nullptr;
		}

		this->necesitaPreparareTermica = necesitaPreparareTermica;
	}

	//constructorul de copiere
	Preparat(const Preparat& obj)
	{
		if (obj.denumirePreparat.length() > 3)
			this->denumirePreparat = obj.denumirePreparat;
		else this->denumirePreparat = "Necunoscut";

		if (obj.pretPreparat > 0)
			this->pretPreparat = obj.pretPreparat;
		else this->pretPreparat = 0;

		if (obj.nrMateriiPrime > 0)
		{
			this->nrMateriiPrime = obj.nrMateriiPrime;
			this->vectorMateriiPrime = new MateriePrima[obj.nrMateriiPrime];
			this->nrBucatiMateriePrima = new int[obj.nrMateriiPrime];

			for (int i = 0; i < this->nrMateriiPrime; i++)
			{
				this->vectorMateriiPrime[i] = obj.vectorMateriiPrime[i];
				this->nrBucatiMateriePrima[i] = obj.nrBucatiMateriePrima[i];
			}
		}
		else
		{
			this->nrMateriiPrime = 0;
			this->vectorMateriiPrime = nullptr;
			this->nrBucatiMateriePrima = nullptr;
		}

		this->necesitaPreparareTermica = obj.necesitaPreparareTermica;
	}

	//operatorul=
	Preparat& operator=(const Preparat& obj)
	{
		if (this != &obj)
		{
			if (this->vectorMateriiPrime != nullptr)
				delete[] this->vectorMateriiPrime;

			if (this->nrBucatiMateriePrima != nullptr)
				delete[] this->nrBucatiMateriePrima;

			if (obj.denumirePreparat.length() > 3)
				this->denumirePreparat = obj.denumirePreparat;
			else this->denumirePreparat = "Necunoscut";

			if (obj.pretPreparat > 0)
				this->pretPreparat = obj.pretPreparat;
			else this->pretPreparat = 0;

			if (obj.nrMateriiPrime > 0)
			{
				this->nrMateriiPrime = obj.nrMateriiPrime;
				this->vectorMateriiPrime = new MateriePrima[obj.nrMateriiPrime];
				this->nrBucatiMateriePrima = new int[obj.nrMateriiPrime];

				for (int i = 0; i < this->nrMateriiPrime; i++)
				{
					this->vectorMateriiPrime[i] = obj.vectorMateriiPrime[i];
					this->nrBucatiMateriePrima[i] = obj.nrBucatiMateriePrima[i];
				}
			}
			else
			{
				this->nrMateriiPrime = 0;
				this->vectorMateriiPrime = nullptr;
				this->nrBucatiMateriePrima = nullptr;
			}

			this->necesitaPreparareTermica = obj.necesitaPreparareTermica;
		}
		return *this;
	}

	//getteri
	string getDenumirePreparat()
	{
		return this->denumirePreparat;
	}

	float getPretPreparat()
	{
		return this->pretPreparat;
	}

	int getNrMateriiPrime()
	{
		return this->nrMateriiPrime;
	}

	MateriePrima* getVectorMateriiPrime()
	{
		return this->vectorMateriiPrime;
	}

	int* getNrBucatiMateriePrima()
	{
		return this->nrBucatiMateriePrima;
	}

	bool getNecesitaPreparareTermica()
	{
		return this->necesitaPreparareTermica;
	}

	//setteri
	void setDenumirePreparat(string denumireNouaPreparat)
	{
		if (denumireNouaPreparat.length() > 3)
			this->denumirePreparat = denumireNouaPreparat;
	}

	void setPretPreparat(float pretNouPreparat)
	{
		if (pretNouPreparat > 0)
			this->pretPreparat = pretNouPreparat;
	}

	void setVectorMateriiPrime(int nrNouMateriiPrime, MateriePrima* vectorNouMateriiPrime, int* nrNouBucatiMateriePrima)
	{
		if (this->vectorMateriiPrime != nullptr)
			delete[] this->vectorMateriiPrime;

		if (this->nrBucatiMateriePrima != nullptr)
			delete[] this->nrBucatiMateriePrima;

		if (nrNouMateriiPrime > 0)
		{
			this->nrMateriiPrime = nrNouMateriiPrime;
			this->vectorMateriiPrime = new MateriePrima[this->nrMateriiPrime];
			this->nrBucatiMateriePrima = new int[this->nrMateriiPrime];
			for (int i = 0; i < this->nrMateriiPrime; i++)
			{
				this->vectorMateriiPrime[i] = vectorNouMateriiPrime[i];
				this->nrBucatiMateriePrima[i] = nrNouBucatiMateriePrima[i];
			}
		}
		else
		{
			this->nrMateriiPrime = 0;
			this->vectorMateriiPrime = nullptr;
			this->nrBucatiMateriePrima = nullptr;
		}
	}

	void setNecesitaPreparareTermica(bool NouNecesitaPreparareTermica)
	{
		this->necesitaPreparareTermica = NouNecesitaPreparareTermica;
	}

	//operatorul care calculeaza nr de kcal pentru fiecare preparat
	float operator()() const 
	{
		float nrKcal = 0;
		for (int i = 0; i < this->nrMateriiPrime; i++)
			nrKcal += vectorMateriiPrime[i].getKcal() * this->nrBucatiMateriePrima[i];

		return nrKcal;
	}
	//operatorul<<
	friend ostream& operator<<(ostream& out, Preparat& obj) 
	{
		out << "Denumire preparat: " << obj.denumirePreparat<<endl;
		//out << "Pret preparat: " << obj.pretPreparat << endl;
		//out << "Total kcal: " << obj() << endl;
		/*out << "Nr materii prime: " << obj.nrMateriiPrime<<endl;
		out << "Vectori materii prime: "<<endl;
		for (int i = 0; i < obj.nrMateriiPrime; i++)
		{
			out << obj.vectorMateriiPrime[i] << endl;
			out << "Nr bucati materie prima: " << obj.nrBucatiMateriePrima[i] << endl;
			out << endl;
		}
		out << "Necesita preparare termica? 1-da, 0-nu. " << obj.necesitaPreparareTermica;*/

		return out;
	}

	//operatorul de citire
	friend istream&operator>> (istream& in, Preparat& obj)
	{
		/*if (obj.vectorMateriiPrime != nullptr)
			delete[] obj.vectorMateriiPrime;

		if (obj.nrBucatiMateriePrima != nullptr)
			delete[] obj.nrBucatiMateriePrima;*/

		cout << "Denumire preparat: ";
		string aux;
		in >> aux;
		if (aux.length() > 3)
			obj.denumirePreparat = aux;
		else obj.denumirePreparat = "Necunoscut";
		/*cout << "Pret preparat: ";
		int aux1=0;
		in >> aux1;
		if (aux1 > 0)
			obj.pretPreparat = aux1;
		else obj.pretPreparat = 0;*/
		/*cout << "Nr materii prime: ";
		int aux2;
		in >> aux2;
		if (aux2 > 0)
		{
			obj.nrMateriiPrime = aux2;
			obj.vectorMateriiPrime = new MateriePrima[obj.nrMateriiPrime];
			obj.nrBucatiMateriePrima = new int[obj.nrMateriiPrime];
			cout << "Vector materii prime: " << endl;
			for (int i = 0; i < obj.nrMateriiPrime; i++)
			{
				in >> obj.vectorMateriiPrime[i];
				cout << "Nr bucati materie prima: ";
				in >> obj.nrBucatiMateriePrima[i];
			}
		}
		else 
		{
			obj.nrMateriiPrime = 0;
			obj.vectorMateriiPrime = nullptr;
			obj.nrBucatiMateriePrima = nullptr;
		}
		cout << "Necesita preparare termica? 1-da, 0-nu. ";
		in>> obj.necesitaPreparareTermica;*/

		return in;
	}

	//oparator+
	Preparat& operator+(float valoareAgaugata)
	{
		if (valoareAgaugata > 0)
		{
			this->pretPreparat += valoareAgaugata;
		}
		else throw Exceptie("Valoare adaugata eronata");
		return *this;
	}

	//operatorul++ in pre-incrementare
	Preparat& operator++()
	{
		this->pretPreparat++;
		return *this;
	}

	//operatorul++ in post-incrementare
	Preparat operator++(int)
	{
		Preparat copie = *this;
		this->pretPreparat++;
		return copie;
	}


	//operator-
	Preparat& operator-(float valoareScazuta)
	{
		if (valoareScazuta > 0 && valoareScazuta <= this->pretPreparat)
		{
			this->pretPreparat -= valoareScazuta;
		}
		else throw Exceptie("Valoare introdusa eronat");
		return *this;
	}

	bool operator==(const Preparat& obj) const 
	{
		if (this->denumirePreparat == obj.denumirePreparat)
			return true;
		else return false;
	}

	bool operator!=(const Preparat& obj)
	{
		return !(*this == obj);
	}

	bool operator<(const Preparat& obj)
	{
		if (this->pretPreparat < obj.pretPreparat)
			return 1;
		else return 0;
	}

	//destructor
	~Preparat()
	{
		
			delete[] vectorMateriiPrime;
			vectorMateriiPrime = nullptr;

			delete[] this->nrBucatiMateriePrima;
		 this->nrBucatiMateriePrima = nullptr;
	}

	//FISIER TEXT
	//scriere in fisier text
	friend ofstream& operator<<(ofstream& file, Preparat& obj)
	{
		file << obj.denumirePreparat;

		return file;
	}

	//citire din fisier text
	friend ifstream& operator>>(ifstream& file, Preparat& obj)
	{
		file >> obj.denumirePreparat;

		return file;
	}

	//FISIER BINAR
	//scriere in fisier binar
	void scriereBinarPreparat(fstream& file)
	{
		//string denumirePreparat
		int nrLitere;
		nrLitere = this->denumirePreparat.length();
		file.write((char*)&nrLitere, sizeof(int));
		file.write(this->denumirePreparat.c_str(), nrLitere);
	}

	//citire din fisier binar
	void citireBinarPreparat(fstream& file)
	{
		int nrLitere;
		file.read((char*)&nrLitere, sizeof(int));
		string aux;
		aux.resize(nrLitere);
		file.read((char*)aux.c_str(), nrLitere);
		this->denumirePreparat = aux;
	}

	//raport privind pretul preparatului. Se vor afisa preparatele cu cel mai mare, respectiv cel mai mic pret
	static void raportPretPreparat(ofstream& file, int nrPreparateRaport, Preparat* vectorPreparateRaport)
	{
		float pretMax=0;
		float pretMin=99999;
		for (int i = 0; i < nrPreparateRaport; i++)
		{
			if (vectorPreparateRaport[i].getPretPreparat() > pretMax)
				pretMax = vectorPreparateRaport[i].getPretPreparat();

			if (vectorPreparateRaport[i].getPretPreparat() < pretMin)
				pretMin = vectorPreparateRaport[i].getPretPreparat();
		}

			file << pretMax << endl;
			file << pretMin << endl;
			for (int i = 0; i < nrPreparateRaport; i++)
			{
				if (vectorPreparateRaport[i].getPretPreparat() == pretMax)
				{
					file << vectorPreparateRaport[i] << endl;
				}

				if (vectorPreparateRaport[i].getPretPreparat() == pretMin)
				{
					file << vectorPreparateRaport[i] << endl;
				}
			}
		
	}

	static void afisareRaportPreparat(ifstream& file)
	{
		float pretMax;
		float pretMin;
		file >> pretMax;
		cout << "Pretul cel mai mare din lista de preparate este: " << pretMax << endl;
		file >> pretMin;
		cout << "Pretul cel mai mic din lista de preparate este: " << pretMin << endl;
		cout << "Preparatele sunt: " << endl;
		for (int i = 0; i <2; i++)
		{
			if (i == 0)
			{
				Preparat p;
				file >> p;
				cout << "Preparatul cu pretul cel mai mare este: " << endl<< p << endl;
			}

			else if (i == 1)
			{
				Preparat p;
				file >> p;
				cout << "Preparatul cu pretul cel mai mic este: " << endl << p << endl;
			}
		}
	}

	//raport privind preparatul cu cel mai mare nr de kcal
	static void raportPreparatKcal(ofstream& file, int nrPreparate, Preparat* preparate)
	{
		float maxKcal=0;
		int poz;
		for (int i = 0; i < nrPreparate; i++)
		{
			if (preparate[i]() > maxKcal)
			{
				poz = i;
				maxKcal = preparate[i]();
			}
		}
		file << maxKcal<<endl;

		for (int i = 0; i < nrPreparate; i++)
		{
			if (i == poz)
				file << preparate[i];
		}
	}

	static void afisarePreparatKcal(ifstream& file)
	{
		float kcalMax;
		file >> kcalMax;
		cout << "Numarul maxim de kcal este: " << kcalMax << endl;
		Preparat p;
		file >> p;
		cout << "Preparatul care are cele mai multe kcal este: " << endl;
		cout << p<<endl<<endl;
	}
};

class MeniuRestaurant
{
	int nrPreparateMeniu;
	Preparat** vectorPointeriPreparate;

public:
	//constructor fara param
	MeniuRestaurant()
	{
		this->nrPreparateMeniu = 0;
		this->vectorPointeriPreparate = nullptr;
	}

	//constructor cu param
	MeniuRestaurant(int nrPreparateMeniu, Preparat** vectorPointeriPreparate)
	{
		if (nrPreparateMeniu > 0)
		{
			this->nrPreparateMeniu = nrPreparateMeniu;
			this->vectorPointeriPreparate = new Preparat * [this->nrPreparateMeniu];
			for (int i = 0; i < this->nrPreparateMeniu; i++)
			{
				this->vectorPointeriPreparate[i] = new Preparat(*vectorPointeriPreparate[i]);
			}
		}
		else
		{
			this->nrPreparateMeniu = 0;
			this->vectorPointeriPreparate = nullptr;
		}
	}

	MeniuRestaurant(const MeniuRestaurant& obj)
	{
		if (obj.nrPreparateMeniu > 0)
		{
			this->nrPreparateMeniu = obj.nrPreparateMeniu;
			this->vectorPointeriPreparate = new Preparat * [this->nrPreparateMeniu];
			for (int i = 0; i < this->nrPreparateMeniu; i++)
			{
				this->vectorPointeriPreparate[i] = new Preparat(*obj.vectorPointeriPreparate[i]);
			}
		}
		else
		{
			this->nrPreparateMeniu = 0;
			this->vectorPointeriPreparate = nullptr;
		}
	}

	MeniuRestaurant& operator=(const MeniuRestaurant& obj)
	{
		if (this != &obj)
		{
			for (int i = 0; i < this->nrPreparateMeniu; i++)
				delete this->vectorPointeriPreparate[i];

			delete[] this->vectorPointeriPreparate;
			if (obj.nrPreparateMeniu > 0)
			{
				this->nrPreparateMeniu = obj.nrPreparateMeniu;
				this->vectorPointeriPreparate = new Preparat * [this->nrPreparateMeniu];
				for (int i = 0; i < this->nrPreparateMeniu; i++)
				{
					this->vectorPointeriPreparate[i] = new Preparat(*obj.vectorPointeriPreparate[i]);
				}
			}
			else
			{
				this->nrPreparateMeniu = 0;
				this->vectorPointeriPreparate = nullptr;
			}
		}
		return *this;
	}

	Preparat returnPreparat(const Preparat& obj)
	{
		for (int i = 0; i < this->nrPreparateMeniu; i++)
		{
			if (*(this->vectorPointeriPreparate[i]) == obj)
			{
				return *vectorPointeriPreparate[i];
			}
			
		}
		return Preparat();
	}

	MeniuRestaurant& operator+=(Preparat *preparatNou)
	{
		MeniuRestaurant copie = *this;
		for (int i = 0; i < this->nrPreparateMeniu; i++)
			delete this->vectorPointeriPreparate[i];

		delete[] this->vectorPointeriPreparate;
		this->nrPreparateMeniu++;

		this->vectorPointeriPreparate = new Preparat * [this->nrPreparateMeniu];

		for (int i = 0; i < copie.nrPreparateMeniu; i++)
		{
			this->vectorPointeriPreparate[i] = new Preparat(*copie.vectorPointeriPreparate[i]);
		}
		this->vectorPointeriPreparate[this->nrPreparateMeniu - 1] = new Preparat(*preparatNou);

		return *this;
	}

	friend ostream& operator<<(ostream& out, const MeniuRestaurant& obj)
	{
		out << "\nMeniu taverna: " << endl;
		if (obj.nrPreparateMeniu != 0)
		{
			for (int i = 0; i < obj.nrPreparateMeniu; i++)
			{
				out << i << ". " << *obj.vectorPointeriPreparate[i] << endl;
			}
		}
		else out << "\n Nu exista Preparate disponibile\n";

		return out;
	}



	//destructor
	~MeniuRestaurant()
	{
		for (int i = 0; i < this->nrPreparateMeniu; i++)
			delete this->vectorPointeriPreparate[i];

		delete[] this->vectorPointeriPreparate;
	}

	
	//FISIER TEXT
	//scriere in fisier text
	friend ofstream& operator<<(ofstream& file, MeniuRestaurant& obj)
	{
		file << obj.nrPreparateMeniu << endl;
		for (int i = 0; i < obj.nrPreparateMeniu; i++)
		{
			file << (*obj.vectorPointeriPreparate[i]) << endl;
		}

		return file;
	}

	//citire din fisier text
	friend ifstream& operator>>(ifstream& file, MeniuRestaurant& obj)
	{
		delete[] obj.vectorPointeriPreparate;

		file >> obj.nrPreparateMeniu;
		obj.vectorPointeriPreparate = new Preparat*[obj.nrPreparateMeniu];
		for (int i = 0; i < obj.nrPreparateMeniu; i++)
		{
			obj.vectorPointeriPreparate[i] = new Preparat();
			file >> (*obj.vectorPointeriPreparate[i]);
		}

		return file;
	}

	//FISIERE BINARE
	//scriere in fisier binar
	void scriereBinarMeniuRestaurant(fstream& file)
	{
		//int nrPreparateMeniu;
		file.write((char*)&this->nrPreparateMeniu, sizeof(int));

		//Preparat** vectorPointeriPreparate;
		for (int i = 0; i < this->nrPreparateMeniu; i++)
		{
			this->vectorPointeriPreparate[i]->scriereBinarPreparat(file);
		}
	}

	//citire din fisier binar
	void citireBinarMeniuRestaurant(fstream& file)
	{
		delete[] this->vectorPointeriPreparate;

		//int nrPreparateMeniu;
		file.read((char*)&this->nrPreparateMeniu, sizeof(int));

		//Preparat** vectorPointeriPreparate;
		this->vectorPointeriPreparate = new Preparat*[this->nrPreparateMeniu];
		for (int i = 0; i < this->nrPreparateMeniu; i++)
		{
			this->vectorPointeriPreparate[i] = new Preparat();
			this->vectorPointeriPreparate[i]->citireBinarPreparat(file);
		}

	}
};

class Client
{
	char* numePrenume;
	bool clientOnline; //1-clientOnline, 0-clientFizicInRestaurant
	int nrMasa; //doar pentru clientii fizici in restaurant

public:
	//constructorul fara parametri
	Client()
	{
		this->numePrenume = new char[strlen("Anonim") + 1];
		strcpy(this->numePrenume, "Anonim");

		this->clientOnline = true;
		this->nrMasa = 0;
	}

	//constructorul cu toti parametri
	Client(const char* numePrenume, bool clientOnline, int nrMasa)
	{
		if (strlen(numePrenume) >= 3)
		{
			this->numePrenume = new char[strlen(numePrenume) + 1];
			strcpy(this->numePrenume, numePrenume);
		}
		else
		{
			this->numePrenume = new char[strlen("Anonim") + 1];
			strcpy(this->numePrenume, "Anonim");
		}

		this->clientOnline = clientOnline;

		if (nrMasa > 0 && this->clientOnline==0)
			this->nrMasa = nrMasa;

		else this->nrMasa = 0;
	}

	//constructorul de copiere
	Client(const Client& obj)
	{
		if (strlen(obj.numePrenume) >= 3)
		{
			this->numePrenume = new char[strlen(obj.numePrenume) + 1];
			strcpy(this->numePrenume, obj.numePrenume);
		}
		else
		{
			this->numePrenume = new char[strlen("Anonim") + 1];
			strcpy(this->numePrenume, "Anonim");
		}

			this->clientOnline = obj.clientOnline;

		if (obj.nrMasa > 0 && this->clientOnline == 0)
			this->nrMasa = obj.nrMasa;

		else this->nrMasa = 0;
	}

	//operatorul de atribuire
	Client& operator=(const Client& obj)
	{
		if (this != &obj)
		{
			if (this->numePrenume != nullptr)
			{
				delete[] this->numePrenume;
			}

			if (strlen(obj.numePrenume) >= 3)
			{
				this->numePrenume = new char[strlen(obj.numePrenume) + 1];
				strcpy(this->numePrenume, obj.numePrenume);
			}
			else
			{
				this->numePrenume = new char[strlen("Anonim") + 1];
				strcpy(this->numePrenume, "Anonim");
			}

			this->clientOnline = obj.clientOnline;

			if (obj.nrMasa > 0 && this->clientOnline == 0)
				this->nrMasa = obj.nrMasa;

			else this->nrMasa = 0;
		}
		return *this;
	}

	//getteri
	char* getNumePrenume()
	{
		return this->numePrenume;
	}

	bool getClientOnline()
	{
		return this->clientOnline;
	}

	int getNrMasa()
	{
		return this->nrMasa;
	}

	//setteri
	void setNumePrenume(const char* numePrenumeNou)
	{
		if (strlen(numePrenumeNou) >= 3)
		{
			this->numePrenume = new char[strlen(numePrenumeNou) + 1];
			strcpy(this->numePrenume, numePrenumeNou);
		}
		else
		{
			this->numePrenume = new char[strlen("Anonim") + 1];
			strcpy(this->numePrenume, "Anonim");
		}
	}

	void setNumarMasa(int nrNouMasa)
	{

		if (nrNouMasa > 0 && this->clientOnline == 0)
			this->nrMasa = nrNouMasa;

		else this->nrMasa = 0;
	}

	void setClientOnline(bool clientOnlineNou)
	{
		this->clientOnline = clientOnlineNou;
	}

	//operatorul<<
	friend ostream& operator<<(ostream& out, Client& obj)
	{
		out << "NumePrenume client: " << obj.numePrenume << endl;
		out << "Este client online? 1-clientOnline, 0-clientFizic: " << obj.clientOnline << endl;
		out << "Numar masa: " << obj.nrMasa << endl;

		return out;
	}

	//operatorul!
	friend void operator!(Client& obj)
	{
		if (obj.clientOnline == 0)
			obj.clientOnline = 1;
		else obj.clientOnline = 0;
	}

	//operatorul>>
	friend istream& operator>>(istream& in, Client& obj)
	{
		if (obj.numePrenume != nullptr)
		{
			delete[] obj.numePrenume;
		}
		char aux[1000];
		cout << "NumePrenume client: ";
		in >> aux;
		if (strlen(aux) >= 3)
		{
			obj.numePrenume = new char[strlen(aux) + 1];
			strcpy(obj.numePrenume, aux);
		}
		else
		{
			obj.numePrenume = new char[strlen("Anonim") + 1];
			strcpy(obj.numePrenume, "Anonim");
		}

		cout << "Este client online? 1-clientOnline, 0-clientFizic: ";
		in >> obj.clientOnline;

		if (obj.clientOnline == 0)
		{
			int nr;
			cout << "Numar masa: ";
			in >> nr;
			if (nr > 0 )
				obj.nrMasa = nr;
		}
		else obj.nrMasa = 0;

		return in;
	}

	//destructor
	~Client()
	{
		if (this->numePrenume != nullptr)
		{
			delete[] this->numePrenume;
			this->numePrenume = nullptr;
		}
	}

	//FISIER TEXT
	// scriere in fisier text
	friend ofstream& operator<<(ofstream& file, Client& obj)
	{
		//char* numePrenume;
		file << obj.numePrenume << endl;
		//bool clientOnline; 
		file << obj.clientOnline << endl;
		//int nrMasa;
		file << obj.nrMasa;

		return file;
	}

	// citire din fisier text
	friend ifstream& operator>>(ifstream& file, Client& obj)
	{
		delete[] obj.numePrenume;

		//char* numePrenume;
		char aux[100];
		file >> aux;
		obj.numePrenume = new char[strlen(aux) + 1];
		strcpy(obj.numePrenume, aux);
		//bool clientOnline;
		file >> obj.clientOnline;
		//int nrMasa;
		file >> obj.nrMasa;

		return file;
	}

	//FISIER BINAR
	// scriere in fisier binar
	void scriereBinarClient(fstream& file)
	{
		// char* numePrenume;
		int nrLitere;
		nrLitere = strlen(this->numePrenume);
		file.write((char*)&nrLitere, sizeof(int));
		for (int i = 0; i < nrLitere; i++)
		{
			file.write((char*)&this->numePrenume[i], sizeof(char));
		}
		
		//bool clientOnline;
		file.write((char*)&this->clientOnline, sizeof(bool));

		//int nrMasa;
		file.write((char*)&this->nrMasa, sizeof(int));
	}
	
	// citire din fisier binar
	void citireBinarClient(fstream& file)
	{
		delete[] this->numePrenume;

		//char* numePrenume;
		int nrLitere;
		file.read((char*)&nrLitere, sizeof(int));
		this->numePrenume = new char[nrLitere + 1];
		for (int i = 0; i < nrLitere; i++)
		{
			file.read((char*)&this->numePrenume[i], sizeof(char));
		}
		this->numePrenume[nrLitere] = '\0';

		//bool clientOnline; 
		file.read((char*)&this->clientOnline, sizeof(bool));

		//int nrMasa;
		file.read((char*)&this->nrMasa, sizeof(int));
	}

	//Raport privind preferintele clientilor: care este ponderea clientilor online , clientilor fizici si cat reprezinta fiecare din totalul acesta 

	static void scriereRaportClienti(ofstream& file, int nrClienti, Client* clienti)
	{
		int nrClientiOnline=0;
		int nrClientiFizici=0;

		for (int i = 0; i < nrClienti; i++)
		{
			if (clienti[i].getClientOnline() == 1)
				nrClientiOnline++;
			else nrClientiFizici++;
		}
		file << nrClienti << endl;
		file << nrClientiOnline << endl;
		file << nrClientiFizici;
	}

	static void afisareRaportClienti(ifstream& file)
	{
		int nrTotalClienti = 0;
		int nrClientiOnline = 0;
		int nrClientiFizici = 0;
		file >> nrTotalClienti;
		file >> nrClientiOnline;
		file >> nrClientiFizici;
		cout << "Dintr-un numar total de " << nrTotalClienti << " clienti, " << nrClientiOnline << " sunt clienti online , iar " << nrClientiFizici << " sunt clienti prezenti fizic in restaurant.";
	}
};

class Comanda
{
protected:

	const int IDComanda; //Id-ul comezii va creste automat
	static int contorIDComanda;
	int dataComanda[3]; //vector static de trei elemente: zi luna an
	Client clientComanda; // clientul care a plasat comanda;
	int nrPreparateDorite;
	Preparat* vectorPreparate;
	bool* preparatDisponibil;
	static MeniuRestaurant meniu;

public:
	//getteri
	int* getDataComanda()
	{
		return this->dataComanda;
	}

	int getNrPreparateDorire()
	{
		return this->nrPreparateDorite;
	}

	Client getClient()
	{
		return this->clientComanda;
	}

	Preparat* getVectoriPreparate()
	{
		return this->vectorPreparate;
	}

	bool* getPreparatDisponibil()
	{
		return this->preparatDisponibil;
	}

	//constructor fara param
	Comanda() :IDComanda(contorIDComanda++)
	{
		for (int i = 0; i < 3; i++)
			this->dataComanda[i] = 0;

		this->clientComanda = Client();
		this->nrPreparateDorite = 0;
		this->vectorPreparate = nullptr;
		this->preparatDisponibil = nullptr;
	}

	static void setMeniuRestaurant(MeniuRestaurant& m)
	{
		meniu = m;
	}

	//constructorul cu toti param
	Comanda(int dataComanda[3], Client clientComanda, int nrPreparateDorite, Preparat* vectorPreparate) :IDComanda(contorIDComanda++)
	{

		if (dataComanda[0] > 0 && dataComanda[0] <= 31)
			this->dataComanda[0] = dataComanda[0];
		else this->dataComanda[0] = 0;

		if (dataComanda[1] > 0 && dataComanda[1] <= 12)
			this->dataComanda[1] = dataComanda[1];
		else this->dataComanda[1] = 0;

		if (dataComanda[2] >2020)
			this->dataComanda[2] = dataComanda[2];
		else this->dataComanda[2] = 0;

		this->clientComanda = clientComanda;
		if (nrPreparateDorite > 0)
		{
			this->nrPreparateDorite = nrPreparateDorite;
			this->vectorPreparate = new Preparat[this->nrPreparateDorite];
			this->preparatDisponibil = new bool[this->nrPreparateDorite];

			for (int i = 0; i < this->nrPreparateDorite; i++)
			{
				this->vectorPreparate[i] = vectorPreparate[i];
				this->preparatDisponibil[i] = true;
			}
		}
		else
		{
			this->nrPreparateDorite = 0;
			this->vectorPreparate = nullptr;
			this->preparatDisponibil = nullptr;
		}
	}

	Comanda(const Comanda& obj) :IDComanda(contorIDComanda++)
	{
		for (int i = 0; i < 3; i++)
			this->dataComanda[i] = obj.dataComanda[i];

		this->clientComanda = obj.clientComanda;
		if (obj.nrPreparateDorite > 0)
		{
			this->nrPreparateDorite = obj.nrPreparateDorite;

			this->vectorPreparate = new Preparat[this->nrPreparateDorite];
			this->preparatDisponibil = new bool[this->nrPreparateDorite];

			for (int i = 0; i < this->nrPreparateDorite; i++)
			{
				this->vectorPreparate[i] = obj.vectorPreparate[i];
				this->preparatDisponibil[i] =true;
			}
		}
		else
		{
			this->nrPreparateDorite = 0;
			this->vectorPreparate = nullptr;
			this->preparatDisponibil = nullptr;
		}
	}

	Comanda& operator=(const Comanda& obj)
	{
		if (this != &obj)
		{
			delete[] this->vectorPreparate;
			this->vectorPreparate = nullptr;
			delete[] this->preparatDisponibil;
			this->preparatDisponibil = nullptr;

			for (int i = 0; i < 3; i++)
				this->dataComanda[i] = obj.dataComanda[i];

			this->clientComanda = obj.clientComanda;
			if (obj.nrPreparateDorite > 0)
			{
				this->nrPreparateDorite = obj.nrPreparateDorite;
				this->vectorPreparate = new Preparat[this->nrPreparateDorite];
				this->preparatDisponibil = new bool[this->nrPreparateDorite];
				for (int i = 0; i < this->nrPreparateDorite; i++)
				{
					this->vectorPreparate[i] = obj.vectorPreparate[i];
					this->preparatDisponibil[i] = true;
				}
			}
			else
			{
				this->nrPreparateDorite = 0;
				this->vectorPreparate = nullptr;
			}
		}
		return *this;
	}

	bool operator!=(Comanda& obj)
	{
		if (this->nrPreparateDorite == obj.nrPreparateDorite)
			return false;
		else return true;
	}

	//metoda de calcul pret total cmd
	 virtual float pretTotalComanda()
	{
		float pretTotalComanda=0;

		for (int i = 0; i < this->nrPreparateDorite; i++)
		{
			pretTotalComanda += this->vectorPreparate[i].getPretPreparat();
		}
		return pretTotalComanda;
	}

	//operatorul<<
	friend ostream& operator<<(ostream& out, Comanda& obj)
	{
		
		out << "ID comanda: " << obj.IDComanda << endl;
		out << "Data comanda: ";
		for (int i = 0; i < 3; i++)
			out << obj.dataComanda[i] << " ";
		out << "\nClient: \n" << obj.clientComanda << endl;
		out << "Numar de preparate dorite: " << obj.nrPreparateDorite << endl;
		out << "Vector preparate: " << endl;
		for (int i = 0; i < obj.nrPreparateDorite; i++)
		{
			if(obj.vectorPreparate[i].getNrMateriiPrime()!=0)
			out << obj.vectorPreparate[i] << endl;
		}

		return out;
	}

	//operatorul>>
	friend istream& operator>>(istream& in, Comanda& obj)
	{
		if (obj.vectorPreparate != nullptr)
		{
			delete[] obj.vectorPreparate;
			obj.vectorPreparate = nullptr;
		}

		cout << "Introduceti ziua comenzii: ";
		int aux=0;
		in >> aux;
		if (aux > 0 && aux <= 31)
			obj.dataComanda[0] = aux;
		else obj.dataComanda[0] = 0;

		cout << "Introduceti luna comenzii: ";
		int aux1;
		in >> aux1;
		if (aux1 > 0 && aux1 <= 12)
			obj.dataComanda[1] = aux1;
		else obj.dataComanda[1] = 0;

		cout << "Introduceti anul comenzii: ";
		int aux2=0;
		in >> aux2;
		if (aux2 > 2020)
			obj.dataComanda[2] = aux2;
		else obj.dataComanda[2] = 0;

		cout << "\nIntroduceti detaliile despre Client: \n" ;
		in >> obj.clientComanda;

		cout << "Introduceti numarul de preparate dorite: " ;
		int aux3=0;
		in >> aux3;
		if (aux3 > 0)
		{
			int ok = 1;
			obj.nrPreparateDorite = aux3;
			obj.vectorPreparate = new Preparat[obj.nrPreparateDorite];
			obj.preparatDisponibil = new bool[obj.nrPreparateDorite];
			for (int i = 0; i < obj.nrPreparateDorite; i++)
			{
				//citire preparat
				in >> obj.vectorPreparate[i];
				obj.preparatDisponibil[i] = false;
				obj.vectorPreparate[i] = obj.meniu.returnPreparat(obj.vectorPreparate[i]);
				if (obj.vectorPreparate[i] != Preparat())
					//verificare procesare preparat
				{
					for (int j = 0; j < obj.vectorPreparate[i].getNrMateriiPrime(); j++)
					{
						int dif = 0;

						if (obj.vectorPreparate[i].getVectorMateriiPrime()[j].getNrBucPeStoc() > obj.vectorPreparate[i].getNrBucatiMateriePrima()[j])
						{
							dif = obj.vectorPreparate[i].getNrBucatiMateriePrima()[j];
							obj.vectorPreparate[i].getVectorMateriiPrime()[j].scadeBucMateriePrima(dif);
							obj.preparatDisponibil[i] = true;
						}
						else {
							bool decizie;
							cout << "\nPreparatul " << obj.vectorPreparate[i].getDenumirePreparat() << " nu poate fi procesat \n";
							cout << "\nDoriti sa pastrati comanda? ";
							cin >> decizie;
							if (decizie == false)
							{
								ok = 0;
							}
							else {
								obj.vectorPreparate[i] = Preparat();
							}

						}
					}
				}

				else
				{
					cout << "\nDenumire introdusa gresit\n";
					ok = 0;
					break;
				}
			}

			if (ok == 1)
			{
				cout << "\nComanda preluata cu succes\n";
			}

			else
			{
				obj.nrPreparateDorite = 0;
				obj.vectorPreparate = nullptr;
				cout << "\nComanda nepreluata\n";
			}
		}
		else
		{
			obj.nrPreparateDorite = 0;
			obj.vectorPreparate = nullptr;
		}
		return in;
	}

	~Comanda()
	{
			delete[] this->vectorPreparate;
			this->vectorPreparate = nullptr;
			delete[] this->preparatDisponibil;
			this->preparatDisponibil = nullptr;
	}

	//FISIER TEXT
	//scriere in fisier text
	friend ofstream& operator<<(ofstream& file, Comanda& obj)
	{
		//int dataComanda[3]; 
		for (int i = 0; i < 3; i++)
		{
			file << obj.dataComanda[i] << endl;
		}

		//Client clientComanda; 
		file << obj.clientComanda << endl;

		//int nrPreparateDorite;
		file << obj.nrPreparateDorite << endl;

		//Preparat* vectorPreparate;
		for (int i = 0; i < obj.nrPreparateDorite; i++)
		{
			file << obj.vectorPreparate[i] << endl;
		}

		return file;
	}

	//citire din fisier text
	friend ifstream& operator>>(ifstream& file, Comanda& obj)
	{
		delete[] obj.vectorPreparate;

		//int dataComanda[3]; 
		file >> obj.dataComanda[0];
		file >> obj.dataComanda[1];
		file >> obj.dataComanda[2];

		//Client clientComanda; 
		file >> obj.clientComanda;

		//int nrPreparateDorite;
		file >> obj.nrPreparateDorite;
		obj.vectorPreparate = new Preparat[obj.nrPreparateDorite];

		//Preparat* vectorPreparate;
		for (int i = 0; i < obj.nrPreparateDorite; i++)
		{
			file >> obj.vectorPreparate[i];
		}

		return file;
	}

	//FISIER BINAR
	// scriere in fisier binar
	virtual void scriereBinarComanda(fstream& file)
	{
		//int dataComanda[3]; 
		file.write((char*)&this->dataComanda[0], sizeof(int));
		file.write((char*)&this->dataComanda[1], sizeof(int));
		file.write((char*)&this->dataComanda[2], sizeof(int));

	   //Client clientComanda; 
		this->clientComanda.scriereBinarClient(file);

	   //int nrPreparateDorite;
		file.write((char*)&this->nrPreparateDorite, sizeof(int));

	   //Preparat* vectorPreparate;
		for (int i = 0; i < this->nrPreparateDorite; i++)
		{
			this->vectorPreparate[i].scriereBinarPreparat(file);
		}
	}

	// citire din fisier binar
	virtual void citireBinarComanda(fstream& file)
	{
		delete[] this->vectorPreparate;

		//int dataComanda[3]; 
		file.read((char*)&this->dataComanda[0], sizeof(int));
		file.read((char*)&this->dataComanda[1], sizeof(int));
		file.read((char*)&this->dataComanda[2], sizeof(int));

		//Client clientComanda; 
		this->clientComanda.citireBinarClient(file);

		//int nrPreparateDorite;
		file.read((char*)&this->nrPreparateDorite, sizeof(int));

		this->vectorPreparate = new Preparat[this->nrPreparateDorite];
		//Preparat* vectorPreparate;
		for (int i = 0; i < this->nrPreparateDorite; i++)
		{
			this->vectorPreparate[i].citireBinarPreparat(file);
		}
	}

	//Raport privind suma totala incasata de restaurant pe anul 2023
	static void inacasariAnuale(ofstream& file, int nrComenzi, Comanda* comenzi)
	{
		float totalIncasari = 0;
		int k=0;
		for (int i = 0; i < nrComenzi; i++)
		{
			if (comenzi[i].getDataComanda()[2] == 2023)
			{
				k++;
				totalIncasari += comenzi[i].pretTotalComanda();
			}
		}

		file << totalIncasari << endl;
		file << k << endl;
	}

	static void afisareRaportTotalIncasari(ifstream& file)
	{
		int nrComenzi=0;
		float totalIncasari=0;
		file >> totalIncasari;
		cout << "In anul 2023 restaurantul a avut incasari in valoare de " << totalIncasari << " lei" << endl << endl;
		file >> nrComenzi;
		cout << "In anul 2023 restaurantul a avut un numar de " << nrComenzi << " comenzi"<<endl<<endl;
	}
};

class ComandaGlovo :public Comanda
{
	string adresaLivrare;
	float pretLivrare;
	bool bacsisLivrator;

public:
	//getteri
	string getAdresaLivrare()
	{
		return this->adresaLivrare;
	}

	float getPretLivrare()
	{
		return this->pretLivrare;
	}

	bool getBacsisLivrator()
	{
		return this->bacsisLivrator;
	}

	//setteri
	void setAdresaLivrare(string AdresaNouaLivrare)
	{
		this->adresaLivrare = AdresaNouaLivrare;
	}

	void setPretLivrare(float pretNouLivrare)
	{
		if (pretNouLivrare >= 0)
			this->pretLivrare = pretNouLivrare;

		else this->pretLivrare = 0;
	}

	void setBacsisLivrator(bool bacsisLivratorActualizat)
	{
		this->bacsisLivrator = bacsisLivratorActualizat;
	}

	//constr fara param
	ComandaGlovo() :Comanda()
	{
		this->adresaLivrare = "Necunoscuta";
		this->pretLivrare = 0;
		this->bacsisLivrator = true;
	}

	//constr cu toti param
	ComandaGlovo(string adresaLivrare, float pretLivrare, bool bacsisLivrator, int dataComanda[3], Client clientComanda, int nrPreparateDorite, Preparat* vectorPreparate) :Comanda(dataComanda, clientComanda, nrPreparateDorite, vectorPreparate)
	{
		this->adresaLivrare = adresaLivrare;
		if (pretLivrare > 0)
			this->pretLivrare = pretLivrare;
		else this->pretLivrare = 0;

		this->bacsisLivrator = bacsisLivrator;
	}

	//constr de copiere
	ComandaGlovo(const ComandaGlovo& comandaGlovo):Comanda(comandaGlovo)
	{
		this->adresaLivrare = comandaGlovo.adresaLivrare;
		this->pretLivrare = comandaGlovo.pretLivrare;
		this->bacsisLivrator = comandaGlovo.bacsisLivrator;
	}

	//destructor
	~ComandaGlovo() {}

	//operatorul de afisare
	friend ostream& operator<<(ostream& out, const ComandaGlovo& obj)
	{
		out << "Adresa de livrare este: " << obj.adresaLivrare << endl;
		out << "Pretul livrarii este: " << obj.pretLivrare << endl;
		out << "Bacsis livrator ? 1-da, 0-nu. : " << obj.bacsisLivrator << endl;
		out << (Comanda&)obj;

		return out;
	}

	//operatorul =
	ComandaGlovo& operator=(const ComandaGlovo& comandaGlovo)
	{
		if (this != &comandaGlovo)
		{
			Comanda::operator=(comandaGlovo);
			this->adresaLivrare = comandaGlovo.adresaLivrare;
			this->pretLivrare = comandaGlovo.pretLivrare;
			this->bacsisLivrator = comandaGlovo.bacsisLivrator;
		}
		return *this;
	}

	//downcasting
	ComandaGlovo(const Comanda& obj):Comanda(obj)
	{
		this->adresaLivrare = "stradaNecunoscuta";
		this->bacsisLivrator = 0;
		this->pretLivrare = 10;
	}

	//operatorul de citire
	friend istream& operator>>(istream& in, ComandaGlovo& obj)
	{
		cout << "Introduceti adresa de livrare: ";
		in >> obj.adresaLivrare;
		cout << "Introduceti pretul livrarii: ";
		in >> obj.pretLivrare;
		cout << "Livratorul primeste bacsis? 1-da, 0-nu.";
		in >> obj.bacsisLivrator;
		in >> (Comanda&)obj;

		return in;
	}

	//scriere in fisier binar
	void scriereBinarComanda(fstream& file)
	{
		Comanda::scriereBinarComanda(file);
		//string adresaLivrare;
		int nrLitere;
		nrLitere = this->adresaLivrare.length();
		file.write((char*) & nrLitere, sizeof(int));
		file.write(this->adresaLivrare.c_str(), nrLitere);

		//float pretLivrare;
		file.write((char*)&this->pretLivrare, sizeof(float));

		//bool bacsisLivrator;
		file.write((char*)&this->bacsisLivrator, sizeof(bool));
	}

	//citire din fisier binar
	void citireBinarComanda(fstream& file)
	{
		Comanda::citireBinarComanda(file);
		//string adresaLivrare;
		int nrLitere;
		file.read((char*)&nrLitere, sizeof(int));
		string aux;
		aux.resize(nrLitere);
		file.read((char*)aux.c_str(), nrLitere);
		this->adresaLivrare = aux;

		//float pretLivrare;
		file.read((char*)&this->pretLivrare, sizeof(float));

		//bool bacsisLivrator;
		file.read((char*)&this->bacsisLivrator, sizeof(bool));

	}

	//calcul pret total comanda
	float pretTotalComanda()
	{
		float pret;
		pret = Comanda::pretTotalComanda() + this->pretLivrare;

		return pret;
	}

	//operatorul < pentru pretul livrarii

	bool operator<(const ComandaGlovo& obj) const
	{
		if (this->pretLivrare < obj.pretLivrare)
			return 1;
		else return 0;
	}

};

int Comanda::contorIDComanda = 0;
MeniuRestaurant Comanda::meniu = MeniuRestaurant();

void MeniuComenzi()
{
	cout << "\n------------------------------------------\n";
	cout << endl << endl << endl << endl;
	cout << "----------------- Meniu Comenzi ---------------" << endl;
	cout << "-1.  Afiseaza materia prima"<<endl;
	cout << "-2.  Citeste materia prima" << endl;
	cout << "-3.  Creste cantitatea materiei prime"<<endl;
	cout << "-4.  Afiseaza preparat" << endl;
	cout << "-5.  Modifica pret preparat" << endl;
	cout << "-6.  Adauga preparat in meniu" << endl;
	cout << "-7.  Preluare comanda client" << endl;
	cout << "-8.  Scrie comanda in fisier csv" << endl;
	cout << "-9.  Scrie si citeste o comanda din fisier binar" << endl;
	cout << "-10. Raport privind materiile prime care au un stoc sub 50 buc " << endl;
	cout << "-11. Raport privind preturile preparatelor din meniu" << endl;
	cout << "-12. Raport privind numarul de kcal al preparatelor din meniu" << endl;
	cout << "-13. Raport privind incasarile anuale ale restaurantului" << endl;
	cout << "-14. Raport privind preferintele clientilor " << endl;
	cout << "-15. Iesire meniu comenzi"<<endl;
	cout << "----------------------------------------------------\n";
}

int main()
{

	//clasa materie prima
	MateriePrima m1;
	cout << m1;
	cout << endl << endl;
	MateriePrima m2("Caracatita", 150, 75);
	cout << m2;

	cout << endl << endl;
	MateriePrima m3(m2);
	cout << m3;
	cout << endl << endl;
	MateriePrima m4("Calamar", 100, 66);
	m3 = m4;
	cout << m3;

	cout << endl << endl;
	MateriePrima m5("Crab", 1, 44);
	cout << "Denumire materie prima: ";
	cout << m5.getDenumireMateriePrima() << endl;
	cout << "Numar bucati pe stoc: ";
	cout << m5.getNrBucPeStoc() << endl;
	cout << "Numar de kcal: ";
	cout << m5.getKcal() << endl;

	cout << endl << endl;
	m5.setDenumireMateriePrima("Peste");
	m5.setNrBucMateriePrima(30);
	m5.setKcal(8);
	cout << "Denumire materie prima: ";
	cout << m5.getDenumireMateriePrima() << endl;
	cout << "Numar bucati pe stoc: ";
	cout << m5.getNrBucPeStoc() << endl;
	cout << "Numar de kcal: ";
	cout << m5.getKcal() << endl;

	cout << endl << endl;
	cout << m1;
	cout << endl << endl;
	/*cin >> m1;
	cout << endl << endl;
	cout << m1;*/


	cout << m2;
	m2.adaugaBucMateiePrima(5);
	cout << endl << endl;
	cout << m2;
	cout << endl << endl;
	m2.scadeBucMateriePrima(6);
	cout << m2;
	cout << endl << endl;

	MateriePrima m6("Creveti", 1, 77);
	MateriePrima m7("Paste", 10, 40);
	MateriePrima m8("Ou", 100, 6);
	MateriePrima m9("Pesmet", 5, 2);
	MateriePrima m10("Scoici", 10000, 7);
	MateriePrima m11("Ulei", 70, 90);
	MateriePrima m12("Rosii", 900, 8);
	MateriePrima m13("ArdeiGras", 300, 7);
	MateriePrima m14("Patrunjel", 90, 3);
	MateriePrima m15("Unt", 800, 6);
	MateriePrima m16("Usturoi", 100, 3);
	MateriePrima m17("Cartofi", 100000, 3);
	MateriePrima m18("FileDePeste", 900, 60);
	MateriePrima m19("Lamaie", 300, 9);
	MateriePrima m20("Salata", 30, 2);
	MateriePrima m21("BranzaFeta", 2, 80);
	MateriePrima m22("vinSec", 6, 8);

	//clasa client
	Client c1;
	cout << c1;
	cout << endl << endl;
	/*cin >> c1;
	cout << c1;*/

	Client c2("PopescuAna", 0, 1);
	cout << "NumePrenume client: " << c2.getNumePrenume() << endl;
	cout << "Este client online? 1-clientOnline, 0-clientFizic: " << c2.getClientOnline() << endl;
	cout << "Numar masa: " << c2.getNrMasa() << endl;
	cout << endl << endl;

	Client c3;
	c3.setNumePrenume("RobertCostescu");
	c3.setClientOnline(0);
	c3.setNumarMasa(5);
	cout << "NumePrenume client: " << c3.getNumePrenume() << endl;
	cout << "Este client online? 1-clientOnline, 0-clientFizic: " << c3.getClientOnline() << endl;
	cout << "Numar masa: " << c3.getNrMasa() << endl;
	cout << endl << endl;

	Client c5("AvramIon", 0, 6);
	Client c6("GigelVasile", 1, 9);
	Client c8("BraeteGladis", 1, 6);
	Client c9("AvramescuAlberta", 0, 6);
	Client c10("PalitaAlberta", 0, 6);

	Client c4(c1);
	cout << c4;
	cout << endl << endl;
	c4 = c2;
	cout << c4;
	cout << endl << endl;

	cout << endl << endl;
	//clasa preparat
	Preparat p1;
	cout << p1;

	cout << endl << endl;
	MateriePrima vectorMateriiPrime1[] = { m6,m7,m14, m11,m16 };
	int nrBucMateriiPrime1[] = { 10,1,1,1,1 };
	Preparat p2("PasteCuCreveti", 100.9, 2, vectorMateriiPrime1, nrBucMateriiPrime1, 1);
	cout << p2;

	cout << endl << endl;
	Preparat p3(p1);
	cout << p3;
	cout << endl << endl;
	MateriePrima vectorMateriiPrime2[] = { m2,m20,m19,m11 };
	int nrBucMateriiPrime2[] = { 2,1,1,1 };
	Preparat p4("CaracatitaLaGratar", 99.99, 1, vectorMateriiPrime2, nrBucMateriiPrime2, 1);
	p3 = p4;
	cout << p3;

	MateriePrima vectorMateriiPrime5[] = { m4,m20,m21,m19,m11 };
	int nrBucMateriiPrime5[] = { 2,1,1,2 ,1 };
	Preparat p5("CalamarCuFeta", 78.99, 5, vectorMateriiPrime5, nrBucMateriiPrime5, 1);

	MateriePrima vectorMateriiPrime6[] = { m10,m22,m14,m16,m11 };
	int nrBucMateriiPrime6[] = { 10,1,1,2 ,1 };
	Preparat p6("ScoiciInSosDeVin", 78.99, 5, vectorMateriiPrime5, nrBucMateriiPrime5, 1);

	MateriePrima vectorMateriiPrime7[] = { m18,m10,m4,m6,m8,m11,m19 };
	int nrBucMateriiPrime7[] = { 4,10,4,10 ,2, 1,1 };
	Preparat p7("FrittoMisto", 71, 5, vectorMateriiPrime5, nrBucMateriiPrime5, 1);

	cout << endl << endl;
	cout << "Denumire preparat: " << p4.getDenumirePreparat() << endl;
	cout << "Pret preparat: " << p4.getPretPreparat() << endl;
	cout << "Nr materii prime: " << p4.getNrMateriiPrime() << endl;
	cout << "Vectori materii prime: " << endl;
	for (int i = 0; i < p4.getNrMateriiPrime(); i++)
	{
		cout << p4.getVectorMateriiPrime()[i] << endl;
		cout << "Nr bucati materie prima: ";
		cout << p4.getNrBucatiMateriePrima()[i] << endl;
		cout << endl;
	}
	cout << "Necesita preparare termica? 1-da, 0-nu. " << p4.getNecesitaPreparareTermica() << endl;

	p4.setDenumirePreparat("CalamarPane");
	p4.setPretPreparat(78.8);
	MateriePrima vectorMateriePrima3[] = { m4,m8,m9 };
	int nrBucatiMateriePrima3[] = { 20,4,1 };
	p4.setVectorMateriiPrime(3, vectorMateriePrima3, nrBucatiMateriePrima3);
	p4.setNecesitaPreparareTermica(1);
	cout << endl << endl;
	cout << "Denumire preparat: " << p4.getDenumirePreparat() << endl;
	cout << "Pret preparat: " << p4.getPretPreparat() << endl;
	cout << "Nr materii prime: " << p4.getNrMateriiPrime() << endl;
	cout << "Vectori materii prime: " << endl;
	for (int i = 0; i < p4.getNrMateriiPrime(); i++)
	{
		cout << p4.getVectorMateriiPrime()[i] << endl;
		cout << "Nr bucati materie prima: ";
		cout << p4.getNrBucatiMateriePrima()[i] << endl;
		cout << endl;
	}
	cout << "Necesita preparare termica? 1-da, 0-nu. " << p4.getNecesitaPreparareTermica() << endl;

	/*cout << endl << endl;
	cin >> p1;*/
	/*cout << endl << endl;
	cout << p1;*/
	cout << endl << endl;
	cout << "Pret preparat: " << p4.getPretPreparat() << endl;
	try
	{
		p4 = p4 + 20;
		cout << endl << endl;
		cout << "Pret preparat: " << p4.getPretPreparat() << endl;
		cout << endl << endl;
	}
	catch (Exceptie obj)
	{
		cout << obj.mesajEroare << endl;
	}

	try
	{
		p4 = p4 - 100;
		cout << "Pret preparat: " << p4.getPretPreparat() << endl;
		cout << endl << endl;
	}
	catch (Exceptie obj)
	{
		cout << obj.mesajEroare << endl;
	}

	cout << endl << endl << endl;
	//clasa comanda
	Comanda cmd1;
	cout << cmd1;
	cout << endl;

	int data[] = { 12,12,2023 };
	Preparat vector0[] = { p5,p6 };
	Comanda cmd5(data, c2, 2, vector0);
	cout << cmd1;
	cout << endl;
	Comanda cmd3(cmd1);
	cout << cmd3;
	cout << endl << endl;

	/*try {
		cin >> cmd1;
		cout << endl << endl;
		cout << cmd1;
		cout << endl << endl;
	}
	catch (Exceptie obj)
	{
		cout << obj.mesajEroare << endl;
	}*/

	cout << endl << endl;
	cout << endl << endl;
	MeniuRestaurant meniu0;
	//clasa meniu
	cout << "\n-------------------------------------------------------------------------------------------------\n";

	Preparat** vectorPointerPreparate;
	vectorPointerPreparate = new Preparat * [5];
	vectorPointerPreparate[0] = new Preparat(p2);
	vectorPointerPreparate[1] = new Preparat(p4);
	vectorPointerPreparate[2] = new Preparat(p5);
	vectorPointerPreparate[3] = new Preparat(p6);
	vectorPointerPreparate[4] = new Preparat(p7);
	MeniuRestaurant meniu1(5, vectorPointerPreparate);

	Comanda::setMeniuRestaurant(meniu1);

	cout << meniu1;
	cout << "\n-------------------------------------------------------------------------------------------------";

	int dataComanda1[] = { 01, 12, 2023 };
	Preparat vectorPreparate1[] = { p1,p2 };
	Comanda cmd2(dataComanda1, c1, 2, vectorPreparate1);
	cout << cmd2;
	cout << endl << endl;

	/*cout << endl << endl;
	cout << endl << endl;
	cout  << p2.getDenumirePreparat() << endl;
	cout << "preparatele p2 si p2 au aceeasi denumire? " << (p2 == p2) << endl;*/

	cout << p2 << endl;
	cout << p2() << endl;
	cout << endl << endl;
	Preparat p;
	cout << p.getPretPreparat() << endl;
	cout << p2.getPretPreparat() << endl;

	p=++p2;
	cout << "operatorul++ pre-incrementare: " << p.getPretPreparat() <<" " << p2.getPretPreparat() << endl;
	p=p2++;
	cout << "operatorul++ post-incrementare: " << p.getPretPreparat() << " " << p2.getPretPreparat() << endl;
	cout << endl << endl << endl;
	cout << "\n-------------------------------------------------------------------------------------------------\n";
	//cin >> cmd2;
	cout << "\n-------------------------------------------------------------------------------------------------\n";
	cout << endl << endl << endl;
	cout << endl << endl << endl;
	cout << endl << endl << endl;

	cout << "\n-------FISIER TEXT Materie Prima----------\n";
	ofstream f1("FisierTextMateriePrima.txt", ios::out);
	f1 << m3;
	f1.close();

	cout << "\nMateria prima 1 inainte de citirea din fisier text\n" << m1 << endl << endl;
	ifstream f2("FisierTextMateriePrima.txt", ios::in);
	f2 >> m1;
	f1.close();

	cout << "\nMateria prima 1 dupa citirea din fisier text\n" << m1 << endl << endl;
	cout << "\n-------FISIER Binar Materie Prima----------\n";

	fstream f3("FisierBinarMateriePrima.bin", ios::binary | ios::out);
	m3.scriereInFBinarMPrima(f3);
	f3.close();

	MateriePrima m30;
	cout << "Materia prima inainte de citirea din fisier binar: \n" << m30 << endl<<endl;
	fstream f4("FisierBinarMateriePrima.bin", ios::binary | ios::in);
	m30.citireFBinarMPrima(f4);
	f4.close();
	cout << "\nMateria prima dupa citirea din fisier binar: \n" << m30 << endl;

	cout << endl << endl;
	cout << "\nClientul c2: \n" << c2;
	cout << endl << endl;

	cout << "\n-------FISIER TEXT Client----------\n";
	ofstream f5("FisierTextClient.txt", ios::out);
	f5 << c2;
	f5.close();

	cout << "\nClientul c1 inainte de citirea din fisierul text\n" << c1 << endl << endl;
	ifstream f6("FisierTextClient.txt", ios::in);
	f6 >> c1;
	f6.close();
	cout << "\nClientul c1 dupa citirea din fisierul text\n" << c1 << endl << endl;

	cout << "\n-------FISIER Binar Client----------\n";
	fstream f7("FisierBinarClient.bin", ios::binary | ios::out);
	c3.scriereBinarClient(f7);
	f7.close();

	cout << "\nClientul c1 inainte de citirea din fisierul binar\n" << c1 << endl << endl;
	fstream f8("FisierBinarClient.bin", ios::binary | ios::in);
	c1.citireBinarClient(f8);
	f8.close();
	cout << "\nClientul c1 dupa citirea din fisierul binar\n" << c1 << endl << endl;

	cout << "\n-------FISIER TEXT Preparat----------\n";
	ofstream f9("FisierTextPreparat.txt", ios::out);
	f9 << p4;
	f9.close();

	cout << "\nPreparatul p1 inainte de citirea din fisier text: \n" << p1.getDenumirePreparat() << endl << endl;
	ifstream f10("FisierTextPreparat.txt", ios::in);
	f10 >> p1;
	f10.close();
	cout << "\nPreparatul p1 dupa citirea din fisier text: \n" << p1.getDenumirePreparat() << endl << endl;

	cout << "\n-------FISIER Binar Preparat----------\n";
	fstream f11("FisierBinarPreparat.bin", ios::binary | ios::out);
	p7.scriereBinarPreparat(f11);
	f11.close();

	cout << "\nPreparatul p1 inainte de citirea din fisier binar: \n" << p1.getDenumirePreparat() << endl << endl;

	fstream f12("FisierBinarPreparat.bin", ios::binary | ios::in);
	p1.citireBinarPreparat(f12);
	f12.close();
	cout << "\nPreparatul p1 dupa citirea din fisier binar: \n" << p1.getDenumirePreparat() << endl << endl;

	cout << "\n-------FISIER TEXT MeniuRestaurant----------\n";
	ofstream f13("FisierTextMeniuRestaurant.txt", ios::out);
	f13 << meniu1;
	f13.close();

	MeniuRestaurant meniu3;
	MeniuRestaurant meniu4;
	cout << "\nMeniul inainte de citirea din fisier text: \n" << meniu3 << endl << endl; 
	ifstream f14("FisierTextMeniuRestaurant.txt", ios::in);
	f14 >> meniu3;
	f14.close();
	cout << "\nMeniul dupa citirea din fisier text: \n" << meniu3 << endl << endl;


	cout << "\n-------FISIER Binar MeniuRestaurant----------\n";
	fstream f15("FisierBinarMeniuRestaurant.bin", ios::binary | ios::out);
	meniu3.scriereBinarMeniuRestaurant(f15);
	f15.close();

	cout << "\nMeniul inainte de citirea din fisier binar: \n" << meniu4 << endl << endl;

	fstream f16("FisierBinarMeniuRestaurant.bin", ios::binary | ios::in);
	meniu4.citireBinarMeniuRestaurant(f16);
	f16.close();
	cout << "\nMeniul dupa citirea din fisier binar: \n" << meniu4 << endl << endl;

	cout << "\n-------FISIER TEXT Comanda----------\n";
	ofstream f17("FisierTextComanda.txt", ios::out);
	f17 << cmd5;
	f17.close();

	cout << "\nComanda inainte de a fi citita din fisierul text\n" ;
	cout << "Data comanda: ";
	for (int i = 0; i < 3; i++)
	{
		cout << cmd1.getDataComanda()[i]<<" ";
	}
	cout << "\nClient: \n";
	cout << "NumePrenume client: " << cmd1.getClient().getNumePrenume() << endl;;
	cout << "Este client online? 1-clientOnline, 0-clientFizic: " << cmd1.getClient().getClientOnline() << endl;
	cout << "Numar masa: " << cmd1.getClient().getNrMasa() << endl;
	cout << "Numar de preparate dorite: " << cmd1.getNrPreparateDorire() << endl;
	cout << "Vector preparate: " << endl;
	for (int i = 0; i < cmd1.getNrPreparateDorire(); i++)
	{
		cout << cmd1.getVectoriPreparate()[i] << endl;
	}

	ifstream f18("FisierTextComanda.txt", ios::in);
	f18 >> cmd1;
	f18.close();

	cout << "\nComanda dupa ce a fost citita din fisierul text\n";
	cout << "Data comanda: ";
	for (int i = 0; i < 3; i++)
	{
		cout << cmd1.getDataComanda()[i] <<" ";
	}
	cout << "\nClient: \n";
	cout << "NumePrenume client: " << cmd1.getClient().getNumePrenume() << endl;;
	cout << "Este client online? 1-clientOnline, 0-clientFizic: " << cmd1.getClient().getClientOnline() << endl;
	cout << "Numar masa: " << cmd1.getClient().getNrMasa() << endl;
	cout << "Numar de preparate dorite: " << cmd1.getNrPreparateDorire() << endl;
	cout << "Vector preparate: " << endl;
	for (int i = 0; i < cmd1.getNrPreparateDorire(); i++)
	{
		cout << cmd1.getVectoriPreparate()[i] << endl;
	}

	cout << "\n-------FISIER Binar Comanda----------\n";
	fstream f19("FisierBinarComanda.bin", ios::binary | ios::out);
	cmd5.scriereBinarComanda(f19);
	f19.close();

	Comanda cmd7;
	cout << "\nComanda inainte de citirea din fisier binar\n" ;
	cout << "Data comanda: ";
	for (int i = 0; i < 3; i++)
	{
		cout << cmd7.getDataComanda()[i]<<" ";
	}
	cout << "\nClient: \n" ;
	cout << "NumePrenume client: " << cmd7.getClient().getNumePrenume() << endl;;
	cout << "Este client online? 1-clientOnline, 0-clientFizic: " << cmd7.getClient().getClientOnline() << endl;
	cout << "Numar masa: " << cmd7.getClient().getNrMasa() << endl;
	cout << "Numar de preparate dorite: " << cmd7.getNrPreparateDorire() << endl;
	cout << "Vector preparate: " << endl;
	for (int i = 0; i < cmd7.getNrPreparateDorire(); i++)
	{
		cout << cmd7.getVectoriPreparate()[i] << endl;
	}

	fstream f20("FisierBinarComanda.bin", ios::binary | ios::in);
	cmd7.citireBinarComanda(f20);
	f20.close();

	cout << "\nComanda dupa citirea din fisier binar\n";
	cout << "Data comanda: ";
	for (int i = 0; i < 3; i++)
	{
		cout << cmd7.getDataComanda()[i]<<" ";
	}
	cout << "\nClient: \n" ;
	cout << "NumePrenume client: " << cmd7.getClient().getNumePrenume() << endl;;
	cout << "Este client online? 1-clientOnline, 0-clientFizic: " << cmd7.getClient().getClientOnline() << endl;
	cout << "Numar masa: " << cmd7.getClient().getNrMasa() << endl;
	cout << "Numar de preparate dorite: " << cmd7.getNrPreparateDorire() << endl;
	cout << "Vector preparate: " << endl;
	for (int i = 0; i < cmd7.getNrPreparateDorire(); i++)
	{
		cout << cmd7.getVectoriPreparate()[i] << endl;
	}

	cout << endl << endl << endl;
	cout << "-----------Scrierea in fisier CSV Materie Prima----------------\n" << endl;
	ofstream f30("ScriereFisierMateriePrimaCsv.csv", ios::out);
	f30 << m20;
	f30.close();

	cout << endl << endl << endl;
	cout << "-----------Scrierea in fisier CSV Preparat----------------\n" << endl;
	ofstream f31("ScriereFisierCsvPreparat.csv", ios::out);
	f31 << p6;
	f31.close();


	cout << "-----------Scrierea in fisier CSV MeniuRestaurant----------------\n" << endl;
	ofstream f32("ScriereFisierCsvMeniuRestaurant.csv", ios::out);
	f32 << meniu1;
	f32.close();

	cout << "-----------Scrierea in fisier CSV Client----------------\n" << endl;
	ofstream f33("ScriereFisierCsvClient.csv", ios::out);
	f33 << c8;
	f33.close();

	cout << "-----------Scrierea in fisier CSV Comanda----------------\n" << endl;
	ofstream f34("ScriereFisierCsvComanda.csv", ios::out);
	f34 << cmd5;
	f34.close();

	cout << endl << endl << endl;
	cout << "-----------Raport materie prima stoc sub 50 buc----------------\n" << endl;
	MateriePrima vectorMateriiPrimeRaport[] = { m5, m2, m4,m7,m9,m10,m22,m20,m21,m11 };
	ofstream raport1("RaportStocMateriePrima.txt", ios::out);
	MateriePrima::raportStocMateriePrima(raport1, 10, vectorMateriiPrimeRaport);
	raport1.close();

	ifstream raport2("RaportStocMateriePrima.txt", ios::in);
	MateriePrima::afisareRaport(raport2);
	raport2.close();



	cout << endl << endl << endl;
	cout << "-----------Raport pret max/min preparat----------------\n" << endl;
	Preparat vectorPreparatRaport[] = { p2,p4,p5,p6,p7 };
	ofstream raport3("RaportPretPreparat.txt", ios::out);
	Preparat::raportPretPreparat(raport3, 5, vectorPreparatRaport);
	raport3.close();

	ifstream raport4("RaportPretPreparat.txt", ios::in);
	Preparat::afisareRaportPreparat(raport4);
	raport4.close();


	cout << "-----------Raport preparat cu cele mai multe kcal----------------\n" << endl;
	Preparat vectorPreparatRaport2[] = { p2,p4,p5,p6,p7 };
	ofstream raport5("RaportPreparatMaxKcal.txt", ios::out);
	Preparat::raportPreparatKcal(raport5, 5, vectorPreparatRaport2);
	raport5.close();

	ifstream raport6("RaportPreparatMaxKcal.txt", ios::in);
	Preparat::afisarePreparatKcal(raport6);
	raport6.close();


	cout << endl << endl << endl;
	cout << "-----------Raport total incasari anuale----------------\n" << endl;
	
	int data7[] = { 10,12,2023 };
	Preparat vectorPreparate7[] = { p2,p5 };
	Comanda cmd13(data7, c2, 2, vectorPreparate7);

	int data17[] = { 10,12,2021 };
	Preparat vectorPreparate17[] = { p2,p5 };
	Comanda cmd17(data17, c2, 2, vectorPreparate17);

	int data8[] = { 10,05,2023 };
	Preparat vectorPreparate8[] = { p2,p4 };
	Comanda cmd8(data8, c3, 2, vectorPreparate8);

	int data9[] = { 15,07,2023 };
	Preparat vectorPreparate9[] = { p5,p4,p2 };
	Comanda cmd9(data8, c4, 3, vectorPreparate9);

	int data13[] = { 15,9,2023 };
	Preparat vectorPreparate13[] = { p7,p4,p2 };
	Comanda cmd16(data13, c4, 3, vectorPreparate13);

	Comanda vectorComenzi45[] = { cmd13,cmd8,cmd7,cmd9,cmd16,cmd17};
	
	ofstream raport8("RaportIncasariAnuale.txt", ios::out);
	Comanda::inacasariAnuale(raport8, 6, vectorComenzi45);
	raport5.close();

	ifstream raport9("RaportIncasariAnuale.txt", ios::in);
	Comanda::afisareRaportTotalIncasari(raport9);
	raport6.close();

	cout << endl << endl << endl;
	cout << "-----------Raport preferinte clienti----------------\n" << endl;

	Client vectorClientiRaport[] = { c2,c3,c5,c6,c8,c9,c10 };
	ofstream raport10("RaportPreferinteClienti.txt", ios::out);
	Client::scriereRaportClienti(raport10, 7, vectorClientiRaport);
	raport10.close();

	ifstream raport11("RaportPreferinteClienti.txt", ios::in);
	Client::afisareRaportClienti(raport11);
	raport11.close();


	cout << endl << endl << endl;
	cout << "\n----------IS-A MateriePrimaVegana------------\n";
	cout << "\nConstr fara param\n";
	MateriePrimaVegana mv1;
	cout << mv1;

	cout << "\nConstr cu toti param param\n";
	string vectorAlergeni[] = { "gluten","lupin" };
	MateriePrimaVegana mv2(1, 2, vectorAlergeni, "Ovaz", 20, 6);
	cout <<endl<< mv2<<endl;

	string vectorAlergeni3[] = { "sulfiti","sulfati" };
	MateriePrimaVegana mv4(1, 2, vectorAlergeni3, "MerisoareDezhidratate", 20, 10);

	string vectorAlergeni5[] = { "gluten"};
	MateriePrimaVegana mv5(1, 1, vectorAlergeni3, "Orz", 2, 60);

	string vectorAlergeni6[] = { "soia" };
	MateriePrimaVegana mv6(1, 1, vectorAlergeni6, "Soia", 2, 8);


	/*cin >> mv2;
	cout << endl << mv2 << endl;*/
	cout << "\nConstr de copiere\n";
	MateriePrimaVegana mv3(mv1);
	cout << endl << mv3 << endl;

	string vectorAlergeni1[] = { "gluten","lupin" };
	mv3.setAlergeni(2, vectorAlergeni1);
	mv3.setEsteCertificatVegan(1);
	cout << endl << mv3 << endl;

	cout << endl << endl << "Operatorul =\n";
	cout << "\nObiectul inainte de mofidicare:\n";
	cout << endl << mv3 << endl;
	cout << "\nObiectul macheta:\n";
	cout << endl << mv2 << endl;
	mv3 = mv2;
	cout << "\nObiectul dupa mofidicare:\n";
	cout << endl << mv3 << endl;

	cout << endl << endl << "---------------------UPCASTING-------------" << endl << endl;
	//sa se transforme  materia prima vegana in materie prima
	cout << "\nInainte de upcasting: \n" << mv3 << endl << endl;
	cout << "\nInainte de upcasting: \n" << m6 << endl << endl;
	m6 = mv3;
	cout << "\nDupa upcasting: \n" << m6 << endl << endl;

	cout << endl << endl << "---------------------DOWNCASTING-------------" << endl << endl;
	MateriePrimaVegana mvNoua = m7;
	cout << "\nMateria prima m7 care o sa fie transformata intr-o materie prima vegana: \n" << m7 << endl << endl;
	cout << "\nMateria prima vegana obtinuta prin transformarea materiei prime in materie prima vegana" << mvNoua << endl << endl;


	cout << endl << endl << endl;
	cout << "\n----------IS-A ComandaGlovo------------\n";
	cout << "\nConstructorul fara parametri \n";
	ComandaGlovo cg1;
	cout << cg1 << endl;

	cg1.setAdresaLivrare("stradaVictoriei");
	cg1.setPretLivrare(8.9);
	cg1.setBacsisLivrator(0);
	cout <<endl<<endl<< cg1 << endl<<endl;

	cout << "\nConstructorul cu toti parametri \n";
	int data10[] = { 10,05,2023 };
	Preparat vectorPreparate10[] = { p2,p4 };
	ComandaGlovo cg2("stradaPrincipala", 9.9, 1, data10, c3, 2, vectorPreparate10);
	cout << endl<<cg2<<endl<<endl;

	cout << "\nConstructorul de copiere \n";
	ComandaGlovo cg3(cg1);
	cout << cg3 << endl;

	cout << "\nOperatorul = \n";
	cg1 = cg2;
	cout << endl << cg1 << endl << endl;

	cout << endl << endl << "---------------------UPCASTING-------------" << endl << endl;
	//transform comanda glovo intr-o comanda 
	cout << "\nComanda inainte de upcasting: " << endl << cg1 << endl << endl;
	cout << "\nComanda inainte de upcasting: " << endl << cmd5 << endl << endl;
	cmd5 = cg1;
	cout << "\nComanda dupa upcasting: " << endl << cmd5 << endl << endl;

	cout << endl << endl << "---------------------DOWNCASTING-------------" << endl << endl;
	ComandaGlovo cgNoua = cmd13;
	cout << "\nComanda  care o sa fie transformata in comanda glovo\n" << cmd13 << endl << endl;
	cout << "\nComanda glovo obtinuta prin transformarea comenzii in comanda gloco\n" << cgNoua << endl << endl;

	cout << endl << endl << "-------------------VIRTUALIZARE CITIRE/SCRIERE FAMILIE DE CLASE-------------" << endl << endl;
	cout << endl << endl << "Materia prima m7: " << endl << m7;
	cout << endl << endl << "Materia prima vegana mv3: " << endl << mv3;

	MateriePrimaDeBaza** vectorPointeriVirtualizare;
	vectorPointeriVirtualizare = new MateriePrimaDeBaza * [2];
	vectorPointeriVirtualizare[0] =new MateriePrima(m7);
	vectorPointeriVirtualizare[1] =new MateriePrimaVegana(mv3);


	fstream f21("VirtualizareMP.bin",  ios::binary | ios::out );
	for (int i = 0; i < 2; i++)
	{
		vectorPointeriVirtualizare[i]->scriereInFBinarMPrima(f21);
	}
	f21.close();

	fstream f22("VirtualizareMP.bin",ios::binary | ios::in);
	for (int i = 0; i < 2; i++)
	{
		vectorPointeriVirtualizare[i]->citireFBinarMPrima(f22);
	}
	f22.close();
	cout << endl << endl << "Materia prima dupa citire din fis binar: " << endl << m7;
	cout << endl << endl << "Materia prima vegana dupa citire din fis binar: " << endl << mv3;


	cout << endl << endl << "-------------------VIRTUALIZARE CITIRE/SCRIERE Comanda-------------" << endl << endl;
	Comanda** vectorComandaVirtualizare;
	vectorComandaVirtualizare = new Comanda * [2];
	vectorComandaVirtualizare[0] = new Comanda(cmd5);
	vectorComandaVirtualizare[1] = new ComandaGlovo(cgNoua);

	fstream f23("VirtualizareComanda.bin", ios::binary | ios::out);
	for (int i = 0; i < 2; i++)
	{
		vectorComandaVirtualizare[i]->scriereBinarComanda(f23);
	}
	f23.close();


	fstream f24("VirtualizareComanda.bin", ios::binary | ios::in);
	for (int i = 0; i < 2; i++)
	{
		vectorComandaVirtualizare[i]->citireBinarComanda(f24);
	}
	f24.close();

	cout << endl << endl << "Comanda cmd7 dupa citire din fis binar: " << endl << cmd5;
	cout << endl << endl << "Comanda glovo cg3 dupa citire din fis binar: " << endl << cgNoua;

	cout << endl << endl << "-------------------CLASA TEMPLATE PRODUCATOR-------------" << endl << endl;
	//constr fara param
	Producator<MateriePrima> prod;
	cout << prod << endl << endl;

	//constr cu toti param
	MateriePrima vectorMPP[] = { m2,m4,m9,m20 };
	Producator<MateriePrima> prod1("ScProducator1", 4, vectorMPP);
	cout <<"Numele producatorului este: "<< prod1.getNumeProducator() << endl;
	cout << "Numarul de elememente pe care acesta le produce este: " << prod1.getNrElemente() << endl;
	cout << "Elementele sunt: " << endl;
	for (int i = 0; i < prod1.getNrElemente(); i++)
	{
		cout << prod1.getVectorElemente()[i].getDenumireMateriePrima()<<endl;
	}
	cout << endl << endl;

	//constr de copiere
	Producator<MateriePrima> prod2(prod1);
	cout << "Numele producatorului este: " << prod2.getNumeProducator() << endl;
	cout << "Numarul de elememente pe care acesta le produce este: " << prod2.getNrElemente() << endl;
	cout << "Elementele sunt: " << endl;
	for (int i = 0; i < prod2.getNrElemente(); i++)
	{
		cout << prod2.getVectorElemente()[i].getDenumireMateriePrima() << endl;
	}
	cout << endl << endl;

	//op=
	prod = prod2;
	cout << "Numele producatorului este: " << prod.getNumeProducator() << endl;
	cout << "Numarul de elememente pe care acesta le produce este: " << prod.getNrElemente() << endl;
	cout << "Elementele sunt: " << endl;
	for (int i = 0; i < prod.getNrElemente(); i++)
	{
		cout << prod.getVectorElemente()[i].getDenumireMateriePrima() << endl;
	}
	cout << endl << endl;

	//operatorul de citire
	/*cin >> prod;
	cout << endl << endl;
	cout << prod;*/

	cout << endl << endl << "-------------------STL-------------" << endl << endl;
	cout << endl  << "-------------------VECTOR STL-------------" << endl << endl;

	vector<MateriePrima> vectorSTL1;
	vectorSTL1.push_back(m2);
	vectorSTL1.push_back(m7);
	vectorSTL1.push_back(m10);
	vectorSTL1.push_back(m20);
	vectorSTL1.push_back(m2);

	cout << "Numarul de elemente pe care le are vectorSTL1 este: " << vectorSTL1.size() << endl;
	cout << "Elementele sunt: " << endl;
	for (int i = 0; i < vectorSTL1.size(); i++)
	{
		cout << vectorSTL1[i] << endl << endl;
	}

	vectorSTL1.pop_back();
	cout << "Numarul nou de elemente pe care le are vectorSTL1 este: " << vectorSTL1.size() << endl;
	cout << "Elementele sunt: " << endl;
	for (int i = 0; i < vectorSTL1.size(); i++)
	{
		cout << vectorSTL1[i] << endl << endl;
	}

	cout << endl<<endl << "-------------------LISTA STL-------------" << endl << endl;
	list<Preparat> listaSTL;
	listaSTL.push_back(p2);
	listaSTL.push_back(p4);
	listaSTL.push_back(p6);
	listaSTL.push_back(p7);
	listaSTL.push_back(p5);

	cout << "Numarul de elemente al listei listaSTL este: " << listaSTL.size() << endl;
	cout << "Elementele sunt: " << endl;
	list<Preparat>::iterator itL;
	for (itL = listaSTL.begin(); itL != listaSTL.end(); itL++)
	{
		cout << *itL << endl;
	}

	listaSTL.pop_back();
	listaSTL.pop_back();

	cout << "Numarul nou de elemente al listei listaSTL este: " << listaSTL.size() << endl;
	cout << "Elementele sunt: " << endl;
	for (itL = listaSTL.begin(); itL != listaSTL.end(); itL++)
	{
		cout << *itL << endl;
	}

	cout << endl << endl << "-------------------Set STL-------------" << endl << endl;
	set<MateriePrimaVegana> setStl;
	set<MateriePrimaVegana> ::iterator itS;

	setStl.insert(mv2);
	setStl.insert(mv5);
	setStl.insert(mv6);
	setStl.insert(mv3);
	setStl.insert(mv4);
	setStl.insert(mv2);


	cout << "Numarul nou de elemente al set-ului setStl este: " << setStl.size() << endl;
	cout << "Elementele sunt: " << endl;
	for (itS = setStl.begin(); itS != setStl.end(); itS++)
	{
		cout << *itS << endl;
	}

	
	cout << endl << endl << "-------------------MAP STL-------------" << endl << endl;
	map<int, MateriePrima> mapSTL;
	map<int, MateriePrima>::iterator itM;
	mapSTL.insert(pair<int, MateriePrima>(10,m2));
	mapSTL.insert(pair<int, MateriePrima>(8, m5));
	mapSTL.insert(pair<int, MateriePrima>(110, m8));
	mapSTL.insert(pair<int, MateriePrima>(510, m20));
	mapSTL.insert(pair<int, MateriePrima>(10, m9));

	cout << "Numarul de elemente al map-ului mapSTL este: " << mapSTL.size() << endl;;
	cout << "Elementele sunt :" << endl<<endl;
	for (itM = mapSTL.begin(); itM != mapSTL.end(); itM++)
	{
		cout << "Cheia de identificare: " << itM->first << endl;
		cout << "Elementul este: " << itM->second << endl << endl;
	}

	//MeniuAdministrator
	int citire = 0;
	do
	{
		MeniuComenzi();
		cin >> citire;
		if (citire == 1)
		{
			system("cls");
			cout << "\nMateria prima este: \n";
			cout << m11;
			cout << endl;
			cin.ignore();
			cin.ignore();
		}
		else if (citire == 2)
		{
			system("cls");
			cout << "\nCitire materie prima: " << endl;
			cin >> m1;
			cout << endl;
			cout << m1;
		}
		else if (citire == 3)
		{
			system("cls");
			cout << "\nAdauga stoc materie prima:" << endl;
			cout << "Stocul actual este: " << m1.getNrBucPeStoc() << endl;
			int i;
			cout << "Introduceti valoarea cu care doriti sa mariti stocul: ";
			cin >> i;
			m1.adaugaBucMateiePrima(i);
			cout << "Stocul actual este: " << m1.getNrBucPeStoc() << endl;
		}
		else if (citire == 4)
		{
			system("cls");
			cout << "Preparatul este: " << endl;
			cout << "Denumire preparat: " << p4.getDenumirePreparat() << endl;
			cout << "Pret preparat: " << p4.getPretPreparat() << endl;
			cout << "Total kcal: " << p4() << endl;
			cout << "Nnumar de materii prime: " << p4.getNrMateriiPrime() << endl;
			cout << "Vectori materii prime: " << endl;
			for (int i = 0; i < p4.getNrMateriiPrime(); i++)
			{
				cout << p4.getVectorMateriiPrime()[i] << endl;
				cout << "Numar bucati materie prima: " << p4.getNrBucatiMateriePrima()[i] << endl;
				cout << endl;
			}
			cout << "Necesita preparare termica? 1-da, 0-nu. " << p4.getNecesitaPreparareTermica() << endl;
			cin.ignore();
			cin.ignore();
		}
		else if (citire == 5)
		{
			system("cls");
			cout << "Pretul actual al preparatului este: " << p4.getPretPreparat() << endl;
			cout << "Doriti sa cresteti pretul sau sa scadeti pretul? 1-pretul creste, 0-pretul scade" << endl;
			bool l;
			cin >> l;
			if (l)
			{
				cout << "Introduceti valoarea cu care doriti sa cresteti pretul preparatului ";
				float r = 0;
				cin >> r;
				p4 = p4 + r;

			}
			else {
				cout << "Introduceti valoarea cu care doriti sa scadeti pretul preparatului ";
				float r = 0;
				cin >> r;
				p4 = p4 - r;
			}
			cout << "Pretul actual al preparatului este: " << p4.getPretPreparat() << endl;

		}
		else if (citire == 6)
		{
			system("cls");
			cout << "Introduceti denumirea preparatului: " << endl;
			string nume;
			cin >> nume;
			p1.setDenumirePreparat(nume);
			cout << "Introduceti pretul preparatului preparatului: " << endl;
			float pret;
			cin >> pret;
			p1.setPretPreparat(pret);
			meniu0 += &p1;
			cout << meniu0;
		}
		else if (citire == 7)
		{
			system("cls");
			cout << meniu1;
			cout << endl;
			cin >> cmd2;
			if (cmd2 != cmd1)
			{
				cout << cmd2;
				cout << "\nPretul comenzii este de " << cmd2.pretTotalComanda() << " lei\n";
			}
		}
		else if (citire == 8)
		{
			system("cls");
			ofstream f34("ScriereFisierCsvComanda.csv", ios::out);
			f34 << cmd5;
			f34.close();
			cout << "Comanda scrisa cu succes! Verificati fisierul!";
			cout << endl << endl << endl << endl;
			cin.ignore();
			cin.ignore();
		}
		else if (citire == 9)
		{
			system("cls");
			fstream f19("FisierBinarComanda.bin", ios::binary | ios::out);
			cmd5.scriereBinarComanda(f19);
			f19.close();

			Comanda cmd7;
			cout << "\nComanda inainte de citirea din fisier binar\n";
			cout << "Data comanda: ";
			for (int i = 0; i < 3; i++)
			{
				cout << cmd7.getDataComanda()[i] << " ";
			}
			cout << "\nClient: \n";
			cout << "NumePrenume client: " << cmd7.getClient().getNumePrenume() << endl;;
			cout << "Este client online? 1-clientOnline, 0-clientFizic: " << cmd7.getClient().getClientOnline() << endl;
			cout << "Numar masa: " << cmd7.getClient().getNrMasa() << endl;
			cout << "Numar de preparate dorite: " << cmd7.getNrPreparateDorire() << endl;
			cout << "Vector preparate: " << endl;
			for (int i = 0; i < cmd7.getNrPreparateDorire(); i++)
			{
				cout << cmd7.getVectoriPreparate()[i] << endl;
			}

			fstream f20("FisierBinarComanda.bin", ios::binary | ios::in);
			cmd7.citireBinarComanda(f20);
			f20.close();

			cout << "\nComanda dupa citirea din fisier binar\n";
			cout << "Data comanda: ";
			for (int i = 0; i < 3; i++)
			{
				cout << cmd7.getDataComanda()[i] << " ";
			}
			cout << "\nClient: \n";
			cout << "NumePrenume client: " << cmd7.getClient().getNumePrenume() << endl;;
			cout << "Este client online? 1-clientOnline, 0-clientFizic: " << cmd7.getClient().getClientOnline() << endl;
			cout << "Numar masa: " << cmd7.getClient().getNrMasa() << endl;
			cout << "Numar de preparate dorite: " << cmd7.getNrPreparateDorire() << endl;
			cout << "Vector preparate: " << endl;
			for (int i = 0; i < cmd7.getNrPreparateDorire(); i++)
			{
				cout << cmd7.getVectoriPreparate()[i] << endl;
			}
			cout << endl << endl << endl << endl;
			cin.ignore();
			cin.ignore();
		}
		else if (citire == 10)
		{
			system("cls");
			ifstream raport2("RaportStocMateriePrima.txt", ios::in);
			MateriePrima::afisareRaport(raport2);
			raport2.close();
			cout << endl << endl << endl << endl;
			cin.ignore();
			cin.ignore();
		}
		else if (citire == 11)
		{
			system("cls");
			ifstream raport4("RaportPretPreparat.txt", ios::in);
			Preparat::afisareRaportPreparat(raport4);
			raport4.close();
			cout << endl << endl << endl << endl;
			cin.ignore();
			cin.ignore();
		}
		else if (citire == 12)
		{
			system("cls");
			ifstream raport6("RaportPreparatMaxKcal.txt", ios::in);
			Preparat::afisarePreparatKcal(raport6);
			raport6.close();
			cout << endl << endl << endl << endl;
			cin.ignore();
			cin.ignore();
		}
		else if (citire == 13)
		{
			system("cls");
			ifstream raport9("RaportIncasariAnuale.txt", ios::in);
			Comanda::afisareRaportTotalIncasari(raport9);
			raport6.close();
			cout << endl << endl << endl << endl;
			cin.ignore();
			cin.ignore();
		}
		else if (citire == 14)
		{
			system("cls");
			ifstream raport11("RaportPreferinteClienti.txt", ios::in);
			Client::afisareRaportClienti(raport11);
			raport11.close();
			cout << endl << endl << endl << endl;
			cin.ignore();
			cin.ignore();
		}
		else if (citire == 15)
		{
			system("cls");
			cout << "La revedere!";
			cout << endl << endl << endl << endl;
			cin.ignore();
			cin.ignore();
		}
	} while (citire > 0 && citire < 15);

	return 0;
}