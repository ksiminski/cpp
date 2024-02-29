#include <concepts>
#include <ostream>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>


/////////////////////////
// [PL] przykład użycia konceptów
//      Implementacja operatora << dla różnych kontenerów. 
//      Koncepty precyzują, który szablon będzie użyty dla klasy-argumentu.
//
// [EN] example of application of concepts
//      Implementation of the operator << for different containers.
//      The concepts specify which template will be used for an argument class.
/////////////////////////
template <typename T>
concept is_map = requires (T v)
{
   typename T::key_type;
   typename T::mapped_type;

   { v.begin() } -> std::same_as <typename T::iterator>;
};

// [PL] szablon dla map 
// [EN] template for maps
template <typename T>
requires is_map<T>
std::ostream & operator<< (std::ostream & sos, const T t) 
{
   sos << "[ ";
   for (const auto & [index, value] : t)
      sos << "(" << index << " : " << value << ") ";
   sos << "]";
   return sos;
}
/////////////////////////

/////////////////////////
template <typename T>
concept container = requires (T v)
{
   {v.begin()} -> std::convertible_to<typename T::iterator>;
};

// [PL] szablon dla innych kontenerów
// [EN] template for other containers
template <typename T>
std::ostream & operator<< (std::ostream & sos, const T t) requires container<T> and (not is_map<T>) and (not std::same_as<T, std::string>)
{
   sos << "[ ";
   for (const auto & d : t)
      sos << d << " ";
   sos << "]";
   return sos;
}
/////////////////////////


int main ()
{
   std::vector<double> w {34.5, 54.2, -23.4};
   std::set<int> s { 6, 3, -1, 5};

   std::cout << w << std::endl;
   std::cout << s << std::endl;

   std::map<std::string, int> persons {{"Ala", 19}, {"Bartek", 18}, {"Kasia", 20}};

   std::cout << persons << std::endl;

   std::unordered_map<std::size_t, std::string> descriptions {{12345678, "empty"}, {23456789, "partial"}, {987654321, "full"}};

   std::cout << descriptions << std::endl;
   
   std::vector<std::vector<double>> matrix
   {
      {45.67, 23.45, 87.56},
      {48.62, 42.18, 65.60},
   };

   std::cout << matrix << std::endl;

   std::map<std::string, std::map<int, std::string>> students
   {
      { "informatics", 
         { 
            {1, "Janek"}, 
            {2, "Ala"}, 
         } 
      },
      { "electronics",  
         { 
            {3, "Basia" },
            {1, "Bartek" },
         } 
      },
      { "automatic control",   
         { 
            {4, "Kasia" },
            {5, "Monika" },
            {2, "Tadeusz" },
         } 
      },
   };

   std::cout << students << std::endl;
   return 0;
}

