#ifndef PERSON2_H
#define PERSON2_H
class Person2{
public:
 Person2()
 {
   dv= 50000;
   isKnown = false;
 }
   int ID;
   int peopleMet;
   Visitor *visitors;
   int dv;
   bool isKnown;
   bool operator<(const Person2 & rhs) const
   {
    return dv < rhs.dv;
   }

};

#endif
