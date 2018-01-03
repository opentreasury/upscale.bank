// Copyright (c) 2011-2016 The UpscaleCoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "WalletFactory.h"

#include "NodeRpcProxy/NodeRpcProxy.h"
#include "Wallet/WalletGreen.h"
#include "UpscaleCoinCore/Currency.h"

#include <stdlib.h>
#include <future>

namespace PaymentService {

WalletFactory WalletFactory::factory;

WalletFactory::WalletFactory() {
}

WalletFactory::~WalletFactory() {
}

UpscaleCoin::IWallet* WalletFactory::createWallet(const UpscaleCoin::Currency& currency, UpscaleCoin::INode& node, System::Dispatcher& dispatcher) {
  UpscaleCoin::IWallet* wallet = new UpscaleCoin::WalletGreen(dispatcher, currency, node);
  return wallet;
}

}
