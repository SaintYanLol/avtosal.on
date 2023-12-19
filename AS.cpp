#include <iostream>
#include <unordered_map>

// Абстрактный класс для представления автомобиля
class Car {
public:
    virtual void display() const = 0;
    virtual Car* clone() const = 0;
    virtual ~Car() = default;
};

// Конкретный класс, представляющий автомобиль типа седан
class Sedan : public Car {
public:
    void display() const override {
        std::cout << "Sedan Car" << std::endl;
    }

    Car* clone() const override {
        return new Sedan(*this);
    }
};

// Конкретный класс, представляющий автомобиль типа внедорожник
class SUV : public Car {
public:
    void display() const override {
        std::cout << "SUV Car" << std::endl;
    }

    Car* clone() const override {
        return new SUV(*this);
    }
};

// Простой прототип для управления клонами
class CarPrototype {
private:
    std::unordered_map<std::string, Car*> prototypes;

public:
    Car* getPrototype(const std::string& type) const {
        auto it = prototypes.find(type);
        if (it != prototypes.end()) {
            return it->second->clone();
        }
        return nullptr;
    }

    void registerPrototype(const std::string& type, Car* prototype) {
        prototypes[type] = prototype;
    }

    ~CarPrototype() {
        for (const auto& entry : prototypes) {
            delete entry.second;
        }
    }
};

int main() {
    CarPrototype carPrototype;

    // Регистрация прототипов
    carPrototype.registerPrototype("Sedan", new Sedan());
    carPrototype.registerPrototype("SUV", new SUV());

    // Создание и использование клонов
    Car* clonedSedan = carPrototype.getPrototype("Sedan");
    Car* clonedSUV = carPrototype.getPrototype("SUV");

    if (clonedSedan) {
        clonedSedan->display();
        delete clonedSedan;
    }

    if (clonedSUV) {
        clonedSUV->display();
        delete clonedSUV;
    }

    return 0;
}
