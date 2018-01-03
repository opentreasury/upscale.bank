// Copyright (c) 2011-2016 The UpscaleCoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once 

#include "Chaingen.h"

#include "UpscaleCoinCore/Currency.h"
#include "TransactionBuilder.h"
#include <Logging/LoggerGroup.h>

class TestGenerator {
public:
  TestGenerator(
    const UpscaleCoin::Currency& currency,
    std::vector<test_event_entry>& eventsRef) :
      generator(currency),
      events(eventsRef) {
    minerAccount.generate();
    generator.constructBlock(genesisBlock, minerAccount, 1338224400);
    events.push_back(genesisBlock);
    lastBlock = genesisBlock;
  }

  const UpscaleCoin::Currency& currency() const { return generator.currency(); }

  void makeNextBlock(const std::list<UpscaleCoin::Transaction>& txs = std::list<UpscaleCoin::Transaction>()) {
    UpscaleCoin::Block block;
    generator.constructBlock(block, lastBlock, minerAccount, txs);
    events.push_back(block);
    lastBlock = block;
  }

  void makeNextBlock(const UpscaleCoin::Transaction& tx) {
    std::list<UpscaleCoin::Transaction> txs;
    txs.push_back(tx);
    makeNextBlock(txs);
  }

  void generateBlocks() {
    generateBlocks(currency().minedMoneyUnlockWindow());
  }

  void generateBlocks(size_t count, uint8_t majorVersion = UpscaleCoin::BLOCK_MAJOR_VERSION_1) {
    while (count--) {
      UpscaleCoin::Block next;
      generator.constructBlockManually(next, lastBlock, minerAccount, test_generator::bf_major_ver, majorVersion);
      lastBlock = next;
      events.push_back(next);
    }
  }

  TransactionBuilder createTxBuilder(const UpscaleCoin::AccountBase& from, const UpscaleCoin::AccountBase& to, uint64_t amount, uint64_t fee) {

    std::vector<UpscaleCoin::TransactionSourceEntry> sources;
    std::vector<UpscaleCoin::TransactionDestinationEntry> destinations;

    fillTxSourcesAndDestinations(sources, destinations, from, to, amount, fee);

    TransactionBuilder builder(generator.currency());

    builder.setInput(sources, from.getAccountKeys());
    builder.setOutput(destinations);

    return builder;
  }

  void fillTxSourcesAndDestinations(
    std::vector<UpscaleCoin::TransactionSourceEntry>& sources,
    std::vector<UpscaleCoin::TransactionDestinationEntry>& destinations,
    const UpscaleCoin::AccountBase& from, const UpscaleCoin::AccountBase& to, uint64_t amount, uint64_t fee, size_t nmix = 0) {
    fill_tx_sources_and_destinations(events, lastBlock, from, to, amount, fee, nmix, sources, destinations);
  }

  void constructTxToKey(
    UpscaleCoin::Transaction& tx,
    const UpscaleCoin::AccountBase& from,
    const UpscaleCoin::AccountBase& to,
    uint64_t amount,
    uint64_t fee,
    size_t nmix = 0) {
    construct_tx_to_key(logger, events, tx, lastBlock, from, to, amount, fee, nmix);
  }

  void addEvent(const test_event_entry& e) {
    events.push_back(e);
  }

  void addCallback(const std::string& name) {
    callback_entry cb;
    cb.callback_name = name;
    events.push_back(cb);
  }

  void addCheckAccepted() {
    addCallback("check_block_accepted");
  }

  void addCheckPurged() {
    addCallback("check_block_purged");
  }

  Logging::LoggerGroup logger;
  test_generator generator;
  UpscaleCoin::Block genesisBlock;
  UpscaleCoin::Block lastBlock;
  UpscaleCoin::AccountBase minerAccount;
  std::vector<test_event_entry>& events;
};
