
/** [PL] Przykład użycia std::any w C++ 
 *  [EN] Example of using std::any in C++
 *  @author Krzysztof Siminski
 *  */

#include <iostream>
#include <vector>
#include <string>
#include <any>

////////////////////////////////////
int main()
{
   std::cout << "std::any" << std::endl;

   std::cout << "===============" << std::endl;
   {
      std::any a = 42;  // int 
      std::cout << "a.type() == " << a.type().name() << std::endl;

      a = std::string("To be or not to be.");  // std::string
      std::cout << "a.type() == " << a.type().name() << std::endl;

      a = 3.14;  // double
      std::cout << "a.type() == " << a.type().name() << std::endl;

   }

   std::cout << "===============" << std::endl;
   {
      std::vector<std::any> v;
      v.push_back(42);
      v.push_back(std::string("To be or not to be."));
      v.push_back(3.14);

      for (const auto& a : v)
      {
         std::cout << "a.type() == " << a.type().name() << std::endl;
      }
   }

   std::cout << "===============" << std::endl;
   {
      std::vector<std::any> v;
      v.push_back(42);
      v.push_back(std::string("To be or not to be."));
      v.push_back(3.14);

      // [PL] odczyt przez wartość / referencję (gdy nie zgadza się typ, zgłasza wyjątek std::bad_any_cast)
      // [EN] read by value / reference (when the type does not match, it throws std::bad_any_cast exception)
      try
      {
         int i = std::any_cast<int>(v[0]);
         std::cout << "i == " << i << std::endl;

         std::string s = std::any_cast<std::string>(v[1]);
         std::cout << "s == " << s << std::endl;

         double d = std::any_cast<double>(v[2]);
         std::cout << "d == " << d << std::endl;
      }
      catch (const std::bad_any_cast& e)
      {
         std::cout << e.what() << std::endl;
      }

      std::cout << "---------------" << std::endl;

      try 
      {
         for (const auto& a : v)
         {
            int i = std::any_cast<int>(a);
            std::cout << "i == " << i << std::endl;
         }
      }
      catch (const std::bad_any_cast& e)
      {
         std::cout << e.what() << std::endl;
      }
   }

   std::cout << "===============" << std::endl;
   {
      std::vector<std::any> v;
      v.push_back(42);
      v.push_back(std::string("To be or not to be."));
      v.push_back(3.14);

      // [PL] odczyt przez stały wskaznik (gdy nie zgadza się typ, zwraca nullptr)
      // [EN] read by const pointer (when the type does not match, it returns nullptr 

      const int * pi = std::any_cast<int>(& v[0]);
      if (pi) 
         std::cout << "*pi == " << *pi << std::endl;

      const std::string * ps = std::any_cast<std::string>(& v[1]);
      if (ps)
         std::cout << "*ps == " << *ps << std::endl;

      const double * pd = std::any_cast<double>(& v[2]);
      if (pd)
         std::cout << "*pd == " << *pd << std::endl;

      std::cout << "---------------" << std::endl;

      for (const auto& a : v)
      {
         const int *pi = std::any_cast<int>(& a);
         if (pi)
            std::cout << "*pi == " << *pi << std::endl;
         else 
            std::cout << "pi == nullptr" << std::endl;
      }
   }

   return 0;
}

