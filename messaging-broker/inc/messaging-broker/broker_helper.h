#ifndef MESSAGING_BROKER_INC_BROKER_HELPER_H
#define MESSAGING_BROKER_INC_BROKER_HELPER_H

#include <hiredis/hiredis.h>
#include <memory>

namespace lzr
{
namespace msg
{
namespace helper
{
/**
 * Simple struct used for encapsulating a Redis context into a smart pointer.
 */
struct redisContextEncapsulate
{
    void operator()(redisContext *p_context);
};

using redisContext = std::unique_ptr<redisContext, redisContextEncapsulate>;
} // namespace helper
} // namespace msg
} // namespace lzr

#endif // MESSAGING_BROKER_INC_BROKER_HELPER_H
