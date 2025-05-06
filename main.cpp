#include <iostream>
#include <string>
#include <vector>
#include "patterns.h"

using namespace std;

class DrinkingStrategy
{
public:
    virtual ~DrinkingStrategy()
    {
    };
    virtual void Drinking(const wstring& Name) const =0;
};

class BuyingStrategy
{
public:
    virtual ~BuyingStrategy()
    {
    };
    virtual void Buying(const wstring& Name) const =0;
};

class MixingStrategy
{
public:
    virtual ~MixingStrategy()
    {
    };
    virtual void Mixing(const wstring& Name) const =0;
};

class NormalDrinking : public DrinkingStrategy
{
public:
    void Drinking(const wstring& Name) const override
    {
        wcout << L"Выпиваем " << Name << L" обычным способом" << endl;
    }
};
class SlowDrinking : public DrinkingStrategy
{
public:
    void Drinking(const wstring& Name) const override
    {
        wcout << L"Медленно потягиваем " << Name << endl;
    }
};
class NormalBuying : public BuyingStrategy
{
public:
    void Buying(const wstring& Name)const override
    {
        wcout << L"Покупаем " << Name << L" в магазине" << endl;
    }
};
class OnlineBuying : public BuyingStrategy
{
public:
    void Buying(const wstring& Name) const override
    {
        wcout << L"Заказываем " << Name << L" онлайн" << endl;
    }
};

class NormalMixing : public MixingStrategy
{
public:
    void Mixing(const wstring& Name) const override
    {
        wcout << L"Смешиваем " << Name << L" с другими напитками" << endl;
    }
};

class NoMixing : public MixingStrategy
{
public:
    void Mixing(const wstring& Name) const override
    {
        wcout << L"Не смешиваем " << Name << L" ни с чем" << endl;
    }
};
class soda
{
private:
    double Volume;
    int Sugar; // Кол-во сахара на 100 мл жидкости
    wstring OriginCountry; // Страна происхождения напитка
    wstring Color;
    wstring Name;

    DrinkingStrategy* drinkingStrategy;
    BuyingStrategy* buyingStrategy;
    MixingStrategy* mixingStrategy;

protected:
    bool glassOrPlastic; // Если true, то газировка в стеклянной бутылке; Если false, то газировка в пластиковой бутылке
    //Шаблонный метод
    void PrepareBottle()
    {
        if (glassOrPlastic == true)
        {
            wcout<<L"Подгатавливаем стеклянную бутылку"<<endl;
        }
        else
        {
            wcout<<L"Подгатавливаем пластиковую бутылку"<<endl;
        }
    }
    virtual void SpecIngredient()=0;
    virtual void Carbonate()=0;
    void PourLiquid() {
        wcout << L"Наполняем бутылку жидкостью объемом " << Volume << L" л" << endl;
    }

    void SealBottle() {
        wcout << L"Запечатываем бутылку" << endl;
    }

    virtual void AddSpecialLabel() {
        wcout << L"Добавляем стандартную этикетку" << endl;
    }
public:
    soda(double volume, int sugar, const wstring& originCountry,
         const wstring& color, const wstring& name,
         DrinkingStrategy* drinking, BuyingStrategy* buying, MixingStrategy* mixing)
        : Volume(volume), Sugar(sugar), OriginCountry(originCountry),
          Color(color), Name(name), glassOrPlastic(false),
          drinkingStrategy(drinking), buyingStrategy(buying), mixingStrategy(mixing) {}
    virtual ~soda()
    {
        delete drinkingStrategy;
        delete buyingStrategy;
        delete mixingStrategy;
    };
    //Шаблонный метод производства
    void PrepareDrink()
    {
        wcout<<L"----Начинаем производство "<<Name<<" -----"<<endl;
        PrepareBottle();
        SpecIngredient();
        Carbonate();
        PourLiquid();
        SealBottle();
        AddSpecialLabel();
    }
    //Стратегии
    void Drink() { drinkingStrategy->Drinking(Name); }
    void Buy() { buyingStrategy->Buying(Name); }
    void Mix() { mixingStrategy->Mixing(Name); }

    double GetVolume() const { return Volume; }
    int GetSugar() const { return Sugar; }
    wstring GetOriginCountry() const { return OriginCountry; }
    wstring GetColor() const { return Color; }
    bool IsGlassBottle() const { return glassOrPlastic; }
};


class tarkhun : public soda
{
protected:
    void SpecIngredient() override
    {
        wcout << L"Добавляем экстракт эстрагона" << endl;
    }

    void Carbonate() override
    {
        wcout << L"Газируем до среднего уровня" << endl;
    }

    void AddSpecialLabel() override
    {
        wcout << L"Добавляем зеленую этикетку с надписью 'Тархун'" << endl;
    }
public:
    tarkhun(double volume, int sugar, const wstring originCountry, const wstring color, DrinkingStrategy* drinking,
            BuyingStrategy* buying, MixingStrategy* mixing):
                soda(volume, sugar, originCountry, color,L"Тархун", drinking, buying, mixing)
                {
                    glassOrPlastic = true;
                } ;
    ~tarkhun()
    {
    };

};


class kvas : public soda
{
protected:
    void SpecIngredient() override
    {
        wcout << L"Добавляем солод и хмель" << endl;
    }

    void Carbonate() override

    {
        wcout << L"Газируем до низкого уровня" << endl;
    }
public:
    kvas(double volume, int sugar, const wstring originCountry, const wstring color, DrinkingStrategy* drinking, BuyingStrategy* buying, MixingStrategy* mixing)
    :soda(volume, sugar, originCountry, color,L"Квас", drinking, buying, mixing)
    {
        glassOrPlastic = false;
    };
    ~kvas()
    {
    };
};


class cola : public soda
{
protected:
    void SpecIngredient() override
    {
        wcout << L"Добавляем экстракт орехов колы и карамель" << endl;
    }

    void Carbonate() override
    {
        wcout << L"Газируем до высокого уровня" << endl;
    }

    void AddSpecialLabel() override
    {
        wcout << L"Добавляем красную этикетку с логотипом бренда" << endl;
    }
public:
    cola(double volume, int sugar, const wstring originCountry, const wstring color,DrinkingStrategy* drinking, BuyingStrategy* buying, MixingStrategy* mixing)
    :soda(volume, sugar, originCountry, color,L"Кола", drinking, buying, mixing)
    {
    glassOrPlastic = false;
    };
    ~cola()
    {
    };
};

enum class GazirovkaType: int
{
    tarkhun = 1,
    kvas = 2,
    cola = 3,


    undefined = 0,
};
soda *CreateSoda(GazirovkaType type)
{
    DrinkingStrategy* drinking;
    BuyingStrategy* buying;
    MixingStrategy* mixing;
    soda *newSoda = nullptr;
    if (type == GazirovkaType::tarkhun)
    {
        drinking = new NormalDrinking();
        buying = new NormalBuying();
        mixing = new NoMixing();
        newSoda = new tarkhun(0.5, 10, L"Россия", L"Зеленый",drinking, buying,mixing);
    }
    else if (type == GazirovkaType::kvas)
    {
        drinking = new SlowDrinking();
        buying = new NormalBuying();
        mixing = new NormalMixing();
        newSoda = new kvas(1.5, 2, L"Россия", L"Коричневый",drinking, buying,mixing);
    }
    else if (type == GazirovkaType::cola)
    {
        drinking = new NormalDrinking();
        buying = new OnlineBuying();
        mixing = new NormalMixing();
        newSoda = new cola(1, 20, L"США", L"Черный",drinking, buying,mixing);
    }
    return newSoda;
};
void AllItems(Iterator<soda*> *iterator)
{
    for (iterator->First(); !iterator->IsDone(); iterator->Next())
    {
        soda* gazirovka = iterator->GetCurrent();
        gazirovka->PrepareDrink();
        gazirovka->Drink();
        gazirovka->Buy();
        gazirovka->Mix();
    }
}
int main()
{
    setlocale(LC_ALL, "Russian");
    size_t n;
    wcout << L"Введите количество газировок" << endl;
    cin >> n;
    wcout << L"---------------------" << endl;
    VectorStack<soda*> GazirovkaVector;
    for (size_t i = 0; i < n; i++) {
        int numberSoda = rand() % 3 + 1;
        GazirovkaType soda_type1 = static_cast<GazirovkaType>(numberSoda);
        soda* soda1 = CreateSoda(soda_type1);
        GazirovkaVector.Push(soda1);
    }
    VectorIterator<soda*> iterator(&GazirovkaVector);
    AllItems (&iterator);
}
