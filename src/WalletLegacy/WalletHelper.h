// Copyright (c) 2011-2016 The UpscaleCoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <future>
#include <map>
#include <mutex>

#include "crypto/hash.h"
#include "IWalletLegacy.h"

namespace UpscaleCoin {
namespace WalletHelper {

class SaveWalletResultObserver : public UpscaleCoin::IWalletLegacyObserver {
public:
  std::promise<std::error_code> saveResult;
  virtual void saveCompleted(std::error_code result) override { saveResult.set_value(result); }
};

class InitWalletResultObserver : public UpscaleCoin::IWalletLegacyObserver {
public:
  std::promise<std::error_code> initResult;
  virtual void initCompleted(std::error_code result) override { initResult.set_value(result); }
};

class SendCompleteResultObserver : public UpscaleCoin::IWalletLegacyObserver {
public:
  virtual void sendTransactionCompleted(UpscaleCoin::TransactionId transactionId, std::error_code result) override;
  std::error_code wait(UpscaleCoin::TransactionId transactionId);

private:
  std::mutex m_mutex;
  std::condition_variable m_condition;
  std::map<UpscaleCoin::TransactionId, std::error_code> m_finishedTransactions;
  std::error_code m_result;
};

class IWalletRemoveObserverGuard {
public:
  IWalletRemoveObserverGuard(UpscaleCoin::IWalletLegacy& wallet, UpscaleCoin::IWalletLegacyObserver& observer);
  ~IWalletRemoveObserverGuard();

  void removeObserver();

private:
  UpscaleCoin::IWalletLegacy& m_wallet;
  UpscaleCoin::IWalletLegacyObserver& m_observer;
  bool m_removed;
};

void prepareFileNames(const std::string& file_path, std::string& keys_file, std::string& wallet_file);
void storeWallet(UpscaleCoin::IWalletLegacy& wallet, const std::string& walletFilename);

}
}
