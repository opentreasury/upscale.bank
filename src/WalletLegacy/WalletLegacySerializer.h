// Copyright (c) 2011-2016 The UpscaleCoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <vector>
#include <ostream>
#include <istream>

#include "crypto/hash.h"
#include "crypto/chacha8.h"

namespace UpscaleCoin {
class AccountBase;
class ISerializer;
}

namespace UpscaleCoin {

class WalletUserTransactionsCache;

class WalletLegacySerializer {
public:
  WalletLegacySerializer(UpscaleCoin::AccountBase& account, WalletUserTransactionsCache& transactionsCache);

  void serialize(std::ostream& stream, const std::string& password, bool saveDetailed, const std::string& cache);
  void deserialize(std::istream& stream, const std::string& password, std::string& cache);

private:
  void saveKeys(UpscaleCoin::ISerializer& serializer);
  void loadKeys(UpscaleCoin::ISerializer& serializer);

  Crypto::chacha8_iv encrypt(const std::string& plain, const std::string& password, std::string& cipher);
  void decrypt(const std::string& cipher, std::string& plain, Crypto::chacha8_iv iv, const std::string& password);

  UpscaleCoin::AccountBase& account;
  WalletUserTransactionsCache& transactionsCache;
  const uint32_t walletSerializationVersion;
};

} //namespace UpscaleCoin
