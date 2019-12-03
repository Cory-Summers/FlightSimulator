#include "Socket.h"
/*
Network::ServerSocket::ServerSocket(uint16_t const & port, SocketType const & type) :
  m_port(port),
  m_type(type)
{
  Initialize();

}

void Network::ServerSocket::Accept()
{
  SOCKET client = INVALID_SOCKET;
  client = accept(m_socket, (sockaddr*)NULL, NULL);
  if (client == INVALID_SOCKET)
  {
    closesocket(m_socket);
    WSACleanup();
    throw "Bad Accept";
  }
  m_connections[m_connections.size()] = client;
}

bool Network::ServerSocket::Initialize()
{

  AddrInfo * address = nullptr;
  GetAddress(&address);
  InitSocket(*address);
  Bind(*address);
}

void Network::ServerSocket::GetAddress(AddrInfo ** address)
{
  int result    = 0;
  AddrInfo* ptr = NULL;
  AddrInfo  hints;
  std::fill(&hints, &hints + sizeof(hints), 0);
  hints.ai_family   = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_flags    = AI_PASSIVE;
  result = getaddrinfo(NULL, std::to_string(m_port).c_str(), &hints, (PADDRINFOA *)*address);
  if (result != 0) 
  {
    WSACleanup();
    throw "getaddrinfo";
  }
}

void Network::ServerSocket::InitSocket(AddrInfo const & address)
{
  m_socket = socket(address.ai_family, address.ai_socktype, address.ai_protocol);
  if (m_socket == INVALID_SOCKET) 
  {
    WSACleanup();
    throw "listen connect";
  }
}

void Network::ServerSocket::Listen()
{
  if (listen(m_socket, SOMAXCONN) == SOCKET_ERROR)
  {
    closesocket(m_socket);
    WSACleanup();
    throw "Failure upon listen";
  }
}

void Network::ServerSocket::Bind(Network::AddrInfo & address)
{
  int result = 0;
  result = bind(m_socket, address.ai_addr, (int)address.ai_addrlen);
  if (result == SOCKET_ERROR) 
  {
    freeaddrinfo(&address);
    closesocket(m_socket);
    WSACleanup();
    throw "Binding Failure";
  }
  freeaddrinfo(&address);
}
*/