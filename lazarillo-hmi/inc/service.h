#ifndef LAZARILLO_HMI_INC_SERVICE_H
#define LAZARILLO_HMI_INC_SERVICE_H

#include "service-base/inc/service_base.h"

namespace lzr
{
namespace hmi
{
class Service : public utils::ServiceBase
{
public:
    Service(std::string const& p_name);

    std::string get_name() override;

    void init() override;

    void run() override;

    void finish() override;

private:
    std::string m_name{""};
};
}
}

#endif // LAZARILLO_HMI_INC_SERVICE_H
