
#include <generator>
#include <iostream>

/////////////////////////
// [PL] przykład korutyny z użyciem std::generator  
// [EN] example of a coroutine with std::generator
/////////////////////////


// [PL] generator 
// [EN] generator  
std::generator<int> count_down(int start) 
{
   while (start > 0) 
   {
      co_yield start; // [PL] Zwraca wartość i zawiesza funkcję. 
                      // [EN] Returns a value and suspends the function.
      start--;
   }
}

int main() 
{

   // [PL] Wywołanie generatora i iteracja po jego wartościach. 
   // [EN] Calling the generator and iterating over its values.
   for (int value : count_down(5)) 
   {
      std::cout << value << std::endl; // [PL] Wypisuje wartości od 5 do 1. 
                                       // [EN] Prints values from 5 to 1.
   }

   return 0; 
}

