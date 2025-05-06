#include <iostream>
#include <string>
#include <vector>
#include "patterns.h"

using namespace std;

class soda
{
private:
    double Volume;
    int Sugar; // Кол-во сахара на 100 мл жидкости
    wstring OriginCountry; // Страна происхождения напитка
    wstring Color;
protected:
    bool glassOrPlastic; // Если true, то газировка в стеклянной бутылке; Если false, то газировка в пластиковой бутылке
public:
    soda(double volume, int sugar, const wstring& originCountry, const wstring& color);
    virtual ~soda();
    double GetVolume() const { return Volume; }
    int GetSugar() const { return Sugar; }
    wstring GetOriginCountry() const { return OriginCountry; }
    wstring GetColor() const { return Color; }

    virtual void Drinking() = 0;
    virtual void Buying() = 0;
    virtual void Mixed() = 0;
};

soda::soda(double volume, int sugar, const wstring& originCountry, const wstring& color)
    : Volume(volume), Sugar(sugar), OriginCountry(originCountry), Color(color), glassOrPlastic(false)
{
}

soda::~soda()
{
}

class tarkhun : public soda
{
public:
    tarkhun(double volume, int sugar, const wstring originCountry, const wstring color);
    ~tarkhun();
    void Drinking()
    {
        wcout << L"Выпьем тархун" << endl;
    }
    void Buying()
    {
        wcout << L"Купим тархун" << endl;
    }
    void Mixed()
    {
        wcout << L"Перемешаем тархун с другой газировкой" << endl;
    }
};

tarkhun::tarkhun(double volume, int sugar, const wstring originCountry, const wstring color)
    : soda(volume, sugar, originCountry, color)
{
    glassOrPlastic = true;
    wcout << L"Взяли бутылку с тархуном" << endl;
}

tarkhun::~tarkhun()
{
    wcout << L"Положили бутылку" << endl;
}

class kvas : public soda
{
public:
    kvas(double volume, int sugar, const wstring originCountry, const wstring color);
    ~kvas();
    void Drinking()
    {
        wcout << L"Выпьем квас" << endl;
    }
    void Buying()
    {
        wcout << L"Купим квас" << endl;
    }
    void Mixed()
    {
        wcout << L"Перемешаем квас с другой газировкой" << endl;
    }
};

kvas::kvas(double volume, int sugar, const wstring originCountry, const wstring color): soda(volume, sugar, originCountry, color)
{
    glassOrPlastic = false;
    wcout << L"Взяли бутылку с квасом" << endl;
}

kvas::~kvas()
{
    wcout << L"Положили бутылку" << endl;
}

class cola : public soda
{
public:
    cola(double volume, int sugar, const wstring originCountry, const wstring color);
    ~cola();
    void Drinking()
    {
        wcout << L"Выпьем колу" << endl;
    }
    void Buying()
    {
        wcout << L"Купим колу" << endl;
    }
    void Mixed()
    {
        wcout << L"Перемешаем колу с другой газировкой" << endl;
    }
};

cola::cola(double volume, int sugar, const wstring originCountry, const wstring color)
    : soda(volume, sugar, originCountry, color)
{
    glassOrPlastic = false;
    wcout << L"Взяли бутылку с колой" << endl;
}

cola::~cola()
{
    wcout << L"Положили бутылку" << endl;
}

enum class GazirovkaType: int
{
    tarkhun = 1,
    kvas = 2,
    cola = 3,

    undefined = 0,
};
soda *CreateSoda(GazirovkaType type)
{
    soda *newSoda = nullptr;
    if (type == GazirovkaType::tarkhun)
    {
        newSoda = new tarkhun(0.5, 10, L"Россия", L"Зеленый");
    }
    else if (type == GazirovkaType::kvas)
    {
        newSoda = new kvas(1.5, 2, L"Россия", L"Коричневый");
    }
    else if (type == GazirovkaType::cola)
    {
        newSoda = new cola(1, 20, L"США", L"Черный");
    }
    return newSoda;
};
void AllItems(Iterator<soda*> *iterator)
{
    for (iterator->First(); !iterator->IsDone(); iterator->Next())
    {
        soda* gazirovka = iterator->GetCurrent();
        gazirovka->Drinking();
        gazirovka->Buying();
        gazirovka->Mixed();
    }
}
int main()
{
    setlocale(LC_ALL,"Russian");
    GazirovkaType type = GazirovkaType::undefined;
    size_t n;
    wcout<<L"Введите количество газировок"<<endl;
    cin>>n;
    wcout<<L"Работа стэка:"<<endl;
    Stack <soda*> sodaStack;
    for (size_t i=0;i<n;i++)
    {
        int numberSoda = rand()%3+1;
        GazirovkaType soda_type = static_cast<GazirovkaType>(numberSoda);
        soda *gazirovka1 = CreateSoda(soda_type);
        sodaStack.Push(gazirovka1);
    }
    StackIterator<soda*> iteratorStack(&sodaStack);
    AllItems(&iteratorStack);
}
