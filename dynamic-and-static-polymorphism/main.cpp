/* [PL] 
 * Polimorfizm dynamiczny i statyczny
 * 2024-02-23
 *
 * Polimorfizm dynamiczny:
 *    - opiera sie na dziedziczeniu,
 *    - korzysta z metod wirtualnych.
 *    
 * Polimorfizm statyczny
 *    - opiera sie na szablonach,
 *    - korzysta z obiektow funkcyjnych.
 *
 * @author Krzystof Siminski
 *
 * [EN] 
 * Dynamic and static polimorphism
 * 2024-02-23
 *
 * Dynamic polymorfism:
 *    - based on inheritance,
 *    - applies virtual methods.
 *
 * Static polymorfism:
 *    - based on templates,
 *    - applies function objects
 *
 * @author Krzystof Siminski
 * */


#include <iostream>

#define debug(x)   std::cerr << __FILE__ << " (" << __LINE__ << ") " << #x << " == " << x << std::endl; 


/////////////////////////////////////////////
// [PL] polimorfizm dynamiczny
// [EN] dynamic polymorphism

/** [PL] Klasa abstrakcyjna przeprowadzajaca operacje na dwoch liczbach. 
 *  [EN] Abstract class running an operation on two numbers.
 * */
class d_operation 
{
   public: 
      void run ()
      {
         double l = 4.56;
         double p = 5.62;
         std::cout << execute (l, p) << std::endl;
      }

   protected:
      /** [PL] operacja na dwoch liczbach 
       *  [EN] operation on two numbers*/
      virtual double execute (const double l, const double p) = 0;
};

/** [PL] Klasa implementujaca metode execute jako minimum. 
 *  [EN] Class implements the execute method as minimum. */
class d_min : public d_operation
{
   protected:
      virtual double execute (const double l, const double p) override
      {
         return std::min (l, p);
      }
};

/** [PL] Klasa implementujaca metode execute jako maksimum. 
 *  [EN] Class implements the execute method as maximum. */
class d_max : public d_operation
{
   protected:
      virtual double execute (const double l, const double p) override
      {
         return std::max (l, p);
      }
};

////////////////////////////////////////////
// [PL] polimorfizm statyczny
// [EN] static polymorphism

/** [PL] Klasa implementujaca operator () jako minimum.
 *  [EN] The class implements operator () as a minimum. */
struct st_min 
{
   double operator() (const double l, const double p)
   {
      return std::min(l, p);
   }
};

/** [PL] Klasa implementujaca operator () jako maksimum.
 *  [EN] The class implements operator () as a maximum. */
struct st_max 
{
   double operator() (const double l, const double p)
   {
      return std::max(l, p);
   }
};

template <typename A>
class st_operation
{
   public:
      A execute; // [PL] obiekt funkcyjny | [EN] function object

   public: 
      void run ()
      {
         double l = 4.56;
         double p = 5.62;
         std::cout << execute (l, p) << std::endl;
      }
};
/////////////////////////////////////////////

int main ()
{
   {
      std::cout << "[PL] polimorfizm dynamiczny" << std::endl;
      std::cout << "[EN] dynamic polymorphism" << std::endl;

      std::cout << "min: "; 
      d_min minimalizator;
      minimalizator.run();

      std::cout << "max: "; 
      d_max maksymalizator;
      maksymalizator.run();
   }
   std::cout << "---------------" << std::endl;
   {
      std::cout << "[PL] polimorfizm statyczny" << std::endl;
      std::cout << "[EN] static polymorphism" << std::endl;
      
      std::cout << "min: "; 
      st_operation<st_min> minimalizator;
      minimalizator.run();

      std::cout << "max: "; 
      st_operation<st_max> maksymalizator;
      maksymalizator.run();
   }

   return 0;
}
