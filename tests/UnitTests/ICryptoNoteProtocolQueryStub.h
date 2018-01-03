// Copyright (c) 2011-2016 The UpscaleCoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <cstdint>

#include "UpscaleCoinProtocol/IUpscaleCoinProtocolObserver.h"
#include "UpscaleCoinProtocol/IUpscaleCoinProtocolQuery.h"

class IUpscaleCoinProtocolQueryStub: public UpscaleCoin::IUpscaleCoinProtocolQuery {
public:
  IUpscaleCoinProtocolQueryStub() : peers(0), observedHeight(0), synchronized(false) {}

  virtual bool addObserver(UpscaleCoin::IUpscaleCoinProtocolObserver* observer) override;
  virtual bool removeObserver(UpscaleCoin::IUpscaleCoinProtocolObserver* observer) override;
  virtual uint32_t getObservedHeight() const override;
  virtual size_t getPeerCount() const override;
  virtual bool isSynchronized() const override;

  void setPeerCount(uint32_t count);
  void setObservedHeight(uint32_t height);

  void setSynchronizedStatus(bool status);

private:
  size_t peers;
  uint32_t observedHeight;

  bool synchronized;
};
