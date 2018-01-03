// Copyright (c) 2011-2016 The UpscaleCoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "IUpscaleCoinProtocolQueryStub.h"

bool IUpscaleCoinProtocolQueryStub::addObserver(UpscaleCoin::IUpscaleCoinProtocolObserver* observer) {
  return false;
}

bool IUpscaleCoinProtocolQueryStub::removeObserver(UpscaleCoin::IUpscaleCoinProtocolObserver* observer) {
  return false;
}

uint32_t IUpscaleCoinProtocolQueryStub::getObservedHeight() const {
  return observedHeight;
}

size_t IUpscaleCoinProtocolQueryStub::getPeerCount() const {
  return peers;
}

bool IUpscaleCoinProtocolQueryStub::isSynchronized() const {
  return synchronized;
}

void IUpscaleCoinProtocolQueryStub::setPeerCount(uint32_t count) {
  peers = count;
}

void IUpscaleCoinProtocolQueryStub::setObservedHeight(uint32_t height) {
  observedHeight = height;
}

void IUpscaleCoinProtocolQueryStub::setSynchronizedStatus(bool status) {
    synchronized = status;
}
