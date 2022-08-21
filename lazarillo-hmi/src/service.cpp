#include "lazarillo-hmi/service.h"

using lzr::hmi::Service;

Service::Service(std::string const& p_name)
    : m_name{p_name}
{}
