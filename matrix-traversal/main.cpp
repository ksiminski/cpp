//////////////////////////////////////////////////////////
//  
// [PL] Porównanie czasu zsumowania elementów macierzy
//      przy przechodzeniu wierszami i kolumnami.
// [EN] Comparision of element summing with
//      row-wise and column-wise matrix traversal.
//
//////////////////////////////////////////////////////////


#include <iostream>
#include <vector>

#include "clock.h"

#define debug(x)   std::cerr << __FILE__ << " (" << __LINE__ << ") " << #x << " == " << x << std::endl


int main ()
{
   std::size_t W {1'000'000};  // liczba wierszy | number of rows
   std::size_t K {1'000};      // liczba kolumn  | number of columns
   
   // macierz | matrix
   const std::vector<std::vector<int>> matrix(W, std::vector<int>(K, 1.0));
   
   ksi::clock stoper;
   {
      // przechodzenie wierszami | row-wise traversal
      int sum = 0;
      stoper.start();
      for (std::size_t w = 0; w < W; w++)
      {
         for (std::size_t k = 0; k < K; k++)
         {
            sum += matrix[w][k]; 
         }
      }
      stoper.stop();
      std::cout << "sum: " << sum << std::endl;
      auto time = stoper.elapsed_milliseconds();
      std::cout << "przechodzenie wierszami | row-wise traversal:    t = " << time << " ms" <<  std::endl;
   }

   {
      // przechodzenie kolumnami | column-wise traversal
      int sum = 0;
      stoper.start();
      for (std::size_t k = 0; k < K; k++)
      {
         for (std::size_t w = 0; w < W; w++)
         {
            sum += matrix[w][k]; 
         }
      }
      stoper.stop();
      auto time = stoper.elapsed_milliseconds();
      std::cout << "sum: " << sum << std::endl;
      std::cout << "przechodzenie kolumnami | column-wise traversal: t = " << time << " ms" <<  std::endl;
   }
   return 0;
}
