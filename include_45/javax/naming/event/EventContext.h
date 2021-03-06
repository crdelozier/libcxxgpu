
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __javax_naming_event_EventContext__
#define __javax_naming_event_EventContext__

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
        class NameParser;
        class NamingEnumeration;
      namespace event
      {
          class EventContext;
          class NamingListener;
      }
    }
  }
}

class javax::naming::event::EventContext : public ::java::lang::Object
{

public:
  virtual void addNamingListener(::javax::naming::Name *, jint, ::javax::naming::event::NamingListener *) = 0;
  virtual void addNamingListener(::java::lang::String *, jint, ::javax::naming::event::NamingListener *) = 0;
  virtual void removeNamingListener(::javax::naming::event::NamingListener *) = 0;
  virtual jboolean targetMustExist() = 0;
  virtual void bind(::javax::naming::Name *, ::java::lang::Object *) = 0;
  virtual void bind(::java::lang::String *, ::java::lang::Object *) = 0;
  virtual ::java::lang::Object * lookup(::javax::naming::Name *) = 0;
  virtual ::java::lang::Object * lookup(::java::lang::String *) = 0;
  virtual void rebind(::javax::naming::Name *, ::java::lang::Object *) = 0;
  virtual void rebind(::java::lang::String *, ::java::lang::Object *) = 0;
  virtual void unbind(::javax::naming::Name *) = 0;
  virtual void unbind(::java::lang::String *) = 0;
  virtual void rename(::javax::naming::Name *, ::javax::naming::Name *) = 0;
  virtual void rename(::java::lang::String *, ::java::lang::String *) = 0;
  virtual ::javax::naming::NamingEnumeration * list(::javax::naming::Name *) = 0;
  virtual ::javax::naming::NamingEnumeration * list(::java::lang::String *) = 0;
  virtual ::javax::naming::NamingEnumeration * listBindings(::javax::naming::Name *) = 0;
  virtual ::javax::naming::NamingEnumeration * listBindings(::java::lang::String *) = 0;
  virtual ::javax::naming::Context * createSubcontext(::javax::naming::Name *) = 0;
  virtual ::javax::naming::Context * createSubcontext(::java::lang::String *) = 0;
  virtual void destroySubcontext(::javax::naming::Name *) = 0;
  virtual void destroySubcontext(::java::lang::String *) = 0;
  virtual ::java::lang::Object * lookupLink(::javax::naming::Name *) = 0;
  virtual ::java::lang::Object * lookupLink(::java::lang::String *) = 0;
  virtual ::javax::naming::NameParser * getNameParser(::javax::naming::Name *) = 0;
  virtual ::javax::naming::NameParser * getNameParser(::java::lang::String *) = 0;
  virtual ::javax::naming::Name * composeName(::javax::naming::Name *, ::javax::naming::Name *) = 0;
  virtual ::java::lang::String * composeName(::java::lang::String *, ::java::lang::String *) = 0;
  virtual ::java::lang::Object * addToEnvironment(::java::lang::String *, ::java::lang::Object *) = 0;
  virtual ::java::lang::Object * removeFromEnvironment(::java::lang::String *) = 0;
  virtual ::java::util::Hashtable * getEnvironment() = 0;
  virtual void close() = 0;
  virtual ::java::lang::String * getNameInNamespace() = 0;
  static const jint OBJECT_SCOPE = 0;
  static const jint ONELEVEL_SCOPE = 1;
  static const jint SUBTREE_SCOPE = 2;
  static ::java::lang::Class class$;
} __attribute__ ((java_interface));

#endif // __javax_naming_event_EventContext__
