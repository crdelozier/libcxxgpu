
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __javax_naming_spi_DirObjectFactory__
#define __javax_naming_spi_DirObjectFactory__

#pragma interface

#include <java/lang/Object.h>
extern "Java"
{
  namespace javax
  {
    namespace naming
    {
        class Context;
        class Name;
      namespace directory
      {
          class Attributes;
      }
      namespace spi
      {
          class DirObjectFactory;
      }
    }
  }
}

class javax::naming::spi::DirObjectFactory : public ::java::lang::Object
{

public:
  virtual ::java::lang::Object * getObjectInstance(::java::lang::Object *, ::javax::naming::Name *, ::javax::naming::Context *, ::java::util::Hashtable *, ::javax::naming::directory::Attributes *) = 0;
  virtual ::java::lang::Object * getObjectInstance(::java::lang::Object *, ::javax::naming::Name *, ::javax::naming::Context *, ::java::util::Hashtable *) = 0;
  static ::java::lang::Class class$;
} __attribute__ ((java_interface));

#endif // __javax_naming_spi_DirObjectFactory__
