// Copyright 2016 Chirstopher Torres (Raven), L3nn0x
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http ://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef __CCHARCLIENT_H__
#define __CCHARCLIENT_H__

#include "croseclient.h"

namespace RoseCommon {
class CliJoinServerReq;
class CliCreateCharReq;
class CliDeleteCharReq;
class CliSelectCharReq;
}

class CCharClient : public RoseCommon::CRoseClient {
 public:
  CCharClient();
  CCharClient(std::unique_ptr<Core::INetwork> _sock);

  bool is_nearby(const CRoseClient* _otherClient) const override { (void)_otherClient; return true; }

  uint32_t sessionId() const { return sessionId_; }

 protected:
  virtual bool HandlePacket(uint8_t* _buffer) override;

  bool JoinServerReply(std::unique_ptr<RoseCommon::CliJoinServerReq> P);
  bool SendCharListReply();
  bool SendCharCreateReply(std::unique_ptr<RoseCommon::CliCreateCharReq> P);
  bool SendCharDeleteReply(std::unique_ptr<RoseCommon::CliDeleteCharReq> P);
  bool SendCharSelectReply(std::unique_ptr<RoseCommon::CliSelectCharReq> P);

  virtual void OnDisconnected() override;

 protected:
  void updateSession();

  enum class eSTATE {
    DEFAULT,
    LOGGEDIN,
    TRANSFERING,
  };

  uint16_t accessRights_;
  eSTATE loginState_;
  uint32_t sessionId_;
  uint32_t userId_;
  uint32_t channelId_;

  std::vector<uint32_t> characterRealId_;
};

#endif
