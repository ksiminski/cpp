
/** [PL] Ten sam problem rozwiązany przez dziedziczenie i przez kompozycję. 
 *
 *       Dziedzieczenie:
 *       Głęboka hierarchia klas sprawia pewne problemy, np. przy wielu metodach
 *       trudno może być znaleźć, która implementacja metody jest wywoływana.
 *
 *       Kompozycja: 
 *       Zamiast implementować metody w klasach pochodnych, jest jedna klasa, która 
 *       jest zbudowana z obiektów implementujących odpowiednią wersję metody.
 *       W poniższych przykładzie zastosowane jest odwrócenie zależności
 *       i dostęp do składowych poprzez interfejsy. Zamiast dziedziczenia
 *       mamy kompozycję i realizację interfejsów. 
 *
 *  [EN] The same problem solved using inheritance and composition.
 *
 *       Inheritance:
 *       A deep class hierarchy causes certain issues; for example, with many methods,
 *       it can be difficult to find which implementation of a method is being called.
 *
 *       Composition:
 *       Instead of implementing methods in derived classes, there is a single class
 *       built from objects that implement the appropriate version of the method.
 *       The example below uses dependency inversion and accesses members
 *       through interfaces. Instead of inheritance, we have composition
 *       and interface implementation.
 *
 *  @author Krzysztof Siminski
 **/

#include <iostream>
#include <memory> 
#include <vector>
#include <string>

namespace inheritance
{
   class A
   {
      int _id; 
      public :
      A (const int id) : _id (id) 
      {} 

      int get_id () const
      {
         return _id; 
      }

      virtual std::string get_colour ()  const
      {
         return {"A::colour() Green"};
      }
      virtual std::string get_suit ()  const
      {
         return {"A::suit() Spades"};
      }
      virtual std::string get_piece ()  const
      {
         return {"A::piece() Rook"};
      }

      virtual void print ()  
      {
         std::cout << "[ " << get_id() << ", " << get_colour() << ", " << get_suit() << ", " << get_piece() << " ]" << std::endl;
      }
   };

   class B : public A
   {
      public :
         B (const int id) : A(id) 
      {}

         virtual std::string get_suit ()  const
         {
            return {"B::suit() Clubs"};
         }
   };

   class C : public B
   {
      public :
         C (const int id) : B(id) 
      {}
         virtual std::string get_piece ()  const
         {
            return {"C::piece() Pawn"};
         }
   };

   class D : public C
   {
      public :
         D (const int id) : C(id) 
      {}
         virtual std::string get_colour ()  const
         {
            return {"D::colour() Blue"};
         }
   };
}

namespace composition
{
   class IColour
   {
      public: 
         virtual std::string get_colour () const = 0; 
   };

   class Green : public IColour 
   {
      public :
         virtual std::string get_colour () const override 
         {
            return {"Green"};
         }
   };

   class Blue : public IColour 
   {
      public :
         virtual std::string get_colour () const override 
         {
            return {"Blue"};
         }
   };

   class ISuit
   {
      public:
         virtual std::string get_suit () const = 0;
   };

   class Spades : public ISuit 
   {
      public:
         virtual std::string get_suit () const override
         {
            return {"Spades"};
         }
   };


   class Clubs : public ISuit 
   {
      public:
         virtual std::string get_suit () const override
         {
            return {"Clubs"};
         }
   };

   class IPiece 
   {
      public :
         virtual std::string get_piece () const = 0;
   };

   class Rook : public IPiece 
   {
      public:
         virtual std::string get_piece () const override
         {
            return {"Rook"};
         }
   };

   class Pawn : public IPiece 
   {
      public:
         virtual std::string get_piece () const override
         {
            return {"Pawn"};
         }
   };

   class GameElement
   {
      std::unique_ptr<IColour> _pColour = nullptr;
      std::unique_ptr<ISuit>   _pSuit   = nullptr;
      std::unique_ptr<IPiece>  _pPiece  = nullptr;

      int _id; 
      public :
      GameElement (const int id, std::unique_ptr<IColour> _pC, std::unique_ptr<ISuit> _pS, std::unique_ptr<IPiece> _pP) 
      : _id(id), _pColour(std::move(_pC)), _pSuit(std::move(_pS)), _pPiece(std::move(_pP))
      {
      }

      std::string get_colour () const 
      {
         return _pColour ? _pColour->get_colour() : "" ;
      }

      std::string get_suit () const 
      {
         return _pSuit ? _pSuit->get_suit() : "";
      }

      std::string get_piece() const 
      {
         return _pPiece ? _pPiece->get_piece() : "";
      }

      void print () const 
      {
         if (_pColour and _pSuit and _pPiece)
            std::cout << "[ " << _id << ", " << get_colour() << ", " << get_suit() << ", " << get_piece() << " ]" << std::endl;

      }
   };
}

////////////////////////////////////
int main()
{
   std::cout << "===================" << std::endl; 
   {
      std::cout << "[PL] dziedziczenie | [EN] inheritance" << std::endl;
      {
         inheritance::C object(1);
         object.print();
      }
      std::cout << "-------------------" << std::endl;
      {
         int id = 1;
         std::vector<std::shared_ptr<inheritance::A>> objects { 
            std::make_shared<inheritance::A>(inheritance::A(++id)), 
            std::make_shared<inheritance::B>(inheritance::B(++id)), 
            std::make_shared<inheritance::C>(inheritance::C(++id)), 
            std::make_shared<inheritance::A>(inheritance::A(++id)), 
            std::make_shared<inheritance::D>(inheritance::D(++id)), 
            std::make_shared<inheritance::C>(inheritance::C(++id)), 
            std::make_shared<inheritance::B>(inheritance::B(++id))
         };

         for (const auto & p : objects)
         {
            p->print();
         }
      }
   }
   std::cout << "===================" << std::endl; 
   {
      std::cout << "[PL] kompozycja | [EN] composition" << std::endl;

      {
         composition::GameElement object(
            1,
            std::make_unique<composition::Green>(composition::Green()), 
            std::make_unique<composition::Clubs>(composition::Clubs()), 
            std::make_unique<composition::Pawn> (composition::Pawn())
            );

         object.print();

      }
      std::cout << "-------------------" << std::endl;
      {
         int id = 1;

         composition::Green g;
         composition::Blue  b;

         composition::Clubs  c;
         composition::Spades s;

         composition::Rook  r; 
         composition::Pawn  p; 

         std::vector<std::shared_ptr<composition::GameElement>> objects 
         { 
            std::make_shared<composition::GameElement>(
                  ++id,
                  std::make_unique<composition::Green>(g),
                  std::make_unique<composition::Spades>(s),
                  std::make_unique<composition::Rook>(r)
                  ), 
            std::make_shared<composition::GameElement>(
                  ++id,
                  std::make_unique<composition::Green>(g),
                  std::make_unique<composition::Clubs>(c),
                  std::make_unique<composition::Rook>(r)
                  ), 
            std::make_shared<composition::GameElement>(
                  ++id,
                  std::make_unique<composition::Green>(g),
                  std::make_unique<composition::Clubs>(c),
                  std::make_unique<composition::Pawn>(p)
                  ), 
            std::make_shared<composition::GameElement>(
                  ++id,
                  std::make_unique<composition::Green>(g),
                  std::make_unique<composition::Spades>(s),
                  std::make_unique<composition::Rook>(r)
                  ), 
            std::make_shared<composition::GameElement>(
                  ++id,
                  std::make_unique<composition::Blue>(b),
                  std::make_unique<composition::Clubs>(c),
                  std::make_unique<composition::Pawn>(p)
                  ), 
            std::make_shared<composition::GameElement>(
                  ++id,
                  std::make_unique<composition::Green>(g),
                  std::make_unique<composition::Clubs>(c),
                  std::make_unique<composition::Pawn>(p)
                  ), 
            std::make_shared<composition::GameElement>(
                  ++id,
                  std::make_unique<composition::Green>(g),
                  std::make_unique<composition::Clubs>(c),
                  std::make_unique<composition::Rook>(r)
                  ) 
         };

         for (const auto & p : objects)
         {
            p->print();
         }
      }
   }
   std::cout << "===================" << std::endl; 
   return 0;
}
////////////////////////////////////

