#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// using namespace std;

// Абстрактный класс "Мед хранилище"
class MedSupply
{
protected:
    std::string name;
    std::string type;
    std::string manufacturer;
    std::string medicineName;
    std::string medSupplyName;

public:
    virtual void enroll() const = 0;
    virtual void print_qnt() const = 0; // quantity
    MedSupply(const std::string &name) : medSupplyName(name) {}
    virtual ~MedSupply() {}
};

class Medicine : public MedSupply
{
private:
    static inline unsigned count{};
    static std::vector<Medicine *> medicines;

protected:
    std::string manufacturer;
    std::string medicineName;
    int article_number;

public:
    Medicine(std::string &supply, std::string name, int number, std::string produce) : MedSupply(supply), manufacturer(produce),
                                                                                       medicineName(name), article_number(number)
    {
        count++;
        medicines.push_back(this); // происходит добавление указателя `this`
                                   //(указатель на текущий объект) в конец вектора `medicines`
    }

    void enroll() const override
    {
        std::cout << "На складе " << medSupplyName << " находится медикамент " << medicineName
                  << " производителя " << manufacturer << ", артикул товара: " << article_number << std::endl;
    }

    void print_qnt() const override
    {
        std::cout << "Текущее количество препаратов - " << count << std::endl;
    }

    static void printAllMedicines()
    {
        std::cout << "Список всех медикаментов:" << std::endl;
        for (const auto &medicine : medicines)
        {
            std::cout << medicine->manufacturer << " " << medicine->medicineName << " артикул: "
                      << medicine->article_number << std::endl; // const auto& medicine : medicines` используется
                                                                // в цикле `for` для обхода элементов вектора.
        }
    }

    ~Medicine()
    {
        count--;
        medicines.erase(std::remove_if(medicines.begin(), medicines.end(),
                                       [this](const Medicine *medicine)
                                       { return medicine == this; }),
                        medicines.end());
    }
};

std::vector<Medicine *> Medicine::medicines;

class MedCit : public MedSupply
{
private:
    static inline unsigned count{};
    static std::vector<MedCit *> medcits;

protected:
    std::string type;
    std::string material;
    std::string size;

public:
    MedCit(std::string &supply, std::string typef, std::string materialf, std::string sizef) : MedSupply(supply), type(typef),
                                                                                               material(materialf), size(sizef)
    {
        count++;
        medcits.push_back(this);
    }

    void enroll() const override
    {
        std::cout << "На складе " << medSupplyName << " находится инструмент " << type
                  << " из материала " << material << " размерa " << size << std::endl;
    }

    void print_qnt() const override
    {
        std::cout << "Текущее количество инструментов - " << count << std::endl;
    }

    static void printAllMedcits()
    {
        std::cout << "Список всех инструментов:" << std::endl;
        for (const auto &medcit : medcits)
        {
            std::cout << medcit->type << " из " << medcit->material << " размера "
                      << medcit->size << std::endl;
        }
    }

    ~MedCit()
    {
        count--;
        medcits.erase(std::remove_if(medcits.begin(), medcits.end(),
                                     [this](const MedCit *medcit)
                                     { return medcit == this; }),
                      medcits.end());
    }
};

std::vector<MedCit *> MedCit::medcits;

class OtherProduct : public MedSupply
{
private:
    static inline unsigned count{};
    static std::vector<OtherProduct *> products;

protected:
    std::string name;
    int expDate;

public:
    OtherProduct(std::string &supply, std::string typef, int date) : MedSupply(supply), name(typef), expDate(date)
    {
        count++;
        products.push_back(this);
    }

    void enroll() const override
    {
        std::cout << "На складе " << medSupplyName << " находится  " << name
                  << ", срок годности(с моммента поступления): " << expDate << " дней" << std::endl;
    }

    void print_qnt() const override
    {
        std::cout << "Текущее количество  - " << count << std::endl;
    }

    static void printAllProducts()
    {
        std::cout << "Список всех дополнительных товаров:" << std::endl;
        for (const auto &product : products)
        {
            std::cout << product->name << ", " << product->expDate << " дней" << std::endl;
        }
    }

    ~OtherProduct()
    {
        count--;
        products.erase(std::remove_if(products.begin(), products.end(),
                                      [this](const OtherProduct *product)
                                      { return product == this; }),
                       products.end());
    }
};

std::vector<OtherProduct *> OtherProduct::products;

int main()
{
    std::string medSupplyName = "Gym";
    Medicine a1(medSupplyName, "Paracetomol", 14, "Agrohealth");
    a1.enroll();
    a1.print_qnt();

    Medicine a2(medSupplyName, "Citromon", 81, "Normalize");
    a2.enroll();
    a2.print_qnt();

    Medicine a3(medSupplyName, "Ibuprofen", 07, "Health");
    a3.enroll();
    a3.print_qnt();

    MedCit a4(medSupplyName, "Scissors", "metal", "small");
    a4.enroll();
    a4.print_qnt();

    MedCit a5(medSupplyName, "Scissors", "metal", "smaller");
    a5.enroll();
    a5.print_qnt();

    OtherProduct a6(medSupplyName, "Gemotogen", 180);
    a6.enroll();
    a6.print_qnt();

    OtherProduct a7(medSupplyName, "Sok", 14);
    a7.enroll();
    a7.print_qnt();

    MedCit *Bandages = new MedCit(medSupplyName, "Bandages", "cotton", "medium");
    Bandages->enroll();
    Bandages->print_qnt();
    MedCit::printAllMedcits();
    delete Bandages;
    a4.print_qnt();

    Medicine **d = new Medicine *[4];
    d[0] = new Medicine(medSupplyName, "Mezim", 93722, "Health");
    d[1] = new Medicine(medSupplyName, "Naiz", 71, "Normal");
    d[2] = new Medicine(medSupplyName, "Alervey", 95, "Heal");
    d[3] = new Medicine(medSupplyName, "Ibuprofen", 03, "SW");

    for (int i = 0; i < 4; ++i)
    {
        d[i]->enroll();
    }
    a1.print_qnt();

    Medicine::printAllMedicines();
    for (int i = 0; i < 4; ++i)
    {
        delete d[i];
    }
    delete[] d;
    a1.print_qnt();

    Medicine::printAllMedicines();
    MedCit::printAllMedcits();
    OtherProduct::printAllProducts();

    return 0;
}
