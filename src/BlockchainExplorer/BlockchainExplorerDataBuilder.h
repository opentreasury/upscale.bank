// Copyright (c) 2011-2016 The UpscaleCoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <vector>
#include <array>

#include "UpscaleCoinProtocol/IUpscaleCoinProtocolQuery.h"
#include "UpscaleCoinCore/ICore.h"
#include "BlockchainExplorerData.h"

namespace UpscaleCoin {

class BlockchainExplorerDataBuilder
{
public:
  BlockchainExplorerDataBuilder(UpscaleCoin::ICore& core, UpscaleCoin::IUpscaleCoinProtocolQuery& protocol);

  BlockchainExplorerDataBuilder(const BlockchainExplorerDataBuilder&) = delete;
  BlockchainExplorerDataBuilder(BlockchainExplorerDataBuilder&&) = delete;

  BlockchainExplorerDataBuilder& operator=(const BlockchainExplorerDataBuilder&) = delete;
  BlockchainExplorerDataBuilder& operator=(BlockchainExplorerDataBuilder&&) = delete;

  bool fillBlockDetails(const Block& block, BlockDetails& blockDetails);
  bool fillTransactionDetails(const Transaction &tx, TransactionDetails& txRpcInfo, uint64_t timestamp = 0);

  static bool getPaymentId(const Transaction& transaction, Crypto::Hash& paymentId);

private:
  bool getMixin(const Transaction& transaction, uint64_t& mixin);
  bool fillTxExtra(const std::vector<uint8_t>& rawExtra, TransactionExtraDetails& extraDetails);
  size_t median(std::vector<size_t>& v);

  UpscaleCoin::ICore& core;
  UpscaleCoin::IUpscaleCoinProtocolQuery& protocol;
};
}
