#ifndef LAZARILLO_HMI_INC_SERVICE_H
#define LAZARILLO_HMI_INC_SERVICE_H

#include "service-base/service_base.h"

namespace lzr
{
namespace hmi
{
class Service : public utils::ServiceBase
{
public:
    Service(std::string const& p_name);

    void init() override;

    void run() override;

    void finish() override;
};
}
}

#endif // LAZARILLO_HMI_INC_SERVICE_H
