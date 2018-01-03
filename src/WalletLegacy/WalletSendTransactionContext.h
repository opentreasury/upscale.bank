// Copyright (c) 2011-2016 The UpscaleCoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <list>
#include <vector>

#include "UpscaleCoinCore/UpscaleCoinBasic.h"
#include "IWalletLegacy.h"
#include "ITransfersContainer.h"

namespace UpscaleCoin {

struct TxDustPolicy
{
  uint64_t dustThreshold;
  bool addToFee;
  UpscaleCoin::AccountPublicAddress addrForDust;

  TxDustPolicy(uint64_t a_dust_threshold = 0, bool an_add_to_fee = true, UpscaleCoin::AccountPublicAddress an_addr_for_dust = UpscaleCoin::AccountPublicAddress())
    : dustThreshold(a_dust_threshold), addToFee(an_add_to_fee), addrForDust(an_addr_for_dust) {}
};

struct SendTransactionContext
{
  TransactionId transactionId;
  std::vector<UpscaleCoin::COMMAND_RPC_GET_RANDOM_OUTPUTS_FOR_AMOUNTS::outs_for_amount> outs;
  uint64_t foundMoney;
  std::list<TransactionOutputInformation> selectedTransfers;
  TxDustPolicy dustPolicy;
  uint64_t mixIn;
};

} //namespace UpscaleCoin
