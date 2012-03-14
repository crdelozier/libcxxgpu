
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __gnu_java_nio_DatagramChannelImpl__
#define __gnu_java_nio_DatagramChannelImpl__

#pragma interface

#include <java/nio/channels/DatagramChannel.h>
#include <gcj/array.h>

extern "Java"
{
  namespace gnu
  {
    namespace java
    {
      namespace nio
      {
          class DatagramChannelImpl;
          class NIODatagramSocket;
      }
    }
  }
  namespace java
  {
    namespace net
    {
        class DatagramSocket;
        class SocketAddress;
    }
    namespace nio
    {
        class ByteBuffer;
      namespace channels
      {
          class DatagramChannel;
        namespace spi
        {
            class SelectorProvider;
        }
      }
    }
  }
}

class gnu::java::nio::DatagramChannelImpl : public ::java::nio::channels::DatagramChannel
{

public:
  jboolean isInChannelOperation();
  void setInChannelOperation(jboolean);
public: // actually protected
  DatagramChannelImpl(::java::nio::channels::spi::SelectorProvider *);
public:
  jint getNativeFD();
  ::java::net::DatagramSocket * socket();
public: // actually protected
  void implCloseSelectableChannel();
  void implConfigureBlocking(jboolean);
public:
  ::java::nio::channels::DatagramChannel * connect(::java::net::SocketAddress *);
  ::java::nio::channels::DatagramChannel * disconnect();
  jboolean isConnected();
  jint write(::java::nio::ByteBuffer *);
  jlong write(JArray< ::java::nio::ByteBuffer * > *, jint, jint);
  jint read(::java::nio::ByteBuffer *);
  jlong read(JArray< ::java::nio::ByteBuffer * > *, jint, jint);
  ::java::net::SocketAddress * receive(::java::nio::ByteBuffer *);
  jint send(::java::nio::ByteBuffer *, ::java::net::SocketAddress *);
private:
  ::gnu::java::nio::NIODatagramSocket * __attribute__((aligned(__alignof__( ::java::nio::channels::DatagramChannel)))) socket__;
  jboolean inChannelOperation;
public:
  static ::java::lang::Class class$;
};

#endif // __gnu_java_nio_DatagramChannelImpl__