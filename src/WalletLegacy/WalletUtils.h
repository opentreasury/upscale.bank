// Copyright (c) 2011-2016 The UpscaleCoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <exception>
#include <iomanip>
#include <iostream>

#include "IWalletLegacy.h"
#include "Wallet/WalletErrors.h"

namespace UpscaleCoin {

inline void throwIf(bool expr, UpscaleCoin::error::WalletErrorCodes ec)
{
  if (expr)
    throw std::system_error(make_error_code(ec));
}

inline std::ostream& operator <<(std::ostream& ostr, const Crypto::Hash& hash) {
  std::ios_base::fmtflags flags = ostr.setf(std::ios_base::hex, std::ios_base::basefield);
  char fill = ostr.fill('0');

  for (auto b : hash.data) {
    ostr << std::setw(2) << static_cast<unsigned int>(b);
  }

  ostr.fill(fill);
  ostr.setf(flags);
  return ostr;
}

} //namespace UpscaleCoin
