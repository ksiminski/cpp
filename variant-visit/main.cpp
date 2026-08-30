/** [PL] Przykład użycia wariantów w C++ 
 *  [EN] Example of using variants in C++
 *  @date 2026-08-30
 *  @author Krzysztof Siminski
 *  */


#include <iostream>
#include <vector>
#include <variant> 

#define debug(x)   std::cout << "(" << __LINE__ << ") " << #x << " == " << x << std::endl;

////////////////////////////////////
// [PL] hierarchia klas | [EN] class hierarchy 

class Animal
{
   public: 
      virtual void speak() const = 0;
      virtual ~Animal() = default;
};

class Dog : public Animal
{
   public:
      void speak() const override
      {
         std::cout << "Woof!" << std::endl;
      }
};

class Cat : public Animal
{
   public:
      void speak() const override
      {
         std::cout << "Meow!" << std::endl;
      }
};

class Insect : public Animal
{
};

class Butterfly : public Insect
{
   public:
      void speak() const override
      {
         std::cout << "Flutter!" << std::endl;
      }
};

class Bee : public Insect
{
   public:
      void speak() const override
      {
         std::cout << "Buzz!" << std::endl;
      }
};
////////////////////////////////////
int main()
{
   std::cout << "[PL] warianty | [EN] variants" << std::endl;

   using animal_variant = std::variant<Dog, Cat, Butterfly, Bee>; 
   std::vector<animal_variant> animals = {Dog{}, Cat{}};
   animals.push_back(Butterfly{});
   animals.push_back(Bee{}); 

   for (const auto & animal : animals)
   {
      std::visit([](const auto & a) { a.speak(); }, animal);
   }

   auto is_bee = [](const auto & a) { return std::holds_alternative<Bee>(a); }; 
   
   std::cout << "[PL] filtrowanie pszczol | [EN] filtering bees" << std::endl;
   for (const auto & animal : animals)
   {
      if (is_bee(animal))
      {
         std::cout << "This is a bee." << std::endl;
      }
      else
      {
         std::cout << "This is not a bee." << std::endl;
      }
   }
   return 0;
}

