// Copyright (c) 2011-2016 The UpscaleCoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "WalletLegacySerialization.h"
#include "WalletLegacy/WalletUnconfirmedTransactions.h"
#include "IWalletLegacy.h"

#include "UpscaleCoinCore/UpscaleCoinSerialization.h"
#include "Serialization/ISerializer.h"
#include "Serialization/SerializationOverloads.h"

namespace UpscaleCoin {

void serialize(UnconfirmedTransferDetails& utd, UpscaleCoin::ISerializer& serializer) {
  serializer(utd.tx, "transaction");
  serializer(utd.amount, "amount");
  serializer(utd.outsAmount, "outs_amount");
  uint64_t time = static_cast<uint64_t>(utd.sentTime);
  serializer(time, "sent_time");
  utd.sentTime = static_cast<time_t>(time);
  uint64_t txId = static_cast<uint64_t>(utd.transactionId);
  serializer(txId, "transaction_id");
  utd.transactionId = static_cast<size_t>(txId);
}

void serialize(WalletLegacyTransaction& txi, UpscaleCoin::ISerializer& serializer) {
  uint64_t trId = static_cast<uint64_t>(txi.firstTransferId);
  serializer(trId, "first_transfer_id");
  txi.firstTransferId = static_cast<size_t>(trId);

  uint64_t trCount = static_cast<uint64_t>(txi.transferCount);
  serializer(trCount, "transfer_count");
  txi.transferCount = static_cast<size_t>(trCount);

  serializer(txi.totalAmount, "total_amount");

  serializer(txi.fee, "fee");
  serializer(txi.hash, "hash");
  serializer(txi.isCoinbase, "is_coinbase");

  UpscaleCoin::serializeBlockHeight(serializer, txi.blockHeight, "block_height");

  serializer(txi.timestamp, "timestamp");
  serializer(txi.unlockTime, "unlock_time");
  serializer(txi.extra, "extra");

  //this field has been added later in the structure.
  //in order to not break backward binary compatibility
  // we just set it to zero
  txi.sentTime = 0;
}

void serialize(WalletLegacyTransfer& tr, UpscaleCoin::ISerializer& serializer) {
  serializer(tr.address, "address");
  serializer(tr.amount, "amount");
}

} //namespace UpscaleCoin
