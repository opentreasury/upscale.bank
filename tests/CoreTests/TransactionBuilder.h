// Copyright (c) 2011-2016 The UpscaleCoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include "UpscaleCoinCore/Account.h"
#include "UpscaleCoinCore/UpscaleCoinFormatUtils.h"
#include "UpscaleCoinCore/Currency.h"

class TransactionBuilder {
public:

  typedef std::vector<UpscaleCoin::AccountKeys> KeysVector;
  typedef std::vector<Crypto::Signature> SignatureVector;
  typedef std::vector<SignatureVector> SignatureMultivector;

  struct MultisignatureSource {
    UpscaleCoin::MultisignatureInput input;
    KeysVector keys;
    Crypto::PublicKey srcTxPubKey;
    size_t srcOutputIndex;
  };

  TransactionBuilder(const UpscaleCoin::Currency& currency, uint64_t unlockTime = 0);

  // regenerate transaction keys
  TransactionBuilder& newTxKeys();
  TransactionBuilder& setTxKeys(const UpscaleCoin::KeyPair& txKeys);

  // inputs
  TransactionBuilder& setInput(const std::vector<UpscaleCoin::TransactionSourceEntry>& sources, const UpscaleCoin::AccountKeys& senderKeys);
  TransactionBuilder& addMultisignatureInput(const MultisignatureSource& source);

  // outputs
  TransactionBuilder& setOutput(const std::vector<UpscaleCoin::TransactionDestinationEntry>& destinations);
  TransactionBuilder& addOutput(const UpscaleCoin::TransactionDestinationEntry& dest);
  TransactionBuilder& addMultisignatureOut(uint64_t amount, const KeysVector& keys, uint32_t required);

  UpscaleCoin::Transaction build() const;

  std::vector<UpscaleCoin::TransactionSourceEntry> m_sources;
  std::vector<UpscaleCoin::TransactionDestinationEntry> m_destinations;

private:

  void fillInputs(UpscaleCoin::Transaction& tx, std::vector<UpscaleCoin::KeyPair>& contexts) const;
  void fillOutputs(UpscaleCoin::Transaction& tx) const;
  void signSources(const Crypto::Hash& prefixHash, const std::vector<UpscaleCoin::KeyPair>& contexts, UpscaleCoin::Transaction& tx) const;

  struct MultisignatureDestination {
    uint64_t amount;
    uint32_t requiredSignatures;
    KeysVector keys;
  };

  UpscaleCoin::AccountKeys m_senderKeys;

  std::vector<MultisignatureSource> m_msigSources;
  std::vector<MultisignatureDestination> m_msigDestinations;

  size_t m_version;
  uint64_t m_unlockTime;
  UpscaleCoin::KeyPair m_txKey;
  const UpscaleCoin::Currency& m_currency;
};
