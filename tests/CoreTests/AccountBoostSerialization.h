// Copyright (c) 2011-2016 The UpscaleCoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include "UpscaleCoinCore/Account.h"
#include "UpscaleCoinBoostSerialization.h"

//namespace UpscaleCoin {
namespace boost
{
  namespace serialization
  {
    template <class Archive>
    inline void serialize(Archive &a, UpscaleCoin::AccountKeys &x, const boost::serialization::version_type ver)
    {
      a & x.address;
      a & x.spendSecretKey;
      a & x.viewSecretKey;
    }

    template <class Archive>
    inline void serialize(Archive &a, UpscaleCoin::AccountPublicAddress &x, const boost::serialization::version_type ver)
    {
      a & x.spendPublicKey;
      a & x.viewPublicKey;
    }

  }
}
