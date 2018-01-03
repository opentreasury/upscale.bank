// Copyright (c) 2011-2016 The UpscaleCoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "WalletUtils.h"

#include "UpscaleCoin.h"

namespace UpscaleCoin {

bool validateAddress(const std::string& address, const UpscaleCoin::Currency& currency) {
  UpscaleCoin::AccountPublicAddress ignore;
  return currency.parseAccountAddressString(address, ignore);
}

}
