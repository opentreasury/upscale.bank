// Copyright (c) 2011-2016 The UpscaleCoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <vector>
#include <unordered_map>

#include "UpscaleCoinCore/Account.h"
#include "UpscaleCoinCore/UpscaleCoinBasic.h"
#include "UpscaleCoinCore/Currency.h"
#include "UpscaleCoinCore/BlockchainIndices.h"
#include "crypto/hash.h"

#include "../TestGenerator/TestGenerator.h"

class TestBlockchainGenerator
{
public:
  TestBlockchainGenerator(const UpscaleCoin::Currency& currency);

  //TODO: get rid of this method
  std::vector<UpscaleCoin::Block>& getBlockchain();
  std::vector<UpscaleCoin::Block> getBlockchainCopy();
  void generateEmptyBlocks(size_t count);
  bool getBlockRewardForAddress(const UpscaleCoin::AccountPublicAddress& address);
  bool generateTransactionsInOneBlock(const UpscaleCoin::AccountPublicAddress& address, size_t n);
  bool getSingleOutputTransaction(const UpscaleCoin::AccountPublicAddress& address, uint64_t amount);
  void addTxToBlockchain(const UpscaleCoin::Transaction& transaction);
  bool getTransactionByHash(const Crypto::Hash& hash, UpscaleCoin::Transaction& tx, bool checkTxPool = false);
  const UpscaleCoin::AccountBase& getMinerAccount() const;
  bool generateFromBaseTx(const UpscaleCoin::AccountBase& address);

  void putTxToPool(const UpscaleCoin::Transaction& tx);
  void getPoolSymmetricDifference(std::vector<Crypto::Hash>&& known_pool_tx_ids, Crypto::Hash known_block_id, bool& is_bc_actual,
    std::vector<UpscaleCoin::Transaction>& new_txs, std::vector<Crypto::Hash>& deleted_tx_ids);
  void putTxPoolToBlockchain();
  void clearTxPool();

  void cutBlockchain(uint32_t height);

  bool addOrphan(const Crypto::Hash& hash, uint32_t height);
  bool getGeneratedTransactionsNumber(uint32_t height, uint64_t& generatedTransactions);
  bool getOrphanBlockIdsByHeight(uint32_t height, std::vector<Crypto::Hash>& blockHashes);
  bool getBlockIdsByTimestamp(uint64_t timestampBegin, uint64_t timestampEnd, uint32_t blocksNumberLimit, std::vector<Crypto::Hash>& hashes, uint32_t& blocksNumberWithinTimestamps);
  bool getPoolTransactionIdsByTimestamp(uint64_t timestampBegin, uint64_t timestampEnd, uint32_t transactionsNumberLimit, std::vector<Crypto::Hash>& hashes, uint64_t& transactionsNumberWithinTimestamps);
  bool getTransactionIdsByPaymentId(const Crypto::Hash& paymentId, std::vector<Crypto::Hash>& transactionHashes);

  bool getTransactionGlobalIndexesByHash(const Crypto::Hash& transactionHash, std::vector<uint32_t>& globalIndexes);
  bool getMultisignatureOutputByGlobalIndex(uint64_t amount, uint32_t globalIndex, UpscaleCoin::MultisignatureOutput& out);
  void setMinerAccount(const UpscaleCoin::AccountBase& account);

private:
  struct MultisignatureOutEntry {
    Crypto::Hash transactionHash;
    uint16_t indexOut;
  };

  struct KeyOutEntry {
    Crypto::Hash transactionHash;
    uint16_t indexOut;
  };
  
  void addGenesisBlock();
  void addMiningBlock();

  const UpscaleCoin::Currency& m_currency;
  test_generator generator;
  UpscaleCoin::AccountBase miner_acc;
  std::vector<UpscaleCoin::Block> m_blockchain;
  std::unordered_map<Crypto::Hash, UpscaleCoin::Transaction> m_txs;
  std::unordered_map<Crypto::Hash, std::vector<uint32_t>> transactionGlobalOuts;
  std::unordered_map<uint64_t, std::vector<MultisignatureOutEntry>> multisignatureOutsIndex;
  std::unordered_map<uint64_t, std::vector<KeyOutEntry>> keyOutsIndex;

  std::unordered_map<Crypto::Hash, UpscaleCoin::Transaction> m_txPool;
  mutable std::mutex m_mutex;

  UpscaleCoin::PaymentIdIndex m_paymentIdIndex;
  UpscaleCoin::TimestampTransactionsIndex m_timestampIndex;
  UpscaleCoin::GeneratedTransactionsIndex m_generatedTransactionsIndex;
  UpscaleCoin::OrphanBlocksIndex m_orthanBlocksIndex;

  void addToBlockchain(const UpscaleCoin::Transaction& tx);
  void addToBlockchain(const std::vector<UpscaleCoin::Transaction>& txs);
  void addToBlockchain(const std::vector<UpscaleCoin::Transaction>& txs, const UpscaleCoin::AccountBase& minerAddress);
  void addTx(const UpscaleCoin::Transaction& tx);

  bool doGenerateTransactionsInOneBlock(UpscaleCoin::AccountPublicAddress const &address, size_t n);
};
