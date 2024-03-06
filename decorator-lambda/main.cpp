/** [PL] Wzorzec projektowy ,,dekorator'' z użyciem lambdy.
 *  [EN] Decorator design pattern with a lambda function.
 *  @date 2024-03-06
 *  @author Krzysztof Siminski
 *  */


#include <iostream>
#include <fstream>
#include <vector>

#define debug(x)   std::cout << "(" << __LINE__ << ") " << #x << " == " << x << std::endl;

int main()
{
   /** [PL] Prosta lambda dufileująca przekazaną wartość.
    *  [EN] A simple lambda doubling the passed value.
    * */
   auto two_times = [] (const int a) 
   {
      return 2 * a;
   };
 
   std::cout << two_times(4) << std::endl;

   /** [PL] Lambda zwraca to, co dostaje.
    *  [EN] The lambda returns what has got.
    * */
   auto decorator = [] (auto input)
   {
      return input;
   };
  
   /** [PL] Parametrem jest int.
    *  [EN] An int is a parameter.
    * */
   std::cout << decorator(4) << std::endl;
   
   /** [PL] Paramterem jest funkcja. Lambda zwraca funkcję, 
    *       której parametrem jest int.
    *  [EN] A function is a parameter. The lambda returns
    *       a function whose parameter is an int.
    * */
   std::cout << decorator(two_times)(4) << std::endl;
   
   /** [PL] Teraz lambda przyjmuje funkcję jako parametr.
    *       Przyjęta funkcja jest w ciele lambdy opakowywane
    *       i w ten sposób powstaje nowa lambda. Ta nowa
    *       lambda jest wzracana.
    *  [EN] Now the lambda takes a function as a parameter. 
    *       Then it wraps the taken function into a new lambda.
    *       Finally the new wrapped lambda is returned.
    *       This is the decorator design pattern.
    * */
   auto negation = [] (auto function)
   {
      auto lambda = [=] (auto param)
      {
         return - function (param);
      };
      return lambda;
   };
  
   std::cout << negation(two_times)(4) << std::endl;
   auto negation_2x = negation(two_times);
   std::cout << negation_2x(4) << std::endl;

   auto negation_negation_2x = negation(negation_2x);
   std::cout << negation_negation_2x(4) << std::endl;

   /** [PL] funkcja zwraca odwrotność.
    *  [EN] The function returns a reciprocal.
    * */
   auto l1 = [] (const auto n) 
   {
      return 1.0 / n;
   };

   /** [PL] Lambda opakowuje funkcję wypisująć tekst.
    *  [EN] A wrapper lambda that adds some printed text.
    * */
   auto decorator_print = [] (auto f)
   {
      auto l = [=] (const auto par)
      {
         std::cout << "++++++++++++" << std::endl;
         return f(par);
      };

      return l;
   };

   std::cout << "============" << std::endl;
   std::cout << l1(4) << std::endl;
   auto cout_l1 = decorator_print(l1);
   std::cout << cout_l1(4) << std::endl;
   std::cout << "============" << std::endl;

   auto square = [] (const auto l) { return l * l;};
   std::cout << "============" << std::endl;
   std::cout << square(4) << std::endl;
   auto cout_square = decorator_print(square);
   std::cout << cout_square(4) << std::endl;
   std::cout << "============" << std::endl;

   /** [PL] Jeszcze jeden przykład.
    *  [EN] One more example. 
    * */
   auto decorator_square = [] (auto f)
   {
      auto l = [=] (auto parametr)
      {
         return f(parametr) * f(parametr);
      };
      return l;
   };

   /** [PL] No i jeszcze jeden.
    *  [EN] And one more.
    * */
   auto decorator_shift = [] (auto f)
   {
      auto l = [=] (auto parametr)
      {
         return f(parametr) + 10;
      };
      return l;
   };

   auto decorator_recip = [] (auto f)
   {
      auto l = [=] (auto parametr)
      {
         return 1.0 / f(parametr);
      };
      return l;
   };

   auto identity = [] (auto p)
   {
      return p;
   };

   auto p {5};
   std::cout << "============" << std::endl;
   std::cout << identity(p) << std::endl;
   std::cout << decorator_square(identity)(p) << std::endl;
   std::cout << decorator_shift(decorator_square(identity))(p) << std::endl;
   std::cout << decorator_recip(decorator_shift(decorator_square(identity)))(p) << std::endl;
   std::cout << "============" << std::endl;
   std::cout << identity(p) << std::endl;
   std::cout << decorator_shift(identity)(p) << std::endl;
   std::cout << decorator_square(decorator_shift(identity))(p) << std::endl;
   std::cout << decorator_recip(decorator_square(decorator_shift(identity)))(p) << std::endl;
   auto rec_sq_sh_iden = decorator_recip(decorator_square(decorator_shift(identity)));
   std::cout << rec_sq_sh_iden(p) << std::endl;
   
   std::cout << "============" << std::endl;

   /** [PL] Lambda opakowuje funkcję i zapisuje wartość
    *       zwracaną przez funkcję do sosia.
    *  [EN] The lambda wraps the passed function and 
    *       logs the value returned by the function 
    *       into a stream. 
    * */
   std::ofstream file ("file.out");
   auto logger = [] (auto function, std::ostream & sos)
   {
      auto l = [&] (auto container, auto index)
      {
         auto result = function(container, index);
         sos << result << std::endl;
         return result;
      };
      return l;
   };

   auto get_item = [] (const auto & numbers, const std::size_t index)
   {
      return numbers[index];
   };

   std::vector numbers {10,11,12,13,14,15,16,17,18,19};

   for (const auto n : {4,5,3,7,8})
   {
      std::cout << get_item(numbers, n) << std::endl;
   }
   std::cout << "--" << std::endl;

   auto get_item_save =  logger(get_item, file);
   for (const auto n : {4,5,3,7,8})
   {
      std::cout << get_item_save(numbers, n) << std::endl;
   }

   std::cout << "============" << std::endl;
   auto trim = [] (auto f, auto mini, auto maxi)
   {
      auto l = [=] (auto container, auto index)
      {
         auto result = f(container, index);
         return std::min(std::max(result, mini), maxi);
      };

      return l;
   };

   auto get_item_trim_0_1   = trim(get_item,  0.0, 1.0);
   auto get_item_trim_m1_p1 = trim(get_item, -1.0, 1.0);

   std::vector values {-3.4, 0.4, 0.888, 2.9, 1.0002};

   for (std::size_t i = 0; i < values.size(); i++)
   {
      std::cout << get_item(values, i) << "\t" << get_item_trim_0_1(values, i) << "\t" << get_item_trim_m1_p1(values, i) << std::endl;
   }
   return 0;
}

