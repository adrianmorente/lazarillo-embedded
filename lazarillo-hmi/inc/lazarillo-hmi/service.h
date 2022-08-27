#ifndef LAZARILLO_HMI_INC_SERVICE_H
#define LAZARILLO_HMI_INC_SERVICE_H

#include "service-base/service_base.h"

#include <QGuiApplication>

namespace lzr
{
namespace hmi
{
class Service : public lzr::service::ServiceBase
{
public:
    Service(int argc, char *argv[]);

    ~Service();

    std::string get_name() override;

    void init() override;

    int run_internal() override;

    void finish() override;

private:
    //
    QGuiApplication *m_app;
};
} // namespace hmi
} // namespace lzr

#endif // LAZARILLO_HMI_INC_SERVICE_H
