
/////////////////////////
// [PL] Przykład haszowania.
// [EN] Example of hashing.
/////////////////////////

#include <iostream>
#include <iomanip>
#include <fstream>
#include <boost/container_hash/hash.hpp>

/////////////////////////

// MurMur3 hash
// https://github.com/aappleby/smhasher/blob/master/src/MurmurHash3.cpp
std::size_t hash_mm(std::size_t x) 
{
   x ^= x >> 33;
   x *= 0xff51afd7ed558ccdLL;
   x ^= x >> 33;
   x *= 0xc4ceb9fe1a85ec53LL;
   x ^= x >> 33;

   return x;
}

std::size_t hash_boost (std::size_t x)
{
   static boost::hash<std::size_t> hasher;
   return hasher(x);
}

std::size_t hash_std (std::size_t x)
{
   static std::hash<std::size_t> hasher;
   return hasher(x);
}

std::size_t hash_boost (char x)
{
   static boost::hash<char> hasher;
   return hasher(x);
}

std::size_t hash_std (char x)
{
   static std::hash<char> hasher;
   return hasher(x);
}


std::size_t hash_boost (double x)
{
   static boost::hash<double> hasher;
   return hasher(x);
}

std::size_t hash_std (double x)
{
   static std::hash<double> hasher;
   return hasher(x);
}

std::size_t hash_boost (const std::string & s)
{
   static boost::hash<std::string> hasher;
   return hasher(s);
}

std::size_t hash_std (const std::string & s)
{
   static std::hash<std::string> hasher;
   return hasher(s);
}

/////////////////////////
int main ()
{
   const int WIDTH { 24 };

   // [PL] hasz liczb naturalnych 
   // [EN] hash of natural numbers

   {
      std::cout 
         << std::setw(WIDTH) << "std" 
         << std::setw(WIDTH) << "boost" 
         << std::setw(WIDTH) << "murmur3" 
         << "   "            << "n" 
         << std::endl;

      for (std::size_t i = 0; i < 100; ++i)
      {
         std::cout 
            << std::setw(WIDTH) << hash_std (i) 
            << std::setw(WIDTH) << hash_boost (i) 
            << std::setw(WIDTH) << hash_mm (i) 
            << "   "            << i 
            << std::endl;
      }
   }
   std::cout << std::endl;
   std::cout << "--------------------------------" << std::endl;
   std::cout << std::endl;

   // [PL] hasz liczb rzeczywistych 
   // [EN] hash of real numbers

   {
      std::cout 
         << std::setw(WIDTH) << "std" 
         << std::setw(WIDTH) << "boost" 
         << "   "            << "n" 
         << std::endl;

      for (double x = 0.0; x < 1.1; x += 0.1)
      {
         std::cout 
            << std::setw(WIDTH) << hash_std (x) 
            << std::setw(WIDTH) << hash_boost (x) 
            << "   "            << x 
            << std::endl;
      }
   }
   std::cout << std::endl;
   std::cout << "--------------------------------" << std::endl;
   std::cout << std::endl;

   // [PL] hasz znakow 
   // [EN] character hash 

   {
      std::cout 
         << std::setw(WIDTH) << "std" 
         << std::setw(WIDTH) << "boost" 
         << "   "            << "c" 
         << std::endl;

      for (char c = 'a'; c < 'z' + 1 ; ++c)
      {
         std::cout 
            << std::setw(WIDTH) << hash_std(c) 
            << std::setw(WIDTH) << hash_boost(c) 
            << "   "            << c 
            << std::endl;
      }
   }
   std::cout << std::endl;
   std::cout << "--------------------------------" << std::endl;
   std::cout << std::endl;

   // [PL] hasz liter jako napisow 
   // [EN] character as string hash 

   {
      std::cout 
         << std::setw(WIDTH) << "std" 
         << std::setw(WIDTH) << "boost" 
         << "   "            << "str" 
         << std::endl;

      std::string text {"a"};
      for (char c = 'a'; c < 'z' + 1 ; ++c)
      {
         std::cout 
            << std::setw(WIDTH) << hash_std(text) 
            << std::setw(WIDTH) << hash_boost(text) 
            << "   "            << text 
            << std::endl;

         text[0]++;
      }
   }
   std::cout << std::endl;
   std::cout << "--------------------------------" << std::endl;
   std::cout << std::endl;

   // [PL] hasz napisow 
   // [EN] string hash 
   {
      std::cout 
         << std::setw(WIDTH) << "std" 
         << std::setw(WIDTH) << "boost" 
         << "   "            << "str" 
         << std::endl;

      std::string text {};
      for (int i = 0; i < 30; ++i)
      {
         std::cout 
            << std::setw(WIDTH) << hash_std(text) 
            << std::setw(WIDTH) << hash_boost(text) 
            << "   "            << text 
            << std::endl;

         text.append("a");
      }
   }
   std::cout << std::endl;
   std::cout << "--------------------------------" << std::endl;
   std::cout << std::endl;

   // [PL] hasz napisow bedacych liniami tego pliku
   // [EN] string hash for lines of this file

   {
      std::cout 
         << std::setw(WIDTH) << "std" 
         << std::setw(WIDTH) << "boost" 
         << "   "            << "str" 
         << std::endl;

      const std::string file_name {"main.cpp"};
      std::ifstream file (file_name);
      std::string line;
      while (std::getline(file, line))
      {
         std::cout 
            << std::setw(WIDTH) << hash_std(line) 
            << std::setw(WIDTH) << hash_boost(line) 
            << "   "            << line 
            << std::endl;
      }
   }
   return 0;
}

