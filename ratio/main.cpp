/** [PL] Metaprogramowanie: przykład użycia biblioteki arytmetyki stosunków liczb całkowitych `std::ratio`. 
 *  [EN] Metaprogramming: an example of application of compile-time rational arithmetic library `std::ratio`.
 *  @author Krzysztof Siminski
 *  @date 2024-05-26
 */ 

#include <iostream>
#include <ratio>

/////////////////////////////////////////////
int main ()
{
   // [PL] definicje ułamków
   // [EN] ratio definitions
   using _1_6 = std::ratio<1, 6>;
   using _3_8 = std::ratio<3, 8>;

   {
      // [PL] operacja na ułamkach
      // [EN] ratio operations
      using sum = std::ratio_add<_1_6, _3_8>; 
      std::cout << sum::num << "/" << sum::den << std::endl;
      using mul = std::ratio_multiply<_1_6, _3_8>; 
      std::cout << mul::num << "/" << mul::den << std::endl;
      using sub = std::ratio_subtract<_1_6, _3_8>; 
      std::cout << sub::num << "/" << sub::den << std::endl;
      using div = std::ratio_divide<_1_6, _3_8>; 
      std::cout << div::num << "/" << div::den << std::endl;
   }
   {
      // [PL] relacje na ułamkach
      // [EN] ratio relations
      if constexpr (std::ratio_less<_1_6, _3_8>::value)
         std::cout << "(" << _1_6::num << "/" << _1_6::den << ") < (" << _3_8::num << "/" << _3_8::den << ")" << std::endl; 
      else 
         std::cout << "(" << _1_6::num << "/" << _1_6::den << ") >= (" << _3_8::num << "/" << _3_8::den << ")" << std::endl; 

      // [PL] std::ratio_less_v<_1_6, _3_8> jest skrótem dla std::ratio_less<_1_6, _3_8>::value
      // [EN] std::ratio_less_v<_1_6, _3_8> is an abbreviation for std::ratio_less<_1_6, _3_8>::value
      if constexpr (std::ratio_less_v<_1_6, _3_8>)
         std::cout << "(" << _1_6::num << "/" << _1_6::den << ") < (" << _3_8::num << "/" << _3_8::den << ")" << std::endl; 
      else 
         std::cout << "(" << _1_6::num << "/" << _1_6::den << ") >= (" << _3_8::num << "/" << _3_8::den << ")" << std::endl; 
   }

   {
      // [PL] przedrostki SI
      // [EN] SI prefixes
      using SI_E_u = std::ratio_multiply<std::exa, std::micro>;
      std::cout << SI_E_u::num << "/" << SI_E_u::den << std::endl;
   }

   return 0;
}

