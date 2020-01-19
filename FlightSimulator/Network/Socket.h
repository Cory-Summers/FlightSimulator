#pragma once
/*
#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <memory>
#include <vector>
#include <array>
namespace Network {
  enum class SocketType : uint32_t { Blocking, NonBlocking};

  using AddrInfo = struct addrinfo;
  class Socket
  {
  public:
    Socket();
    virtual bool Initialize() = 0;
  protected:
    SOCKET m_socket;
  };
  class ServerSocket : public Socket 
  {
  public:
    ServerSocket(uint16_t const &, SocketType const &);
    void Accept();
    bool Initialize() override;
  protected:
    void GetAddress(AddrInfo **);
    void InitSocket(AddrInfo const &);
    void Listen();
    void Bind(AddrInfo &);
    uint16_t   m_port;
    SocketType m_type;
    std::array<SOCKET, 5> m_connections;
  };
}
*/

