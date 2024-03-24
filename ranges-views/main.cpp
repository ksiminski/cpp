/** [PL] Trochę przykładów zakresów i widoków (ranges and views). 
 *  [EN] Some examples of ranges and views
 *  @date 2024-03-24
 *  @author Krzysztof Siminski
 *  */


#include <algorithm>
#include <concepts>
#include <iostream>
#include <numeric>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

#define debug(x)   std::cout << "(" << __LINE__ << ") " << #x << " == " << x << std::endl;

void print (auto && container)
{
   std::cout << "[ ";
   for (const auto & w : container)
      std::cout << w << " " ;
   std::cout << "]" << std::endl;
}

/** [PL] Koncept dla kontenera z metodą begin(). 
 *  [EN] The concept for a container with begin() method.  */
template <typename T>
concept is_container = requires (T t) 
{
   {t.begin()} -> std::convertible_to<typename T::iterator>;
};


/** [PL] Koncept dla std::string_view. 
 *  [EN] The concept for a std::string_view.  */
template <typename T>
concept is_string_like = std::is_convertible_v<T, std::string_view>;

/** [PL] Szablon operatora << ograniczony konceptami. 
 *  [EN] The template of the operator << constrained with concepts. */
template <class T>
requires is_container<T> and (not is_string_like<T>)
std::ostream & operator << (std::ostream & sos, const T & container)
{
   sos << "[ ";
   for (const auto & w : container)
     sos << w << " " ;
   sos << "]";
   return sos;
}

////////////////////////////////////
int main()
{
   std::vector<int> ints (20);
   std::iota(ints.begin(), ints.end(), 1) ;
   print (ints);
   std::cout << ints << std::endl;
   std::cout << std::endl;

   // [PL] filtrowanie
   // [EN] filtering

   std::cout << "[PL] filtrowanie | [EN] filtering" << std::endl;

   auto range = std::views::all(ints);
   print(range);

   auto divisible_3 = [] (const auto & w) { return w % 3 == 0;};
   print (range | std::views::filter(divisible_3));
   print (range | std::views::filter(divisible_3) | std::views::reverse);
   auto negacja = [] (const auto & w) {return -w;};
   print (range | std::views::filter(divisible_3) | std::views::transform(negacja));

   print (range | std::views::drop(5));
   print (range | std::views::drop(5) | std::views::take(5));
   auto zz = range | std::views::drop(5) | std::views::take(5);
   for (auto & z : zz)
      z *= -1;
   print(range);
   std::ranges::sort(range | std::views::drop(5) | std::views::take(5));
   print (range);
   auto zz1 = range | std::views::filter(divisible_3);
   print (zz1);
   for (auto & z : zz1)
      z += 100;
   print (range);
   std::ranges::sort(range);
   print (range);

   std::cout << std::endl;

   // [PL] zip 
   // [EN] zip

   std::cout << "[PL] zip | [EN] zip" << std::endl;

   std::vector<char> lower ('z' - 'a' + 1);
   std::vector<char> upper ('z' - 'a' + 1);
   
   std::ranges::iota(lower, 'a');
   std::ranges::iota(upper, 'A');
   
   print (lower);
   print (upper);

   auto mapping {std::views::zip (lower, upper)};
   for (const auto & [l, g] : mapping)
   {
      std::cout << l << " <--> " << g << std::endl;
   }

   std::cout << std::endl;

   // [PL] podział napisu  
   // [EN] string split 

   std::cout << "[PL] podział napisu | [EN] string split" << std::endl;
   
   using std::operator""sv;
   constexpr auto jontek {"Szumia jodly na gor szczycie."sv};
   constexpr auto delimiter {" "sv};

   for (const auto word : std::views::split(jontek, delimiter))
      std::cout << "[" << std::string_view(word) << "]" << std::endl;

   return 0;
}

