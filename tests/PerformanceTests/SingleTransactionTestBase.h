// Copyright (c) 2011-2016 The UpscaleCoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include "UpscaleCoinCore/Account.h"
#include "UpscaleCoinCore/UpscaleCoinBasic.h"
#include "UpscaleCoinCore/UpscaleCoinFormatUtils.h"

#include <Logging/LoggerGroup.h>

class single_tx_test_base
{
public:
  bool init()
  {
    using namespace UpscaleCoin;

    Currency currency = CurrencyBuilder(m_nullLog).currency();
    m_bob.generate();

    if (!currency.constructMinerTx(0, 0, 0, 2, 0, m_bob.getAccountKeys().address, m_tx))
      return false;

    m_tx_pub_key = getTransactionPublicKeyFromExtra(m_tx.extra);
    return true;
  }

protected:

  Logging::LoggerGroup m_nullLog;
  UpscaleCoin::AccountBase m_bob;
  UpscaleCoin::Transaction m_tx;
  Crypto::PublicKey m_tx_pub_key;
};
