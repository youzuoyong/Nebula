/*******************************************************************************
 * Project:  Nebula
 * @file     HttpStep.hpp
 * @brief    Http服务的异步步骤基类
 * @author   Bwar
 * @date:    2016年8月13日
 * @note
 * Modify history:
 ******************************************************************************/
#ifndef SRC_ACTOR_STEP_HTTPSTEP_HPP_
#define SRC_ACTOR_STEP_HTTPSTEP_HPP_

#include <actor/step/Step.hpp>
#include "util/http/http_parser.h"

namespace neb
{

class HttpStep: public Step
{
public:
    HttpStep(std::shared_ptr<Step> pNextStep = NULL, ev_tstamp dTimeout = gc_dDefaultTimeout);
    HttpStep(std::shared_ptr<SocketChannel> pUpstreamChannel, std::shared_ptr<Step> pNextStep = nullptr, ev_tstamp dTimeout = gc_dDefaultTimeout);
    HttpStep(const HttpStep&) = delete;
    HttpStep& operator=(const HttpStep&) = delete;
    virtual ~HttpStep();

    virtual E_CMD_STATUS Callback(
                    std::shared_ptr<SocketChannel> pUpstreamChannel,
                    const HttpMsg& oHttpMsg,
                    void* data = NULL) = 0;

    bool HttpPost(const std::string& strUrl, const std::string& strBody, const std::map<std::string, std::string>& mapHeaders);
    bool HttpGet(const std::string& strUrl);

protected:
    bool HttpRequest(const HttpMsg& oHttpMsg);

    std::shared_ptr<SocketChannel> m_pUpstreamChannel;
};

} /* namespace neb */

#endif /* SRC_ACTOR_STEP_HTTPSTEP_HPP_ */
