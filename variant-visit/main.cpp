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
   std::cout << "std::variant" << std::endl;
   std::cout << "=============================" << std::endl;

   {
      using various_types = std::variant<int, double, std::string>;
      various_types v1 = 42;
      various_types v2 = 3.14;
      various_types v3 = std::string("Hello, World!");

      std::cout << "v1 : " << std::get<int>(v1) << std::endl; 
      std::cout << "v2 : " << std::get<double>(v2) << std::endl;
      std::cout << "v3 : " << std::get<std::string>(v3) << std::endl;

      std::cout << std::endl; 

      v1 = -12.345;
      v2 = std::string("To be or not to be.");
      v3 = 100; 

      std::cout << "v1 : " << std::get<double>(v1) << std::endl;
      std::cout << "v2 : " << std::get<std::string>(v2) << std::endl;
      std::cout << "v3 : " << std::get<int>(v3) << std::endl;

      // [PL] Odczytanie nieprawidłowego typu powoduje zgłoszenie wyjątku std::bad_variant_access.
      // [EN] Reading an incorrect type causes a std::bad_variant_access exception to be thrown.
      try
      {
         std::cout << std::endl; 
         std::cout << "v1 : " << std::get<int>(v1) << std::endl;
      }
      catch (const std::bad_variant_access & e)
      {
         std::cout << e.what() << std::endl;
      }
   }

   std::cout << "=============================" << std::endl;

   {
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
   }
   return 0;
}

